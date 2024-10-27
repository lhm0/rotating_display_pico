// =========================================================================================================================================
//                                                 Rotating Display RD56m
//                                                    © Ludwin Monz
// License: Creative Commons Attribution - Non-Commercial - Share Alike (CC BY-NC-SA)
// you may use, adapt, share. If you share, "share alike".
// you may not use this software for commercial purposes 
// =========================================================================================================================================


#include "FlashFS.h"
#include <Arduino.h>
#include <SD.h>
#include <SPI.h>

#define PIN_SD_MOSI       19
#define PIN_SD_MISO       16
#define PIN_SD_SCK        18
#define PIN_SD_SS         17

// Constructor

FlashFS::FlashFS(String path) {
  this->_path = path;
  if (_isDirectory()) {
      _mkdir(_path);              // creat path, if it does not exist yet
    }
}

// Initialization routine

bool FlashFS::begin() {

  bool initok = SD.begin(PIN_SD_SS, SPI_FULL_SPEED);       
  if (!(initok))  {
    Serial.println("Card Mount Failed"); // check, if card o.k.
  }
  else {
      uint8_t cardType = SD.type();

      switch (cardType) {
        case 0:
        Serial.println("SD1");
        break;
      case 1:
        Serial.println("SD2");
        break;
      case 3:
        Serial.println("SDHC/SDXC");
        break;
      default:
        Serial.println("Unknown");
      }

    uint64_t volumesize = SD.totalClusters();
    volumesize *= SD.clusterSize();

    Serial.printf("SD Volume Size: %lluMB\n", volumesize/1000000);

  }
  return initok;
}

// Routine zum Lesen einer Datei
String FlashFS::read_f() {
  File file = SD.open(_path.c_str(), FILE_READ);
  if (!file) {
    Serial.println(_path + ": Failed to open file for reading");
    return "";
  }
  String text = file.readString();  
  file.close();
  return text;
}

// Routine zum Schreiben einer Datei
void FlashFS::write_f(String text) {
  if (SD.exists(_path.c_str())) SD.remove(_path);   // replace existing file with new one

  File file = SD.open(_path.c_str(), FILE_WRITE);

  if (!file) {
    Serial.println(_path + "Failed to open file for writing");
    return;
  }
  file.print(text);
  file.flush();
  file.close();
}

void FlashFS::write_f(uint8_t* data, size_t len) {
  File file = SD.open(_path.c_str(), FILE_WRITE);
  if (!file) {
    Serial.println(_path + "Failed to open file for writing");
    return;
  }
  file.write(data, len);
  file.flush();
  file.close();
}

File* FlashFS::open_f(String mode) {

  if (_isDirectory()) {
    return nullptr; // return null pointer to indicate error
  }
  if (mode=="r") _file = new File(SD.open(_path.c_str(), FILE_READ));
  if (mode=="w") _file = new File(SD.open(_path.c_str(), FILE_WRITE));
  if ((mode!="r")&&(mode!="w")) _file = nullptr;
  return _file;
}

bool FlashFS::close_f() {
  if (_file) {
    _file->close();
    delete _file;
    _file = nullptr;
    return true; // successful close
  }
  return false; // file not open
}

/////////////////////////////////////////////////////////
// the following functions manipulate files and directories.
// path formate:
// - folders end with "/"
// - the root folder is "/"
// - files have an extension ".xxx"
// 
// examples
// /variables/ssid.txt
// /variables/
// 
// in order to use the functions, a source object needs to be created:
// FlashFS mysource{"/variables/ssid.txt"}
// then, the function with its target path needs to be called:
// mysource.rename_f("/variables/new_ssid.txt")
// mysource.move_f("/ssid.txt")
// mysource.copy_f("/ssid.txt")
//
// This syntax also works for folders:
// FlashFS mysource{"/variables/test/"}
// mysource.rename_f("/variables/new_test/")
// mysource.move_f("/test/")
// mysource.copy_f("/test/")
/////////////////////////////////////////////////////////

bool FlashFS::_isDirectory() {
    return _path.indexOf('.') == -1;
}

