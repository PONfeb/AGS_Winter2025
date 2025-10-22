
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
    if (KEY::GetIns().GetInfo(KEY_TYPE::GAME_END).down) {
        visible_ = false;
    }

    if (!visible_) return;

    // --- マウス優先処理 ---
    bool mouseHoverContinue = CheckMousePointA(PauseContinue_);
    bool mouseHoverExit = CheckMousePointA(PauseExit_);


    // マウスがどちらかに重なっている場合はマウス操作を優先
    if (mouseHoverContinue) selected_ = ButtonID::CONTINUE;

    else if (mouseHoverExit) selected_ = ButtonID::EXIT;

    // --- コントローラー・キーボード操作 ---
    if (KEY::GetIns().IsLeftStickUpTriggered()) {
        selected_ = ButtonID::CONTINUE;
    }
    else if (KEY::GetIns().IsLeftStickDownTriggered()) {
        selected_ = ButtonID::EXIT;
    }

    // --- 決定入力（共通） ---
    if (KEY::GetIns().GetInfo(KEY_TYPE::ATTACK).down)
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

    // 半透明背景
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
    DrawBox(0, 0, Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, GetColor(100, 100, 100), TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    // 現在の選択状態を反映して描画
    bool isHoverContinue = (selected_ == ButtonID::CONTINUE);
    bool isHoverExit     = (selected_ == ButtonID::EXIT);

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
