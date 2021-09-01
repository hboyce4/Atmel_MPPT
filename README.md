# Atmel_MPPT
A Maximum Power Point Tracker converter for solar panels, running on an Atmel 8-bit MCU

Possible improvements to be made:
- Add load switch to cut power to the USB port when the battery is too low and prevent overdischarge/BMS cutout.
- Update to a 32-bit MCU.
- Change the AP3513 switching regulator IC for one with a smaller quiescent current.
