#pragma once
#ifndef COMMON_FUNC_H_
#define COMMON_FUNC_H_
#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_image.h"
#include <string>
using namespace std;

//Loads individual image
inline SDL_Surface* loadSurface(std::string path)
{
    //Load image at specified path
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    }

    return loadedSurface;
}
extern SDL_Texture* gTexture;


//SDL_Texture* loadTexture(string path, SDL_Renderer* gRenderer);
inline SDL_Texture* loadTexture(string path, SDL_Renderer* gRenderer)
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}
inline bool loadMedia(SDL_Renderer* gRenderer)
{
    //Loading success flag
    bool success = true;

    //Load PNG texture
    gTexture = loadTexture("Resources/down.bmp", gRenderer);
    if (gTexture == NULL)
    {
        printf("Failed to load texture image!\n");
        success = false;
    }

    return success;
}
//Frees media and shuts down SDL


#endif