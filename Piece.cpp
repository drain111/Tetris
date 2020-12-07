#include "Piece.h"

Piece::~Piece() {
	if (blocks.size() != 0) {
		blocks.clear();
		blocks.shrink_to_fit();
	}
}


Piece::Piece(SDL_Renderer* gRenderer) {
	blocks.reserve(4);
	int randNumb = rand() % 7;
	switch (randNumb) {
		case 0:
			blocks.push_back(Block(25, 25, 200, 0, gRenderer)); // ith element is a copy of this
			blocks.push_back(Block(25, 25, 225, 0, gRenderer)); // ith element is a copy of this
			blocks.push_back(Block(25, 25, 200, 25, gRenderer)); // ith element is a copy of this
			blocks.push_back(Block(25, 25, 225, 25, gRenderer)); // ith element is a copy of this
			isASquare = true;
			break;
		case 1:
			for (int i = 0; i < 4; i++) {
				blocks.push_back(Block(25, 25, 200, 25 * i, gRenderer)); // ith element is a copy of this
			}
			centery = 50;
			centerx = 200;
			break;
		case 2:
			blocks.push_back(Block(25, 25, 175, 25, gRenderer)); // ith element is a copy of this
			blocks.push_back(Block(25, 25, 200, 25, gRenderer)); // ith element is a copy of this
			blocks.push_back(Block(25, 25, 200, 0, gRenderer)); // ith element is a copy of this
			blocks.push_back(Block(25, 25, 225, 0, gRenderer)); // ith element is a copy of this
			centery = 25;
			centerx = 200;
			break;
		case 3:
			blocks.push_back(Block(25, 25, 175, 0, gRenderer)); // ith element is a copy of this
			blocks.push_back(Block(25, 25, 200, 0, gRenderer)); // ith element is a copy of this
			blocks.push_back(Block(25, 25, 200, 25, gRenderer)); // ith element is a copy of this
			blocks.push_back(Block(25, 25, 225, 25, gRenderer)); // ith element is a copy of this
			centery = 25;
			centerx = 200;
			break;
		case 4:
			blocks.push_back(Block(25, 25, 200, 0, gRenderer)); // ith element is a copy of this
			blocks.push_back(Block(25, 25, 200, 25, gRenderer)); // ith element is a copy of this
			blocks.push_back(Block(25, 25, 200, 50, gRenderer)); // ith element is a copy of this
			blocks.push_back(Block(25, 25, 225, 50, gRenderer)); // ith element is a copy of this
			centery = 25;
			centerx = 200;
			break;
		case 5:
			blocks.push_back(Block(25, 25, 200, 0, gRenderer)); // ith element is a copy of this
			blocks.push_back(Block(25, 25, 200, 25, gRenderer)); // ith element is a copy of this
			blocks.push_back(Block(25, 25, 200, 50, gRenderer)); // ith element is a copy of this
			blocks.push_back(Block(25, 25, 175, 50, gRenderer)); // ith element is a copy of this
			centery = 25;
			centerx = 200;
			break;
		case 6:
			blocks.push_back(Block(25, 25, 175, 25, gRenderer)); // ith element is a copy of this
			blocks.push_back(Block(25, 25, 200, 25, gRenderer)); // ith element is a copy of this
			blocks.push_back(Block(25, 25, 225, 25, gRenderer)); // ith element is a copy of this
			blocks.push_back(Block(25, 25, 200, 0, gRenderer)); // ith element is a copy of this
			centery = 25;
			centerx = 200;
			break;
		default:
			break;
	}

	for (int i = 0; i < 4; i++) {
		blocks.push_back(Block(25,25, 200, 25*i, gRenderer)); // ith element is a copy of this
	}
	
}
bool Piece::CheckLeftWall() {
	for (int i = 0; i < 4; i++) {
		if (blocks[i].CheckLeftWall()) {
			return true;
		}
	}
	return false;
}
bool Piece::CheckRightWall(int width) {
	for (int i = 0; i < 4; i++) {
		if (blocks[i].CheckRightWall(width)) {
			return true;
		}
	}
	return false;
}
bool Piece::CheckFloor(int height) {
	for (int i = 0; i < 4; i++) {
		if (blocks[i].CheckFloor(height)) {
			return true;
		}
	}
	return false;
}
void Piece::MoveDown(int y) {
	for (int i = 0; i < 4; i++) {
		blocks[i].MoveBlockDown(y);
	}
	centery += y;
}
void Piece::MoveLeft(int x) {
	for (int i = 0; i < 4; i++) {
		blocks[i].MoveBlockLeft(x);
	}
	centerx -= x;
}
void Piece::MoveRight(int x) {
	for (int i = 0; i < 4; i++) {
		blocks[i].MoveBlockRight(x);
	}
	centerx += x;

}
void Piece::Render(SDL_Renderer* gRenderer) {
	for (int i = 0; i < 4; i++) {
		blocks[i].Render(gRenderer);
	}
}
vector<Block> Piece::GetBlocks() {
	return blocks;
}
void Piece::GetIndexes(int* indexes, int movement) {
	for (int i = 0; i < 4; i++) {
		indexes[i*2] = blocks[i].GetIndexX(movement);
		indexes[i*2+1] = blocks[i].GetIndexY(movement);
	}
}
void Piece::Rotate() {
	if (isASquare)
		return;
	for (int i = 0; i < 4; i++) {
		blocks[i].Rotate(centerx, centery);
	}
}
void Piece::RotateBack() {
	if (isASquare)
		return;
	for (int i = 0; i < 4; i++) {
		blocks[i].RotateBack(centerx, centery);
	}
}