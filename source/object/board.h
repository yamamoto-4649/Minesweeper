#pragma once
#include"../libs/frameWork/object.h"
#include<vector>

class Board :public Object {
public:
	Board(Scene* sc);
	~Board()override;
	void Init()override;
	void Update()override;
	void Draw()override;
private:
	struct Block {
		int number;
		bool bomb;
		bool flag;
		bool isOpen;

		Block()
			:number{0}
			,bomb{false}
			,flag{false}
			,isOpen{false}
		{}
	};
	
	std::vector<Block>board;


};