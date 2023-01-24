#pragma once
#include"../libs/frameWork/object.h"

class GameClear :public Object {
public:
	GameClear(Scene* sc);
	~GameClear()override;
	void Init()override;
	void Update()override;
	void Draw()	override;

	void SetClear();
	void ResetClear();
	void SetNum(int num) { bombNum = num; }
private:
	int bombNum;
	int winnerCounter;
	int hFont;
	int frameCounter;
	bool isClear;
	bool dispString;

};