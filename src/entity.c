#include <SDL/SDL.h>
#include "global.h"
#include "types.h"

typedef enum
{
    HORIZONTAL,
    VERTICAL
} DIRECTION;

typedef struct Hitbox
{
    SDL_Rect hitbox;
    BOOL is_walkable;
} HITBOX;

typedef struct Entity
{
    CCHAR *sprite;
    SDL_Surface *surface;
    UINT width;
    UINT height;
    UINT total_width;
    UINT total_height;
    DIRECTION direction;
    UINT index;
    HITBOX hitbox;

} ENTITY;

typedef struct Player
{
    ENTITY entity;
    /*
    * TODO: include attack and others
    */
} PLAYER;

VOID next_sprite (ENTITY *e)
{
    if ((*e).direction == HORIZONTAL)
    {
        (*e).width *= 2;
        (*e).width %= (*e).total_width;
        (*e).index = ((*e).index + 1) % (UINT)((*e).total_width / (*e).width);
    }
    else
    {
        (*e).height *= 2;
        (*e).height %= (*e).total_height;
        (*e).index = ((*e).index + 1) % (UINT)((*e).total_height / (*e).height);
    }
}

UINT initialize_hitbox (HITBOX *h, SDL_Rect r, BOOL w)
{
    (*h).hitbox = r;
    (*h).is_walkable = w;
    return 0;
}


UINT initialize_entity (struct Entity *e, CCHAR *s, UINT w, UINT h, UINT t_w, UINT t_h, DIRECTION d, UINT i, struct Hitbox hb)
{
    (*e).sprite = s;
    (*e).surface = IMG_Load(s);
    (*e).width = w;
    (*e).height = h;
    (*e).total_width = t_w;
    (*e).total_height = t_h;
    (*e).direction = d;
    (*e).index = i;
    (*e).hitbox = hb;
    return 0;
}

UINT initialize_player (struct Player *p, ENTITY e)
{
    (*p).entity = e;
    return 0;
}

SDL_Rect sdl_r(UINT a, UINT b)
{
    SDL_Rect r;
    r.x = a;
    r.y = b;
    return r;
}

/* BASIC MOVEMENTS */
UINT up (struct Player *p)
{
    (*p).entity.hitbox.hitbox.y -= SPEED_PLAYER;
    return 0;
}

UINT down (struct Player *p)
{
    (*p).entity.hitbox.hitbox.y += SPEED_PLAYER;
    return 0;
}

UINT left (struct Player *p)
{
    (*p).entity.hitbox.hitbox.x -= SPEED_PLAYER;
    return 0;
}

UINT right (struct Player *p)
{
    (*p).entity.hitbox.hitbox.x += SPEED_PLAYER;
    return 0;
}

UINT up_right (struct Player *p)
{
    (*p).entity.hitbox.hitbox.y -= (INT)(3*SPEED_PLAYER/4);
    (*p).entity.hitbox.hitbox.x += (INT)(3*SPEED_PLAYER/4);
    return 0;
}

UINT up_left (struct Player *p)
{
    (*p).entity.hitbox.hitbox.y -= (INT)(3*SPEED_PLAYER/4);
    (*p).entity.hitbox.hitbox.x -= (INT)(3*SPEED_PLAYER/4);
    return 0;
}

UINT down_right (struct Player *p)
{
    (*p).entity.hitbox.hitbox.y += (INT)(3*SPEED_PLAYER/4);
    (*p).entity.hitbox.hitbox.x += (INT)(3*SPEED_PLAYER/4);
    return 0;
}

UINT down_left (struct Player *p)
{
    (*p).entity.hitbox.hitbox.y += (INT)(3*SPEED_PLAYER/4);
    (*p).entity.hitbox.hitbox.x -= (INT)(3*SPEED_PLAYER/4);
    return 0;
}

BOOL is_player_in_rect (struct Player p, UINT x, UINT y)
{
    if (p.entity.hitbox.hitbox.x >= x && p.entity.hitbox.hitbox.x + p.entity.width <= WIDTH - x)
    {
        if (p.entity.hitbox.hitbox.y >= 0 && p.entity.hitbox.hitbox.y + p.entity.height <= HEIGHT - y)
        {
            return true;
        }
    }
    return false;
}

VOID replace_player (struct Player *p)
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
}
