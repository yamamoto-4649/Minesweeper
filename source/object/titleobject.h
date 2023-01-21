#pragma once
#include"../libs/frameWork/object.h"

class TitleObject :public Object {
public:
	TitleObject(Scene* sc)	;
	~TitleObject()	override;
	void Init()		override { Object::Init(); }
	void Update()	override { Object::Update(); }
	void Draw()		override { Object::Draw(); }

	/// <summary>
	/// �I������L�[����������
	/// </summary>
	/// <param name="true	">������</param>
	/// <param name="false	">�����ĂȂ�</param>
	/// <returns></returns>
	bool EndKeyInput()		;

private:
};