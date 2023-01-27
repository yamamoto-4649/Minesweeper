#include "titleobject.h"

#include"../libs/frameWork/scenemanager.h"
#include"../libs/common/keyManager.h"

namespace {
	KeyManager* keys = nullptr;
}

TitleObject::TitleObject(Scene* sc)
	:Object(sc)
	,hFont{-1}
	,keystop{true}
	,mouseInput{false}
{}

TitleObject::~TitleObject(){
	DeleteFontToHandle(hFont);

}

void TitleObject::Init(){

	hFont = CreateFontToHandle("",64,-1);
	assert(hFont > 0);


	keys = new KeyManager();
	std::vector<int>keyNumberList;
	keyNumberList.reserve(10);
	keyNumberList.emplace_back(KEY_INPUT_SPACE);
	keyNumberList.emplace_back(KEY_INPUT_RETURN);
	keyNumberList.emplace_back(KEY_INPUT_TAB);
	keyNumberList.emplace_back(KEY_INPUT_ESCAPE);
	keyNumberList.shrink_to_fit();
	keys->SetKey(keyNumberList);
}

void TitleObject::Update(){
	bool mouse = GetMouseInput() & MOUSE_INPUT_LEFT;
	mouseInput = mouse && !keystop;
	keystop = mouse;

	if (mouseInput || keys->Down(KEY_INPUT_SPACE)) {
		SceneManager::SceneChange("Game");
	}

}

void TitleObject::Draw(){

	DrawFormatStringToHandle(200,200,0x7fbfff, hFont, u8"Title");

	DrawFormatString(300,400,0x1,"スペースキー,エンター,マウス左を押してGameScene");

}

bool TitleObject::EndKeyInput(){

	return keys->Down(KEY_INPUT_ESCAPE);
}
