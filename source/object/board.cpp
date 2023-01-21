#include "board.h"

namespace {
	static const int WIDTH = 4;// is board width _ num x
	static const int HEIGHT = 4;// is board height _ num y
	static const int BOARD_X = 100;// first position _ x
	static const int BOARD_Y = 100;// first position _ y
	static const int BlockSize = 64;// all block size _ width and height

}

Board::Board(Scene* sc)
	:Object(sc)
	,board()
{}

Board::~Board(){

}

void Board::Init(){
	Block firstInitValue = {0,false,false};
	board.resize(WIDTH * HEIGHT, firstInitValue);
	
	// rand reset to bomb
	for(Block& aBlock:board){
		bool haveBomb = static_cast<bool>(GetRand(1));
		aBlock.bomb = haveBomb;
	}



}

void Board::Update(){

}

void Board::Draw() {

	// disp blocks
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			Block& block = board.at(y*WIDTH+x);
			int posx = x * BlockSize + BOARD_X;
			int posy = y * BlockSize + BOARD_Y;
			DrawBox(posx,posy,posx+BlockSize,posy+BlockSize,  0x808080, !block.isOpen);
			
			// disp a block
			//DrawBox(posx,posy,posx+BlockSize,posy+BlockSize,  GetColor(100,(y*WIDTH+x)*25 % 255, 100), !block.isOpen);
		}
	}
}
