
#include "../Application.h"
#include "../Common/Instance.h"
#include "../Manager/KeyManager.h"
#include "TitleScene.h"

TitleScene::TitleScene(void)
{
}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Init(void)
{
}

void TitleScene::Update(void)
{

	if (KEY::GetIns().GetInfo(KEY_TYPE::JUMP).down || KEY::GetIns().GetInfo(KEY_TYPE::JUMP).down)
	{
		Ins::scene().ChangeScene(SceneManager::SCENE_ID::GAME);
	}

}

void TitleScene::Draw(void)
{


	DrawBox(0, 0, Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, GetColor(0, 0, 255), TRUE);

	DrawString(100, 100, "Title Scene", GetColor(255, 255, 255));

}

void TitleScene::Release(void)
{
}
