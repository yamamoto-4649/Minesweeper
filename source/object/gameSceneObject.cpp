#include "gameSceneObject.h"

#include"../component/gameEase.h"


GameSceneObject::GameSceneObject(Scene* sc)
	:Object(sc)
{
	Create<GameEase>();
}

GameSceneObject::~GameSceneObject()
{
}
