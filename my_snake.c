#include "gba.h"
#include "8x8.til"

#define COLOR_WHITE     BGR(31, 31, 31)
#define COLOR_BLACK     0
#define FONT_SIZE       8
/*
* Draw a font of code with color.
* ptr specifies the font's top left corner.
*/
void draw_char(hword *ptr, hword color, int code){
    hword   *p;
    int     i, j;
    unsigned char   *font = char8x8[code];

    for (i = 0; i < FONT_SIZE; i++) {
        p = ptr + LCD_WIDTH * i;
        for (j = FONT_SIZE - 1; j >= 0; j--, p++) {
            if (font[i] & (1 << j))
            *p = color;
        }
    }
}

draw_dot(hword *fb, int x, int y){
            *(fb + (LCD_WIDTH * y) + x) = BGR(0x1F, 0x1F, 0x1F);
}

main(){
    hword   *fb = (hword*)VRAM;
    int     key;
    int     x = 10;
    int     y = 10;
    int     i;

    /* Initialize LCD Control Register to use Mode 3. */
    gba_register(LCD_CTRL) = LCD_BG2EN | LCD_MODE3;
    /*
    * Loop forever reading a key status and displaying the
    * corresponding character.
    */
    for (;;) {
        /* Read a key status from Key Status Register. */
        key = gba_register(KEY_STATUS);
        if (! (key & KEY_DOWN)) {
            for(i = 0; i < 1300; i++){
                draw_dot(fb, x, y);
            }
            if(y <= 160) y++;
        }
        //else                    draw_char(fb + 30, COLOR_BLACK, 25);
        if (! (key & KEY_UP)) {
            for(i = 0; i < 1300; i++){
                draw_dot(fb, x, y);
            }
            if(y >= 0) y--;
        }
        //else                  draw_char(fb + 40, COLOR_BLACK, 24);
        if (! (key & KEY_LEFT)) {
            for(i = 0; i < 1300; i++){
                draw_dot(fb, x, y);
            }
            if(x >= 0) x--;
        }
        //else                    draw_char(fb + 50, COLOR_BLACK, 27);
        if (! (key & KEY_RIGHT)) {
            for(i = 0; i < 1300; i++){
                draw_dot(fb, x, y);
            }
            if(x <= 240) x++;
        }
        //else                     draw_char(fb + 60, COLOR_BLACK, 26);

    }
}
