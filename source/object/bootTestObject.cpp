#include "bootTestObject.h"

#include"../libs/frameWork/scenemanager.h"

BootTestObject::BootTestObject(Scene* sc)
	:Object		(sc)
	,hFont{-1}
{}
BootTestObject::~BootTestObject(){
	DeleteFontToHandle(hFont);
}
void BootTestObject::Init(){
	FillMaskScreen(0);

	hFont= CreateFontToHandle("",96,-1);
	assert(hFont > 0);
}
void BootTestObject::Update(){
	
	SceneChangeKey();
}
void BootTestObject::Draw() {
	//��̐���
	std::string explanation = "";
	explanation += "���� Debug Scene \n";
	explanation += "�uSpace key�v �� TitleScene\n";
	explanation += "�uSpace �� LeftShift key �� GameScene�v\n";
	DrawFormatString(100, 50, 0xff66ff,explanation.c_str());

	//�ҏW�p�̎咣
	std::string str = "�f�o�b�O�p�V�[��";

	DrawFormatStringToHandle(400 - str.size()*GetFontSizeToHandle(hFont), 600-128, 0xffffff, hFont, str.c_str());
}

void BootTestObject::SceneChangeKey() {
	bool spaceKey	= CheckHitKey(KEY_INPUT_SPACE)||(GetMouseInput()&MOUSE_INPUT_LEFT)||CheckHitKey(KEY_INPUT_RETURN);
	bool lShiftKey	= CheckHitKey(KEY_INPUT_LSHIFT);
	
	if (spaceKey&& !lShiftKey) 
		SceneManager::SceneChange("Title");

	if (spaceKey&& lShiftKey) 
		SceneManager::SceneChange("Game");
}
