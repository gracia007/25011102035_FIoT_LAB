# CAT7 - 16x2 LCD Driver Development and Dynamic Display Control

| Field | Details |
|---|---|
| **EXP** | CAT7 |
| **DATE** | 24/08/2026 |
| **NAME OF EXP** | 16x2 LCD Driver Development and Dynamic Display Control |
| **HARDWARE SETUP / PLATFORM** | AT89S52 (8051 core) development board, 11.0592 MHz crystal, Keil uVision, 16x2 HD44780 LCD (4-bit mode), 4x4 keypad |
| **TASK NO** | Task 7A - LCD Initialization and Character/String Display, Task 7B - Cursor Positioning and Dynamic Value Update, Task 7C - 4x4 Keypad-Based Character Movement |

## Circuit Diagram

![Circuit Diagram](circuit.png)

## Tasks

### Task 7A - LCD Initialization and Character/String Display

**Project folder:** [`TASKA_LCD_Init_Char_String_Display/`](TASKA_LCD_Init_Char_String_Display/)

#### Core Logic / Pseudocode / Code Base

**Working Principle:**

A 16x2 HD44780-compatible LCD is driven in 4-bit mode using GPIO pins for RS, E and D4–D7 (RW tied to GND). Each byte is sent as two nibbles, latched by a HIGH-to-LOW pulse on E. RS selects command (0) or data (1).

**Pseudocode:**

1. `lcd_init()`: wait > 15 ms, send the 4-bit wake-up sequence (0x03, 0x03, 0x03, 0x02).
2. Send Function Set `0x28` (4-bit, 2-line, 5x8 font).
3. Send Display ON/Cursor OFF `0x0C`, Entry Mode `0x06`, Clear Display `0x01`.
4. `lcd_cmd(c)`: RS = 0, send upper nibble, pulse E, send lower nibble, pulse E.
5. `lcd_data(d)`: same as `lcd_cmd` with RS = 1.
6. Display characters and strings on row 1 (0x80) and row 2 (0xC0).

**Code Base:**

The driver functions `lcd_init()`, `lcd_cmd()` and `lcd_data()` are derived from the HD44780 datasheet command table. A helper `lcd_nibble()` writes D4–D7 and generates the enable pulse.

#### INFERENCE

Characters and strings are displayed correctly on both rows of the LCD in 4-bit mode, showing that the HD44780 can be initialised and controlled with only six GPIO lines using the datasheet command sequence.


### Task 7B - Cursor Positioning and Dynamic Value Update

**Project folder:** [`TASKB_Cursor_Positioning_Dynamic_Update/`](TASKB_Cursor_Positioning_Dynamic_Update/)

#### Core Logic / Pseudocode / Code Base

**Working Principle:**

Cursor positioning uses the DDRAM address map: row 0 starts at 0x00 and row 1 at 0x40, so the Set DDRAM Address command is `0x80 + address`. Numbers are converted to ASCII digits before being written.

**Pseudocode:**

1. `lcd_goto(row, col)`: send command `0x80 + col` for row 0 or `0xC0 + col` for row 1.
2. `lcd_puts(str)`: call `lcd_data()` for each character until '\0'.
3. `lcd_print_number(value)`: convert the value to digits by repeated division by 10 and print them in the correct order.
4. Place a label at a fixed position and update the number next to it periodically.
5. Overwrite old digits (or pad with spaces) so the display stays clean.

**Code Base:**

`lcd_goto()`, `lcd_puts()` and `lcd_print_number()` build on the Task A driver to give positioned text and dynamically updated values.

#### INFERENCE

Text appears at the requested row and column, and numeric values update in place without clearing the whole screen, demonstrating DDRAM addressing and number-to-ASCII conversion.


### Task 7C - 4x4 Keypad-Based Character Movement

**Project folder:** [`TASKC_Keypad_Character_Movement/`](TASKC_Keypad_Character_Movement/)

#### Core Logic / Pseudocode / Code Base

**Working Principle:**

A character is moved across the 16x2 display using the 4x4 keypad. Keys 2, 8, 4 and 6 act as Up, Down, Left and Right. The current row and column are stored, and on each valid key the old position is erased and the character is drawn at the new position.

**Pseudocode:**

1. Initialise the LCD and keypad; set `row = 0`, `col = 0` and draw the character.
2. Scan the keypad for a key press (with debounce).
3. Key 2: row = 0; Key 8: row = 1; Key 4: col−− (if > 0); Key 6: col++ (if < 15).
4. Erase the old position by writing a space there.
5. Draw the character at the new (row, col) using `lcd_goto()`.
6. Repeat continuously.

**Code Base:**

Combines the keypad scanning routine with `lcd_goto()` and `lcd_data()`. Boundary checks keep the character within the 16x2 area.

#### INFERENCE

The character moves up, down, left and right on the LCD according to the keys pressed and stops at the display edges, showing the integration of keypad input and LCD output in an interactive application.
