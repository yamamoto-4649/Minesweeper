#include "board.h"

namespace {
	static const int WIDTH = 9;
	static const int HEIGHT = 9;
	static const int DEPTH = 9;
	static const int BOMB_MAX = (WIDTH * HEIGHT * DEPTH)/8;
	static const int BLOCK_SIZE = 64;
}

Board::Board(Scene* sc)
	:Object(sc)
	,board()
{}

Board::~Board(){

}

void Board::Init(){
	board.resize(WIDTH * HEIGHT * DEPTH);

}

void Board::Update(){

}

void Board::Draw() {
	for (int z = 0; z < DEPTH; z++) {
		for (int y = 0; y < HEIGHT; y++) {
			for (int x = 0; x < WIDTH; x++) {
				int index = x + y * WIDTH + z * HEIGHT*WIDTH;


				VECTOR pos = VGet(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, DEPTH*BLOCK_SIZE/4);
				pos += VGet(x * BLOCK_SIZE, y * BLOCK_SIZE, z * BLOCK_SIZE);
				VECTOR size = VGet(BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
				
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255/2);
				DrawCube3D(pos - size / VGet(2, 2, 2), pos + size / VGet(2, 2, 2), 0xffffff, 0xffffff, TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
				DrawCube3D(pos - size / VGet(2, 2, 2), pos + size / VGet(2, 2, 2), 0,0, FALSE);
			
			}
		}
	}

}
