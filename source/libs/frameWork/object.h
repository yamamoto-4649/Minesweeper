#pragma once

#include"myDxLib.h"

#include<string>
#include<list>
class Scene;

class Object {
public:
	Object(Scene* sc)		
		:myScene(sc)
		,myDestroy{false}
		,myStopUpdate{false}
	{}
	virtual ~Object()		{}
	virtual void Init()		{}
	virtual void Update()	{}
	virtual void Draw()		{}


	/// <summary>
	/// �����V�[���擾
	/// </summary>
	/// <returns></returns>
	Scene* GetScene()			{ return myScene	;}




	/// <summary>
	/// �j���t���O�@�Q�b�^�[
	/// </summary>
	/// <returns></returns>
	const bool GetDestroy()		{ return myDestroy	;}

	/// <summary>
	/// �X�V��~�t���O�@�Q�b�^�[
	/// </summary>
	/// <returns></returns>
	const bool GetStopUpdate() { return myStopUpdate; }

	/// <summary>
	/// �j���t���O�@�Z�b�^�[
	/// </summary>
	/// <param name="_flag"></param>
	void MyDestroy()			{ myDestroy = true	;}

	/// <summary>
	/// �X�V��~�t���O�@�Z�b�^�[
	/// </summary>
	/// <param name="true	">stop</param>
	/// <param name="false	">start</param>
	/// <returns></returns>
	void SetMyUpdate(bool flag = false) { myStopUpdate = flag; }

private:

	Scene* myScene		;//�����V�[��
	bool myDestroy		;//�j���t���O
	bool myStopUpdate	;//�X�V��~�t���O true�F��~
};
