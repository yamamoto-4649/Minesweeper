#include "fpstimer.h"

FpsTimer::FpsTimer()
	:mStartTime(0)
	,mCount(0)
	,mFps(0)
{
}

void FpsTimer::Update(){
	//�P�t���[���ڂȂ玞�����L��
	if (mCount == 0)
		mStartTime = GetNowCount();

	//�U�O�t���[���ڂȂ畽�ς��v�Z
	if (mCount == N) {
		int nowTime = GetNowCount();
		mFps = 1000.f/((nowTime - mStartTime) / static_cast<float>(N));
		mCount = 0;
		mStartTime = nowTime;
	}

	mCount++;

}

void FpsTimer::Draw(){
	DrawFormatString(0, 0,0xffffff, "%.1f", mFps);
}

void FpsTimer::Wait(){
	int tookTime = GetNowCount() - mStartTime;		//������������
	int waitTime = mCount * 1000 / FPS - tookTime;	//�҂ׂ�����
	if (waitTime > 0)
		Sleep(waitTime);	//�ҋ@
}
