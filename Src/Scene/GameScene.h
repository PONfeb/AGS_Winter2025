
#pragma once

#include "SceneBase.h"
#include "../Debug/Grid.h"
#include "../Common/Camera.h"
#include "../Common/PauseMenu.h"
#include "../Object/Stage/RoomType_A.h"
#include "../Object/Player/Player.h"
#include "../Application.h"

class SceneManager;

class Grid;

class Camera;

class PauseMenu;

class RoomType_A;

class Player;

class GameScene : public SceneBase
{
public:

	GameScene(void);
	~GameScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:

	// グリッド線
	Grid* grid_;

	// カメラ
	Camera* camera_;

	// ポーズメニュー
	PauseMenu pauseMenu_;

	// ステージ
	RoomType_A* stageA_;

	// プレイヤー
	Player* player_;

	bool wasPauseVisible_;
};
