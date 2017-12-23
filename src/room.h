#include <SDL/SDL.h>
#include "global.h"
#include "entity.h"
#include "types.h"

typedef struct Block
{
    CCHAR *sprite;
    SDL_Surface *surface;
    HITBOX hitbox;
} BLOCK;

/* INITIALIZE OUR BLOCK WITH MAP INDEX */
UINT initialize_block (struct Block *, CCHAR *, INT, INT);

/* FUNCTION FOR BIG COLLISION VERIFICATION */
BOOL is_in_collision(struct Player, UINT, UINT);

/* REPLACE THE PLAYER - COLLISION */
VOID replace_player (struct Player *, struct Block);

