
#include "GameScene.h"

#include "../Application.h"

#include "../Debug/Grid.h"

#include "../Common/Instance.h"
#include "../Common/Camera.h"
#include "../Common/PauseMenu.h"

#include "../Object/Stage/Stage.h"
#include "../Object/Stage/StageManager.h"

#include "../Object/Player/Player.h"

#include "../Object/Enemy/Enemy.h"

#include "../Object/Shot/ShotManager.h"


GameScene::GameScene(void) : stageMgr_(nullptr), enemy_(nullptr), player_(nullptr), camera_(nullptr), shotMgr_(nullptr), grid_(nullptr), pauseMenu_(nullptr), wasPauseVisible_(false)
{
}

GameScene::~GameScene(void)
{
}

void GameScene::Init(void)
{

#ifdef _DEBUG
	// グリッド線
    //grid_ = new Grid();
    //grid_->Init();
#endif

    // プレイヤー
    player_ = new Player();
    player_->Init();

    // カメラ
    camera_ = new Camera();
	camera_->Init();
    camera_->SetFollow(player_);
	camera_->ChangeMode(Camera::MODE::FOLLOW);

    enemy_ = new Enemy();
    enemy_->Init(VGet(0, 0, 200));

    // ステージ情報
	stageMgr_ = new StageManager();
    stageMgr_->Init();

	// プレイヤーにショットマネージャーをセット
	shotMgr_ = new ShotManager();
	player_->SetShotManager(shotMgr_);

    pauseMenu_ = new PauseMenu();
    pauseMenu_->Init();

    wasPauseVisible_ = false;

}

void GameScene::Update(void)
{

    // まず入力処理
    pauseMenu_->Update(); // ポーズ画面の更新は必ず呼ぶ

    if (pauseMenu_->IsVisible()) {
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
    //// グリッド線
    //grid_->Update();
#endif // _DEBUG

    // カメラ更新
    camera_->Update();

    // ステージ更新
	stageMgr_->Update();

    enemy_->Update(*player_, 5.0f);

	// プレイヤー
    player_->Update();

    // ステージ当たり判定
    FieldCollision(player_);
    WallCollision(player_);

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

    DrawBox(0, 0, Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, GetColor(0, 0, 0), TRUE);
    DrawString(0, 0, "Game Scene", GetColor(0, 0, 0));
    
#ifdef _DEBUG
    //// グリッド線
    //grid_->Draw();
#endif // _DEBUG

    camera_->SetBeforeDraw();
	camera_->DrawDebug();

    // ステージ
	stageMgr_->Draw();

	player_->Draw();

	player_->DrawDebug();

    enemy_->Draw();


    shotMgr_->Draw();

    pauseMenu_->Draw();

}

void GameScene::Release(void)
{

#ifdef _DEBUG
    //// グリッド線
    //grid_->Release();
    //delete grid_;
    //grid_ = nullptr;
#endif // _DEBUG

    camera_->Release();
	delete camera_;
	camera_ = nullptr;

	// ステージ
	stageMgr_->Release();
	delete stageMgr_;
	stageMgr_ = nullptr;

	//stage_->Release();
	//delete stage_;
	//stage_ = nullptr;

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

    pauseMenu_->Release();
    delete pauseMenu_;
    pauseMenu_ = nullptr;

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
                shot->SetEnd();
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

// 床との判定
void GameScene::FieldCollision(Player* player)
{
    auto& stages = stageMgr_->GetStages(); // 3つ全部

    VECTOR pos = player->GetPos();
    VECTOR startPos = VAdd(pos, player->GetStartCapsulePos());
    VECTOR endPos = VAdd(pos, player->GetEndCapsulePos());

    for (auto& stage : stages)
    {
        const auto& ids = stage->GetModelIds();
        if (ids.empty()) continue;  // ←必須

        for (int modelId : ids)    // 複数モデル対応
        {
            if (modelId < 0) continue;

            MV1_COLL_RESULT_POLY hit = MV1CollCheck_Line(modelId, -1, startPos, endPos);

            if (hit.HitFlag)
            {
                float groundY = hit.HitPosition.y;

                if (pos.y < groundY)
                {
                    pos.y = groundY;
                    player->SetPos(pos);
                    return;
                }
            }
        }
    }
}

// 壁との判定
void GameScene::WallCollision(Player* player)
{
    auto& stages = stageMgr_->GetStages();

    VECTOR pos = player->GetPos();
    VECTOR capStart = VAdd(pos, player->GetStartCapsulePos());
    VECTOR capEnd = VAdd(pos, player->GetEndCapsulePos());
    float radius = player->GetCapsuleRadius();

    for (auto& stage : stages)
    {
        const auto& ids = stage->GetModelIds();
        if (ids.empty()) continue;

        for (int modelId : ids)
        {
            if (modelId < 0) continue;

            auto hit = MV1CollCheck_Capsule(modelId, -1, capStart, capEnd, radius);

            for (int i = 0; i < hit.HitNum; i++)
            {
                pos = VAdd(pos, VScale(hit.Dim[i].Normal, 1.5f));
            }

            MV1CollResultPolyDimTerminate(hit);
        }
    }

    player->SetPos(pos);
}