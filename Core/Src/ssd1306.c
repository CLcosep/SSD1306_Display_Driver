#include "ssd1306.h"
#include "fonts.h"

uint8_t BD_FRAMEBUFFER[BD_FB_SIZE] = {0};

void bd_set_pixel(int x, int y, bool state) {
    // SSD1306 OLED offsets the pixel vertically rather than the standard horizonal

    int pos = x + (y >> 3) * BD_FB_WIDTH; 
    uint8_t bitmask = (1  << (y & 0x7));

    if (state) {
        BD_FRAMEBUFFER[pos] |= bitmask;
    } else { 
        BD_FRAMEBUFFER[pos] &= ~bitmask;
    }
}

bool bd_get_pixel(int x, int y) {
    int pos = x + (y >> 3) * BD_FB_WIDTH;
    uint8_t bitmask = (1  << (y & 0x7));

    return BD_FRAMEBUFFER[pos] & bitmask;
}

void bd_draw_bitmap(int x, int y, int width, int height, const uint8_t *bitmap) {

    uint8_t chkMsk = 0;
    int size = width * height >> 3;

    int originX = x;
    int originY = y;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < 8; j++) {
            chkMsk = 0x80 >> j;
            bd_set_pixel(x, y, bitmap[i] & chkMsk);
            x++;

            if ((x - originX) == width) {
                y++;
                x = originX;
            }

            if ((y - originY) == height) {
                return;
            }
        }
    }
}

// void bd_draw_text (int x, int y, int size, char *text) {
//     const uint8_t *font;
//     const uint8_t *drawChar;

//     int runningX = x;
//     int runningY = y;

//     int target;

//     switch(size) {
//         case 16:
//         default:
//             font = CGA16;
//     }

//     for (int i = 0; i < strlen(text); i++) {
        
//         if (runningX >= BD_FB_WIDTH) {
//             runningX = x;
//             runningY += size;
//         }

//         if (runningY >= BD_FB_HEIGHT) {
//             return;
//         }
        
//         target = (size * size >> 3) * (text[i] - ' ');
//         drawChar = font + target;

//         bd_draw_bitmap(runningX, runningY, size, size, drawChar);

//         runningX += size;
//     }
// }

// SPI
// void bd_dummy_tx(uint8_t byte) {;}
// void bd_dummy_cd(bool state) {;}
// void bd_dummy_cs(bool state) {;}

// void (*bd_spi_tx)(uint8_t byte) = &bd_dummy_tx;
// void (*bd_set_cd)(bool state) = &bd_dummy_cd;
// void (*bd_set_cs)(bool state) = &bd_dummy_cs;

// void bd_set_spi_tx(void (*spi_tx)(uint8_t byte)) {
//     bd_spi_tx = spi_tx;
// }

// void bd_set_set_cd(void (*set_cd)(bool state)) {
//     bd_set_cd = set_cd;
// }

// void bd_set_set_cs(void (*set_cs)(bool state)) {
//     bd_set_cs = set_cs;
// }

void bd_send_cmd(uint8_t cmd) {
    uint8_t buf[2] = {0x00, cmd};
    HAL_I2C_Master_Transmit(&hi2c1, SSD1306_I2C_ADDR, buf, 2, HAL_MAX_DELAY);
}


void bd_send_data(uint8_t data) {
    uint8_t buf[2] = {0x40, data};
    HAL_I2C_Master_Transmit(&hi2c1, SSD1306_I2C_ADDR, buf, 2, HAL_MAX_DELAY);
}

void bd_init() {
    bd_send_cmd(BD_COM_SET_DISPLAY_OFF);

    bd_send_cmd(BD_COM_SET_DISPLAY_CLCK_DIV_OSC);
    bd_send_cmd(0x80);

    bd_send_cmd(BD_COM_SET_MULTIPLEX_RATIO);
    bd_send_cmd(0x3F);

    bd_send_cmd(BD_COM_SET_DISPLAY_OFFSET);
    bd_send_cmd(0x00);

    bd_send_cmd(BD_COM_SET_DISPLAY_START_LINE);

    bd_send_cmd(BD_COM_CHARGE_PUMP_SETTING);
    bd_send_cmd(0x14);

    bd_send_cmd(BD_COM_SET_MEM_ADDR_MODE);
    bd_send_cmd(0x02);

    bd_send_cmd(BD_COM_SET_SEGMENT_REMAP_COL127);

    bd_send_cmd(BD_COM_SET_COM_OUT_SCAN_DIRECTION_RE);

    bd_send_cmd(BD_COM_SET_COM_PIN_H_CONFIG);
    bd_send_cmd(0x12);

    bd_send_cmd(BD_COM_SET_CONTRAST_CONTROL);
    bd_send_cmd(0xCF);

    bd_send_cmd(BD_COM_SET_PRE_CHARGE_PERIOD);
    bd_send_cmd(0xF1);

    bd_send_cmd(BD_COM_SET_V_DESELECT_LVL);
    bd_send_cmd(0x40);

    bd_send_cmd(BD_COM_DISPLAY_ALL_ON_RESUME);

    bd_send_cmd(BD_COM_SET_DISPLAY_NORMAL);

    bd_send_cmd(BD_COM_SET_DISPLAY_ON);


}

void bd_display_update() {

    int size = BD_FB_HEIGHT / 8;
    for (int page = 0; page < size; page++) {
        bd_send_cmd(BD_COM_SET_PAGE_START_ADDR | page);
        bd_send_cmd(BD_COM_SET_LOW_COL_ADDR);
        bd_send_cmd(BD_COM_SET_HIGH_COL_ADDR);
        for (int i = 0; i < BD_FB_WIDTH; i++) {
            int col = BD_FRAMEBUFFER[page * BD_FB_WIDTH + i];
            bd_send_data(col);
        }        
        
    }
}