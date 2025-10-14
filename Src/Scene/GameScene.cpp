
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

    enemy_ = new Enemy();
    enemy_->Init(VGet(0, 0, 200)); // プレイヤーの前方に配置

    // ステージ
    stageA_ = new RoomType_A();
    stageA_->Init();

	// プレイヤーにショットマネージャーをセット
	shotMgr_ = new ShotManager();
	player_->SetShotManager(shotMgr_);

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

    enemy_->Update(*player_, 5.0f);

	// プレイヤー
    player_->Update();

    shotMgr_->Update();

    CheckCollision();


    // --- ゲームクリア・ゲームオーバー判定 ---
    if (player_->GetHP() <= 0)
    {
        Ins::scene().ChangeScene(SceneManager::GAME_OVER);
        return;
    }

    if (!enemy_->IsAlive())
    {
        Ins::scene().ChangeScene(SceneManager::GAME_CLEAR);
        return;
    }
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

    enemy_->Draw();

    // プレイヤーHP
    std::string playerHpText = "Player HP: " + std::to_string(player_->GetHP());
    DrawString(20, 50, playerHpText.c_str(), GetColor(0, 0, 0));

    // 敵HP（敵は1体想定）
    if (enemy_ && enemy_->IsAlive())
    {
        std::string enemyHpText = "Enemy HP: " + std::to_string(enemy_->GetHP());
        DrawString(20, 80, enemyHpText.c_str(), GetColor(255, 0, 0));
    }

    shotMgr_->Draw();

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

    enemy_->Release();
    delete enemy_;
    enemy_ = nullptr;

    shotMgr_->Release();
    delete shotMgr_;
    shotMgr_ = nullptr;

	pauseMenu_.Release();

}

void GameScene::CheckCollision()
{
    // プレイヤーの攻撃弾と敵の当たり判定
    if (enemy_ && enemy_->IsAlive())
    {
        for (auto& shot : shotMgr_->GetShots()) // GetShots() は ShotManager が保持する弾のリストを返す関数
        {
            if (!shot->IsAlive()) continue;

            VECTOR diff = VSub(enemy_->GetPos(), shot->GetPos());
            float dist = sqrtf(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);

            if (dist <= enemy_->GetRadius() + shot->GetCollisionRadius())
            {
                enemy_->TakeDamage(shot->GetDamage());
                shot->SetEnd(); // 弾を消す関数（既に作っていない場合は作る）
            }
        }
    }

    if (enemy_ && enemy_->IsAlive())
    {
        VECTOR diff = VSub(player_->GetPos(), enemy_->GetPos());
        float dist = sqrtf(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);

        if (dist <= player_->GetCollisionRadius() + enemy_->GetRadius())
        {
            player_->TakeDamage(1); // 衝突時のダメージ
        }
    }
}
