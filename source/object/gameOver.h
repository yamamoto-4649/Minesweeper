#pragma once
#include"../libs/frameWork/object.h"

class GameOver :public Object {
public:
	GameOver(Scene* sc);
	~GameOver()override;
	void Init()override;
	void Update()override;
	void Draw()override;

	void ResetOver();
	void SetOver() { isOver = true; }
	bool GetOver() { return isOver; }
private:
	int frameCounter;
	int hFont;
	bool isOver;

};
