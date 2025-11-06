
#pragma once

#include "Base/SceneBase.h"

#include "../Application.h"

#include "../Debug/Grid.h"

#include "../Common/Camera.h"
#include "../Common/PauseMenu.h"

#include "../Object/Stage/Stage1_1.h"
#include "../Object/Player/Player.h"
#include "../Object/Enemy/Enemy.h"
#include "../Object/Shot/ShotManager.h"

class SceneManager;

class Grid;

class Camera;

class PauseMenu;

class RoomType_A;

class Player;

class Enemy;

class ShotManager;

class GameScene : public SceneBase
{
public:

	GameScene(void);
	~GameScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	void CheckCollision();

	void FieldCollision(Player* player);
	void WallCollision(Player* player);

private:

	// グリッド線
	Grid* grid_;

	// カメラ
	Camera* camera_;

	// ポーズメニュー
	PauseMenu* pauseMenu_;

	// ステージ
	Stage1_1* stage1_1;

	// プレイヤー
	Player* player_;

	// 敵
	Enemy* enemy_;

	ShotManager* shotMgr_;

	bool wasPauseVisible_;
};
