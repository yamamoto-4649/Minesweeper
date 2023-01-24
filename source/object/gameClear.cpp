#include "gameClear.h"

#include"../libs/frameWork/scene.h"
#include"gameOver.h"

GameClear::GameClear(Scene* sc)
	:Object(sc)
	,winnerCounter{0}
	,hFont{-1}
	,frameCounter{0}
	,isClear{false}
	,dispString{false}
{}

GameClear::~GameClear(){
	DeleteFontToHandle(hFont);
}

void GameClear::Init(){
	hFont= CreateFontToHandle("",-1,-1,-1);
	assert(hFont > 0);
}

void GameClear::Update(){
	auto gameOver= GetScene()->Invoke<GameOver>();
	if (gameOver)
		if (gameOver->GetOver())
			isClear = false;


	if ( !isClear)
		return;

	frameCounter++;

	if(winnerCounter>= 64)
		dispString = true;
	else
		winnerCounter++;

	if (!dispString) {

	DeleteFontToHandle(hFont);
	hFont = CreateFontToHandle("", winnerCounter, -1, -1);
	}

	if (dispString && isClear) {
		DeleteFontToHandle(hFont);
		hFont = CreateFontToHandle("", 64, -1, -1);


	}


}

void GameClear::Draw(){

	if ( !isClear)
		return;
	Vec2 screenMiddle = { SCREEN_WIDTH / 2 ,SCREEN_HEIGHT / 2};
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,frameCounter*10>=255?255:frameCounter*10);
	int boxSizeRadius = 100;
	DrawBox( 0,0
			,SCREEN_WIDTH,SCREEN_HEIGHT, 0xffffff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);


	int offsetX = GetDrawFormatStringWidthToHandle(hFont,"clear") / 2;
	int offsetY = GetFontSizeToHandle(hFont)/2;
	DrawStringToHandle(screenMiddle.x-offsetX, screenMiddle.y-offsetY, "clear", 0x0,hFont);


	if ( !dispString)
		return;


	DrawStringToHandle(screenMiddle.x-offsetX, screenMiddle.y-offsetY,"clear",0x0,hFont);
}

void GameClear::SetClear(){
	isClear = true;
}

void GameClear::ResetClear() { 
	winnerCounter = 0;
	frameCounter = 0;
	isClear = false;
	dispString = false;
}