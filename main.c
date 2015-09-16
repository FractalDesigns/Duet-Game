//
//  main.c
//  Duet
//
//  Created by achraf on 23/08/15.
//  Copyright © 2015 achraf. All rights reserved.
//

//
//  main.c
//  sdlGame
//
//  Created by Achraf EL AFRIT on 3/16/15.
//  Copyright (c) 2015 Achraf EL AFRIT. All rights reserved.
//

#include "Header.h"
#ifndef UPDATE
#define UPDATE
#define update(texture,positionrect) SDL_RenderCopy(rendertarget, texture, NULL, &positionrect)
//this macro is for use with SDL_Rect x
#endif
#define movebox(box)   if (box.y<480) {box.y+=4;box.x+=0*sin((double)currenttick);}else {box.y= -40;box.x=0+rand()%400 ;}


//this macro is for use with 2 SDL_Rect box,y

#define aBallhit(rect) (tambchou(blueballposition, rect)==yes || tambchou(redballposition, rect)==yes)
#define notout(ball1,ball2) ( ball1.x<440 && ball1.x>0 && ball2.x<440 && ball2.x>0 && ball1.y<480 && ball1.y>0 && ball2.y<480 && ball2.x>0 )
#ifndef OPTION
#define OPTION
typedef enum { startgame, exitgame } option;
#endif
typedef struct point { float x, y; } point;

#ifndef TEXTURELOADER
#define TEXTURELOADER
SDL_Texture *loadTexture(const char filepath[], SDL_Renderer *renderTarget)
{
    SDL_Texture *texture;
    SDL_Surface *surface = IMG_Load(filepath);
    texture = SDL_CreateTextureFromSurface(renderTarget, surface);
    SDL_FreeSurface(surface);
    return texture;
}
#endif
boolean tambchou(SDL_Rect rect1, SDL_Rect rect2){
    return((rect1.x + rect1.w <rect2.x + 10 || rect1.x + 10> rect2.x + rect2.w ||
            rect1.y + rect1.h <rect2.y + 12 || rect1.y> rect2.y + rect2.h - 12) ? no : yes);
}


