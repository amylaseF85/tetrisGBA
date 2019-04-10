#include "gba.h"
#include "8x8.til"

#define COLOR_WHITE     BGR(31, 31, 31)
#define COLOR_BLACK     0
#define FONT_SIZE       8

int mino_test[4][4];
hword tcolor[4][4];

struct box{
    int x, y;
    int width, height;
};

void draw_box(struct box *b, int x, int y, hword color){
    hword *base, *d;
    int w,h;

    base = (hword*)VRAM + LCD_WIDTH * y + x;

    for(h = b->height; h > 0; h--){
        d = base;
        for(w = b->width; w > 0; w--)
            *(d++) = color;
        base += LCD_WIDTH;
    }
    b->x = x;
    b->y = y;
}

void move_box(struct box *b, int x, int y, hword color){
    draw_box(b, b->x, b->y, COLOR_BLACK);
    draw_box(b, x, y, color);
}


main(){
    //hword   *fb = (hword*)VRAM;
    int     key;
    int     x = 20;
    int     y = 10;
    int     i;
    struct box b;
    b.x = 0;
    b.y = 0;
    b.width = 5;
    b.height = 5;

    mino_test[1][0] = 1;
    mino_test[1][1] = 1;
    mino_test[1][2] = 1;
    mino_test[1][3] = 1;
    tcolor[1][0] = BGR(0,31,31);
    tcolor[1][1] = BGR(0,31,31);
    tcolor[1][2] = BGR(0,31,31);
    tcolor[1][3] = BGR(0,31,31);

    /* Initialize LCD Control Register to use Mode 3. */
    gba_register(LCD_CTRL) = LCD_BG2EN | LCD_MODE3;


    draw_box(&b, (3 + 1) * 5, (3 + 1) * 5, tcolor[1][1]);
    /*
    * Loop forever reading a key status and displaying the
    * corresponding character.
    */
    for (;;) {}
}
