#pragma once
class EASEING {
public:
//1��Ⴂ100�ŕԂ�	0�`100
	/*
	* ������l�܂ňړ�����
	*/
	

	static float EInOutSine(int x);
	static float EInOutQuad(int x);
	static float EInOutCubic(int x);
	static float EInOutQuart(int x);
	static float EInOutQuint(int x);
	static float EInOutExpo(int x);
	static float EInOutCirc(int x);
	static float EInOutBack(int x);
	static float EInOutElastic(int x);
	static float EInOutBounce(int x);

private:
	static float easeInOutSine(float x)	;
	static float easeInOutQuad(float x)	;
	static float easeInOutCubic(float x)	;
	static float easeInOutQuart(float x)	;
	static float easeInOutQuint(float x)	;
	static float easeInOutExpo(float x)	;
	static float easeInOutCirc(float x)	;
	static float easeInOutBack(float x)	;
	static float easeInOutElastic(float x)	;
	static float easeOutBounce(float x)	;
	static float easeInOutBounce(float x)	;
};