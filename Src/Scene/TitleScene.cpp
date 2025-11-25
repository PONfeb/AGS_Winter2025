
#include "TitleScene.h"

#include "../Application.h"

#include "../Common/Instance.h"

#include "../Common/PauseMenu.h"

TitleScene::TitleScene(void)
{
}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Init(void)
{

	//img_ = LoadGraph((Application::PATH_TITLE + "Title.png").c_str());
	//if (img_ == -1)
	//{
	//	printfDx("Title.png “Ç‚Ýž‚ÝŽ¸”s\n");
	//}
	//else
	//{
	//	printfDx("Title.png “Ç‚Ýž‚Ý¬Œ÷ %d\n", img_);
	//}

	Ins::sound().LoadBGM("Title", (Application::PATH_SOUND + "Title.wav").c_str());
	Ins::sound().PlayBGM("Title");

	pauseMenu_ = new PauseMenu();
	pauseMenu_->Init();

}

void TitleScene::Update(void)
{

	pauseMenu_->Update();

	if (KEY::GetIns().GetInfo(KEY_TYPE::JUMP).down)
	{
		Ins::scene().ChangeScene(SceneManager::SCENE_ID::GAME);
	}

}

void TitleScene::Draw(void)
{

	//DrawRotaGraph(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y / 2, 1.f, 0, img_, true);

	DrawString(10, 10, "TitleScene", GetColor(255, 255, 255));
	pauseMenu_->Draw();

}

void TitleScene::Release(void)
{

	Ins::sound().StopBGM();

}
