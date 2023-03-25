#include "GameEngine.h"
#include "Chessboard.h"

#include <iostream>

Chessboard::Chessboard() 
{
	// Source size of image
	srcRect.w = srcRect.h = 64;
	srcRect.x = srcRect.y = 0;

	// Desired size of image
	destRect.w = destRect.h = 64;
	destRect.x = destRect.y = 0;
}

Chessboard::~Chessboard() {}


void Chessboard::DrawBoard()
{
	for (int row = 0; row < 10; row++)
	{
		for (int column = 0; column < 10; column++)
		{
			destRect.x = column * 64;
			destRect.y = row * 64;

			switch (chessboard[row][column].texture)
			{
				// Field colors
				case 'X':
					TextureMenager::Draw(fields_colors[0], srcRect, destRect);
					break;

				case 'O':
					TextureMenager::Draw(fields_colors[1], srcRect, destRect);
					break;

				// Numeric_tags
				case 1:
					TextureMenager::Draw(numeric_tags[0], srcRect, destRect);
					break;

				case 2:
					TextureMenager::Draw(numeric_tags[1], srcRect, destRect);
					break;

				case 3:
					TextureMenager::Draw(numeric_tags[2], srcRect, destRect);
					break;

				case 4:
					TextureMenager::Draw(numeric_tags[3], srcRect, destRect);
					break;

				case 5:
					TextureMenager::Draw(numeric_tags[4], srcRect, destRect);
					break;

				case 6:
					TextureMenager::Draw(numeric_tags[5], srcRect, destRect);
					break;

				case 7:
					TextureMenager::Draw(numeric_tags[6], srcRect, destRect);
					break;

				case 8:
					TextureMenager::Draw(numeric_tags[7], srcRect, destRect);
					break;

				// Letter_tags
				case 'A':
					TextureMenager::Draw(letter_tags[0], srcRect, destRect);
					break;

				case 'B':
					TextureMenager::Draw(letter_tags[1], srcRect, destRect);
					break;

				case 'C':
					TextureMenager::Draw(letter_tags[2], srcRect, destRect);
					break;

				case 'D':
					TextureMenager::Draw(letter_tags[3], srcRect, destRect);
					break;

				case 'E':
					TextureMenager::Draw(letter_tags[4], srcRect, destRect);
					break;

				case 'F':
					TextureMenager::Draw(letter_tags[5], srcRect, destRect);
					break;

				case 'G':
					TextureMenager::Draw(letter_tags[6], srcRect, destRect);
					break;

				case 'H':
					TextureMenager::Draw(letter_tags[7], srcRect, destRect);
					break;

				default:
					break;
			}
		}
	}
}
