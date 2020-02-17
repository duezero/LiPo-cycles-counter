# LiPo-cycles-counter

Keep tracking of number of cycles of your LiPo batteries using NFC tags<br />
I usually keep this device near the battery charger, before charging a battery I add a count to it<br />
[Video](https://www.youtube.com/watch?v=cQ8MbUWtfQA&feature=youtu.be)

*MODES OF OPERATION* <br />

RM - READ MODE (short press mode button) <br />
Read tag info   <br />

CM - COUNTER MODE (short press mode button)<br />
Like read mode but counter is increased by 1 unit (default mode after power on)

SET MODE (press mode button for 2 sec)<br />
Write all tag info (short press mode button for menu navigation, up and down button for change values, E button for exit)

*COMPONENTS* <br />
- Arduino NANO
- RC522 RFID reader
- 16x2 LCD 
- 4 pushbuttons
- some 220Ω resistors
- some 100nF cap
- 4.7k trimmer
- RFID tags (mifare classic 1k, default password FFFFFFFFFFFF)

**IMPORTANT**<br />
LiPo cells are enclosed in aluminum foil that can interfere with rfid tags, by placing the tag on the bottom of the battery there should be no problems. On the side of batteries instead probably the tag will not work. To avoid interferences is necessary to increase distance(using non metallic shim) between tag and battery until reading is ok. <br />

3D files are not available yet
