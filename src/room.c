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

UINT initialize_block (struct Block *b, CCHAR *s, INT indexX, INT indexY)
{
    (*b).sprite = s;
    (*b).surface = IMG_Load(s);
    (*b).hitbox.hitbox = sdl_r(((indexX * BLOCK_WIDTH) % (WIDTH-23-23)) + 23,((indexY * BLOCK_HEIGHT) % (HEIGHT-42-42)) + 42);
    /* MAKE SURE THE BLOCK IS NOT WALKABLE */
    (*b).hitbox.is_walkable = false;
    return 0;
}

BOOL is_in_collision (struct Player p, UINT a, UINT b)
{
    if (is_player_in_rect(p,a,b))
        return true;
    return false;
}


VOID replace_player (struct Player *p, struct Block *b)
{
    /* SQUARE:
    *  x=23         y=0         (top left)
    *  x=WIDTH-23   y=0         (top right)
    *  x=23         y=HEIGHT-42 (bot left)
    *  x=WIDTH-23   y=HEIGHT-42 (bot right)
    */

    /* X SIDE */
    if ((*p).entity.hitbox.hitbox.x < 23)
    {
        (*p).entity.hitbox.hitbox.x = 23;
    }
    if ((*p).entity.hitbox.hitbox.x + (*p).entity.width > WIDTH - 23)
    {
        (*p).entity.hitbox.hitbox.x = WIDTH - 23 - (*p).entity.width;
    }

    /* Y SIDE */
    if ((*p).entity.hitbox.hitbox.y < 0)
    {
        (*p).entity.hitbox.hitbox.y = 0;
    }
    if ((*p).entity.hitbox.hitbox.y + (*p).entity.height > HEIGHT - 42)
    {
        (*p).entity.hitbox.hitbox.y = HEIGHT - 42 - (*p).entity.height;
    }

    /* BLOCK SIDE */
    for (INT i = 0; i < 2; i++)
    {
        /* LEFT SIDE */
        if ((*p).entity.hitbox.hitbox.x + (*p).entity.width > (*b[i]).hitbox.hitbox.x && (*p).entity.hitbox.hitbox.x <= (*b[i]).hitbox.hitbox.x + SPEED_PLAYER &&
            (*p).entity.hitbox.hitbox.y + (*p).entity.height + SPEED_PLAYER > (*b[i]).hitbox.hitbox.y && (*p).entity.hitbox.hitbox.y - SPEED_PLAYER <= (*b[i]).hitbox.hitbox.y + BLOCK_HEIGHT/2)
        {
            (*p).entity.hitbox.hitbox.x -= SPEED_PLAYER;
        }

        /* RIGHT SIDE */
        if ((*p).entity.hitbox.hitbox.x < (*b[i]).hitbox.hitbox.x + BLOCK_WIDTH && (*p).entity.hitbox.hitbox.x >= (*b[i]).hitbox.hitbox.x + BLOCK_WIDTH - SPEED_PLAYER &&
            (*p).entity.hitbox.hitbox.y + (*p).entity.height + SPEED_PLAYER > (*b[i]).hitbox.hitbox.y && (*p).entity.hitbox.hitbox.y - SPEED_PLAYER <= (*b[i]).hitbox.hitbox.y + BLOCK_HEIGHT/2)
        {
            (*p).entity.hitbox.hitbox.x += SPEED_PLAYER;
        }

        /* TOP SIDE */
        if ((*p).entity.hitbox.hitbox.x + (*p).entity.width > (*b[i]).hitbox.hitbox.x && (*p).entity.hitbox.hitbox.x <= (*b[i]).hitbox.hitbox.x + BLOCK_WIDTH &&
            (*p).entity.hitbox.hitbox.y + (*p).entity.height >= (*b[i]).hitbox.hitbox.y && (*p).entity.hitbox.hitbox.y + (*p).entity.height <= (*b[i]).hitbox.hitbox.y + SPEED_PLAYER)
        {
            (*p).entity.hitbox.hitbox.y -= SPEED_PLAYER;
        }

        /* BOT SIDE */
        if ((*p).entity.hitbox.hitbox.x + (*p).entity.width > (*b[i]).hitbox.hitbox.x && (*p).entity.hitbox.hitbox.x <= (*b[i]).hitbox.hitbox.x + BLOCK_WIDTH &&
            (*p).entity.hitbox.hitbox.y >= (*b[i]).hitbox.hitbox.y + BLOCK_HEIGHT/2 - SPEED_PLAYER && (*p).entity.hitbox.hitbox.y <= (*b[i]).hitbox.hitbox.y + BLOCK_HEIGHT/2)
        {
            (*p).entity.hitbox.hitbox.y += SPEED_PLAYER;
        }
    }
}