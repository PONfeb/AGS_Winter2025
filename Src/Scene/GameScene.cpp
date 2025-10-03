
#include "GameScene.h"
#include "../Common/Instance.h"

GameScene::GameScene(void)
{
}

GameScene::~GameScene(void)
{
}

void GameScene::Init(void)
{
    // グリッド線
    grid_ = new Grid();
    grid_->Init();

    // カメラは SceneManager 管理のものを使う
    Ins::scene().GetCamera()->ChangeMode(Camera::MODE::FREE);

    // ステージ
    stageA_ = new RoomType_A();
    stageA_->Init();

	// プレイヤー
	player_ = new Player();
    player_->Init("player.mv1");
}

void GameScene::Update(void)
{
    // グリッド線
    grid_->Update();

    // カメラ更新（SceneManager のカメラを使う）
    Ins::scene().GetCamera()->Update();

    stageA_->Update();

	// プレイヤー
    player_->Update();
}

void GameScene::Draw(void)
{
    DrawBox(0, 0, Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, GetColor(255, 255, 255), TRUE);
    DrawString(0, 0, "Game Scene", GetColor(0, 0, 0));

    // グリッド線
    grid_->Draw();

    // カメラの設定は SceneManager 側でやっているのでここでは不要
    stageA_->Draw();

	player_->Draw();
}

void GameScene::Release(void)
{
    // グリッド線
    grid_->Release();
    delete grid_;
    grid_ = nullptr;

    stageA_->Release();
    delete stageA_;
    stageA_ = nullptr;

	// プレイヤー
	player_->Release();
	delete player_;
	player_ = nullptr;
}
