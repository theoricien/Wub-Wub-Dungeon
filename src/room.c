#include <SDL/SDL.h>
#include <stdio.h>
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
    return 0;
}

BOOL is_in_collision (struct Player p, UINT a, UINT b)
{
    if (is_player_in_rect(p,a,b))
        return true;
    return false;
}


BOOL replace_entity (struct Entity *p)
{
    /* SQUARE:
    *  x=23         y=0         (top left)
    *  x=WIDTH-23   y=0         (top right)
    *  x=23         y=HEIGHT-42 (bot left)
    *  x=WIDTH-23   y=HEIGHT-42 (bot right)
    */

    BOOL res = false;

    /* X SIDE */
    if ((*p).hitbox.hitbox.x < 23)
    {
        (*p).hitbox.hitbox.x = 23;
        res = true;
    }
    if ((*p).hitbox.hitbox.x + (*p).width > WIDTH - 23)
    {
        (*p).hitbox.hitbox.x = WIDTH - 23 - (*p).width;
        res = true;
    }

    /* Y SIDE */
    if ((*p).hitbox.hitbox.y < 0)
    {
        (*p).hitbox.hitbox.y = 0;
        res = true;
    }
    if ((*p).hitbox.hitbox.y + (*p).height > HEIGHT - 42)
    {
        (*p).hitbox.hitbox.y = HEIGHT - 42 - (*p).height;
        res = true;
    }
    return res;
}

BOOL replace_entity_block (struct Entity *p, struct Block b)
{
    /* FIRST IF: CLASSIC MOVEMENT (UP,RIGHT,LEFT,DOWN) */
    /* SECOND IF: DIAGONAL MOVEMENT */

    /* BLOCK SIDE */
    /* LEFT SIDE */
    BOOL res = false;
    if ((*p).hitbox.hitbox.x + (*p).width > b.hitbox.hitbox.x + SPEED_PLAYER_D && (*p).hitbox.hitbox.x <= b.hitbox.hitbox.x + SPEED_PLAYER &&
        (*p).hitbox.hitbox.y + (*p).height > b.hitbox.hitbox.y + SPEED_PLAYER && (*p).hitbox.hitbox.y < b.hitbox.hitbox.y + BLOCK_HEIGHT/2 - SPEED_PLAYER)
    {
        (*p).hitbox.hitbox.x -= SPEED_PLAYER;
        res = true;
    }

    if ((*p).hitbox.hitbox.x + (*p).width > b.hitbox.hitbox.x && (*p).hitbox.hitbox.x <= b.hitbox.hitbox.x &&
        (*p).hitbox.hitbox.y + (*p).height > b.hitbox.hitbox.y + SPEED_PLAYER_D && (*p).hitbox.hitbox.y < b.hitbox.hitbox.y + BLOCK_HEIGHT/2 - SPEED_PLAYER_D)
    {
        (*p).hitbox.hitbox.x -= SPEED_PLAYER_D;
        res = true;
    }
    /* RIGHT SIDE */
    if ((*p).hitbox.hitbox.x >= b.hitbox.hitbox.x + BLOCK_WIDTH - SPEED_PLAYER && (*p).hitbox.hitbox.x < b.hitbox.hitbox.x + BLOCK_WIDTH - SPEED_PLAYER_D &&
        (*p).hitbox.hitbox.y + (*p).height > b.hitbox.hitbox.y + SPEED_PLAYER_D && (*p).hitbox.hitbox.y < b.hitbox.hitbox.y + BLOCK_HEIGHT/2 - SPEED_PLAYER_D)
    {
        (*p).hitbox.hitbox.x += SPEED_PLAYER;
        res = true;
    }

    if ((*p).hitbox.hitbox.x >= b.hitbox.hitbox.x + BLOCK_WIDTH - SPEED_PLAYER_D && (*p).hitbox.hitbox.x < b.hitbox.hitbox.x + BLOCK_WIDTH &&
        (*p).hitbox.hitbox.y + (*p).height > b.hitbox.hitbox.y + SPEED_PLAYER_D && (*p).hitbox.hitbox.y < b.hitbox.hitbox.y + BLOCK_HEIGHT/2 - SPEED_PLAYER_D)
    {
        (*p).hitbox.hitbox.x += SPEED_PLAYER_D;
        res = true;
    }
    /* TOP SIDE */
    if ((*p).hitbox.hitbox.x + (*p).width > b.hitbox.hitbox.x && (*p).hitbox.hitbox.x <= b.hitbox.hitbox.x + BLOCK_WIDTH)
    {
        if ((*p).hitbox.hitbox.y + (*p).height > b.hitbox.hitbox.y + SPEED_PLAYER_D && (*p).hitbox.hitbox.y + (*p).height <= b.hitbox.hitbox.y + SPEED_PLAYER)
        {
            (*p).hitbox.hitbox.y -= SPEED_PLAYER;
            res = true;
        }

        if ((*p).hitbox.hitbox.y + (*p).height > b.hitbox.hitbox.y && (*p).hitbox.hitbox.y + (*p).height <= b.hitbox.hitbox.y + SPEED_PLAYER_D)
        {
            (*p).hitbox.hitbox.y -= SPEED_PLAYER_D;
            res = true;
        }
        /* BOT SIDE */
        if ((*p).hitbox.hitbox.y >= b.hitbox.hitbox.y + BLOCK_HEIGHT/2 - SPEED_PLAYER && (*p).hitbox.hitbox.y < b.hitbox.hitbox.y + BLOCK_HEIGHT/2 - SPEED_PLAYER_D)
        {
            (*p).hitbox.hitbox.y += SPEED_PLAYER;
            res = true;
        }

        if ((*p).hitbox.hitbox.y >= b.hitbox.hitbox.y + BLOCK_HEIGHT/2 - SPEED_PLAYER_D && (*p).hitbox.hitbox.y < b.hitbox.hitbox.y + BLOCK_HEIGHT/2)
        {
            (*p).hitbox.hitbox.y += SPEED_PLAYER_D;
            res = true;
        }
    }
    return res;
}

