# shloader
NetBSD/evbsh3 Bootloader

![The bootloader](https://gist.githubusercontent.com/RyuKojiro/088e8690d54d4ac0029da8539f06fc18/raw/0129357012502a590b56c7915bad21112b01e32f/shloader.png)

# Status
- [x] Loading kernel over serial
  - [x] Using NetBSD's sh3 SCIF register definitions
    - This requires my branch with SH4A SCIF support added, as my board is SH4A
- [ ] Loading kernel from SD Card
  - [ ] Add the SD support code created here to the sh3 kernel to give it access to the SD card
- [x] Running from memory
- [x] Running from flash
- [x] Running from EPROM
- [ ] Clean it up
  - [ ] Easily configurable serial port
  - [ ] Figure out how this and the landisk port bootloader could be merged together

# Wheat Board Notes
There are two boot modes, one used for booting the EPROM with the MiniMonitor, the other for booting the flash.

- EPROM Mode
  - Reset Vector: `0xA0000000`
  - RAM Region:   `0x08000000 - 0x0C000000`
  - Flash Region: `0x88000000 - 0x8C000000`
- Flash Mode
  - Reset Vector: `0x10000000`
  - RAM Region:   `0x88000000 - 0x8C000000`
  - Flash Region: `0x10000000 - ???`
