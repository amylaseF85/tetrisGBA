//
// r g b . c
//
// RGB flag drawing program coded with C
//
// May 4, 2003 by Wataru Nishida (http://www.wnishida.com)
//

typedef unsigned short hword;		// Half word

#define VRAM		0x06000000	// VRAM frame buffer start address
#define gba_register(p)	*((volatile hword*) p)	// I/O register handling macro
#define LCD_CTRL	0x04000000	// LCD control
#define   LCD_BG2EN	0x0400		//   Enable BG2
#define   LCD_MODE3	3		//   Video mode 3
#define LCD_WIDTH	240		// 240 dots / horizontal line
#define LCD_HEIGHT	160		// 160 dots / vertical line
#define BGR(r, g, b)	((b << 10) + (g << 5) + r)

int main() {
  hword* ptr = (hword*) VRAM;		// Use VRAM as a frame buffer
  int i, j;

  // Initialize LCD

  gba_register(LCD_CTRL) = LCD_BG2EN | LCD_MODE3;	// Mode 3: Use BG 2

  // Draw RGB bands

  for (i = 0; i < (LCD_HEIGHT / 3); i++) {
    for (j = 0; j < LCD_WIDTH; j++)
       *(ptr++) = BGR(31, 0, 0);	// Red line
   }

  for (i = 0; i < (LCD_HEIGHT / 3); i++) {
    for (j = 0; j < LCD_WIDTH; j++)
       *(ptr++) = BGR(0, 31, 0);	// Blue line
   }

  for (i = 0; i < (LCD_HEIGHT / 3); i++) {
    for (j = 0; j < LCD_WIDTH; j++)
       *(ptr++) = BGR(0, 0, 31);	// Green line
   }

  // Loop forever

  while (1) ;
 }
