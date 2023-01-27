#pragma once
#include"../libs/frameWork/object.h"

class GameSceneObject :public Object {
public:
	GameSceneObject(Scene* sc);
	~GameSceneObject()	;
	void Init()override;
	void Update()override;
	void Draw()override;
private:
	int counter;
	float anser;

};
