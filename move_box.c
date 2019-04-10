
#include "gba.h"
#include "8x8.til"

#define COLOR_WHITE     BGR(31, 31, 31)
#define COLOR_BLACK     0

struct box{
    int x, y;
    int width, height;
}
/*
* Draw a font of code with color.
* ptr specifies the font's top left corner.
*/
draw_box(struct box *b, int x, int y, hword color){
    hword *base, *d;
    int w,h;

    base = (hword*)VRAM + LCD_WIDTH * y + x;

    for(h = b->height; h > 0; h--){
        d = base;
        for(w = b->width; w > 0; w--){
            *(d++) = color;
        }
        base += LCD_WIDTH;
    }
    b->x = x;
    b->y = y;
}

void move_box(struct box *b, int x, int y, hword color){
    draw_box(b, b->x, b->y, COLOR_BLACK);
    draw_box(b, x, y, color);
}

ball_step(struct box *b, int ballx, int bally, hword color, int dx, int dy){
    move_box(&ball, ballx, bally, COLOR_WHITE);
    ballx += dx;
    bally += dy;
    if(ballx <= 0 || ballx >= (240 - ball.width)) dx = -dx;
    if(bally <= 0 || bally >= (160 - ball.height)) dy = -dy;
}

void wait(int val) {
    int     i, j;

    for (i = 0; i < val; i++)
        for (j = 0; j < val; j++)
                    ;
}

main(){
    hword   *fb = (hword*)VRAM;
    int     key;
    int     x = 20;
    int     y = 10;
    int     ballx = 10;
    int     bally = 10;
    int     i;
    struct box b;
    b.x = 0;
    b.y = 0;
    b.width = 30;
    b.height = 5;
    struct box ball;
    ball.x = 10;
    ball.y = 10;
    ball.width = 5;
    ball.height = 5;

    /* Initialize LCD Control Register to use Mode 3. */
    gba_register(LCD_CTRL) = LCD_BG2EN | LCD_MODE3;
    /*
    * Loop forever reading a key status and displaying the
    * corresponding character.
    */
    int dx = 1;
    int dy = 1;

    move_box(&ball, ballx, bally, COLOR_WHITE);
    for (;;) {
        move_box(&b, x, y, COLOR_WHITE);
        /* Read a key status from Key Status Register. */
         key = gba_register(KEY_STATUS);
        if (! (key & KEY_DOWN)) {
            move_box(&b, x, y, COLOR_WHITE);
            if(y <= 160) y++;
        }
        //else                    draw_char(fb + 30, COLOR_BLACK, 25);
        if (! (key & KEY_UP)) {
            move_box(&b, x, y, COLOR_WHITE);
            if(y >= 0) y--;
        }
        //else                  draw_char(fb + 40, COLOR_BLACK, 24);
        if (! (key & KEY_LEFT)) {
            move_box(&b, x, y, COLOR_WHITE);
            if(x >= 0) x--;
        }
        //else                    draw_char(fb + 50, COLOR_BLACK, 27);
        if (! (key & KEY_RIGHT)) {
            move_box(&b, x, y, COLOR_WHITE);
            if(x <= 210) x++;
        }

        move_box(&ball, ballx, bally, COLOR_WHITE);
        ballx += dx;
        bally += dy;
        if(ballx <= 0 || ballx >= (240 - ball.width)) dx = -dx;
        if(bally <= 0 || bally >= (160 - ball.height)) dy = -dy;
        wait(40);
    }
}
