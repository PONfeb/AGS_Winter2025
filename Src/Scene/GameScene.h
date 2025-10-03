
#pragma once

#include "SceneBase.h"
#include "../Application.h"
#include "../Debug/Grid.h"
#include "../Common/Camera.h"
#include "../Object/Stage/RoomType_A.h"
#include "../Object/Player/Player.h"

class SceneManager;

class Grid;

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

	// ステージ
	RoomType_A* stageA_;

	// プレイヤー
	Player* player_;
};
