#include "Block.h"

Block::Block() {

}
Block::~Block() {
    
}
Block::Block(int width, int height, int incomingX, int incomingY, SDL_Renderer* gRenderer) {
    stretchRect.w = width;
    stretchRect.h = height;
    stretchRect.x = incomingX;
    stretchRect.y = incomingY;
    //this->loadMedia(gRenderer);
}

void Block::Render(SDL_Renderer* gRenderer) {
    SDL_RenderCopy(gRenderer, gTexture, NULL, &stretchRect);
}

void Block::close() {
    SDL_DestroyTexture(gTexture);
    gTexture = NULL;
}

bool Block::CheckLeftWall() {
    
    return stretchRect.x <= 0;
}
bool Block::CheckRightWall(int width) {
    return stretchRect.x >= width;
}
bool Block::CheckFloor(int height) {
    return stretchRect.y >= height;
}
int Block::x() {
    return stretchRect.x;
}
int Block::y() {
    return stretchRect.y;
}
int Block::GetIndexX(int movement) {
    return stretchRect.x / movement;
}
int Block::GetIndexY(int movement) {
    return stretchRect.y / movement;
}
void Block::MoveBlockDown(int y) {
    stretchRect.y += y;
}
void Block::MoveBlockLeft(int x) {
    stretchRect.x -= x;
}
void Block::MoveBlockRight(int x) {
    stretchRect.x += x;
}
bool Block::operator == (Block& op2)
{
    Block* foo = dynamic_cast<Block*>(&op2);
    if (foo->x() == x() && foo->y() == y())
    {
        return true;
    }
    else
    {
        return false;
    }
}
void Block::Rotate(int centerx, int centery) {
    int provisionalx = centerx - stretchRect.x;
    int provisionaly = centery - stretchRect.y;
    int xToReassign = (1 * provisionaly);
    int yToReassign = (-1 * provisionalx);
    stretchRect.x = centerx - xToReassign;
    stretchRect.y = centery - yToReassign;
}
void Block::RotateBack(int centerx, int centery) {
    int provisionalx = centerx - stretchRect.x;
    int provisionaly = centery - stretchRect.y;
    int xToReassign = (-1 * provisionaly);
    int yToReassign = (1 * provisionalx);
    stretchRect.x = centerx - xToReassign;
    stretchRect.y = centery - yToReassign;
}