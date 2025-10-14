
#include "GameOver.h"
#include "../Common/Instance.h"

GameOver::GameOver(void)
{
}

GameOver::~GameOver(void)
{
}

void GameOver::Init(void)
{
}

void GameOver::Update(void)
{
	if (Ins::input().IsTrgDown(KEY_INPUT_SPACE))
	{
		Ins::scene().ChangeScene(SceneManager::SceneId::TITLE);
	}
}

void GameOver::Draw(void)
{

	DrawBox(0, 0, Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, GetColor(0, 0, 255), TRUE);

	DrawString(100, 100, "GameOver Scene", GetColor(255, 255, 255));

}

void GameOver::Release(void)
{
}