BOOL replace_projectile_block (struct Entity *p, struct Block b)
{
    /* TOP & BOT SIDE */
    if ((*p).hitbox.hitbox.x + (*p).width > b.hitbox.hitbox.x && // LEFT
        (*p).hitbox.hitbox.x <= b.hitbox.hitbox.x + BLOCK_WIDTH) // RIGHT
    {
        if ((*p).hitbox.hitbox.y + (*p).height/3 > b.hitbox.hitbox.y && (*p).hitbox.hitbox.y + (*p).height/2 < b.hitbox.hitbox.y + BLOCK_HEIGHT)
        {
            return true;
        }
    }
    return false;
}

VOID projectile_update (struct Weapon *w)
{
    for (UINT i = 0; i < NB_PROJECTILE; i++)
    {
        if (w[i].is_created)
        {
            if (w[i].entity.lookat == UP)
                w[i].entity.hitbox.hitbox.y -= PROJECTILE_SPEED;
            else if (w[i].entity.lookat == LEFT)
                w[i].entity.hitbox.hitbox.x -= PROJECTILE_SPEED;
            else if (w[i].entity.lookat == DOWN)
                w[i].entity.hitbox.hitbox.y += PROJECTILE_SPEED;
            else
                w[i].entity.hitbox.hitbox.x += PROJECTILE_SPEED;
        }
    }
}

BOOL can_create_projectile (UINT *curr_time)
{
    if (SDL_GetTicks() - *curr_time > PROJECTILE_LATENCY)
    {
        *curr_time = SDL_GetTicks();
        return true;
    }
    return false;
}

UINT projectile_x (struct Player p)
{
    if (p.entity.lookat == UP || p.entity.lookat == DOWN)
        return p.entity.hitbox.hitbox.x + p.entity.width/2 - PROJECTILE_SIZE/2;
    if (p.entity.lookat == LEFT)
        return p.entity.hitbox.hitbox.x - PROJECTILE_SIZE/2;
    return p.entity.hitbox.hitbox.x + p.entity.width - PROJECTILE_SIZE/2;
}

UINT projectile_y (struct Player p)
{
    if (p.entity.lookat == LEFT || p.entity.lookat == RIGHT)
        return p.entity.hitbox.hitbox.y;
    if (p.entity.lookat == UP)
        return p.entity.hitbox.hitbox.y - PROJECTILE_SIZE/2;
    return p.entity.hitbox.hitbox.y + PROJECTILE_SIZE/2;
}

VOID create_new_projectile (struct Player *p)
{
    for (UINT i = 0; i < NB_PROJECTILE; i++)
    {
        if ((*p).weapons[i].is_created == false)
        {
            HITBOX tmp_;
            ENTITY tmp;
            UINT x,y;
            x = projectile_x(*p);
            y = projectile_y(*p);
            initialize_hitbox(&tmp_,sdl_r(x,y));
            initialize_entity(&tmp,"ball.png",PROJECTILE_SIZE,PROJECTILE_SIZE,PROJECTILE_SIZE,PROJECTILE_SIZE,HORIZONTAL,0,tmp_);
            (*p).weapons[i].entity = tmp;
            (*p).weapons[i].entity.lookat = (*p).entity.lookat;
            (*p).weapons[i].is_created = true;
            break;
        }
    }
}

VOID delete_projectile (struct Hitbox *tmp_hitbox, struct Entity *tmp_entity, struct Player *player, UINT j)
{
    initialize_hitbox(tmp_hitbox, sdl_r(-PROJECTILE_SIZE, -PROJECTILE_SIZE));
    initialize_entity(tmp_entity, "ball.png",PROJECTILE_SIZE,PROJECTILE_SIZE,PROJECTILE_SIZE,PROJECTILE_SIZE,HORIZONTAL,0,*tmp_hitbox);
    player->weapons[j].entity = *tmp_entity;
    player->weapons[j].is_created = false;
}
