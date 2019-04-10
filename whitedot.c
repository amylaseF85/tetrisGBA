#include "gba.h"

make_square(hword *fb){
    int x,y;
    for(x = 10; x < 20; x++){
        for(y = 10; y < 20; y++){
            *(fb + (LCD_WIDTH * y) + x) = BGR(0x1F, 0x1F, 0x1F);
        }
    }
}

main(){
    hword *fb = (hword*)VRAM;
    int x,y;

    gba_register(LCD_CTRL) = LCD_BG2EN | LCD_MODE3;
    make_square(fb);
    for(x = 10; x < 20; x++){
        for(y = 10; y < 20; y++){
            *(fb + (LCD_WIDTH * y) + x) = BGR(0x00, 0x1F, 0x1F);
            *(fb + (LCD_WIDTH * y) + x + 10) = BGR(0x1F, 0x1F, 0x1F);

        }
    }
    for(;;){}
}
