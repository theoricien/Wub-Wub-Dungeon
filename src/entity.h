#include <SDL/SDL.h>
#include "global.h"
#include "types.h"

typedef enum
{
    UP,
    DOWN,
    LEFT,
    RIGHT
} LOOKAT;

typedef enum
{
    HORIZONTAL,
    VERTICAL
} DIRECTION;

typedef struct Hitbox
{
    SDL_Rect hitbox;
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
    LOOKAT lookat;
    UINT index;
    HITBOX hitbox;

} ENTITY;

typedef struct Weapon
{
    ENTITY entity;
    BOOL is_created;
} WEAPON;

typedef struct Player
{
    ENTITY entity;
    UINT health;
    WEAPON *weapons;
} PLAYER;

/* TAKE THE NEXT SPRITE */
SDL_Rect next_sprite (struct Entity, LOOKAT);

/* INITIALIZE A HITBOX */
UINT initialize_hitbox (struct Hitbox *, SDL_Rect);

/* INITIALIZE AN ENTITY */
UINT initialize_entity (struct Entity *, CCHAR *, UINT, UINT, UINT, UINT, DIRECTION, UINT, struct Hitbox);

/* INITIALIZE A PLAYER */
UINT initialize_player (struct Player *, struct Entity, struct Weapon *);

/* INITIALIZE A WEAPON */
UINT initialize_weapon(struct Weapon *, struct Entity);

/* SHORTCUT TO RETURN A SIMPLE SDL_Rect */
SDL_Rect sdl_r (UINT, UINT);

/* DIRECTION OF A PLAYER */
UINT up (struct Player *);
UINT down (struct Player *);
UINT left (struct Player *);
UINT right (struct Player *);
UINT up_right (struct Player *);
UINT up_left (struct Player *);
UINT down_right (struct Player *);
UINT down_left (struct Player *);

/* IS THE PLAYER IN THE ROOM */
BOOL is_player_in_rect (struct Player, UINT, UINT);
