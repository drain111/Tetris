/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include "CommonFunc.h"
#include <stdio.h>
//#include <string>
//#include <vector>
#include "Piece.h"

//Key press surfaces constants
enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};
//Screen dimension constants
const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 800;
const int movement = SCREEN_WIDTH / 16;
Uint32 frameTime = 0;
Uint32 prevTime = 0;
Piece *actualPiece;
vector<vector<Block>> blockScreen;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
SDL_Window* gWindow2 = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gScreenSurface2 = NULL;
SDL_Renderer* gRenderer = NULL;
//The images that correspond to a keypress
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

//Current displayed image
SDL_Surface* gCurrentSurface = NULL;
//The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;
int main(int argc, char* argv[]);
//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();
void close();

bool BlockUnder(vector<vector<Block>> blockScreen, int *i, int x, int y);




