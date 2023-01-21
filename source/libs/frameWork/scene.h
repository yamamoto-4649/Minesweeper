#pragma once
#include<list>
#include<string>

class Object;

class Scene {
public:
	Scene()					;
	virtual ~Scene()		;
	virtual void Update()	;
	virtual void Draw()		;

	/// <summary>
	/// �I�u�W�F�N�g�̐���
	/// <para>���X�g�ɒǉ���
	/// �A�h���X��Ԃ�</para>
	/// </summary>
	/// <returns></returns>
	template<class C>
	C* Create() {
		C* tempObject= new C(this);
		ObjectParam node;
		node.object = tempObject;
		objectList.emplace_back(node);
		rankChange = true;
		return tempObject;
	}

	template<class C>
	C* Create(std::string name) {
		C* tempObject = new C(this);
		ObjectParam node;
		node.object = tempObject;
		node.name = name;
		objectList.emplace_back(node);
		rankChange = true;
		return tempObject;
	}

	/// <summary>
	/// <para>�I�u�W�F�N�g�̌Ăяo��</para>
	/// <para>�����N���X���ォ��1����Ă���</para>
	/// </summary>
	/// <returns></returns>
	template<class C>
	C* Invoke();


	//���O�Əォ��1�Ăяo��
	template<class C>
	C* Invoke(std::string name);

	//�����Ăяo��
	template<class C>
	std::list<C*> Invokes();

	//���O�ƃN���X�w��@�Ăяo��
	template<class C>
	std::list<C*> Invokes(std::string name);

	//���O���畡���Ăяo��
	std::list<Object*> Invokes(std::string name);

	/// <summary>
	/// <para>�I�u�W�F�N�g�̔j��</para>
	/// <para>�����N���X���ォ��1����</para>
	/// </summary>
	/// <typeparam name="C"></typeparam>
	template<class C>
	void Destroy();

	/// <summary>
	/// <para>�I�u�W�F�N�g�̔j��</para>
	/// <para>�����N���X���ォ��1����</para>
	/// </summary>
	/// <param name="object"></param>
	void Destroy(Object* object);

	/// <summary>
	/// �S�ẴI�u�W�F�N�g�X�V��~
	/// </summary>
	void AllUpdateStop();

	/// <summary>
	/// �S�ẴI�u�W�F�N�g�X�V�J�n
	/// </summary>
	void AllUpdateStart();

	/// <summary>
	/// �`��D�揇�ʕύX ����
	/// </summary>
	/// <param name="obj  ">�ύX�������I�u�W�F�N�g</param>
	/// <param name="rank">�D��x</param>
	void Scene::ChangeDispRank(Object* obj, int rank);

private:
	struct ObjectParam {
		bool wantInit;//������
		int dispRank;//draw�D�揇��
		std::string name;//������
		Object* object;//�I�u�W�F�N�g

		ObjectParam()
			:wantInit(true)
			,object(nullptr)
			,dispRank(100)
			,name{""}
		{}
	};

	void AllDestroy();//�S�ẴI�u�W�F�N�g���폜
	void DestroyDrawObject(Object* object);//�`��I�u�W�F�N�g�j��
	static bool DispSort(const ObjectParam& rank1, const ObjectParam& rank2);//����ւ�

	std::list<ObjectParam>objectList;//�I�u�W�F�N�g�L�^�p
	std::list<ObjectParam>objectDrawList;//�I�u�W�F�N�g�`��p
	bool rankChange;//�`��ύX�\��

};

template<class C>
inline C* Scene::Invoke() {
	for (ObjectParam node : objectList) {
		C* object = dynamic_cast<C*>(node.object);
		if (object != nullptr)
			return object;
	}
	return nullptr;
}

template<class C>
inline C* Scene::Invoke(std::string name) {
	for (ObjectParam& node : objectList) {
		C* object = dynamic_cast<C*>(node.object);
		if (object == nullptr)
			continue;
		if (node.name != name)
			continue;
		return object;
	}
	return nullptr;
}

template<class C>
inline std::list<C*> Scene::Invokes() {
	std::list<C*> list;
	for (auto& m : objectList) {
		C* object = dynamic_cast<C*>(m.object);
		if (object != nullptr)
			list.emplace_back(object);
	}
	return list;
}


template<class C>
std::list<C*> Scene::Invokes(std::string name) {
	std::list<C*>list;
	for (auto& m : objectList) {
		C* object = dynamic_cast<C*>(m.object);

		if (object == nullptr)
			continue;
		if (m.name != name)
			continue;

		list.emplace_back(object);
	}
	return list;
}

template<class C>
inline void Scene::Destroy() {
	for (auto it = objectList.begin(); it != objectList.end(); ) {
		C* object = dynamic_cast<C*>((*it).object);
		if (object != nullptr) {
			delete object;
			object = nullptr;

			it = objectList.erase(it);
			return;
		}
		else {
			++it;
		}
	}
}
