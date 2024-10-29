# Rotating Display Pico

## Abstract: 
The Rotating Display Pico is a compact disc-sized device that rotates quietly using a CD motor. It features 56 white LEDs which are controlled by a raspberry pi pico. The device can display animated images as well as time and weather data sourced from the internet. It is wirelessly powered and controlled via a user-friendly web interface. The device uses off-the-shelf components and is easy to assemble in a DIY electronics project.
 
<p align="center"> 
  <img src="images/figure00.jpeg" style="display: inline-block; margin: 0px; max-width: 600px">
</p>

<p align="center"> 
<a href="https://youtu.be/Msv1gF6FXeg" target="_blank">
  <img src="images/yt1.jpeg" style="display: inline-block; margin: 0px; max-width: 600px">
</a>
</p> 

## 1. Description of the device

The Rotating Display pico device comprises two primary units: a power supply unit and a display board (**figure 1**). Both are circular in design, with a diameter of 120mm, similar to the dimensions of a standard Compact Disk. The display board is rotated by a CD motor. Energy is wirelessly transmitted from the power supply unit to the display board, eliminating the need for wired connections.

<p align="center"> 
  <img src="images/figure01.jpeg" style="display: inline-block; margin: 0px; max-width: 600px">
</p>

**Figure 1:  Rotating Display pico assembly.** The lower PCB is the power supply with wireless power transmission, the upper PCB is the display board.

The display board is equipped with a row containing 56 white LEDs. The LED operations are controlled by a Raspberry Pi Pico W, which at the same time generates the display content, maintains a Wi-Fi connection to the internet, and provides a web user interface. Images (including animated images) can be stored on and loaded from a micro SMD card. 

This internet connection allows the device to retrieve the time from a time server, ensuring time accuracy. It also allows for the acquisition of weather data. Device operation is managed through a web interface (**figure 2**), accessible from any web browser. The interface allows users to manage login credentials, upload image files to the display, and control image and configuration files through a file manager.

<p align="center"> 
  <img src="images/figure02a.jpeg" style="display: inline-block; margin: 3px; max-width: 180px">
  <img src="images/figure02b.jpeg" style="display: inline-block; margin: 3px; max-width: 180px">
  <img src="images/figure02c.jpeg" style="display: inline-block; margin: 3px; max-width: 180px">
</p>
<p align="center"> 
  <img src="images/figure02d.jpeg" style="display: inline-block; margin: 3px; max-width: 180px">
  <img src="images/figure02e.jpeg" style="display: inline-block; margin: 3px; max-width: 180px">
  <img src="images/figure02f.jpeg" style="display: inline-block; margin: 3px; max-width: 180px">
</p>


**Figure 2:** The **web user interface** allows for operating mode selection and device configuration.

## 2. Operating modes

When switched on, the device tries to connect to a known wifi. If no valid wifi credentials are found, the unit will be configured as wifi access point. In this mode, a computer or mobile device can be connected, directly (SSID: RD56m, no password). 

Once the wifi connection has been established, the unit will display its IP address on the  home page of the device (**figure 3**). Enter this address in your web browser. This will load the web user interface and will allow you to configure your local wifi.

<p align="center"> 
  <img src="images/figure03.jpeg" style="display: inline-block; margin: 0px; max-width: 600px">
</p>

**Figure 3: home page.**

There are several operating modes that display time and weather information (**figure 4**). The logo clock mode integrates a customizable image into the clock face. The image can be easily uploaded from the user interface. The same is true for the analog clock, which uses a customizable clock face in the background.

<p align="center"> 
  <img src="images/figure04a.jpeg" style="display: inline-block; margin: 3px; max-width: 290px">
  <img src="images/figure04b.jpeg" style="display: inline-block; margin: 3px; max-width: 290px">
</p>
<p align="center"> 
  <img src="images/figure04c.jpeg" style="display: inline-block; margin: 3px; max-width: 290px">
  <img src="images/figure04d.jpeg" style="display: inline-block; margin: 3px; max-width: 290px">
</p>
<p align="center"> 
  <img src="images/figure04e.jpeg" style="display: inline-block; margin: 3px; max-width: 290px">
  <img src="images/figure04f.jpeg" style="display: inline-block; margin: 3px; max-width: 290px">
</p>


**Figure 4: operating modes.** Modes can be selected and configured through the web interface.

## 3. Mechanical design

The device consists of two assemblies: power supply and display. The power supply board is also the base plate, which can either be placed on a flat surface or hung on a wall. A standard CD motor is attached to this board so that the CD tray above the power supply board can accommodate the display assembly. The display board is fixed with two M2 x 6 mm screws. Furthermore, the base plate carries a potentiometer to control the motor speed as well as an on/off switch for the motor.

