#pragma once

#include"../frameWork/myDxLib.h"
#include<string>

/// <summary>
/// 1�������� �����\��
/// </summary>
class OneCharacterSpacing {
public:
	OneCharacterSpacing();
	//~OneCharacterSpacing();
	//void Init();
	void Update();
	void Draw(float x,float y,int color);

	//�����ƃt�H���g�n���h����ݒ�
	void SetStr(std::string str);
	//�t�H���g�n���h���ݒ�
	void SetFont(int handle) { hFont = handle; }
	//�\���X�s�[�h��ύX�@�P�b������
	void SetSpeed(float speed) { dispSpeed = speed; }
	//���b�őS���\�����邩
	int GetSize();
	//�\���J�E���g�Ⴄ
	int GetCount() { return static_cast<int>(count); }

	//������S���\���������@true�F�S���\�����Ă���
	bool GetAllDisp();
	//������S���\������
	void AllDisp();
	
	//wstring��string�֕ϊ�
	static std::string WStringToString(std::wstring oWString);
	//string��wstring�֕ϊ�
	static std::wstring StringToWString(std::string oString);
private:


	std::wstring myWStr;
	float count;
	float dispSpeed;
	int hFont;
};