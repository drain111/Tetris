#include "Main_Class.h"
#include <algorithm>    // std::max
#include <iostream>

using namespace std;




int main(int argc, char* argv[])
{

	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia(gRenderer))
		{
			printf("Failed to load media!\n");
		}
		else
		{
            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
            //Main loop flag
            bool quit = false;
            SDL_Rect stretchRect;
            stretchRect.x = 0;
            stretchRect.y = movement;
            stretchRect.w = movement;
            stretchRect.h = movement;
            int line = 0;
            //Event handler
            SDL_Event e;
            //While application is running
            while (!quit)
            {
                
                frameTime = SDL_GetTicks();
                //SDL_FillRect(gScreenSurface, NULL, 0x000000);
                int currentPlacesPieces[8];
                actualPiece->GetIndexes(currentPlacesPieces, movement);
                //Handle events on queue
                while (SDL_PollEvent(&e) != 0)
                {

                    //User requests quit
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                    //User presses a key
                    else if (e.type == SDL_KEYDOWN)
                    {
                        //Select surfaces based on key press
                        switch (e.key.keysym.sym)
                        {
                        case SDLK_UP:
                            //gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
                            break;
                        case SDLK_q:
     
                        case SDLK_e:
                            actualPiece->Rotate();
                            actualPiece->GetIndexes(currentPlacesPieces, movement);
                            if (actualPiece->CheckRightWall(SCREEN_WIDTH) || actualPiece->CheckLeftWall() || actualPiece->CheckFloor(SCREEN_HEIGHT) || BlockUnder(blockScreen, currentPlacesPieces, 0, 0)) {
                                actualPiece->RotateBack();
                            }
                            break;
                        case SDLK_DOWN:
                            stretchRect.y += movement;
                            if (actualPiece->CheckFloor(SCREEN_HEIGHT-movement) || BlockUnder(blockScreen,  currentPlacesPieces, 0, 1)) {
                                vector<Block> aux = actualPiece->GetBlocks();
                                Block ghostBlock = Block();
                                for (int i = 0; i < 4; ++i) {
                                    blockScreen[aux[i].x() / movement][aux[i].y() / movement] = aux[i];
                                }
                                for (int i = 3; i >= 0; --i) {
                                    bool line = true;
                                    for (int j = 0; j < blockScreen.size(); ++j) {
                                        if (blockScreen[j][aux[i].y() / movement] == ghostBlock) {
                                            line = false;
                                            break;
                                        }
                                    }
                                    if (line == true) {
                                        for (int j = 0; j < blockScreen.size(); ++j) {
                                            for (int k = aux[i].y() / movement; k > 0; --k) {
                                                blockScreen[j][k] = blockScreen[j][k-1];
                                                if(!(blockScreen[j][k] == ghostBlock))
                                                    blockScreen[j][k].MoveBlockDown(movement);
                                            }
                                            blockScreen[j][0] = ghostBlock;
                                        }
                                    }
                                }
                                delete actualPiece;
                                actualPiece = new Piece(gRenderer);
                                actualPiece->GetIndexes(currentPlacesPieces, movement);

                                //cout << "Pressed down" << line << "\n";
                            }
                            else {
                                actualPiece->MoveDown(movement);

                            }
                            //gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
                            break;

                        case SDLK_LEFT:
                            stretchRect.x -= movement;
                            stretchRect.x = max(stretchRect.x, 0);
                            if (actualPiece->CheckLeftWall() || BlockUnder(blockScreen, currentPlacesPieces, -1, 0)) {
                                
                            }
                            else {
                                actualPiece->MoveLeft(movement);
                            }

                            //gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
                            break;

                        case SDLK_RIGHT:
                            stretchRect.x += movement;
                            stretchRect.x = min(stretchRect.x, movement*7);
                            if (actualPiece->CheckRightWall(SCREEN_WIDTH - movement) || BlockUnder(blockScreen, currentPlacesPieces, 1, 0)) {

                            }
                            else {
                                actualPiece->MoveRight(movement);
                            }

                            //gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
                            break;

                        default:
                            //gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
                            break;
                        }
                    }
                    
                }
                if (frameTime - prevTime > 1000) {
                    if (actualPiece->CheckFloor(SCREEN_HEIGHT-movement) || BlockUnder(blockScreen, currentPlacesPieces, 0, 1)) {
                        vector<Block> aux = actualPiece->GetBlocks();
                        Block ghostBlock = Block();

                        for (int i = 0; i < 4; ++i) {
                            blockScreen[aux[i].x() / movement][aux[i].y() / movement] = aux[i];
                        }
                        for (int i = 3; i >= 0; --i) {
                            bool line = true;
                            for (int j = 0; j < blockScreen.size(); ++j) {
                                if (blockScreen[j][aux[i].y() / movement] == ghostBlock) {
                                    line = false;
                                    break;
                                }
                            }
                            if (line == true) {
                                for (int j = 0; j < blockScreen.size(); ++j) {
                                    for (int k = aux[i].y() / movement; k > 0; --k) {
                                        blockScreen[j][k] = blockScreen[j][k - 1];
                                        if (!(blockScreen[j][k] == ghostBlock))
                                            blockScreen[j][k].MoveBlockDown(movement);
                                    }

                                    blockScreen[j][0] = ghostBlock;
                                }
                            }
                        }
                        //actualPiece->Piece::~Piece();
                        delete actualPiece;
                        actualPiece = new Piece(gRenderer);
                        //cout << "Pressed down" << line << "\n";

                    }
                    else {
                        actualPiece->MoveDown(movement);
                    }
                    prevTime = SDL_GetTicks();
                }
                //Clear screen
                SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
                SDL_RenderClear(gRenderer);

                //Render texture to screen
                for (vector<vector<Block>>::iterator i = blockScreen.begin(); i < blockScreen.end(); ++i) {
                    for (vector<Block>::iterator j = (*i).begin(); j < (*i).end(); ++j) {
                        if (&j != nullptr) {
                            j->Render(gRenderer);
                        }
                    }
                }
                actualPiece->Render(gRenderer);
                
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                //SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

                //Update screen
                SDL_RenderPresent(gRenderer);




                //Apply the current image
                SDL_BlitScaled(gCurrentSurface, NULL, gScreenSurface, &stretchRect);

                //Update the surface
                SDL_UpdateWindowSurface(gWindow);
                line++;

            }
		}
	}
    //Free resources and close SDL
    close();

    return 0;
}
bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                actualPiece = new Piece(gRenderer);
                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }
    for (int i = 0; i < SCREEN_WIDTH / movement; i++) {
        vector<Block> blockAux;
        Block ghostBlock = Block();
        for (int j = 0; j < SCREEN_HEIGHT / movement; j++)
            blockAux.push_back(ghostBlock);
        //blockAux.reserve(8);
        blockScreen.push_back(blockAux);
    }
    return success;
}

