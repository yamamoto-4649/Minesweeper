#pragma once
#include"../libs/frameWork/object.h"
#include<vector>

class Board :public Object {
public:
	Board(Scene* sc);
	~Board()		override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;
private:
	struct Block {
		int nuber;
		bool bomb;
		bool flag;
		bool isOpen;
	};

	std::vector<Block>board;
	Vec2 mouseIndex;
	int hFont;
	bool firstClick;
	bool onBoard;
	bool keystop;

	/// <summary>
	/// <para>BOMB_MAX�̐��������e��ǉ���</para>
	/// <para>board�̒��g��������		  </para>
	/// </summary>
	void BombShuffle();
	/// <summary>
	/// <para>�w�肵���v�f�̎���ɂ��锚�e�̌���Ԃ�</para>
	/// <para>�{����͈͊O�Ȃ�[�P��Ԃ�</para>
	/// </summary>
	/// <param name="index">�w��</param>
	/// <returns></returns>
	const int CountBombAroundBlock(int index);
	// �S�u���b�N���͂̔��e�𐔂��� count bomb around block
	void CountBombAroundBlockAll();

	/// <summary>
	/// �w�肵������̔��e����Ȃ��u���b�N��A�����ĊJ����
	/// </summary>
	void OpenAroundEmptyBlock(int index);

	void CheckGameClear();
	void CheckGameOver(int index);
};