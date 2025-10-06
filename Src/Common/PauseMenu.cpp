
#include "PauseMenu.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "instance.h"
#include <DxLib.h>

PauseMenu::PauseMenu()
{
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::Init() 
{

	PauseContinue_.pos = { DEFAULT_POS_X, DEFAULT_POS_Y - PAUSE_OFFSET_Y / 2 - PAUSE_SPACE };
	PauseContinue_.size = { PAUSE_OFFSET_X, PAUSE_OFFSET_Y };

	PauseExit_.pos = { DEFAULT_POS_X, DEFAULT_POS_Y + PAUSE_OFFSET_Y / 2 + PAUSE_SPACE };
	PauseExit_.size = { PAUSE_OFFSET_X, PAUSE_OFFSET_Y };

	LoadInit();

}

void PauseMenu::LoadInit()
{

	PauseContinueImg_      = LoadGraph((Application::PATH_UI + "Continue.png").c_str());
	PauseContinueHoverImg_ = LoadGraph((Application::PATH_UI + "Continue_hover.png").c_str());
	PauseExitImg_          = LoadGraph((Application::PATH_UI + "QuitGame.png").c_str());
	PauseExitHoverImg_     = LoadGraph((Application::PATH_UI + "QuitGam_hover.png").c_str());

}

void PauseMenu::Update()
{

	if (Ins::input().IsTrgDown(KEY_INPUT_ESCAPE)) {
		if (!IsVisible()) {
			Show();
		}
		else {
			Hide();
		}
	}

	if (!visible_) return;

	if (Ins::input().IsTrgMouseLeft())
	{
		if (CheckMousePointA(PauseContinue_)) {
			Ins::scene().ChangeScene(SceneManager::SceneId::GAME);
		}
		else if (CheckMousePointA(PauseExit_)) {
			DxLib_End();
			exit(0);
		}
	}

}

void PauseMenu::Draw()
{

	if (!visible_) return;

	// îºìßñæÉOÉåÅ[îwåi
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(0, 0, Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, GetColor(100, 100, 100), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// É{É^Éìï`âÊ
	bool isHoverReturn = CheckMousePointA(PauseContinue_);
	bool isHoverExit = CheckMousePointA(PauseExit_);

	DrawRotaGraph(PauseContinue_.pos.x, PauseContinue_.pos.y, 1.0f, 0.0f, isHoverReturn ? PauseContinueHoverImg_ : PauseContinueImg_, TRUE);

	DrawRotaGraph(PauseExit_.pos.x, PauseExit_.pos.y, 1.0f, 0.0f, isHoverExit ? PauseExitHoverImg_ : PauseExitImg_, TRUE);

}

void PauseMenu::Release(void)
{

	DeleteGraph(PauseContinueImg_);
	DeleteGraph(PauseContinueHoverImg_);
	DeleteGraph(PauseExitImg_);
	DeleteGraph(PauseExitHoverImg_);

}

void PauseMenu::Show() { visible_ = true; }

void PauseMenu::Hide() { visible_ = false; }

bool PauseMenu::IsVisible() const { return visible_; }