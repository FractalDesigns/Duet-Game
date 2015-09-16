//
//  Header.h
//  Duet
//
//  Created by achraf on 23/08/15.
//  Copyright © 2015 achraf. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#ifndef SDL
#define SDL
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "SDL2_mixer/SDL_mixer.h"
//#include "SDL_ttf.h"
#endif
#include "time.h" // using this library to generate a real random function
#include "menu.h"

#ifndef BOOLEAN
#define BOOLEAN
typedef enum { yes, no } boolean;
#endif