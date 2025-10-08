
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
#ifdef _DEBUG
    grid_ = new Grid();
    grid_->Init();
#endif

    // プレイヤーを先に作成
    player_ = new Player();
    player_->Init("player.mv1");

    // ステージ
    stageA_ = new RoomType_A();
    stageA_->Init();

    // カメラ
    auto camera = Ins::scene().GetCamera();
    camera->ChangeMode(Camera::MODE::FOLLOW);
    camera->SetBeforeDrawFollow(player_); // ここでプレイヤーをセット

    pauseMenu_.Init();
    wasPauseVisible_ = false;
}

void GameScene::Update(void)
{

    // まず入力処理
    pauseMenu_.Update(); // ポーズ画面の更新は必ず呼ぶ

    if (pauseMenu_.IsVisible()) {
        if (!wasPauseVisible_) {
            wasPauseVisible_ = true;
            // BGM停止など
        }
        // ポーズ中はゲーム本体の更新をスキップ
        return;
    }
    else {
        if (wasPauseVisible_) {
            wasPauseVisible_ = false;
            // BGM再開など
        }
    }

#ifdef _DEBUG
    // グリッド線
    grid_->Update();
#endif // _DEBUG

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
    
#ifdef _DEBUG
    // グリッド線
    grid_->Draw();
#endif // _DEBUG

    // カメラの設定は SceneManager 側でやっているのでここでは不要
    stageA_->Draw();

	player_->Draw();

    pauseMenu_.Draw();

}

void GameScene::Release(void)
{

#ifdef _DEBUG
    // グリッド線
    grid_->Release();
    delete grid_;
    grid_ = nullptr;
#endif // _DEBUG

    stageA_->Release();
    delete stageA_;
    stageA_ = nullptr;

	// プレイヤー
	player_->Release();
	delete player_;
	player_ = nullptr;

	pauseMenu_.Release();

}
