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
	,mouseIndex()
	,onBoard{false}
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
	Vec2 mousePosition;
	GetMousePoint(&mousePosition.x,&mousePosition.y);
	mouseIndex = (mousePosition - Vec2{ BOARD_X,BOARD_Y }) / Vec2{ BlockSize,BlockSize };



	// confirming mouse on the board 
	bool left = mousePosition.x >= BOARD_X;
	bool up	  = mousePosition.y >= BOARD_Y;
	bool right= mousePosition.x <= BOARD_X + WIDTH  * BlockSize ;
	bool down = mousePosition.y <= BOARD_Y + HEIGHT * BlockSize ;

	onBoard = left && up && right && down;




}

void Board::Draw() {

	// disp blocks
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			Block& block = board.at(y*WIDTH+x);
			int posx = x * BlockSize + BOARD_X;
			int posy = y * BlockSize + BOARD_Y;
			DrawBox(posx,posy,posx+BlockSize,posy+BlockSize,  0x808080, !block.isOpen);
	// disp blocks frame
			DrawBox(posx,posy,posx+BlockSize,posy+BlockSize,  0x808080/2, FALSE);
			
	// disp mouse frame 
			if (onBoard && y == mouseIndex.y && x == mouseIndex.x) {
					posx = mouseIndex.x * BlockSize + BOARD_X;
					posy = mouseIndex.y * BlockSize + BOARD_Y;
					DrawBox(posx, posy, posx + BlockSize, posy + BlockSize, 0xffffff, FALSE);
			}

			
			// disp a block
			//DrawBox(posx,posy,posx+BlockSize,posy+BlockSize,  GetColor(100,(y*WIDTH+x)*25 % 255, 100), !block.isOpen);
		}
	}
}
