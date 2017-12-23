#include <SDL/SDL.h>
#include "types.h"

/* IF A KEY IS RELEASED */
BOOL isKeyRelease(Uint8 *, UINT);

/* IF A KEY IS CURRENTLY PRESSED */
BOOL isKeyPress(Uint8 *, UINT);

/* IF A KEY IS PRESSED 1 TIME */
BOOL isKeyPressed(Uint8 *, Uint8 *, UINT);
