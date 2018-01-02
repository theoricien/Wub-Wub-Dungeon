#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdbool.h>
#include "room.h"
#include "input.h"

INT main (INT argc, CHAR **argv)
{
    /* SDL INITILIZATION */
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface* s_screen = SDL_SetVideoMode(WIDTH, HEIGHT, 16, SDL_HWSURFACE|SDL_DOUBLEBUF);

    /* INITIALIZATION */
    ENTITY tmp_entity;
    HITBOX tmp_hitbox;
    Uint8 *keyStates = SDL_GetKeyState(NULL);
    Uint8 *old_keyStates = SDL_GetKeyState(NULL);
    BOOL loose = false;

    PLAYER player;
    /* LIST CONCEPT IS BULLSHIT WHEN YOU HAVE MATHS */
    WEAPON projectiles[NB_PROJECTILE];
    initialize_hitbox(&tmp_hitbox, sdl_r(-PROJECTILE_SIZE, -PROJECTILE_SIZE));
    initialize_entity(&tmp_entity, "ball.png",PROJECTILE_SIZE,PROJECTILE_SIZE,PROJECTILE_SIZE,PROJECTILE_SIZE,HORIZONTAL,0,tmp_hitbox);
    for (UINT i = 0; i < NB_PROJECTILE; i++)
    {
        projectiles[i].entity = tmp_entity;
        projectiles[i].is_created = false;
    }
    SDL_Rect player_direction;
    initialize_hitbox(&tmp_hitbox, sdl_r(300, 400));
    initialize_entity(&tmp_entity,"player.png",55,86,220,86,HORIZONTAL,0,tmp_hitbox);
    initialize_player(&player,tmp_entity,projectiles);

    ENTITY background;
    initialize_hitbox(&tmp_hitbox, sdl_r(0,0));
    initialize_entity(&background,"background.png",WIDTH,HEIGHT,WIDTH,HEIGHT,HORIZONTAL,0,tmp_hitbox);

    ENTITY loose_background;
    initialize_entity(&loose_background,"background_loose.png",WIDTH,HEIGHT,WIDTH,HEIGHT,HORIZONTAL,0,tmp_hitbox);

    ENTITY full_heart[NB_HEARTS];
    ENTITY empty_heart[NB_HEARTS];
    for (UINT i = 0; i < NB_HEARTS; i++)
    {
        initialize_hitbox(&tmp_hitbox, sdl_r(16+(i*50), HEIGHT-24-HEART_SIZE));
        initialize_entity(&full_heart[i],"full_heart.png",HEART_SIZE,HEART_SIZE,HEART_SIZE,HEART_SIZE,HORIZONTAL,0,tmp_hitbox);
        initialize_entity(&empty_heart[i],"empty_heart.png",HEART_SIZE,HEART_SIZE,HEART_SIZE,HEART_SIZE,HORIZONTAL,0,tmp_hitbox);
    }

    BLOCK block[NB_BLOCK];
    initialize_block(&block[0], "block.png", 5, 3);
    initialize_block(&block[1], "block.png", 6, 3);

    /* MAIN LOOP */
    BOOL b = false;
    UINT curr_time = SDL_GetTicks();
    UINT projectile_time = SDL_GetTicks();
    while (!b)
    {
        /* EVENT GESTION */
        SDL_Event event;
        SDL_PollEvent(&event);
        switch (event.type)
        {
            case SDL_QUIT:
                b = true;
                break;

        }
        /* KEYBOARD VALUES */
        keyStates = SDL_GetKeyState(NULL);

        /* IF YOU DON'T LOOSE */
        if (loose == false)
        {
            /* IF SOME KEYS ARE PRESSED */
            if (keyStates[SDLK_w] && keyStates[SDLK_d])
            {
                up_right(&player);
                player.entity.lookat = UP;
            }
            else if (keyStates[SDLK_w] && keyStates[SDLK_a])
            {
                up_left(&player);
                player.entity.lookat = LEFT;
            }
            else if (keyStates[SDLK_s] && keyStates[SDLK_a])
            {
                down_left(&player);
                player.entity.lookat = DOWN;
            }
            else if (keyStates[SDLK_s] && keyStates[SDLK_d])
            {
                down_right(&player);
                player.entity.lookat = RIGHT;
            }
            else if (keyStates[SDLK_w])
            {
                up(&player);
                player.entity.lookat = UP;
            }
            else if (keyStates[SDLK_s])
            {
                down(&player);
                player.entity.lookat = DOWN;
            }
            else if (keyStates[SDLK_d])
            {
                right(&player);
                player.entity.lookat = RIGHT;
            }
            else if (keyStates[SDLK_a])
            {
                left(&player);
                player.entity.lookat = LEFT;
            }
            /* PROJECTILE KEYS */
            if (keyStates[SDLK_UP])
            {
                player.entity.lookat = UP;
                if (can_create_projectile(&projectile_time))
                    create_new_projectile(&player);
            }
            else if (keyStates[SDLK_LEFT])
            {
                player.entity.lookat = LEFT;
                if (can_create_projectile(&projectile_time))
                    create_new_projectile(&player);
            }
            else if (keyStates[SDLK_DOWN])
            {
                player.entity.lookat = DOWN;
                if (can_create_projectile(&projectile_time))
                    create_new_projectile(&player);
            }
            else if (keyStates[SDLK_RIGHT])
            {
                player.entity.lookat = RIGHT;
                if (can_create_projectile(&projectile_time))
                    create_new_projectile(&player);
            }
        }

        /* IF HE LOOSES */
        if (player.health <= 0)
        {
            loose = true;
        }

        /* REPLACE OUR PLAYER IF HE IS OUT OF THE BORDERS */
        replace_entity(&player.entity);

        /* REPLACE PLAYER IF HE COLLIDE A BLOCK */
        for (UINT i = 0; i < NB_BLOCK; i++)
            replace_entity_block(&player.entity, block[i]);

        /* UPDATE PROJECTILES */
        projectile_update(player.weapons);

        /* DELETE SOME PROJECTILES IF THEY COLLIDE SOMETHING */
        for (UINT i = 0; i < NB_BLOCK; i++)
        {
            for (UINT j = 0; j < NB_PROJECTILE; j++)
            {
                if (replace_entity_block(&player.weapons[j].entity, block[i]))
                {
                    initialize_hitbox(&tmp_hitbox, sdl_r(-PROJECTILE_SIZE, -PROJECTILE_SIZE));
                    initialize_entity(&tmp_entity, "ball.png",PROJECTILE_SIZE,PROJECTILE_SIZE,PROJECTILE_SIZE,PROJECTILE_SIZE,HORIZONTAL,0,tmp_hitbox);
                    player.weapons[j].entity = tmp_entity;
                    player.weapons[j].is_created = false;
                }
                if (replace_entity(&player.weapons[j].entity))
                {
                    initialize_hitbox(&tmp_hitbox, sdl_r(-PROJECTILE_SIZE, -PROJECTILE_SIZE));
                    initialize_entity(&tmp_entity, "ball.png",PROJECTILE_SIZE,PROJECTILE_SIZE,PROJECTILE_SIZE,PROJECTILE_SIZE,HORIZONTAL,0,tmp_hitbox);
                    player.weapons[j].entity = tmp_entity;
                    player.weapons[j].is_created = false;
                }
            }
        }

        /* DRAW */
        SDL_FillRect(s_screen, 0, SDL_MapRGB((*s_screen).format, 0, 0, 0)); // BLACK BACKGROUND

        /* BLIT ALL YOUR SURFACE HERE */
        SDL_BlitSurface(background.surface, 0, s_screen, &background.hitbox.hitbox);
        SDL_BlitSurface(block[0].surface, 0, s_screen, &block[0].hitbox.hitbox);
        SDL_BlitSurface(block[1].surface, 0, s_screen, &block[1].hitbox.hitbox);
        if (loose == true)
            SDL_BlitSurface(loose_background.surface, 0, s_screen, &loose_background.hitbox.hitbox);
        for (UINT i = 0; i < NB_PROJECTILE; i++)
        {
            if (player.weapons[i].is_created)
                SDL_BlitSurface(player.weapons[i].entity.surface, 0, s_screen, &player.weapons[i].entity.hitbox.hitbox);
        }
        player_direction = next_sprite(player.entity, player.entity.lookat);
        SDL_BlitSurface(player.entity.surface, &player_direction, s_screen, &player.entity.hitbox.hitbox);
        for (UINT i = 0; i < NB_HEARTS; i++)
            SDL_BlitSurface(empty_heart[i].surface, 0, s_screen, &empty_heart[i].hitbox.hitbox);
        for (UINT i = 0; i < player.health; i++)
            SDL_BlitSurface(full_heart[i].surface, 0, s_screen, &full_heart[i].hitbox.hitbox);

        /* REFRESH OUR SCREEN */
        SDL_Flip(s_screen);

        /* OLD KEYBOARD VALUE SAVED */
        for (UINT i = 0; keyStates[i]; i++)
            old_keyStates[i] = keyStates[i];

        /* FRAME PER SECOND LIMIT */
        if (curr_time + SDL_GetTicks() > FRAME_PER_SECOND)
        {
            SDL_Delay(FRAME_PER_SECOND);
            curr_time = SDL_GetTicks();
        }
    }
    /* FREE ALL OF OUR STUFF HERE */
    SDL_FreeSurface(player.entity.surface);
    /* ALL IS COOL MAN */
    return EXIT_SUCCESS;
}
