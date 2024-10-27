// =========================================================================================================================================
//                                                 Rotating Display RD56m
//                                                    © Ludwin Monz
// License: Creative Commons Attribution - Non-Commercial - Share Alike (CC BY-NC-SA)
// you may use, adapt, share. If you share, "share alike".
// you may not use this software for commercial purposes 
// =========================================================================================================================================



// ******************************************************************************************************************************************
//
//          this class provides methods for saving and loading data to and from the SPIFFS (SPI Flash File System)
//          
// ******************************************************************************************************************************************


#ifndef ffs_H
#define ffs_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <SD.h>
#include "SPI.h"

class FlashFS {
  private:
  
    String _path;
    bool _isDirectory();                                    // returns true, if path is a directory
    bool _mkdir(String path);                               // make directory. path shall end with "/"

  
    File * _file = nullptr;                                 // holds pointer to file, when opened


  public:
    FlashFS(String _path);                                  // Constructor. path is either file or folder
    bool begin();                                           // initiates the file system. Returns false if initiation failed
    void write_f(String text);                              // write String to file.
    void write_f(uint8_t* data, size_t len);                // write len bytes of binary data[] to file
    String read_f();                                        // read String from file.

    bool exists();

    File* open_f(String mode);                              // open file
    bool close_f();                                         // close file


    String listFilesInJson();                               // list all files in the root directory in JSON format

    bool rename_f(String newPath);                          // rename file or directory
    bool delete_f();                                        // delete a file


    bool copy_f(String destPath);                           // copy file or folder (including content)


    bool move_f(String destPath);                           // move file or folder (including content)

    bool copyFirstImage(String destFileName);               // copy first image of a RDC file into separate RDC file

    bool read_f(uint8_t (*bitmap)[165], int x, int y, int frame);           //
    
};

#endif