bool BlockUnder(vector<vector<Block>> blockScreen, int *i, int x, int y) {
    Block ghostBlock = Block();
    bool under = false;
    for (int j = 0; j < 4; j++) {
        if (!(blockScreen[i[j * 2] + static_cast<unsigned __int64>(x)][i[(j * 2) + 1] + static_cast<unsigned __int64>(y)] == ghostBlock)) {
            return true;
        }
    }
    return false;
}


bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load default surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("F:/Descargas/04_key_presses/press.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL)
    {
        printf("Failed to load default image!\n");
        success = false;
    }

    //Load up surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("F:/Descargas/04_key_presses/up.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL)
    {
        printf("Failed to load up image!\n");
        success = false;
    }

    //Load down surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("F:/Descargas/04_key_presses/down.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL)
    {
        printf("Failed to load down image!\n");
        success = false;
    }

    //Load left surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("F:/Descargas/04_key_presses/left.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL)
    {
        printf("Failed to load left image!\n");
        success = false;
    }

    //Load right surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("F:/Descargas/04_key_presses/right.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL)
    {
        printf("Failed to load right image!\n");
        success = false;
    }

    return success;
}
void close()
{
    //Free loaded image
    //SDL_DestroyTexture(gTexture);
    //gTexture = NULL;

    //Destroy window    
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}
