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

/* REPLACE THE ENTITY - COLLISION */
BOOL replace_entity (struct Entity *);

/* REPLACE THE ENTITY IF HE COLLIDE A BLOCK */
BOOL replace_entity_block (struct Entity *, struct Block );

/* MOVE OUR PROJECTILES */
VOID projectile_update (struct Weapon *);

/* IF WE CAN CREATE A PROJECTILE */
BOOL can_create_projectile (UINT *);

/* RETURN THE COORDS FOR PROJECTILES */
UINT projectile_x (struct Player);
UINT projectile_y (struct Player);

/* CREATE A PROJECTILE */
VOID create_new_projectile (struct Player *);
