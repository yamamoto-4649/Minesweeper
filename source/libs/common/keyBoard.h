#pragma once

class KeyBoard {
public:
	KeyBoard();
	KeyBoard(int keyNumber);
	void SetKey(int keyNumber) { key = keyNumber; }
	//�������P�t���[��
	bool KeyDown();
	//�������P�t���[��
	bool KeyUp();
	//����������
	bool KeyDownKeep();
private:
	bool keystop;
	int key;
};