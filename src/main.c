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
    initialize_hitbox(&tmp_hitbox, sdl_r(300, 400), true);
    initialize_entity(&tmp_entity,"player.png",55,86,55,86,HORIZONTAL,0,tmp_hitbox);
    initialize_player(&player,tmp_entity);

    ENTITY background;
    initialize_hitbox(&tmp_hitbox, sdl_r(0,0), true);
    initialize_entity(&background,"background.png",WIDTH,HEIGHT,WIDTH,HEIGHT,HORIZONTAL,0,tmp_hitbox);

    ENTITY loose_background;
    initialize_entity(&loose_background,"background_loose.png",WIDTH,HEIGHT,WIDTH,HEIGHT,HORIZONTAL,0,tmp_hitbox);

    ENTITY full_heart[NB_HEARTS];
    ENTITY empty_heart[NB_HEARTS];
    for (UINT i = 0; i < NB_HEARTS; i++)
    {
        initialize_hitbox(&tmp_hitbox, sdl_r(16+(i*50), HEIGHT-24-HEART_SIZE), true);
        initialize_entity(&full_heart[i],"full_heart.png",HEART_SIZE,HEART_SIZE,HEART_SIZE,HEART_SIZE,HORIZONTAL,0,tmp_hitbox);
        initialize_entity(&empty_heart[i],"empty_heart.png",HEART_SIZE,HEART_SIZE,HEART_SIZE,HEART_SIZE,HORIZONTAL,0,tmp_hitbox);
    }

    BLOCK block[2];
    initialize_block(&block[0], "block.png", 5, 3);
    initialize_block(&block[1], "block.png", 6, 3);

    /* MAIN LOOP */
    BOOL b = false;
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

        /* IF SOME KEYS ARE PRESSED */
        if (keyStates[SDLK_UP] && keyStates[SDLK_RIGHT])
        {
            up_right(&player);
        }
        else if (keyStates[SDLK_UP] && keyStates[SDLK_LEFT])
        {
            up_left(&player);
        }
        else if (keyStates[SDLK_DOWN] && keyStates[SDLK_LEFT])
        {
            down_left(&player);
        }
        else if (keyStates[SDLK_DOWN] && keyStates[SDLK_RIGHT])
        {
            down_right(&player);
        }
        else if (keyStates[SDLK_UP])
        {
            up(&player);
        }
        else if (keyStates[SDLK_DOWN])
        {
            down(&player);
        }
        else if (keyStates[SDLK_RIGHT])
        {
            right(&player);
        }
        else if (keyStates[SDLK_LEFT])
        {
            left(&player);
        }
        else if (old_keyStates[SDLK_SPACE] == 0 && keyStates[SDLK_SPACE] == 1) /* TEMPORARY FOR LOOSING HEALTH WITHOUT ENEMY */
        {
            player.health -= 1;
            return 5;
        }

        /* IF HE LOOSES */
        if (player.health <= 0)
        {
            loose = true;
        }

        /* REPLACE OUR PLAYER IF HE IS OUT OF THE BORDERS */
        replace_player(&player);
        replace_player_block(&player, block[0]);
        replace_player_block(&player, block[1]);
        /* DRAW */
        SDL_FillRect(s_screen, 0, SDL_MapRGB((*s_screen).format, 0, 0, 0)); // BLACK BACKGROUND
        /* BLIT ALL YOUR SURFACE HERE */
        if (loose == false)
            SDL_BlitSurface(background.surface, 0, s_screen, &background.hitbox.hitbox);
        else
            SDL_BlitSurface(loose_background.surface, 0, s_screen, &loose_background.hitbox.hitbox);
        SDL_BlitSurface(block[0].surface, 0, s_screen, &block[0].hitbox.hitbox);
        SDL_BlitSurface(block[1].surface, 0, s_screen, &block[1].hitbox.hitbox);
        for (UINT i = 0; i < NB_HEARTS; i++)
            SDL_BlitSurface(empty_heart[i].surface, 0, s_screen, &empty_heart[i].hitbox.hitbox);
        for (UINT i = 0; i < player.health; i++)
            SDL_BlitSurface(full_heart[i].surface, 0, s_screen, &full_heart[i].hitbox.hitbox);
        SDL_BlitSurface(player.entity.surface, 0, s_screen, &player.entity.hitbox.hitbox);
        /* REFRESH OUR SCREEN */
        SDL_Flip(s_screen);

        /* OLD KEYBOARD VALUE SAVED */
        for (UINT i = 0; keyStates[i]; i++)
            old_keyStates[i] = keyStates[i];
    }
    /* FREE ALL OF OUR STUFF HERE */
    SDL_FreeSurface(player.entity.surface);
    /* ALL IS COOL MAN */
    return EXIT_SUCCESS;
}
