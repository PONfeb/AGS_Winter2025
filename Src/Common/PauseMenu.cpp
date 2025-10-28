
#include "PauseMenu.h"

#include <DxLib.h>

#include "instance.h"

PauseMenu::PauseMenu() : visible_(false), PauseContinueImg_(-1), PauseContinueHoverImg_(-1), PauseExitImg_(-1), PauseExitHoverImg_(-1)
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

	selected_ = ButtonID::NONE;

}

void PauseMenu::LoadInit()
{

	PauseContinueImg_      = LoadGraph((Application::PATH_PAUSE + "Continue.png").c_str());
	PauseContinueHoverImg_ = LoadGraph((Application::PATH_PAUSE + "Continue_hover.png").c_str());
	PauseExitImg_          = LoadGraph((Application::PATH_PAUSE + "QuitGame.png").c_str());
	PauseExitHoverImg_     = LoadGraph((Application::PATH_PAUSE + "QuitGame_hover.png").c_str());

	if (PauseContinueImg_ == -1) {
		printfDx("Continue.png 読み込み失敗\n");
	}

}

void PauseMenu::Update()
{

    // ポーズの表示切替
    if (KEY::GetIns().GetInfo(KEY_TYPE::MENU).down) {
        if (!visible_)
        {
            Show();
        }
        else
        {
            Hide();
        }
    }

    if (!visible_) return;

	// --- マウス操作 ---
    if (CheckMousePointA(PauseContinue_)) selected_ = ButtonID::CONTINUE;
    else if (CheckMousePointA(PauseExit_)) selected_ = ButtonID::EXIT;

	// --- キーボード操作 ---
    //if (KEY::GetIns().GetInfo(KEY_TYPE::UP).down) selected_ = ButtonID::CONTINUE;
    //else if (KEY::GetIns().GetInfo(KEY_TYPE::DOWN).down) selected_ = ButtonID::EXIT;

    // --- コントローラー操作 ---
    if (KEY::GetIns().GetInfo(KEY_TYPE::UP).down) selected_ = ButtonID::CONTINUE;
	else if (KEY::GetIns().GetInfo(KEY_TYPE::DOWN).down) selected_ = ButtonID::EXIT;

	if (KEY::GetIns().GetInfo(KEY_TYPE::APPLY).down)
	{
        if (selected_ == ButtonID::CONTINUE) {
            Hide(); // ポーズ解除
        }
        else if (selected_ == ButtonID::EXIT) {
			DxLib_End();
			exit(0);
        }
    }

}

void PauseMenu::Draw()
{

    if (!visible_) return;

#ifdef _DEBUG
    if (selected_ == ButtonID::CONTINUE)
    {
        DrawString(100, 300, "Continue", GetColor(255, 255, 255));
    }
	else if (selected_ == ButtonID::EXIT)
	{
		DrawString(100, 300, "Exit", GetColor(255, 255, 255));
	}
#endif // _DEBUG

    // 半透明背景
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
    DrawBox(0, 0, Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, GetColor(100, 100, 100), TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    // 現在の選択状態を反映して描画
    bool isHoverContinue = (CheckMousePointA(PauseContinue_) || selected_ == ButtonID::CONTINUE);
    bool isHoverExit     = (CheckMousePointA(PauseExit_) || selected_ == ButtonID::EXIT);

    if (selected_ == ButtonID::NONE) {
        isHoverContinue = false;
        isHoverExit = false;
    }

    DrawRotaGraph(PauseContinue_.pos.x, PauseContinue_.pos.y, 1.0f, 0.0f,
        isHoverContinue ? PauseContinueHoverImg_ : PauseContinueImg_, TRUE);

    DrawRotaGraph(PauseExit_.pos.x, PauseExit_.pos.y, 1.0f, 0.0f,
        isHoverExit ? PauseExitHoverImg_ : PauseExitImg_, TRUE);

}

void PauseMenu::Release(void)
{

	DeleteGraph(PauseContinueImg_);
	DeleteGraph(PauseContinueHoverImg_);
	DeleteGraph(PauseExitImg_);
	DeleteGraph(PauseExitHoverImg_);

}
