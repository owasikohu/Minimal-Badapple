#include "gba_types.h"
#include "erapi.h"

extern int __end[];

const u16 palette[] = { 0x0000, 0xFFFF };

const u8 hello[] = { 130, 103, 130, 133, 130, 140, 130, 140, 130, 143, 129, 64, 130, 151, 130, 143,
130, 146, 130, 140, 130, 132, 129, 73, 129, 73 }; //shift-jis

//これがないとDrawTextが正常に描画されない。は？
const unsigned short gfxSharedPal[4] __attribute__((aligned(4))) __attribute__((visibility("hidden")))= {
	0x7C1F,0x7FFF,0x281F,0x123B,
};

int main() {
  ERAPI_HANDLE_REGION region;
  u32 key, quit;
  // init
  ERAPI_FadeIn(1);
  ERAPI_InitMemory( (ERAPI_RAM_END - (u32)__end) >> 10);
  ERAPI_SetBackgroundMode(0);
  // palette
  ERAPI_SetBackgroundPalette(&palette[0], 0x00, 0x02);
  // region & text
  region = ERAPI_CreateRegion(0, 0, 0x01, 0x01, 0x1C, 0x03);
  ERAPI_SetTextColor(region, 0x01, 0x00);
  ERAPI_DrawText(region, 0x00, 0x00, hello);



  // loop
  quit = 0;
  while (quit == 0) {
    // read keys
    key = ERAPI_GetKeyStateRaw();
    // quit
    if (key & ERAPI_KEY_B) quit = 1;
    // render frame
    ERAPI_RenderFrame(1);
  }
  // exit
  return ERAPI_EXIT_TO_MENU;
}