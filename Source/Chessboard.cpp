#include "Chessboard.h"
#include "TextureMenager.h"

int chessboard[8][8] = 
{
			{ 0, 1, 0, 1, 0, 1, 0, 1 },
			{ 1, 0, 1, 0, 1, 0, 1, 0 },
			{ 0, 1, 0, 1, 0, 1, 0, 1 },
			{ 1, 0, 1, 0, 1, 0, 1, 0 },
			{ 0, 1, 0, 1, 0, 1, 0, 1 },
			{ 1, 0, 1, 0, 1, 0, 1, 0 },
			{ 0, 1, 0, 1, 0, 1, 0, 1 },
			{ 1, 0, 1, 0, 1, 0, 1, 0 }
};

Chessboard::Chessboard()
{
	whiteSqr = TextureMenager::LoadTexture("Assets/whiteSqr.png");
	blackSqr = TextureMenager::LoadTexture("Assets/blackSqr.png");
}

Chessboard::~Chessboard() {}

void Chessboard::LoadBoard(int board[8][8])
{

}

void Chessboard::DrawBoard()
{
}
