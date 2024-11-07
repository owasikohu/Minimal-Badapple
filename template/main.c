#include "def.h"
#include "erapi.h"

extern int __end[];

const u16 palette[] = { 0x0000, 0xFFFF };

const unsigned char hello_world[] = {
    0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x21, 0x21, 0x00 // NULL終端
};


int main() {
  ERAPI_HANDLE_REGION region;
  u32 quit;

  ERAPI_FadeIn(1);
  ERAPI_InitMemory((ERAPI_RAM_END - (u32)__end) >> 10);
  ERAPI_SetBackgroundMode(0);


  ERAPI_SetBackgroundPalette(&palette[0], 0x00, 0x02);

  region = ERAPI_CreateRegion(0, 0, 0x01, 0x01, 0x1C, 0x03);
  ERAPI_SetTextColor(region, 0x01, 0x00);


  ERAPI_DrawText(region, 0x50, 0x08, hello_world);

  quit = 0;
  while (quit == 0)
  {
    u32 key = ERAPI_GetKeyStateRaw();
    if (key & ERAPI_KEY_B) quit = 1;
    ERAPI_RenderFrame(1);
  }

  return ERAPI_EXIT_TO_MENU;
}
