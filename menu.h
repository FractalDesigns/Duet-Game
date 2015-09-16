//
//  menu.h
//  Duet
//
//  Created by achraf on 23/08/15.
//  Copyright © 2015 achraf. All rights reserved.
//

#ifndef BOOLEAN
#define BOOLEAN
typedef enum { yes, no } boolean;
#endif
#ifndef OPTION
#define OPTION
typedef enum { startgame, exitgame } option;
#endif
#ifndef SDL
#define SDL
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "SDL2_mixer/SDL_mixer.h"
//#include "SDL_ttf.h"
#endif
#ifndef RUNMENU
#define RUNMENU
extern void runmenu(boolean*, boolean*,SDL_Renderer* ,option*);
#endif

#ifndef UPDATE
#define UPDATE
#define update(texture,positionrect) SDL_RenderCopy(rendertarget, texture, NULL, &positionrect)
//this macro is for use with SDL_Rect x
#endif