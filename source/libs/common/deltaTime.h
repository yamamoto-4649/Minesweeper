#pragma once
#include<DxLib.h>

class DeltaTime {
public:
	DeltaTime() { time = GetNowHiPerformanceCount(); }
	//���C��Update�̈�ԍŌ�ɒu��
	void Update() { time = GetNowHiPerformanceCount(); }
	
	float GetDeltTime() {
		return (GetNowHiPerformanceCount() - time) / 1000000;
	}
private:
	double time;
};