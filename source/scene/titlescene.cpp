#include "titlescene.h"

#include<DxLib.h>
#include"../object/titleobject.h"

TitleScene::TitleScene(){
	//SetBackgroundColor(0xff,0xff,0x84);
	SetBackgroundColor(0xe5, 0xff, 0xff);

	Create<TitleObject>();


}
TitleScene::~TitleScene(){
}