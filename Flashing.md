# Hyasynth Reference and Flashing

### Team 1: James Campbell, Angus Campbell, Matthew Cooke, Mark Harley, Tom Burnip

## Microcontroller details

The microcontroller being used is Silabs' EFM8LB12F64E-C-QFN32.

## Flashing
### Building the project

During development, the project was built using the Keil c51 toolchain through SiLab's Simplicity Studio. The full compliment of files to enable this will be provided. 

The project can be imported in to simplicity studio using the import wizard under File, and built using the hammer icon. If successful, this should produce .hex files under `project/Keil 8051 [version] Debug/`. You will need this file later, so don't lose it.

### Converting
As far as my testing goes, this part of the process, and flashing, only works on Windows. See the Linux issues section for more.

The next parts of the process require some more tools that Silabs provides. These can be downloaded [here](https://www.silabs.com/documents/public/example-code/AN945SW.zip)

You need to convert the raw .hex file to a .efm8 before flashing, using the tool hex2boot.exe, located under `/AN945SW/Tools/Windows/`. Run this using powershell or cmd with a command something like this `.\hex2boot.exe input_file.hex -o Filename.efm8`. The full details and documentation of this utility are available in section 6 [here.](https://www.silabs.com/documents/public/application-notes/an945-efm8-factory-bootloader-user-guide.pdf)

### Flashing
#### Ingredients:
- Windows computer
- USB to serial programmer, also known as an FTDI chip
- Wires
- .efm8 file that you prepared earlier
- Hyasynth
- efm8load.exe tool

#### Method:

1. Connect the FTDI programmer to the laser bee (make sure it is set to 3v3). Use the leftmost pin on the small header for ground, rightmost for power, and second from the left for c2d, leftmost of the big header for rx and 2nd from the left of the big header for tx.
1. Plug the programmer into the computer, and find out what serial port it is attached to. 
1. Set the Hyasynth to bootloader mode. This can be done by grounding the C2D pin (3.7, or the second pin from the left on the header) as the device is reset (for 50ms if you want the specifics).
1. Optionally, find out what port the programmer is operating on. efm8load.exe will choose one for you if you do not specify, and it will probably pick the wrong one. 
1. Run efm8load.exe with a command something like `./efm8load.exe -p PORT Filename.efm8`.
1. Reset the Hyasynth and serve.

### Linux issues

An attempt was made to get this working on linux, but two big issues arose: hex2boot, and actually flashing it. Hex2boot is only distributed as an exe, with no source files. [One repo on github](https://github.com/kamnxt/efm8load) reports success running it under wine, but attempts to use wine bore no fruit. In addition a third party hex2boot converter found on github was tried, and this also did not work. As for flashing it, SiLabs distributes the python source files for efm8flash, but attempts to use this failed. It requires some modification (detailed [here](https://community.silabs.com/s/article/how-to-use-efm8-uart-bootloader-on-linux?language=en_US)), and some difficult to source libraries, and despite following the instructions, it did not work.
