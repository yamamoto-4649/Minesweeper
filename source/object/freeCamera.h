#pragma once
#include"../libs/frameWork/object.h"

/// <summary>
/// ���R�J����
/// </summary>
class FreeCamera :public Object {
public:
	FreeCamera(Scene* sc);
	~FreeCamera()		override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;

	//�J�������W
	const VECTOR& GetPos() { return position+velocity; }
	void SetPos(VECTOR pos) { position = pos; }
	void SetTar(VECTOR tar) { target = tar; }
	//�J���������x�N�g��
	VECTOR GetDir();
	//const VECTOR& GetRot() { return rotation; }
private:
	void DispMove();
	void UpDownMove();
	void Movement();


	VECTOR position;
	VECTOR target;
	VECTOR tarPos;
	VECTOR velocity;
	VECTOR rotation;
	Vec2 mouse;
	Vec2 oldMouse;

};