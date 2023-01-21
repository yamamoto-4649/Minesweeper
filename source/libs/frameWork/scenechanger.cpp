#include "scenechanger.h"

#include<Windows.h>
//#include<cassert>

#include"../../scene/bootScene.h"
#include"../../scene/titlescene.h"
#include"../../scene/gamescene.h"


Scene* SceneChanger::Changer(std::string scene) {
	if		(scene == "boot")		return new BootScene()		;//�f�o�b�O�p
	else if	(scene == "Title")		return new TitleScene()		;//�^�C�g��
	else if (scene == "Game")		return new GameScene()		;//�Q�[��
	else {
		MessageBox(NULL, ("���̃V�[���͂���܂���\n" + scene+"\n"+"�����������Ƒ��s�ł��܂�").c_str(), "SceneFactory", MB_ICONERROR | MB_OK);
		//assert(false);
		return nullptr;
	}

}
