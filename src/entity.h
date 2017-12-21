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
    UINT x;
    UINT y;
    UINT (*up)(struct Player*);
    UINT (*down)(struct Player*);
    UINT (*left)(struct Player*);
    UINT (*right)(struct Player*);
} PLAYER;

/* TAKE THE NEXT SPRITE */
VOID next_sprite (struct Entity*);

/* INITIALIZE A HITBOX */
UINT initialize_hitbox (struct Hitbox *, SDL_Rect, BOOL);

/* INITIALIZE AN ENTITY */
UINT initialize_entity (struct Entity *, CCHAR *, UINT, UINT, UINT, UINT, DIRECTION, UINT, struct Hitbox);

/* INITIALIZE A PLAYER */
UINT initialize_player (struct Player *, struct Entity);

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

/* REPLACE THE PLAYER - COLLISION */
VOID replace_player (struct Player *);
