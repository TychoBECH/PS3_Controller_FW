# ? PS3 Controller ? PIC18 Firmware Project
*(Firmware project for PIC18F56Q71, generated with MPLAB X & MCC)*

This repository contains the firmware for a custom **PS3 controller interface** implemented on a **Microchip PIC18F56Q71** microcontroller.  
The project is built using **MPLAB X**, **MCC (MPLAB Code Configurator)**, and the **XC8 compiler**.  
It includes driver libraries, auto?generated hardware modules, and complete production build outputs.  
[1](https://onedrive.live.com/?id=e892f261-23a4-206f-8037-473301000000&cid=376f23a4e892f261&web=1)

---

## ? Features

- Custom firmware for PS3?style input handling  
- Built on **PIC18F56Q71**  
- MCC?generated hardware drivers:
  - ADC  
  - UART  
  - SPI  
  - I²C  
  - System / Clock / Pins  
  [2](https://onedrive.live.com/?id=57a4fc3e-89be-4efe-9909-6fc0d10e87df&cid=376f23a4e892f261&web=1)
- Custom modules:
  - `CC2500_driver` ? RF transceiver driver  
  - `BQ27427` ? Battery fuel gauge driver  
  [2](https://onedrive.live.com/?id=57a4fc3e-89be-4efe-9909-6fc0d10e87df&cid=376f23a4e892f261&web=1)
- Clean and modular project layout inside MPLAB X

---

## ? Project Structure

### Root Project  
- **PS3_Controller.X** ? Main MPLAB X project directory  
  [1](https://onedrive.live.com/?id=e892f261-23a4-206f-8037-473301000000&cid=376f23a4e892f261&web=1)

### Source Code Highlights  
- `main.c` ? Initialization and main loop  
  [3](https://onedrive.live.com/?id=e7a84742-802f-454e-9cf3-d50dd5482c89&cid=376f23a4e892f261&web=1)
- MCC Generated:
  - `system.c`, `interrupt.c`, `pins.c`, `clock.c`  
  - `adc.c`, `spi1.c`, `uart1.c`, `i2c1.c`  
  - Corresponding headers under `mcc_generated_files/`  
  [2](https://onedrive.live.com/?id=57a4fc3e-89be-4efe-9909-6fc0d10e87df&cid=376f23a4e892f261&web=1)
- Custom drivers:
  - `drivers/CC2500_driver.c`  
  - `drivers/BQ27427.c`  
  [2](https://onedrive.live.com/?id=57a4fc3e-89be-4efe-9909-6fc0d10e87df&cid=376f23a4e892f261&web=1)

---

## ? Production Build Outputs

These are automatically generated after building the project in MPLAB X:

| File | Description |
|------|-------------|
| **PS3_Controller.X.production.elf** | Firmware ELF binary [4](https://onedrive.live.com/?id=e892f261-23a4-206f-8037-692801000000&cid=376f23a4e892f261&web=1) |
| **PS3_Controller.X.production.hxl** | HEX listing file [5](https://onedrive.live.com/?id=e892f261-23a4-206f-8037-ab7701000000&cid=376f23a4e892f261&web=1) |
| **PS3_Controller.X.production.map** | Memory map output [6](https://onedrive.live.com?cid=376F23A4E892F261&id=376F23A4E892F261!s384365c08e344ec7818101f1b5cb079f) |
| **PS3_Controller.X.production.sym** | Symbol table [7](https://onedrive.live.com/?id=5b983104-a594-469f-bff9-670d14ff4e3c&cid=376f23a4e892f261&web=1) |
| **PS3_Controller.X.production.lst** | Compiler listing [8](https://onedrive.live.com/?id=e892f261-23a4-206f-8037-5b1700000000&cid=376f23a4e892f261&web=1) |
| **PS3_Controller.X.production.sdb** | Debug data [9](https://onedrive.live.com/?id=384365c0-8e34-4ec7-8181-01f1b5cb079f&cid=376f23a4e892f261&web=1) |
| **PS3_Controller.X.production.o** | Object file [10](https://onedrive.live.com/?id=e892f261-23a4-206f-8037-a87701000000&cid=376f23a4e892f261&web=1) |
| **PS3_Controller.X.production.mum** | Metadata module [11](https://onedrive.live.com/?id=e892f261-23a4-206f-8037-76af00000000&cid=376f23a4e892f261&web=1) |
| **PS3_Controller.X.production.rlf** | MPLAB compiled artifact [12](https://onedrive.live.com/?id=e892f261-23a4-206f-8037-3d2f01000000&cid=376f23a4e892f261&web=1) |

---

## ? Dependencies

- **MPLAB X IDE** (v6.0+ recommended)  
- **XC8 Compiler**  
- **MPLAB Code Configurator (MCC)**  
- **PIC18F56Q71** microcontroller  
- Optional external modules:
  - TI **BQ27427** battery gauge  
  - TI **CC2500** RF transceiver  

---

## ? Building the Firmware

1. Open the project folder: **PS3_Controller.X**  
2. Ensure the **XC8 compiler** is selected  
3. Click the **Build** button  
4. Generated binaries will appear in `dist/` under the production folder  
   (listing shown above)

---

## ?? Running the Firmware

1. Flash the `.hex` or `.elf` file using PICkit 4 / ICD4 / Snap  
2. Connect hardware modules:
   - PS3 input interface  
   - CC2500 transceiver  
   - BQ27427 gauge  
3. Power the board ? firmware starts automatically

---

## ? License

Some source files include Microchip?s MCC license headers.  
Refer to individual files for details.  
[3](https://onedrive.live.com/?id=e7a84742-802f-454e-9cf3-d50dd5482c89&cid=376f23a4e892f261&web=1)

---

## ? Credits

Developed by **Tycho Kropf**  
[1](https://onedrive.live.com/?id=e892f261-23a4-206f-8037-473301000000&cid=376f23a4e892f261&web=1)