#include "gba.h"
#include "8x8.til"

#define COLOR_WHITE BGR(31,31,31)
#define COLOR_Z BGR(31,0,0)
#define COLOR_O BGR(31,31,0)
#define COLOR_I BGR(0,31,31)
#define COLOR_BLACK 0
#define FONT_SIZE 8

void draw_char(hword *ptr, hword color, int code){
    hword *p;
    int i, j;
    unsigned char *font = char8x8[code];

    for(i = 0; i< FONT_SIZE; i++){
        p = ptr + LCD_WIDTH * i;
        for(j = FONT_SIZE - 1; j >= 0; j--, p++){
            if(font[i] & (1 << j))
                *p = color;
        }
    }
}

void print_char(int x, int y, int num, char* c){
    int i;
    hword *fb = (hword*)VRAM;
    for(i = 0; i < num; i++){
        draw_char(fb + (LCD_WIDTH * (10+y)) + (8*x), COLOR_WHITE, c[i]);
        x++;
        if(x > 30){
            y++;
            x = 0;
        }
    }
}


main(){
    //char *c = "remain";
    gba_register(LCD_CTRL) = LCD_BG2EN | LCD_MODE3;
    print_char(10,10,6,"remain");

    for(;;){}
}
