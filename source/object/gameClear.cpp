#include "gameClear.h"

GameClear::GameClear(Scene* sc)
	:Object(sc)
	,isClear{false}
	,bombNum{0}
{}

GameClear::~GameClear(){

}

void GameClear::Init(){

}

void GameClear::Update(){

}

void GameClear::Draw(){
#ifdef _DEBUG
	DrawFormatString(64,64,0x0,"%d",bombNum);
#endif

	if ( !isClear)
		return;
	int oldSize= GetFontSize();
	SetFontSize(64);
	DrawString(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,"clear",0x0);
	SetFontSize(oldSize);
}

void GameClear::SetClear(){
	isClear = true;
}
