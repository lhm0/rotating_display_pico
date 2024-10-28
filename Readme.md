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