<p align="center"> 
  <img src="images/figure05a.jpeg" style="display: inline-block; margin: 3px; max-width: 290px">
  <img src="images/figure05b.jpeg" style="display: inline-block; margin: 3px; max-width: 290px">
</p>

**Figure 5: Power Supply Board** with CD motor (middle), 12 V power jack (lower side), and speed potentiometer

An important requirement for the display board is that the center of mass of the unit is exactly in the middle, on the axis of rotation of the motor. This is the only way to ensure smooth and vibration-free running of the display. To achieve this, the electronic components are arranged symmetrically to the vertical axis of symmetry (**figure 7**). This initially ensures that the center of gravity lies on this vertical axis. However, since the components cannot be distributed symmetrically to the horizontal axis of symmetry, the center of gravity must be shifted to the center along this axis using balancing weights. For this purpose, two M3x6mm screws with two nuts each are placed to the right and left of the micro SD card slot. The overall balancing result is very good, but can certainly be further optimized.

<p align="center"> 
  <img src="images/figure06a.jpeg" style="display: inline-block; margin: 3px; max-width: 290px">
  <img src="images/figure06b.jpeg" style="display: inline-block; margin: 3px; max-width: 290px">
</p>

**Figure 6: Display Board.** Main components are the LED row, the Raspberry Pi Pico W microcontroller, and two driver chips for the LEDs. On the backside of the board the secondary coil of the wireless power supply is attached.

<p align="center"> 
  <img src="images/figure07.jpeg" style="display: inline-block; margin: 20px; max-width: 600px">
</p>

**Figure 7:** The components of the display board are arranged symmetrically to the vertical axis of symmetry. Balancing weights are used to shift the center of gravity to the middle of the disk.

The LED row consists of 56 discrete, rectangular LEDs. The components each have a width of 2.0 mm and can be lined up with little spacing. However, the row of LEDs is not arranged symmetrically to the center of the disk, but shifted by 0.5 mm. If the display panel is rotated by 180 degrees, this decentration causes the LEDs to be shifted by exactly 1 mm from the original grid (**figure 8**). This results in rotational interlacing: the radial resolution is increased from 2 to 1 mm. At the same time, the perceived frame rate also increases by a factor of 2..

<p align="center"> 
  <img src="images/figure08.jpeg" style="display: inline-block; margin: 20px; max-width: 600px">
</p>

**Figure 8:** The LED row is shifted radially by half a LED width. The two halfs of the row generate an interlacing effect, which doubles both the radial resolution and the image frame rate.

