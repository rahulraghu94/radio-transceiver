Using RF24 libraries to implement a simple program on 
Beaglebone Black, placed on the quadcopter, to act a simple reciever.
Using JeeLibs Libraries by JeeLabs to implement a simple C Program
on the Ardiuino Controller to act as a radio transmitter for the Quadcopter.

The Radio Tranceiver is an nRF24L01 IC. The range is about 100m. The range can
be extended using boosters that are available in stores. We will not be interfacing
the a booster as it is not needed at this stage.

The following are the KEY:VALUE pair that the reciever can recieve and which
the transmitter transmits:
	T:VALUE		Sets throttle to VALUE
	R:VALUE		Sets Roll set point to VALUE
	P:VALUE		Sets Pitch set point to VALUE
	Y:VALUE		Sets Yaw set point to VALUE

The reciever will initially respond with a "Connection Success" message 
When connected to the Transmitter. The transmitter can then go about 
sending control signals to the Reciever. Once shut down, a "Diconnect"
message will be relayed from the Reciever.

The transmitter will continuously send control singals that relay current 
orientation and throttle set points. This will be reciever by the BBB on the
Quadcopter. The BBB will respond to any changes in incoming data. 
The BBB will respond at frequent intervals to denote an active connection.



Airspayce RadioHead: http://www.airspayce.com/mikem/arduino/RadioHead/index.html
PyBBIO: https://github.com/graycatlabs/PyBBIO
