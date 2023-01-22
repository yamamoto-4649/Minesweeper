#include "board.h"
#include<random>

namespace {
	static const int WIDTH = 4;// is board width _ num x
	static const int HEIGHT = 4;// is board height _ num y
	static const int BOARD_X = 100;// first position _ x
	static const int BOARD_Y = 100;// first position _ y
	static const int BLOCK_SIZE = 64;// all block size _ width and height
	static const int BOMB_MAX = 4;// first bomb count
}

Board::Board(Scene* sc)
	:Object(sc)
	,board()
	,mouseIndex()
	,onBoard{false}
	,keystop{false}
{}

Board::~Board(){

}

void Board::Init(){
	Block firstInitValue = {0,false,false};
	board.resize(WIDTH * HEIGHT, firstInitValue);
	keystop = true;
	
	// rand reset to bomb
	/*for(Block& aBlock:board){
		bool haveBomb = static_cast<bool>(GetRand(1));
		aBlock.bomb = haveBomb;
	}*/

	// bomb shuffle 
	BombShuffle();

	// count bomb around block
	for (int i = 0; i < board.size(); i++) {
		int bombNum= CountBombAroundBlock(i);
		board.at(i).nuber = bombNum;
	}


}

void Board::Update(){
	Vec2 mousePosition;
	GetMousePoint(&mousePosition.x,&mousePosition.y);
	mouseIndex = (mousePosition - Vec2{ BOARD_X,BOARD_Y }) / Vec2{ BLOCK_SIZE,BLOCK_SIZE };



	// confirming mouse on the board 
	bool left = mousePosition.x >= BOARD_X;
	bool up	  = mousePosition.y >= BOARD_Y;
	bool right= mousePosition.x <= BOARD_X + WIDTH  * BLOCK_SIZE ;
	bool down = mousePosition.y <= BOARD_Y + HEIGHT * BLOCK_SIZE ;

	onBoard = left && up && right && down;


	// mouse click
	if (onBoard) {
	// change flag active
		bool mouseRight = GetMouseInput() & MOUSE_INPUT_RIGHT;
		if (mouseRight && !keystop) {
			int index = mouseIndex.y * WIDTH + mouseIndex.x;
			// isn't open 
			if( !board.at(index).isOpen)
				board.at(index).flag = !board.at(index).flag;
		}


	// block open
		bool mouseLeft = GetMouseInput() & MOUSE_INPUT_LEFT;
		if (mouseLeft && !keystop) {
			int index = mouseIndex.y * WIDTH + mouseIndex.x;
			// open true is skip
			if(!board.at(index).flag && !board.at(index).isOpen)
				board.at(index).isOpen= true;
		}

		keystop = mouseRight || mouseLeft;
	}
}

void Board::Draw() {

	// disp blocks
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			Block& block = board.at(y*WIDTH+x);
			int posx = x * BLOCK_SIZE + BOARD_X;
			int posy = y * BLOCK_SIZE + BOARD_Y;
			DrawBox(posx,posy,posx+BLOCK_SIZE,posy+BLOCK_SIZE,  0x808080, !block.isOpen);
	// disp a block
			//DrawBox(posx,posy,posx+BlockSize,posy+BlockSize,  GetColor(100,(y*WIDTH+x)*25 % 255, 100), !block.isOpen);

	// disp blocks frame
			DrawBox(posx,posy,posx+BLOCK_SIZE,posy+BLOCK_SIZE,  0x808080/2, FALSE);
			
	// disp mouse frame 
			if (onBoard && y == mouseIndex.y && x == mouseIndex.x) {
				int mousePosX = mouseIndex.x * BLOCK_SIZE + BOARD_X;
				int mousePosY = mouseIndex.y * BLOCK_SIZE + BOARD_Y;
				DrawBox(mousePosX, mousePosY, mousePosX + BLOCK_SIZE, mousePosY + BLOCK_SIZE, 0xffffff, FALSE);
			}
	// disp bomb
			if (block.bomb)
				DrawCircle(posx+BLOCK_SIZE/2,posy+BLOCK_SIZE/2,BLOCK_SIZE/2,0x222222,TRUE);
			if (block.flag)
				DrawTriangle(posx+BLOCK_SIZE/2,posy,posx,posy+BLOCK_SIZE,posx+BLOCK_SIZE,posy+BLOCK_SIZE,0xffff00,FALSE);
	// disp bomb count
			if(block.isOpen)
			DrawFormatString(posx,posy,0x0,"%d",block.nuber);
		}
	}
}

void Board::BombShuffle(){
	for (int i = 0; i < BOMB_MAX; i++) {
		board.at(i).bomb = true;
	}

 	std::random_shuffle(board.begin(),board.end());
}

const int Board::CountBombAroundBlock(int index){

	// num out index
	if (index < 0 || board.size() <= index)
		return -1;

	// bomb is skip
	if (board.at(index).bomb)
		return -1;

	int bombCount = 0;
	for (int y = -1; y <= 1; y++) {
		for (int x = -1; x <= 1; x++) {
			int indexX= index% WIDTH;
			int indexY= index/ WIDTH;

			int aroundX= indexX+ x;
			int aroundY= indexY+ y;

			if  (
					aroundX < 0
				 || aroundY < 0
				 || WIDTH <= aroundX
				 || HEIGHT <= aroundY
				)
				continue;
	
			int aroundIndex = aroundY* WIDTH+ aroundX;


			if ( !board.at(aroundIndex).bomb)
				continue;

			bombCount++;
		}
	}

	return bombCount;
}