The LEDs must output the image information at exactly the right position with each rotation. For spatial alignment of the image, a trigger signal is generated at a defined position for each rotation, which triggers the sequential, clocked output of the pixels. The trigger signal must be spatially very stable, otherwise no smooth image can be generated. It turned out that a Hall sensor is best suited for this purpose. It is located on the left-hand side of the disk at the 10:30 clock position (see **figure 6**, left picture). The magnet is glued into a hole of the power supply PCB (see figure 5, left picture, 2 o'clock position).

## 4. Electronics architecture

The distribution of the electronic circuitry between the two assemblies is shown in **figure 9**. The power supply assembly contains a Royer converter for wireless power transfer to the display assembly and an adjustment of the motor speed. The 56 LEDs of the display assembly are arranged in a matrix and are multiplexed by the microcontroller. The displayed content is either loaded from the internet via Wifi (time, weather data) or generated from image data locally, which is stored on a micro SD card.

<p align="center"> 
  <img src="images/figure09.jpeg" style="display: inline-block; margin: 20px; max-width: 600px">
</p>

## 5. Power supply board

The core of the power supply is a Royer converter for wireless power transfer. An excellent article on the operation and design of the circuit can be found at [Mikrocontroller.net](https://www.mikrocontroller.net/articles/Royer_Converter) (German) and the circuit was taken from there. Two transistors are alternately switched (push pull operation) so that a current flows through one half of the coil at a time. The coil belongs to a resonant circuit with a resonant frequency of about 120 kHz. The control voltage for the transistors is obtained via a coupling coil (**figure 10**). The secondary coil is located below the display board (see **figure 6**, right).

The Royer circuit uses very few components. However, the coil is quite complex. It is a bifilar coil, where the two halves are interleaved. In addition, the coupling coil must be connected with the correct polarity, otherwise the two transistors will be destroyed. In the early stages of development, the coil was wound with copper wire. However, this solution was quite difficult to reproduce, so in the final design the coils (bifilar primary coil, coupling coil, secondary coil) were implemented as a printed circuit (see **figure 5**, left and **figure 6** right). The circuit was found to have surprisingly high and perfectly adequate transmission efficiency, although the quality factor of the printed coils is inevitably compromised. The Royer converter with the printed coil assembly is absolutely safe to rebuild. It is supplied with 12 V. 

<p align="center"> 
  <img src="images/figure10.jpeg" style="display: inline-block; margin: 20px; max-width: 600px">
</p>

**Figure 10: Royer converter**. Compare [Mikrocontroller.net](https://www.mikrocontroller.net/articles/Royer_Converter) for reference.


There is also a circuit for supplying the CD motor on the power supply board. By means of an adjustable voltage regulator, a variable voltage between 1.7V and 6.0V is generated. It can be adjusted via a potentiometer. The voltage range corresponds to the specified operating range of the CD motor. The supply of the motor can be interrupted with a switch, for example to allow programming of the microcontrollers.

## 6. Display Board
The 56 LEDs of the display are arranged in a matrix with 7 columns and 8 rows (**figure 11**). The microcontroller activates the columns successively and sets the rows for each columns as needed.

The columns are activated by connecting them to +5V by means of a p-channel MOSFET, each. The control of the MOSFETs needs 5V logic (+5V = off, 0V = on), while the Raspberry pi pico operates with 3.3V logic. Therefore, levels need to be shifted, which is done with the 74HCT138. The circuit is a 3 bit decoder. One of the 8 outputs can be selected by setting the 3 inputs accordingly. Only the selected output goes to "L", while all other outputs are "H". This ensures, that only one LED column can be selected at a time.

The 8 rows are activated by means of a Darlington transistor each. The transistors are arraged in an array (ULN2803). The resistors set the LED current to about 60 mA. This is well with the [specification of the LEDs](https://www.led1.de/shop/files/Datenblaetter/Rechteckig/WEHWW02-D1M.pdf).

<p align="center"> 
  <img src="images/figure11.jpeg" style="display: inline-block; margin: 20px; max-width: 600px">
</p>

**Figure 11: Schematic of the Display Board**

The timing of the display is critical in order to generate stable largely flicker free grey level images. **Figure 12** shows the timing sequence. The display rotates with a frequency of up to 10 Hz. The Hall sensor generates a reference signal once it is within reach of the static magnet. Within the 100 ms per revolution, 240 lines with 56 pixels each are successively displayed. Each line will be displayed for 100ms/240 = 420µs. In order to generate grey levels, each pixel is split into 8 "sub pixels". If all of the subpixels are "on", the intensity of the pixel will be maximal, if 4 subpixels are "on" and 4 subpixels are "off", intensity of the pixel will be medium, and if all subpixels are "off", intensity will be zero. The time per subpixel is 420µs/8 = 52µs. Within this time, the multiplexing of the LEDs has to happen. Each column of the matrix will be displayed for 52µs/7 = 7.5µs. 

<p align="center"> 
  <img src="images/figure12.jpeg" style="display: inline-block; margin: 20px; max-width: 600px">
</p>

**Figure 12: Timing of the LED control.** Within the time per revolution of 100ms, 240 lines with 8 grey levels are displayed. 

The high speed of the multiplexing has quite some implications. The electronics and its setup needs to allow for very short and steep 60 mA current pulses. In order to manage electromagnetic interference, a 4 layer board has been used. The two inner layers are grounding planes, all vias have a grounding "companion", in order to ensure [proper current return paths](https://www.youtube.com/live/ySuUZEjARPY?si=sn-svxhxvuI3ehGK). Furthermore, the microcontroller needs to control the output lines in a strict and very fast time regime.

Fortunately, the RP2040 microcontroller has a powerful unit for controlling the input and outputs (PIO = programmable IO) (**figure 13**). This unit is used to manage the multiplexing and decouple its timing from the processor and its interrupts as much as possible. The solution ensures not only the necessary very high speed for the multiplexing, but also generates a stable time regime.

<p align="center"> 
  <img src="images/figure13.jpeg" style="display: inline-block; margin: 20px; max-width: 600px">
</p>

**Figure 13: RP2040 programmable IO (PIO).** The unit allows for fast multiplexing of the LEDs. 

The full circuit diagram of the display board is shown in **figure 14**. All details can be obtained from the [GitHub repository](https://github.com/lhm0/rotating_display_pico/tree/master).

<p align="center"> 
  <img src="images/figure14a.jpeg" style="display: inline-block; margin: 20px; max-width: 600px">
</p>

<p align="center"> 
  <img src="images/figure14b.jpeg" style="display: inline-block; margin: 20px; max-width: 600px">
</p>

**Figure 14: Circuit diagram of the display board** 

 





