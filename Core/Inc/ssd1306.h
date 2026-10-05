#ifndef SSD1306_H
#define SSD1306_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_def.h"
#include "stm32f1xx_hal_i2c.h"


#define BD_FB_WIDTH 128
#define BD_FB_HEIGHT 64
#define BD_FB_SIZE ((BD_FB_WIDTH * BD_FB_HEIGHT) / 8)
#define BD_START_TRANSFER 24

// SSD1306 COMMAND TABLE
#define SSD1306_I2C_ADDR (0x3C << 1)

// Fundamental Command table
#define BD_COM_SET_CONTRAST_CONTROL             (0x81)  //select 1 to 256 contrast steps
#define BD_COM_DISPLAY_ALL_ON_RESUME            (0xA4)  // resume to RAM content display
#define BD_COM_DISPLAY_ALL_ON                   (0XA5)  // Output ignores RAM content
#define BD_COM_SET_DISPLAY_NORMAL               (0XA6)  // normal display
#define BD_COM_SET_DISPLAY_INVERSE              (0XA7)  // inverse display
#define BD_COM_SET_DISPLAY_OFF                  (0XAE)  // display off (sleepmode)
#define BD_COM_SET_DISPLAY_ON                   (0XAF)  // display on

// scrolling command table
#define BD_COM_CONT_VRIGHT_HSCROLL              (0x29)
#define BD_COM_CONT_VLEFT_HSCROLL               (0x2A)
#define BD_COM_SCROLL_DEACT                     (0x2E)
#define BD_COM_SCROLL_ACTIVATE                  (0x2F)
#define BD_COM_SET_VSCROLL_AREA                 (0xA3)

// Addressing Setting command table
#define BD_COM_SET_MEM_ADDR_MODE                (0X20) 
/*
    A[1:0] = 00b = horizontal addressing mode
    01b = vertical addressing mode
    10b = Page addressing mode
    11b = invalid
*/
#define BD_COM_SET_LOW_COL_ADDR                 (0X00)
#define BD_COM_SET_HIGH_COL_ADDR                (0X10)

#define BD_COM_SET_COL_ADDR                     (0x21) 
/*
    A[6:0]: column start address, range: 0-127d, RESET(0d)
    B[6:0]: column end address,   range: 0-127d, RESET(127d)
    *for horizonal or vertical addressing mode only*
*/

#define BD_COM_SET_PAGE_ADDR                    (0X22)
/*
    A[2:0]: Page start Address, range: 0-7d, RESET(0d)
    B[2:0]: Page end Address,   range: 0-7d, RESET(7d)
    *for only horizontal and vertical addressing mode
*/
#define BD_COM_SET_PAGE_START_ADDR              (0XB0)

// Hardware Config command table
#define BD_COM_SET_DISPLAY_START_LINE           (0x40)
#define BD_COM_SET_SEGMENT_REMAP_COL0           (0xA0)
#define BD_COM_SET_SEGMENT_REMAP_COL127         (0xA1)
#define BD_COM_SET_MULTIPLEX_RATIO              (0xA8)
#define BD_COM_SET_COM_OUT_SCAN_DIRECTION_N     (0xC0)
#define BD_COM_SET_COM_OUT_SCAN_DIRECTION_RE    (0xC8)
#define BD_COM_SET_DISPLAY_OFFSET               (0xD3)
#define BD_COM_SET_COM_PIN_H_CONFIG             (0xDA)

// Timing and Driving Scheme Setting command table
#define BD_COM_SET_DISPLAY_CLCK_DIV_OSC         (0xD5)
#define BD_COM_SET_PRE_CHARGE_PERIOD            (0xD9)
#define BD_COM_SET_V_DESELECT_LVL               (0xDB)
#define BD_COM_NOP                              (0xE3)

// chargepump
#define BD_COM_CHARGE_PUMP_SETTING              (0x8D)

void bd_set_pixel(int x, int y, bool state);
bool bd_get_pixel(int x, int y);
void bd_draw_bitmap(int x, int y, int width, int height, const uint8_t *bitmap);
// void bd_draw_text (int x, int y, int size, char *text);
void bd_send_cmd(uint8_t cmd);
void bd_send_data(uint8_t data);
void bd_init();
void bd_display_update();


extern I2C_HandleTypeDef hi2c1;

#endif