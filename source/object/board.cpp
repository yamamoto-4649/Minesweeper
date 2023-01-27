#include "board.h"

#include"../libs/frameWork/scene.h"
#include<random>
#include"gameClear.h"
#include"gameOver.h"

namespace {
	static const int WIDTH = 9;// is board width _ num x
	static const int HEIGHT = 9;// is board height _ num y
	static const int BOARD_X = 100;// first position _ x
	static const int BOARD_Y = 100;// first position _ y
	static const int BLOCK_SIZE = 48;// all block size _ width and height
	static const int BOMB_MAX = 10;// first bomb count
}

Board::Board(Scene* sc)
	:Object(sc)
	,board()
	,mouseIndex()
	,hFont{-1}
	,firstClick{false}
	,onBoard{false}
	,keystop{false}
{}

Board::~Board(){
	DeleteFontToHandle(hFont);
}

void Board::Init(){
	Block firstInitValue = {0,false,false};
	board.resize(WIDTH * HEIGHT, firstInitValue);
	keystop = true;
	firstClick = true;
	hFont = CreateFontToHandle("",BLOCK_SIZE,-1);
	assert(hFont > 0);
	
	// rand reset to bomb
	/*for(Block& aBlock:board){
		bool haveBomb = static_cast<bool>(GetRand(1));
		aBlock.bomb = haveBomb;
	}*/

	// bomb shuffle 
	BombShuffle();

	// count bomb around block
	CountBombAroundBlockAll();


}

void Board::Update(){
	Vec2 mousePosition;
	GetMousePoint(&mousePosition.x,&mousePosition.y);
	mouseIndex = (mousePosition - Vec2{ BOARD_X,BOARD_Y }) / Vec2{ BLOCK_SIZE,BLOCK_SIZE };

#ifdef _DEBUG
	//reset 
	if (CheckHitKey(KEY_INPUT_R)) {
		board.clear();
		Block firstInitValue = { 0,false,false };
		board.resize(WIDTH * HEIGHT, firstInitValue);
		firstClick = true;
		keystop = true;

		BombShuffle();

		for (int i = 0; i < board.size(); i++) {
			int bombNum = CountBombAroundBlock(i);
			board.at(i).nuber = bombNum;
		}

		auto gamecP = GetScene()->Invoke<GameClear>();
		if (gamecP) {
			gamecP->ResetClear();
		}
		auto gameoP = GetScene()->Invoke<GameOver>();
		if (gameoP) {
			gameoP->ResetOver();
		}
	}
#endif

	// confirming mouse on the board 
	bool left = mousePosition.x >= BOARD_X;
	bool up	  = mousePosition.y >= BOARD_Y;
	bool right= mousePosition.x <= BOARD_X + WIDTH  * BLOCK_SIZE ;
	bool down = mousePosition.y <= BOARD_Y + HEIGHT * BLOCK_SIZE ;

	onBoard = left && up && right && down;


	// mouse click
	
	// change flag active
	bool mouseRight = GetMouseInput() & MOUSE_INPUT_RIGHT;
	if (mouseRight && !keystop) {

		if (onBoard) {
			int index = mouseIndex.y * WIDTH + mouseIndex.x;
			// isn't open 
			if (!board.at(index).isOpen)
				board.at(index).flag = !board.at(index).flag;
		}
	}

	// block open
	bool mouseLeft = GetMouseInput() & MOUSE_INPUT_LEFT;
	if (mouseLeft && !keystop) {

		if (onBoard) {
			int index = mouseIndex.y * WIDTH + mouseIndex.x;
			// open true is skip
			if (!board.at(index).flag && !board.at(index).isOpen) {
				board.at(index).isOpen = true;

				// firstClick Or click block is bomb zero 
				
				if (!firstClick&& CountBombAroundBlock(index) == 0) {

					// open chain
					OpenAroundEmptyBlock(index);
				}
				if (firstClick) {
					//first delete bomb
					if (board.at(index).bomb) {
						board.at(index).bomb = false;
						struct EmptyBlock {
							Block aBlock;
							int oldNumber;
						};
						std::vector<EmptyBlock>emptyBlock;

						emptyBlock.reserve(board.size());
						for (int i = 0; i < board.size(); i++) {
							if (board.at(i).bomb)
								continue;
							if (i == index)
								continue;
							EmptyBlock send;
							send.aBlock = board.at(i);
							send.oldNumber = i;
							emptyBlock.emplace_back(send);
						}
						emptyBlock.shrink_to_fit();
						int oldBomb = index;
						int bombNum = GetRand(emptyBlock.size() - 1);
						if(bombNum!=0)
							oldBomb = emptyBlock.at(bombNum).oldNumber;
						
						board.at(oldBomb).bomb = true;
						CountBombAroundBlockAll();
					}



					OpenAroundEmptyBlock(index);
					firstClick = false;
				}
				
				CheckGameOver(index);
			}
		}
	}
	keystop = mouseRight || mouseLeft;

	CheckGameClear();
}