int main(int argc, char* argv[]) {
    //initialize and loading variables
    char *bgmm[11] = { "l1.mp3", "l2.mp3", "l3.mp3", "l4.mp3", "l5.mp3", "l6.mp3", "l7.mp3", "l8.mp3", "l9.mp3", "l10.mp3", "l11.mp3" };
    char *bv[11] = { "can we live together.wav",
        "can't you just relax do you even remember.wav",
        "chage is good for you.wav",
        "grace and integrity are what define us.wav",
        "how do thrive and grow under pressure.wav",
        "i don't want you to keep going.wav",
        "i know sometimes it feels like you have no controle",
        "i want to help you but you need to let me.wav",
        "is there another way.wav",
        "once an action is done it cannot be undone.wav",
        "push any further and yu will  break.wav" };
    SDL_Color color;
    const point center = { 220.0, 350.0 };
    int currenttick, score=0;
    short circleradius = 44,musicselect=0;
    boolean mainmenu = yes;
    double theta = 0.0,speed=0.09;
    //Uint8 alpha;
    SDL_Renderer *rendertarget = NULL;
    
    SDL_Rect rectangle1 = { 320, 0, 100, 20 }, rectangle2 = { 230, rectangle1.y-80, 100, 20 };
    SDL_Rect littlerectangle1 = { 310, rectangle1.y - 165, 50, 20 };
    SDL_Rect cube1 = { 300, rectangle1.y - 270, 40, 40 }, cube2 = { 310, cube1.y - 90, 40, 40 }, cube3 = { 305, cube2.y - 90, 40, 40 };
    
    SDL_Rect redballposition = { center.x + circleradius*sin(theta), center.y + circleradius*cos(theta), 25, 25 };
    SDL_Rect blueballposition = { center.x - circleradius*sin(theta), center.y - circleradius*cos(theta), 25, 25 };
    
    const Uint8 *keystate;
    SDL_Window *window = NULL;
    SDL_Texture *redball = NULL, *blueball = NULL, *box = NULL; //gametexture
    
    // Initialize SDL2
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2560);
    Mix_Music *bgm = Mix_LoadMUS("l1.mp3");
    
    Mix_Chunk *voice = Mix_LoadWAV("trust your instincts.wav"), *hitsound = Mix_LoadWAV("Samples/3816133910831170.wav");
    Mix_PlayChannel(2,voice,0);
    Mix_PlayMusic(bgm, -1);
    
    
    
    // Create an application window with the following settings:
    window = SDL_CreateWindow("An SDL2 window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 440, 480, SDL_WINDOW_SHOWN  );
    
    rendertarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    box = loadTexture("box.png", rendertarget);
    
    redball = loadTexture("redball.png", rendertarget);
    blueball = loadTexture("bleuball.png", rendertarget);
    
    
    //SDL_SetRenderDrawColor(rendertarget, 0x23, 0x23, 0x23, 0x23);
    SDL_SetRenderDrawColor(rendertarget, 0x99, 0x99, 0xF8, 0x23);
    color.r = 0x99;
    color.g = 0x99;
    color.b = 0xF8;
    color.a = 0x23;
    option select = exitgame;
    //gameloop
    
    boolean gamerunning = yes, programruns = yes;
    SDL_Event e;
    
    while (programruns == yes){
        while (gamerunning == yes && select == startgame){
            
            
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT)
                    gamerunning = no;
            };
            srand(time(0));
            
            currenttick = SDL_GetTicks();
            if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE){
                SDL_RenderClear(rendertarget);
                SDL_RenderPresent(rendertarget);
                //SDL_RenderCopy(rendertarget, gameTitle, NULL, &Gametitleposition);
                //update(gameTitle, Gametitleposition);
                
                SDL_RenderPresent(rendertarget);
                mainmenu = yes;
                break;
                //code to stop game and get back to menu
            }
            keystate = SDL_GetKeyboardState(NULL);
            
            if (keystate[SDL_SCANCODE_LEFT]) {
                theta += speed;
                redballposition.x = center.x + circleradius*sin(theta);
                redballposition.y = center.y + circleradius*cos(theta);
                blueballposition.x = center.x - circleradius*sin(theta);
                blueballposition.y = center.y - circleradius*cos(theta);
            }
            else if (keystate[SDL_SCANCODE_RIGHT]){
                
                theta -= speed;
                redballposition.x = center.x + circleradius*sin(theta);
                redballposition.y = center.y + circleradius*cos(theta);
                blueballposition.x = center.x - circleradius*sin(theta);
                blueballposition.y = center.y - circleradius*cos(theta);
                
            }
            else if (keystate[SDL_SCANCODE_UP]){
                
                
                circleradius += 2;
                redballposition.x = center.x + circleradius*sin(theta);
                redballposition.y = center.y + circleradius*cos(theta);
                blueballposition.x = center.x - circleradius*sin(theta);
                blueballposition.y = center.y - circleradius*cos(theta);
            }
            else if (keystate[SDL_SCANCODE_DOWN]){
                
                circleradius -= 2;
                redballposition.x = center.x + circleradius*sin(theta);
                redballposition.y = center.y + circleradius*cos(theta);
                blueballposition.x = center.x - circleradius*sin(theta);
                blueballposition.y = center.y - circleradius*cos(theta);
            }
            movebox(rectangle1);
            srand(currenttick);
            movebox(rectangle2);
            
            srand(currenttick);
            movebox(littlerectangle1);
            srand(currenttick);
            movebox(cube1);
            srand(currenttick);
            movebox(cube2);
            srand(currenttick);
            movebox(cube3);
            SDL_RenderClear(rendertarget);
            update(redball, redballposition);
            update(blueball, blueballposition);
            update(box, rectangle1);
            update(box, rectangle2);
            update(box, littlerectangle1);
            update(box, cube1);
            update(box, cube2);
            update(box, cube3);
            
            SDL_RenderPresent(rendertarget);
            
            
            
            
            if (aBallhit(rectangle1) || aBallhit(rectangle2) || aBallhit(littlerectangle1) || aBallhit(cube1) || aBallhit(cube2) || aBallhit(cube3)){
                
                Mix_PlayChannel(1, hitsound, 0);
                //reinitialize Game
                
                //rectangle1 = { 220, 0, 100, 20 };
                rectangle1.x= 220;
                rectangle1.y= 0;
                rectangle1.w= 100;
                rectangle1.h= 20;
                //rectangle2 = { 130, rectangle1.y - 80, 100, 20 };
                rectangle2.x= 130;
                rectangle2.y= rectangle1.y - 80;
                rectangle2.w= 100;
                rectangle2.h= 20;
                //littlerectangle1 = { 210, rectangle1.y - 165, 50, 20 };
                littlerectangle1.x= 210;
                littlerectangle1.y= rectangle1.y - 165;
                littlerectangle1.w= 50;
                littlerectangle1.h= 20;
                //cube1 = { 200, rectangle1.y - 270, 40, 40 };
                cube1.x= 200;
                cube1.y= rectangle1.y - 270;
                cube1.w= 40;
                cube1.h= 40;
                //cube2 = { 210, cube1.y - 90, 40, 40 };
                cube2.x= 210;
                cube2.y= cube1.y - 90;
                cube2.w= 40;
                cube2.h= 40;
                //cube3 = { 205, cube2.y - 90, 40, 40 };
                cube3.x= 205;
                cube3.y= cube2.y - 90;
                cube3.w= 40;
                cube3.h= 40;
                
                
                //redballposition = { center.x + circleradius*sin(theta), center.y + circleradius*cos(theta), 25, 25 };
                redballposition.x= center.x + circleradius*sin(theta);
                redballposition.y= center.y + circleradius*cos(theta);
                redballposition.w= 25;
                redballposition.h= 25;
                //blueballposition = { center.x - circleradius*sin(theta), center.y - circleradius*cos(theta), 25, 25 };
                blueballposition.x=  center.x - circleradius*sin(theta);
                blueballposition.y= center.y - circleradius*cos(theta);
                blueballposition.w= 25;
                blueballposition.h= 25;
                
                circleradius = 44;
                gamerunning = yes;
                mainmenu = yes;
                printf("\n your score is: %d", score);
                score = 0;
                Mix_HaltMusic();
                Mix_FreeMusic(bgm);
                if (musicselect == 10)
                    musicselect = 0;
                else
                    musicselect += 1;
                
                bgm = Mix_LoadMUS(bgmm[musicselect]);
                voice = Mix_LoadWAV(bv[musicselect]);
                Mix_PlayMusic(bgm,-1);
                Mix_PlayChannel(2, voice, 0);
                srand(currenttick);
                
                color.b = rand(); srand(currenttick*100);
                color.a = rand(); srand(currenttick*1000);
                color.g = rand(); srand(currenttick*10000);
                color.r = rand();
                
                SDL_SetRenderDrawColor(rendertarget, color.r, color.g, color.b, color.a);
                
                break;
                
                //insert code when collision happens
                
            }
            if (musicselect == 6 ){
                color.b = rand(); srand(currenttick * 100);
                color.r = rand(); srand(currenttick * 1000);
                color.g = rand();
                SDL_SetTextureColorMod(box, color.r, color.g, color.b);
            }
            else if (musicselect == 7){
                //SDL_SetTextureColorMod(box, 0, 0, 0);
            }
            //if (rectangle1.y >= 200){
            //	alpha = 20;
            //	SDL_SetTextureAlphaMod(box,alpha);
            //}
            //else
            //	alpha=100;
            
            if( (notout(redballposition,blueballposition))&&(rectangle1.y == 400 || rectangle2.y == 400 || littlerectangle1.y == 400 || cube1.y == 400 || cube2.y == 400 || cube3.y == 400)){
                score += 1;
                //	printf("\n score = %d", score);
                
                
            }
            
            if (SDL_GetTicks() - currenttick<1000.0 / 60)/*60 FPS*/
            {
                SDL_Delay(1000 / 60 - SDL_GetTicks() + currenttick);
            }
        }
        runmenu(&programruns,&mainmenu,rendertarget,&select);
    }
    // Close and destroy the window
    SDL_DestroyWindow(window);
    
    // Clean up
    SDL_Quit();
    IMG_Quit();
    Mix_Quit();
    SDL_DestroyTexture(redball);
    SDL_DestroyTexture(blueball);
    SDL_DestroyTexture(box);
    
    SDL_DestroyRenderer(rendertarget);
    
    redball = NULL;
    blueball = NULL;
    box = NULL;
    rendertarget = NULL;
    return 0;
}