bool FlashFS::_mkdir(String path) {
  Serial.println("_mkdir - path: " + path);

  if (path=="/") return true;
  if (path.endsWith("/")) {                   // check if path ends with "/"
    path.remove(path.length()-1);             // remove the last character
  }
  if (!SD.exists(path.c_str())) {             // check if directory already exists
    bool success = SD.mkdir(path.c_str());    // make directory, if it does not exist, yet
      if (!success) {
        Serial.println(path + ": Failed to create directory");
      }
    return success;
  } else {
    return true;
  }
}

String FlashFS::listFilesInJson() {
  JsonDocument doc;
  JsonArray array = doc.to<JsonArray>();

  File root = SD.open(_path.c_str());
  if(!root){ 
    Serial.println(_path+": Error opening directory");
    return "";
  }
  if(!root.isDirectory()){
    Serial.println(_path+": Not a directory");
    return "";
  }

  File file = root.openNextFile();
  while(file){
    String fileName = file.name();
    if ((fileName[0] != '.')&&(fileName !="System Volume Information")) {
      array.add(fileName);
    }
    file = root.openNextFile();
  }

  String jsonString;
  serializeJson(doc, jsonString);

  return jsonString;
}


bool FlashFS::rename_f(String newPath) {
  Serial.println("rename_f - _path: " + _path);
  Serial.println("rename_f - newPath: " + newPath);

  bool success; 

  success = SD.rename(_path.c_str(), newPath.c_str());

  if (success) {
    _path = newPath;
  }
  return success;
}

bool FlashFS::delete_f() {
  Serial.println("delete_f - _path: " + _path);

  if (_isDirectory()) {
    // remove all files and subdirectories recursively, before deleting the directory
    File root = SD.open(_path.c_str());
    if (!root) {
      return false;
    }
    
    File file = root.openNextFile();
    while(file){
      String fileName = file.name();
      String filePath = _path + "/" + fileName;
      if (file.isDirectory()) {
        // delete subdirectory
        FlashFS* subDir = new FlashFS(filePath);
        subDir -> delete_f();
        delete subDir;
      } else {
        if (!SD.remove(filePath.c_str())) {
          return false;
        }
      }
      file = root.openNextFile();    
    }
    // now directory is empty. remove the directory
    return SD.rmdir(_path.c_str());
  } else {
    // delete a single file
    return SD.remove(_path.c_str());
  }
}

bool FlashFS::copy_f(String destPath) {
  Serial.println("copy_f - _path: " + _path);
  Serial.println("copy_f - destPath: " + destPath);

  String sourcePath = _path;
  if (_isDirectory()) {
    // create destination directory if it doesn't exist
    _mkdir(destPath);
    // copy all files and subdirectories recursively
    File root = SD.open(_path.c_str());
    File file = root.openNextFile();
    while(file) {
      String sourceFileName = file.name();
      String sourceFilePath = sourcePath + "/" + sourceFileName;

      if (file.isDirectory()) {
        String subDirDestPath = destPath + "/" + sourceFileName;
        FlashFS* subDir = new FlashFS(sourceFilePath);
        subDir -> copy_f(subDirDestPath);
        delete subDir;
      } else {
        String destFilePath = destPath + "/" + sourceFileName;
        File* srcFile = new File(SD.open(sourceFilePath.c_str(), FILE_READ));
        File* destFile = new File(SD.open(destFilePath.c_str(), FILE_WRITE));
        if (!srcFile || !destFile) {
          return false; // copy failed
        }
        while (srcFile->available()) {
          destFile->write(srcFile->read());
          destFile->flush();
        }
        srcFile->close();
        destFile->close();
        delete srcFile;
        delete destFile;
      }

      file = root.openNextFile();    
    }
    return true;
  } else {
    // determine destination path:
    // extract file name from sourcePath
    String fileName = "";
    int lastSlashIndex = sourcePath.lastIndexOf("/");
    if (lastSlashIndex >= 0) {
      fileName = sourcePath.substring(lastSlashIndex + 1);
    }
    destPath = destPath + "/" + fileName;

    Serial.println("copy_f: sourcePath = "+sourcePath+" destPath = "+destPath);

    if (!SD.exists(destPath)) {
      File srcFile = SD.open(sourcePath.c_str(), FILE_READ);
      File destFile = SD.open(destPath.c_str(), FILE_WRITE);
      if (!srcFile || !destFile) {
        Serial.println("error opening the file.");
        return false; 
      }

      size_t n;  
      uint8_t buf[64];
      while ((n = srcFile.read(buf, sizeof(buf))) > 0) {
        destFile.write(buf, n);
      }

      srcFile.close();
      destFile.close();
    }
    else {
      Serial.println("copy_f: \"" + destPath + "\" already exists");
    }

    return true;
  }
}

