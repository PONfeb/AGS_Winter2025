
#pragma once

#include "Base/SceneBase.h"

class SceneManager;

class Grid;

class Camera;

class PauseMenu;

class Stage;

class StageManager;

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

	Stage* stage_;

	// ステージ
	StageManager* stageMgr_;

	// プレイヤー
	Player* player_;

	// 敵
	Enemy* enemy_;

	ShotManager* shotMgr_;

	bool wasPauseVisible_;
};