void Board::Draw() {
	auto overP = GetScene()->Invoke<GameOver>();


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
			if (block.bomb && block.isOpen)
				DrawCircle(posx+BLOCK_SIZE/2,posy+BLOCK_SIZE/2,BLOCK_SIZE/2,0x222222,TRUE);

			if(overP){
				if (block.bomb && overP->GetOver())
					DrawCircle(posx + BLOCK_SIZE / 2, posy + BLOCK_SIZE / 2, BLOCK_SIZE / 2, 0x222222, TRUE);
			}
#ifdef _DEBUG
			bool debugKeyD = CheckHitKey(KEY_INPUT_D);
			if (block.bomb && debugKeyD) 
				DrawCircle(posx + BLOCK_SIZE / 2, posy + BLOCK_SIZE / 2, BLOCK_SIZE / 2, 0x222222, TRUE);
			if(debugKeyD)
				DrawFormatString(posx,posy,0x0,"%d",block.nuber);
#endif
	//disp flag
			if (block.flag)
				DrawTriangle(posx+BLOCK_SIZE/2,posy,posx,posy+BLOCK_SIZE,posx+BLOCK_SIZE,posy+BLOCK_SIZE,0xffff00,FALSE);
	// disp bomb count
			if (block.isOpen && !block.bomb) {
				int size= GetDrawFormatStringWidthToHandle(hFont, "%d", block.nuber);
				DrawFormatStringToHandle(posx+size/2, posy, 0x0,hFont, "%d", block.nuber);
//				DrawFormatString(posx,posy,0x0,"%d",block.nuber);
			}
		}
	}
}

void Board::BombShuffle(){
	for (int i = 0; i < BOMB_MAX; i++) {
		board.at(i).bomb = true;
	}

 	std::random_shuffle(board.begin(),board.end(), [&](int i) {return GetRand(100)%i;});
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

void Board::CountBombAroundBlockAll(){
	// count bomb around block
	for (int i = 0; i < board.size(); i++) {
		int bombNum = CountBombAroundBlock(i);
		board.at(i).nuber = bombNum;
	}
}

void Board::OpenAroundEmptyBlock(int index) {
	if (index < 0 || board.size() <= index)
		return;

	for (int y = -1; y <= 1; y++) {
		for (int x = -1; x <= 1; x++) {
			int aroundX = (index % WIDTH) + x;
			int aroundY = (index / WIDTH) + y;

			if (aroundX < 0
				|| aroundY < 0
				|| aroundX >= WIDTH
				|| aroundY >= HEIGHT
				)
				continue;

			int aroundIndex = aroundY * WIDTH + aroundX;
			if (board.at(aroundIndex).bomb)
				continue;
			if (board.at(aroundIndex).isOpen)
				continue;

			board.at(aroundIndex).isOpen = true;

	// chain
			if(board.at(aroundIndex).nuber==0)
				OpenAroundEmptyBlock(aroundIndex);
		}
	}

}

void Board::CheckGameClear(){
	std::vector<Block>emptyBlock;
	emptyBlock.reserve(board.size());
	for (int i = 0; i < board.size(); i++) {
		Block block = board.at(i);
		if (block.isOpen)
			continue;

		emptyBlock.emplace_back(block);
	}
	emptyBlock.shrink_to_fit();




	if ((emptyBlock.size()) != BOMB_MAX)
		return;

	auto gameP= GetScene()->Invoke<GameClear>();
	if (!gameP)
		return;

	gameP->SetClear();

}

void Board::CheckGameOver(int index){
	if (!board.at(index).bomb)
		return;


	auto gameoP = GetScene()->Invoke<GameOver>();
	if (!gameoP)
		return;

	auto clear = GetScene()->Invoke<GameClear>();
	if (!clear)
		return;

	if (clear->GetClear())
		return;

	gameoP->SetOver();


}
