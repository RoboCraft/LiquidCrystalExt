/* This is header file for LiquidCrystalExt library which adds support
 * for pin drivers to LiquidCrystal library for Arduino, thus giving
 * an opportunity to use LCD connected, for example, through a shift register.
 * 
 * See the article about LCDs based on HD44780 at http://robocraft.ru/blog/arduino/503.html
 *
 * Copyright (C) 2011 Artem Borisovskiy (bytefu@gmail.com), http://robocraft.ru
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef LIQUIDCRYSTALEXT_H
#define LIQUIDCRYSTALEXT_H

#include <inttypes.h>
#include "Print.h"
#include "LineDriver.h"

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00


class LiquidCrystalBase: public Print
{
public:
  void begin(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS);

  void clear();
  void home();

  void noDisplay();
  void display();
  void noBlink();
  void blink();
  void noCursor();
  void cursor();
  void scrollDisplayLeft();
  void scrollDisplayRight();
  void leftToRight();
  void rightToLeft();
  void autoscroll();
  void noAutoscroll();

  void createChar(uint8_t, uint8_t[]);
  void setCursor(uint8_t, uint8_t); 
  
  #if defined(ARDUINO) && ARDUINO >= 100
  virtual size_t write(uint8_t data);
  #else
  virtual void write(uint8_t data);
  #endif
  
  void command(uint8_t);

protected:
  virtual void config() = 0;
  virtual void send(uint8_t, uint8_t) = 0;
  virtual void write4bits(uint8_t) = 0;

  uint8_t _displayfunction;
  uint8_t _displaycontrol;
  uint8_t _displaymode;
  uint8_t _initialized;
  uint8_t _numlines,_currline;
};


class LiquidCrystal: public LiquidCrystalBase
{
public:
  LiquidCrystal(uint8_t rs, uint8_t enable,
    uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
    uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
    LineDriver *line_driver = 0, uint8_t backlight = 0xFF);

  LiquidCrystal(uint8_t rs, uint8_t rw, uint8_t enable,
    uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
    uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
    LineDriver *line_driver = 0, uint8_t backlight = 0xFF);

  LiquidCrystal(uint8_t rs, uint8_t rw, uint8_t enable,
    uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
    LineDriver *line_driver = 0, uint8_t backlight = 0xFF);

  LiquidCrystal(uint8_t rs, uint8_t enable,
    uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
    LineDriver *line_driver = 0, uint8_t backlight = 0xFF);

  void backlight(bool on = true);
  void noBacklight();

protected:
  void init(uint8_t fourbitmode, uint8_t rs, uint8_t rw, uint8_t enable,
    uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
    uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
    uint8_t backlight, LineDriver *line_driver);

  virtual void config();
  virtual void send(uint8_t, uint8_t);
  virtual void write4bits(uint8_t);
  void write8bits(uint8_t);
  void pulseEnable();

  LineDriver *_pins;
  uint8_t _rs_pin; // LOW: command.  HIGH: character.
  uint8_t _rw_pin; // LOW: write to LCD.  HIGH: read from LCD.
  uint8_t _enable_pin; // activated by a HIGH pulse.
  uint8_t _data_pins[8];
  uint8_t _backlight_pin; // should be connected to the base of a transistor

  uint8_t _displayfunction;
  uint8_t _displaycontrol;
  uint8_t _displaymode;
  uint8_t _initialized;
  uint8_t _numlines,_currline;
};

#endif // LIQUIDCRYSTALEXT_H
