//
//  menu.c
//  Duet
//
//  Created by achraf on 23/08/15.
//  Copyright © 2015 achraf. All rights reserved.
//

#include "menu.h"

SDL_Texture *loadTexture1(const char filepath[], SDL_Renderer *renderTarget)
{
    SDL_Texture *texture;
    SDL_Surface *surface = IMG_Load(filepath);
    texture = SDL_CreateTextureFromSurface(renderTarget, surface);
    SDL_FreeSurface(surface);
    return texture;
}



void runmenu(boolean *programruns, boolean *mainmenu,SDL_Renderer *rendertarget,option * select){
    SDL_Event e;
    const Uint8 *keystate;
    int currenttick;
    SDL_Rect Gametitleposition = { 0, 0, 440, 480 }, startgameposition = { 0, 120, 440, 120 }, exitGamePosition = { 0, 240, 440, 120 };
    SDL_Texture *gameTitle = NULL, *startGame = NULL, *exitGAME = NULL;
    
    gameTitle = loadTexture1("DUET.png", rendertarget);
    startGame = loadTexture1("startGamepressed.png", rendertarget);
    exitGAME = loadTexture1("exitnotpressed.png", rendertarget);
    startGame = loadTexture1("startGamepressed.png", rendertarget);
    exitGAME = loadTexture1("exitnotpressed.png", rendertarget);
    gameTitle = loadTexture1("DUET.png", rendertarget);
    update(gameTitle, Gametitleposition);
    update(startGame, startgameposition);
    update(exitGAME, exitGamePosition);
    SDL_RenderPresent(rendertarget);
    
    while (*mainmenu == yes) {
        currenttick = SDL_GetTicks();
        
        
        SDL_RenderClear(rendertarget);
        switch (*select) {
            case startgame:
                SDL_DestroyTexture(gameTitle);
                SDL_DestroyTexture(startGame);
                SDL_DestroyTexture(exitGAME);
                startGame = loadTexture1("startGamepressed.png", rendertarget);
                exitGAME = loadTexture1("exitnotpressed.png", rendertarget);
                gameTitle = loadTexture1("DUET.png", rendertarget);
                update(gameTitle, Gametitleposition);
                update(startGame, startgameposition);
                update(exitGAME, exitGamePosition);
                SDL_RenderPresent(rendertarget);
                //                SDL_DestroyTexture(gameTitle);
                //                SDL_DestroyTexture(startGame);
                //                SDL_DestroyTexture(exitGAME);
                break;
                
            case exitgame:
                
                SDL_DestroyTexture(gameTitle);
                SDL_DestroyTexture(startGame);
                SDL_DestroyTexture(exitGAME);
                startGame = loadTexture1("StartGameNotpressed.png", rendertarget);
                exitGAME = loadTexture1("Exit.png", rendertarget);
                gameTitle = loadTexture1("DUET.png", rendertarget);
                update(gameTitle, Gametitleposition);
                update(startGame, startgameposition);
                update(exitGAME, exitGamePosition);
                SDL_RenderPresent(rendertarget);
                SDL_RenderPresent(rendertarget);
                //                SDL_DestroyTexture(gameTitle);
                //                SDL_DestroyTexture(startGame);
                //                SDL_DestroyTexture(exitGAME);
                SDL_RenderClear(rendertarget);
                break;
        }
        while (SDL_PollEvent(&e)) {
            // SDL_WaitEvent(&e);
            if (e.type == SDL_QUIT){
                *mainmenu = no;
                *programruns = no;
                
            }
            else if (e.type == SDL_KEYDOWN){
                
                keystate = SDL_GetKeyboardState(NULL);
                if (keystate[SDL_SCANCODE_DOWN]) {
                    *select = (*select == startgame) ? exitgame : startgame;
                }
                else if (keystate[SDL_SCANCODE_UP]){
                    *select = (*select == startgame) ? exitgame : startgame;
                }
                else if (keystate[SDL_SCANCODE_SPACE]){
                    *mainmenu = (*select == startgame) ? no : yes;
                    if (*select == exitgame){
                        *programruns = no;
                        *mainmenu = no;
                        
                    }
                    
                    
                }
            }
            
            
        };
        
        if (SDL_GetTicks() - currenttick < 1000.0 / 6)/*60 FPS*/
        {
            SDL_Delay(1000 / 6 - SDL_GetTicks() + currenttick);
        }
        
        SDL_DestroyTexture(gameTitle);
        SDL_DestroyTexture(startGame);
        SDL_DestroyTexture(exitGAME);
    }
}
