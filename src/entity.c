#include <SDL/SDL.h>
#include "global.h"
#include "types.h"

typedef enum
{
    DOWN = 0,
    LEFT = 1,
    RIGHT = 2,
    UP = 3
} LOOKAT;

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

typedef struct Weapon
{
    ENTITY entity;
    BOOL is_created;
    UINT speed;
} WEAPON;

typedef struct Player
{
    ENTITY entity;
    UINT health;
    WEAPON *weapons;
} PLAYER;


SDL_Rect next_sprite (struct Entity e, LOOKAT index)
{
    SDL_Rect r;
    if (e.direction == HORIZONTAL)
    {
        r.x = e.width * index;
        r.y = 0;
        r.w = e.width;
        r.h = e.total_height;
    }
    else
    {
        r.x = 0;
        r.y = (e.height * index) % e.total_height;
        r.w = e.total_width;
        r.h = e.height;
    }
    return r;
}

UINT initialize_hitbox (struct Hitbox *h, SDL_Rect r, BOOL w)
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

UINT initialize_player (struct Player *p, ENTITY e, WEAPON *w)
{
    (*p).entity = e;
    (*p).weapons = w;
    (*p).health = NB_HEARTS; /* 3 HP */
    return 0;
}

UINT initialize_weapon(struct Weapon *w, ENTITY e)
{
    (*w).entity = e;
    (*w).is_created = false;
    (*w).speed = PROJECTILE_SPEED;
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

BOOL is_player_in_rect (struct Player p, UINT a, UINT b)
{
    if (p.entity.hitbox.hitbox.x >= a && p.entity.hitbox.hitbox.x + p.entity.width <= WIDTH - a &&
        p.entity.hitbox.hitbox.y >= 0 && p.entity.hitbox.hitbox.y + p.entity.height <= HEIGHT - b)
    {
        return true;
    }
    return false;
}

