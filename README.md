# esphome-protected-cover
This project is based on a (modified) Shelly 2.5. The software is based on ESPHome with a custom cover component. I've implemented a time based cover and used a reed switch to detect the window status. The cover won't do anything when the window is open. At the end, the cover can be operated intuitively with Home Assistant.

## Hardware preparation
> NOTE: Any modifications to your hardware and the use of this software is at your own risk.

In my case, I am not using the SW inputs on the Shelly to control the cover with existing buttons. So I decided to use the screw terminals from SW1 and SW2 to connect my reed switch to. The SW1 input will be used as GND and SW2 input will be connected to GPIO0. To do so, start with removing the 47k&Omega; resistors (R13 and R14).

<img src="Pictures/SHELLY_noR.jpg" width="500">

The next step is to connect the screw terminals to GND and GPIO0. Both exists on the program header, so you can connect those pins to the screw terminals with some wires. Be aware to make no short circuits! You can solder the GND wire to a more accessible place, of course.

<img src="Pictures/SHELLY_int_wired.jpg" width="500">

You can now attach your reed switch easily to your Shelly!

<img src="Pictures/SHELLY_finished.jpg" width="500">

## Software
Use your favourite UART-USB converter to upload the ESPHome configuration to your Shelly. You can use the legs of three resistors to fit in the program header. Solder the other ends to a pinheader and connect it to the UART-USB converter.
