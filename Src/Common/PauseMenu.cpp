
#include "PauseMenu.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include <DxLib.h>

PauseMenu::PauseMenu()
{
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::Init() {

	pauseSelectImg_ = LoadGraph((Application::PATH_UI + "stage_select.png").c_str());
	pauseSelectHoverImg_ = LoadGraph((Application::PATH_UI + "stage_select_hover.png").c_str());
	pauseExitImg_ = LoadGraph((Application::PATH_UI + "game_exit.png").c_str());
	pauseExitHoverImg_ = LoadGraph((Application::PATH_UI + "game_exit_hover.png").c_str());

	pauseSelect_.pos = { DEFAULT_POS_X, DEFAULT_POS_Y - PAUSE_OFFSET_Y / 2 - PAUSE_SPACE };
	pauseSelect_.size = { PAUSE_OFFSET_X, PAUSE_OFFSET_Y };

	pauseExit_.pos = { DEFAULT_POS_X, DEFAULT_POS_Y + PAUSE_OFFSET_Y / 2 + PAUSE_SPACE };
	pauseExit_.size = { PAUSE_OFFSET_X, PAUSE_OFFSET_Y };
}

void PauseMenu::Update() {

	InputManager& input = InputManager::GetInstance();
	SceneManager& scene = SceneManager::GetInstance();

	if (input.IsTrgDown(KEY_INPUT_ESCAPE)) {
		if (!IsVisible()) {
			Show();
		}
		else {
			Hide();
		}
	}

	if (!visible_) return;

	if (input.IsTrgMouseLeft())
	{
		if (CheckMousePointA(pauseSelect_)) {
			scene.ChangeScene(SceneManager::SCENE_ID::SELECT);
		}
		else if (CheckMousePointA(pauseExit_)) {
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
	bool isHoverReturn = CheckMousePointA(pauseSelect_);
	bool isHoverExit = CheckMousePointA(pauseExit_);

	DrawRotaGraph(pauseSelect_.pos.x, pauseSelect_.pos.y, 1.0f, 0.0f, isHoverReturn ? pauseSelectHoverImg_ : pauseSelectImg_, TRUE);

	DrawRotaGraph(pauseExit_.pos.x, pauseExit_.pos.y, 1.0f, 0.0f, isHoverExit ? pauseExitHoverImg_ : pauseExitImg_, TRUE);
}

void PauseMenu::Release(void)
{
	DeleteGraph(pauseSelectImg_);
	DeleteGraph(pauseSelectHoverImg_);
	DeleteGraph(pauseExitImg_);
	DeleteGraph(pauseExitHoverImg_);
}

void PauseMenu::Show() { visible_ = true; }

void PauseMenu::Hide() { visible_ = false; }

bool PauseMenu::IsVisible() const { return visible_; }