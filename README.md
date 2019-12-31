# LiPo-cycles-counter

Keep tracking of number of cycles of your LiPo batteries using NFC tags<br />
I usually keep this device near the battery charger, before charging a battery I add a count to it.

*MODES OF OPERATIONS* <br />

RM - READ MODE (short press mode button) <br />
Read tag info   <br />

CM - COUNTER MODE (short press mode button)<br />
Like read mode but counter is increased by 1 unit (default mode after power on)

SET MODE (press mode button for 2 sec)<br />
Write all tag info (short press mode button for menu navigation, up and down button for change values, E button for exit)


- Arduino NANO
- RC522 RFID reader
- 16x2 LCD 
- 4 pushbuttons
- some 220Ω resistors
- some 100nF cap
- 4.7k trimmer
- RFID tags (mifare classic 1k, default password FFFFFFFFFFFF)
