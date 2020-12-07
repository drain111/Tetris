#pragma once
#include "CommonFunc.h"
#include <string>

using namespace std;

class Block {
   
    bool move();
    void close();
    bool checkCollision(int otherX, int otherY);
    SDL_Rect stretchRect;



    public:
        void Render(SDL_Renderer* gRenderer);
        explicit Block();
        ~Block();
        Block(int, int, int, int, SDL_Renderer*);
        void MoveBlockDown(int y);
        void MoveBlockLeft(int x);
        void MoveBlockRight(int x);
        bool CheckLeftWall();
        bool CheckRightWall(int width);
        bool CheckFloor(int height);
        int x();
        int y();
        int GetIndexX(int movement);
        int GetIndexY(int movement);
        bool operator == (Block& op2);
        void Rotate(int centerx, int centery);
        void RotateBack(int centerx, int centery);

};
