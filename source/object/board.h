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
		bool isOpen;
	};

	std::vector<Block>board;

};