#include <SDL/SDL.h>
#include "types.h"

BOOL isKeyRelease(Uint8 *key, UINT keycode)
{
    if (key[keycode])
        return false;
    return true;
}

BOOL isKeyPress(Uint8 *key, UINT keycode)
{
    if (key[keycode])
        return true;
    return false;
}

BOOL isKeyPressed(Uint8 *curr_key, Uint8 *old_key, UINT keycode)
{
    return isKeyRelease(old_key, keycode) && isKeyPress(curr_key, keycode);
}
