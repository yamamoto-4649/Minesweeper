#include "freeCamera.h"


namespace {
	static const float FastCameraPosY = 1000.f;
}

FreeCamera::FreeCamera(Scene* sc)
	:Object(sc)
	, position(VGet(0, 300,-500))
	,target(VGet(0,0,1))
	,tarPos(VGet(0, 300, -500))
	, rotation(VGet(0,0,0))
	, velocity(VGet(0,0,0))
	,mouse({0,0})
	,oldMouse({0,0})
{}
FreeCamera::~FreeCamera(){


}
void FreeCamera::Init(){


	MATRIX matrix = MGetTranslate(VGet(0, FastCameraPosY, -500));
	position = VTransform(position, matrix);
	tarPos = position;

	////�ŏ��̍������w��
	//position = VTransform(position,MGetTranslate(VGet(0, FastCameraPosY,0)));
	//tarPos = VTransform(tarPos,MGetTranslate(VGet(0, FastCameraPosY,0)));

	//�K�p
	SetCameraPositionAndTarget_UpVecY(position, target);

}
void FreeCamera::Update(){
		GetMousePoint(&mouse.x,&mouse.y);

	UpDownMove();


	if (GetMouseInput() & MOUSE_INPUT_RIGHT)
		DispMove();
	
	//MATRIX rotY = MGetRotY(rotation.y);
	//VECTOR offset = VGet(0, 300, -500);
	//offset = VTransform(offset, rotY);
	//position=VAdd(velocity, offset);

	Movement();

	//pos Resset
	if (CheckHitKey(KEY_INPUT_LCONTROL)) {

		position = VGet(0, 0, 0)		;
		target=VGet(0, 0, 1)		;
		tarPos=VGet(0, 300, -500)	;
		rotation=VGet(0, 0, 0)		;
		velocity=VGet(0, 0, 0)		;

		Init();
	}


	//printfDx("mVecX = %d\n",mVec.x);
	//printfDx("mVecY = %d\n",mVec.y);
	//printfDx("rotation.x = %f\n",rotation.x/DX_PI_F*180);
	//printfDx("rotation.y = %f\n",rotation.y/DX_PI_F*180);

	oldMouse = mouse;
}
void FreeCamera::Draw(){
	//DrawString(0,SCREEN_HEIGHT-GetFontSize(),"�E�N���b�N�Ŏ��_�ړ�",0xffffff);

	////MATRIX matrix = MGetTranslate(VGet(0, 300, -500));
	//MATRIX matrix = MGetTranslate(VGet(0, 0,0));
	//VECTOR pos = VTransform(position, matrix);
	////SetCameraPositionAndTarget_UpVecY(pos, target);

	MATRIX rotY = MGetRotY(rotation.y);
	//MATRIX move = MGetTranslate(VGet(0,300,-500));
	MATRIX move = MGetTranslate(tarPos);
	MATRIX rotX = MGetRotX(rotation.x);
	//MATRIX ans= MMult(move,rotY);
	VECTOR tar = VTransform(target,MMult(MMult(rotX, rotY), move));
	//MATRIX ans = MMult(rotX,rotY);
	//MATRIX ans2 = MMult(ans,move);
	//VECTOR tar = VTransform(target,ans2);

	SetCameraPositionAndTarget_UpVecY(VAdd(position,velocity),VAdd(tar,velocity));
	
	//DrawSphere3D(VGet(0,100,500),20,16,0xffffff,0xffffff,true);
	//
	//DrawSphere3D(tar,20,16,0xffffff,0xffffff,true);



}


VECTOR FreeCamera::GetDir(){

	MATRIX rotY = MGetRotY(rotation.y);
	MATRIX move = MGetTranslate(tarPos);
	MATRIX rotX = MGetRotX(rotation.x);

	VECTOR tar = VTransform(target, MMult(MMult(rotX, rotY), move));


	VECTOR vec = tar - position;

	vec = VScale(VNorm(vec),0.1f);

	return vec;
}

void FreeCamera::DispMove(){
Vec2 mVec = { mouse.x - oldMouse.x,oldMouse.y - mouse.y };
	mVec.x /= 1.5f;
	mVec.y /= 1.5f;

	float num = mVec.x*0.01;
	rotation.y += num;
	num = (mVec.y *0.9)* DX_PI_F / 180.0f;
	rotation.x += -num;


if (CheckHitKey(KEY_INPUT_LEFT)) {
		rotation.y -= 10 * DX_PI_F / 180.0f;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT) ){
		rotation.y += 10 * DX_PI_F / 180.0f;
	}
	if (CheckHitKey(KEY_INPUT_UP)) {
		rotation.x -= 10 * DX_PI_F / 180.0f;
	}
	if ( CheckHitKey(KEY_INPUT_DOWN)) {
		rotation.x += 10 * DX_PI_F / 180.0f;
	}
	if (rotation.x < -85* DX_PI_F / 180.0f)rotation.x = -85 * DX_PI_F / 180.0f;
	if (rotation.x > 85 *DX_PI_F / 180.0f)rotation.x = 85 * DX_PI_F / 180.0f;
	
}

void FreeCamera::UpDownMove(){
	const int NUM = 20;

bool upKey = CheckHitKey(KEY_INPUT_SPACE);
	bool downKey = CheckHitKey(KEY_INPUT_LSHIFT);
	if (upKey) {
		velocity.y += NUM;
	}
	if (downKey) {
		velocity.y += -NUM;
	}

}

void FreeCamera::Movement() {
	static float METERS = 100.f;
	static float MOVE_SPEED = METERS/3;// 25.5f;
	MOVE_SPEED=(GetMouseInput()&MOUSE_INPUT_RIGHT)?METERS/3:25.5f;
	
	bool wKey = CheckHitKey(KEY_INPUT_W);
	bool sKey = CheckHitKey(KEY_INPUT_S);
	bool aKey = CheckHitKey(KEY_INPUT_A);
	bool dKey = CheckHitKey(KEY_INPUT_D);
	
	Vec2 vec = {0,0};
	
	if (wKey) {
		vec.y = 1;
	}
	if (sKey) {
		vec.y = -1;

	}

	if (dKey) {
		vec.x = 1;

	}
	if (aKey) {
		vec.x = -1;

	}

	if (vec.x == 0 && vec.y == 0)
		return;

	float inputAngle = atan2(vec.x,vec.y);//���͂̊p�x
	MATRIX rotY = MGetRotY(inputAngle+rotation.y);	//Y���̉�]�s��
	VECTOR move = VGet(0, 0, MOVE_SPEED);//��]���ĂȂ��Ƃ��̈ړ��x�N�g��

	tarPos = VAdd(position, VTransform(move, rotY));
	position = VAdd(position, VTransform(move, rotY));
}
