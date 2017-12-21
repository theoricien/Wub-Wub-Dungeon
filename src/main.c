#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdbool.h>
#include "global.h"
#include "types.h"
#include "entity.h"



INT main (INT argc, CHAR **argv)
{
    /* SDL INITILIZATION */
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface* s_screen = SDL_SetVideoMode(WIDTH, HEIGHT, 16, SDL_HWSURFACE|SDL_DOUBLEBUF);

    /* INITIALIZATION */
    ENTITY tmp_entity;
    HITBOX tmp_hitbox;
    Uint8 *keyStates = NULL;

    PLAYER player;
    initialize_hitbox(&tmp_hitbox, sdl_r(WIDTH/2, HEIGHT/2), true);
    initialize_entity(&tmp_entity,"player.png",55,86,55,86,HORIZONTAL,0,tmp_hitbox);
    initialize_player(&player,tmp_entity);

    ENTITY background;
    initialize_hitbox(&tmp_hitbox, sdl_r(0,0), true);
    initialize_entity(&background,"background.png",WIDTH,HEIGHT,WIDTH,HEIGHT,HORIZONTAL,0,tmp_hitbox);

    /* MAIN LOOP */
    BOOL b = false;
    while (!b)
    {

        /* EVENT GESTION */
        SDL_Event event;
        SDL_PollEvent(&event);
        keyStates = SDL_GetKeyState(NULL);
        switch (event.type)
        {
            case SDL_QUIT:
                b = true;
                break;

            /* IF KEY IS PRESSED */
            case SDL_KEYDOWN:
                if (keyStates[SDLK_UP] && keyStates[SDLK_RIGHT])
                {
                    if (is_player_in_rect(player, 23, 42))
                        up_right(&player);
                    if (!is_player_in_rect(player, 23, 42))
                        replace_player(&player);
                    break;
                }
                else if (keyStates[SDLK_UP] && keyStates[SDLK_LEFT])
                {
                    if (is_player_in_rect(player, 23, 42))
                        up_left(&player);
                    if (!is_player_in_rect(player, 23, 42))
                        replace_player(&player);
                    break;
                }
                else if (keyStates[SDLK_DOWN] && keyStates[SDLK_LEFT])
                {
                    if (is_player_in_rect(player, 23, 42))
                        down_left(&player);
                    if (!is_player_in_rect(player, 23, 42))
                        replace_player(&player);
                    break;
                }
                else if (keyStates[SDLK_DOWN] && keyStates[SDLK_RIGHT])
                {
                    if (is_player_in_rect(player, 23, 42))
                        down_right(&player);
                    if (!is_player_in_rect(player, 23, 42))
                        replace_player(&player);
                    break;
                }
                else if (keyStates[SDLK_UP])
                {
                    if (is_player_in_rect(player, 23, 42))
                        up(&player);
                    if (!is_player_in_rect(player, 23, 42))
                        replace_player(&player);
                    break;
                }
                else if (keyStates[SDLK_DOWN])
                {
                    if (is_player_in_rect(player, 23, 42))
                        down(&player);
                    if (!is_player_in_rect(player, 23, 42))
                        replace_player(&player);
                    break;
                }
                else if (keyStates[SDLK_RIGHT])
                {
                    if (is_player_in_rect(player, 23, 42))
                        right(&player);
                    if (!is_player_in_rect(player, 23, 42))
                        replace_player(&player);
                    break;
                }
                else if (keyStates[SDLK_LEFT])
                {
                    if (is_player_in_rect(player, 23, 42))
                        left(&player);
                    if (!is_player_in_rect(player, 23, 42))
                        replace_player(&player);
                    break;
                }
                break;
        }

        /* DRAW */
        SDL_FillRect(s_screen, 0, SDL_MapRGB((*s_screen).format, 0, 0, 0)); // BLACK BACKGROUND
        /* BLIT ALL YOUR SURFACE HERE */
        SDL_BlitSurface(background.surface, 0, s_screen, &background.hitbox.hitbox);
        SDL_BlitSurface(player.entity.surface, 0, s_screen, &player.entity.hitbox.hitbox);
        /* REFRESH OUR SCREEN */
        SDL_Flip(s_screen);
    }
    /* FREE ALL OF OUR STUFF HERE */
    SDL_FreeSurface(player.entity.surface);
    /* ALL IS COOL MAN */
    return EXIT_SUCCESS;
}
