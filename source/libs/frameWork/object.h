#pragma once

#include"myDxLib.h"

#include<string>
#include<list>
class Scene;
class Component;

class Object {
public:
	Object(Scene* sc);
	virtual ~Object();
	virtual void Init()		;
	virtual void Update()	;
	virtual void Draw()		;


	/// <summary>
	/// �����V�[���擾
	/// </summary>
	/// <returns></returns>
	Scene* GetScene()			{ return myScene	;}



	/// <summary>
	/// �R���|�[�l���g�̐���
	/// <para>���X�g�ɒǉ���
	/// �A�h���X��Ԃ�</para>
	/// </summary>
	/// <returns></returns>
	template<class C>
	C* Create() {
		C* sendCom = new C(this);
		ComponentParam send;
		send.myComponent = sendCom;

		comPonentList.emplace_back(send);
		return sendCom;
	}
	/// <summary>
	/// �R���|�[�l���g�̐���
	/// <para>���X�g�ɒǉ���
	/// �A�h���X��Ԃ�</para>
	/// </summary>
	/// <returns></returns>
	template<class C>
	C* Create(std::string name) {
		C* sendCom = new C(this);
		ComponentParam send;
		send.myComponent = sendCom;
		send.name = name;

		comPonentList.emplace_back(send);
		return sendCom;
	}


	/// <summary>
	/// <para>�R���|�[�l���g�̌Ăяo��</para>
	/// <para>�����N���X���ォ��1����Ă���</para>
	/// </summary>
	/// <returns></returns>
	template<class C>
	C* Invoke() {
		for (auto& aCom : comPonentList) {
			C* send =  dynamic_cast<C*>(aCom.myComponent);
			if (!send)
				continue;

			return send;
		}

		return nullptr;
	}

	/// <summary>
	/// <para>�R���|�[�l���g�̔j��</para>
	/// <para>�����N���X���ォ��1����</para>
	/// </summary>
	/// <typeparam name="C"></typeparam>
	template<class C>
	void Destroy() {
		for (auto it = comPonentList.begin(); it != comPonentList.end();) {
			C* aCom = (*it);

			if (aCom) {
				delete aCom;
				it = comPonentList.erase(it);
			}
			else {
				it++;
			}

		}
	}

	void SetComponent(Component* setComponent);

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
	struct ComponentParam{
		Component* myComponent;
		std::string name;
		bool wantInit;

		ComponentParam()
			:myComponent(nullptr)
			,wantInit{true}
			,name("")
		{}
	};

	Scene* myScene		;//�����V�[��
	bool myDestroy		;//�j���t���O
	bool myStopUpdate	;//�X�V��~�t���O true�F��~
	std::list<ComponentParam>comPonentList;
	//std::list<Component*>comPonentList;
};
