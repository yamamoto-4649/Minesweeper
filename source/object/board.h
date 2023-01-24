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
	/// <para>BOMB_MAXの数だけ爆弾を追加し</para>
	/// <para>boardの中身を混ぜる		  </para>
	/// </summary>
	void BombShuffle();
	/// <summary>
	/// <para>指定した要素の周りにある爆弾の個数を返す</para>
	/// <para>ボムや範囲外ならー１を返す</para>
	/// </summary>
	/// <param name="index">指定</param>
	/// <returns></returns>
	const int CountBombAroundBlock(int index);
	// 全ブロック周囲の爆弾を数える count bomb around block
	void CountBombAroundBlockAll();

	/// <summary>
	/// 指定した周りの爆弾じゃないブロックを連鎖して開ける
	/// </summary>
	void OpenAroundEmptyBlock(int index);

	void CheckGameClear();
	void CheckGameOver(int index);
};