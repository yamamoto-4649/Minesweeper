#include "gameOver.h"

#include"../libs/frameWork/scene.h"
#include"gameClear.h"

GameOver::GameOver(Scene* sc)
	:Object(sc)
	,frameCounter{0}
	,hFont{-1}
	,isOver{false}
{
}

GameOver::~GameOver(){
	DeleteFontToHandle(hFont);
}

void GameOver::Init(){
	hFont = CreateFontToHandle("", -1, -1);
	assert(hFont>0);
}

void GameOver::Update(){
	auto gameClear = GetScene()->Invoke<GameClear>();
	if (gameClear)
		if (gameClear->GetClear())
			isOver = false;

	if (!isOver)
		return;
	frameCounter++;

	DeleteFontToHandle(hFont);
	hFont=CreateFontToHandle("",frameCounter>=64?64:frameCounter,-1);

}

void GameOver::Draw(){
	if (!isOver)
		return;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, frameCounter * 11 >= 255/3 ? 255/3 : frameCounter * 11);
	DrawBox(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,0x0,TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	Vec2 screenSize = { SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2 };
	int offsetX = GetDrawFormatStringWidthToHandle(hFont, "gameover") / 2;
	int offsetY = GetFontSizeToHandle(hFont) / 2;

	DrawStringToHandle(screenSize.x- offsetX, screenSize.y - offsetY, "gameover", 0xff0000,hFont);
}

void GameOver::ResetOver(){
	isOver = false;
	frameCounter = 0;
}
