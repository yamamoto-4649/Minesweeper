#pragma once
#include<DxLib.h>

namespace {
	static const int FPS = 60;	//�ݒ肵��FPS
}

class FpsTimer {
	int mStartTime;         //����J�n����
	int mCount;             //�J�E���^
	float mFps;             //fps
	const int N = 60;//���ς����T���v����

public:
	FpsTimer();
	void Update();
	void Draw();
	void Wait();
};