
#include "GameClear.h"
#include "../Common/Instance.h"

GameClear::GameClear(void)
{
}

GameClear::~GameClear(void)
{
}

void GameClear::Init(void)
{
}

void GameClear::Update(void)
{
	if (Ins::input().IsTrgDown(KEY_INPUT_SPACE))
	{
		Ins::scene().ChangeScene(SceneManager::SCENE_ID::TITLE);
	}
}

void GameClear::Draw(void)
{

	DrawBox(0, 0, Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, GetColor(0, 0, 255), TRUE);

	DrawString(100, 100, "GameClear Scene", GetColor(255, 255, 255));

}

void GameClear::Release(void)
{
}
