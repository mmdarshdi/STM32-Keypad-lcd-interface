# STM32 Keypad & LCD Interface

![MCU](https://img.shields.io/badge/MCU-STM32F103C8T6-03234B)
![Language](https://img.shields.io/badge/language-C-555555)
![Framework](https://img.shields.io/badge/framework-STM32%20HAL-03234B)
![IDE](https://img.shields.io/badge/IDE-Keil%20%C2%B5Vision-2e7d32)
![License](https://img.shields.io/badge/license-MIT-yellow)

Embedded C firmware for the **STM32F103C8T6** that scans a **5×4 matrix keypad** and displays the typed characters on a **16×2 character LCD**. Built with STM32CubeMX and the STM32 HAL.

## Overview

The firmware drives the keypad rows as outputs and reads the columns as inputs with internal pull-ups. Each pressed key is looked up in a character table, appended to a text buffer and rendered on the LCD, so the display always shows everything typed so far.

## Features

- Row/column scanning of a 20-key (5×4) matrix keypad, one row driven low at a time
- Internal pull-ups on the column inputs, so no external pull-up resistors are needed
- 5 ms row-settling delay and blocking wait-for-release logic acting as a simple debounce
- Typed characters accumulated in a string buffer and shown on the LCD
- 16×2 LCD in 8-bit parallel mode
- Fully configured through STM32CubeMX (`.ioc` file included)

## Hardware

| Component | Details |
|-----------|---------|
| MCU | STM32F103C8T6 (ARM Cortex-M3) |
| Input | 5×4 matrix keypad (20 keys) |
| Display | 16×2 character LCD (HD44780-compatible), 8-bit write-only mode, driven by the custom `lcd.c` / `lcd.h` driver |
| Programmer / debugger | ST-Link over SWD |

## Pin Mapping

### Keypad

| Signal | Pin | Direction |
|--------|-----|-----------|
| Row 1 (R1) | PA8 | Output |
| Row 2 (R2) | PA9 | Output |
| Row 3 (R3) | PA10 | Output |
| Row 4 (R4) | PA11 | Output |
| Row 5 (R5) | PA12 | Output |
| Column 1 (C1) | PB5 | Input, pull-up |
| Column 2 (C2) | PB4 | Input, pull-up |
| Column 3 (C3) | PB3 | Input, pull-up |
| Column 4 (C4) | PA15 | Input, pull-up |

### LCD

| Signal | Pin |
|--------|-----|
| D0 – D7 | PA0 – PA7 |
| Control lines (RS, RW, EN) | GPIOB, pin numbers defined in `lcd.h` |

### System

| Function | Pin |
|----------|-----|
| SWDIO / SWCLK | PA13 / PA14 |
| HSE crystal | PD0 / PD1 |
| USART1 TX / RX (configured, see notes) | PB6 / PB7 |

> SWD is used for debugging, so PA15, PB3 and PB4 are free to be used as normal GPIO.

## Key Layout

|        | C1  | C2  | C3  | C4  |
|--------|-----|-----|-----|-----|
| **R1** | `F` | `f` | `#` | `*` |
| **R2** | `1` | `2` | `3` | `U` |
| **R3** | `4` | `5` | `6` | `D` |
| **R4** | `7` | `8` | `9` | `E` |
| **R5** | `L` | `0` | `R` | `T` |

Function and navigation keys are mapped to single characters in the `KEY[]` table in `Core/Src/main.c`, so the layout can be changed in one place.

## How It Works

1. `read_keypad()` drives one row LOW and holds the other four rows HIGH.
2. After a short settling delay, all four columns are read. A column reading LOW means the key at that row/column intersection is pressed.
3. The firmware waits for the key to be released (a simple blocking debounce) before moving on.
4. The character is appended to the `str[]` buffer, the string is terminated, and the LCD is updated.
5. The process repeats for rows 2 to 5. If no key is pressed, the function returns `'N'`.

## System Configuration

| Item | Value |
|------|-------|
| System clock | HSE with PLL ×9, 72 MHz (8 MHz crystal) |
| APB1 / APB2 | 36 MHz / 72 MHz |
| Flash latency | 2 wait states |
| USART1 | 115200 baud, 8N1, remapped to PB6/PB7. Initialised but not used by the current application logic |

## Project Structure

```
.
├── Core/                  Application sources (main.c) and peripheral setup
├── Drivers/               STM32 HAL and CMSIS drivers
├── MDK-ARM/               Keil µVision project
├── LCD and KEYPAD.ioc     STM32CubeMX configuration
└── README.md
```

## Build & Flash

**Requirements:** Keil µVision 5 (with the `Keil.STM32F1xx_DFP` pack) and an ST-Link programmer. STM32CubeMX is optional.

1. Clone the repository:
   ```bash
   git clone https://github.com/mmdarshdi/STM32-Keypad-lcd-interface.git
   ```
2. Open the `.uvprojx` file inside `MDK-ARM/` in Keil µVision.
3. Build the project (**F7**) and flash it to the board (**F8**).

To change the pin configuration, open `LCD and KEYPAD.ioc` in STM32CubeMX and regenerate the code. Your code inside the `USER CODE` blocks is preserved.

## Usage

1. Wire the keypad and LCD according to the pin tables above.
2. Power the board. The LCD is cleared on start-up.
3. Press keys on the keypad. Each character appears on the LCD in the order it was typed.

## Possible Improvements

- Bounds check on the 20-byte input buffer
- Non-blocking, timer-driven scanning instead of polling with `HAL_Delay`
- Dedicated clear and backspace keys
- Forwarding typed characters over USART1

## Related Projects

- [STM32-UART-USART-Communication](https://github.com/mmdarshdi/STM32-UART-USART-Communication)
- [STM32-Timer-Start-Stop-Control](https://github.com/mmdarshdi/STM32-Timer-Start-Stop-Control)
- [STM32-IR-Pulse-Counter](https://github.com/mmdarshdi/STM32-IR-Pulse-Counter)

## License

Released under the MIT License. See [LICENSE](LICENSE) for details.

## Author

**Mohammadrahim Arshadi**, Biomedical Engineer focused on medical embedded systems
[GitHub](https://github.com/mmdarshdi) · [LinkedIn](https://www.linkedin.com/in/mmdarshdi)
