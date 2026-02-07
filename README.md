# BARE_METAL_PATH
## GOAL:
To learn the basics of bare metal programming through simulation on Wokwi starting with Arduino Nano (We will update as time goes on) using PlatformIO IDE (All available on VS Code).
## REQUIREMENTS:
1. Install VS Code
2. Download the PlatformIO extension on VS Code
3. Download Wokwi extension on VS Code
4. Click on the PlatformIO icon on the left-most side of the VS Code app on your device and create a new project.
5. Happy praticing.
6. Download the ATMEGA328P datasheet
7. Download a Pin-Out diagram for Arduino Nano to use as a reference.
8. Find a good resources to learn Bit Twiddling in C or Bare metal programming.
## PROCEDURES:
1. Always create a diagram.json file in the folder of your PlatformIO project and paste the diagram.json file in this repo
2. Always create a wokwi.toml and paste this:
[wokwi]
version=1
firmware=".pio/build/nanoatmega328new/firmware.hex"
elf=".pio/build/nanoatmega328new/firmware.elf"
//THE ABOVE IS FOR ARDUINO NANO
