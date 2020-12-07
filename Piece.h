#pragma once
//#include "CommonFunc.h"
#include <vector>
#include "Block.h"
#include <stdlib.h>     /* srand, rand */

class Piece {
	vector<Block> blocks;
	int centerx = 0;
	int centery = 0;
	bool isASquare = false;
	public:
		~Piece();
		explicit Piece(SDL_Renderer*);
		void Render(SDL_Renderer* gRenderer);
		void MoveDown(int y);
		void MoveLeft(int x);
		void MoveRight(int x);
		bool CheckLeftWall();
		bool CheckRightWall(int width);
		bool CheckFloor(int height);
		vector<Block> GetBlocks();
		void GetIndexes(int* indexes, int movement);
		void Rotate();
		void RotateBack();

};