bool FlashFS::move_f(String destPath) {
  Serial.println("move_f - _path: " + _path);
  Serial.println("move_f - destPath: " + destPath);

  if (copy_f(destPath)) {
    delete_f();
    _path = destPath;
    return true;
  } else {
    return false; // move failed
  }
}


bool FlashFS::exists() {
  Serial.println("exists(): "+_path);
  return !SD.exists(_path);
}

// read the data into bitmap array. lower left hand corner is x, y
bool FlashFS::read_f(uint8_t (*bitmap)[165], int x, int y, int frame) {

  File file = SD.open(_path.c_str());
  uint8_t buffer[165];
  bool success = true;
  unsigned int xd, yd, noOfFrames;

  if (!file) {
    Serial.println("Failed to open file for reading");
    success = false;
    return success;
  } 

  if (file.read((uint8_t*)&xd, sizeof(xd)) != sizeof(xd)) {
    Serial.println("Failed to read xd from file");
    success = false;
    return success;
  }

  if (file.read((uint8_t*)&yd, sizeof(yd)) != sizeof(yd)) {
    Serial.println("Failed to read yd from file");
    success = false;
    return success;
  }

  if (file.read((uint8_t*)&noOfFrames, sizeof(noOfFrames)) != sizeof(noOfFrames)) {
    Serial.println("Failed to read noOfFrames from file");
    success = false;
    return success;
  }

  int ymax = yd*3/2;
  if ((yd*3%2)!=0) ymax++;

  unsigned long offset = 12 + frame * xd * ymax;
  file.seek(offset);   //go to start position of frame
//  Serial.printf("Frame: %d  Offset: %d\n", frame, offset);

  y = (y*3/2)/2*2;            // make y an even number
  if ((y+ymax)>=165) ymax = 165 - y-1;


  for (int xs=x; ((xs<xd+x) && (xs<110)); xs++) {
    int bytesRead = file.read(buffer, (yd*3/2));       // read bytes of one column
    memcpy(&bitmap[xs][y], buffer, ymax);
  }
      
  file.close();
  return success;
}


// read RDC file, generate new destFile, which contains first image of the source
bool FlashFS::copyFirstImage(String destFileName) {

  byte* buffer = new byte[18165];
  int bytesRead;
  bool success = true;
  unsigned int xd, yd, noOfFrames;

  File file = SD.open(_path.c_str());
  
  if (!file) {
    Serial.println("Failed to open sourceFile for reading");
    success = false;
    return success;
  } 

  if (file.read((uint8_t*)&xd, sizeof(xd)) != sizeof(xd)) {
    Serial.println("Failed to read xd from file");
    success = false;
    return success;
  }

  if (file.read((uint8_t*)&yd, sizeof(yd)) != sizeof(yd)) {
    Serial.println("Failed to read yd from file");
    success = false;
    return success;
  }

  if (file.read((uint8_t*)&noOfFrames, sizeof(noOfFrames)) != sizeof(noOfFrames)) {
    Serial.println("Failed to read noOfFrames from file");
    success = false;
    return success;
  }

  int ymax = yd*3/2;
  if ((yd*3%2)!=0) ymax++;

  int bytesFirstImage = 12 + xd * ymax;
  Serial.print("generate first image RDC. bytesFirstImage: ");
  Serial.println(bytesFirstImage);
  file.seek(0);   //go to beginning of file
  bytesRead = file.read(buffer, bytesFirstImage);       // read first image
      
  file.close();

  SD.remove(destFileName.c_str());                      // delete temp file, if it already exists
  File destFile = SD.open(destFileName.c_str(), FILE_WRITE);
  if (!destFile) {
    Serial.println("Failed to open destFile for writing");
    success = false;
    return success;
  } 
  destFile.write(buffer, bytesRead);
  destFile.close();

  delete[] buffer;

  return success;
}  
