
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

	//stage_ = new Stage();
	//stage_->Init();

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
	//stage_->Update();

    enemy_->Update(*player_, 5.0f);

	// プレイヤー
    player_->Update();

    // ステージ当たり判定
    //FieldCollision(player_);
    //WallCollision(player_);

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

	//stage_->Draw();

    // ステージ
	stageMgr_->Draw();

	player_->Draw();

	player_->DrawDebug();

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

    VECTOR pos = player->GetPos();

    // カプセルの足元をチェックして地面の高さを取得
    VECTOR startPos = VAdd(pos, player->GetStartCapsulePos());
    VECTOR endPos = VAdd(pos, player->GetEndCapsulePos());

    int modelId_1 = stage_->GetModelId_1();
 
    MV1_COLL_RESULT_POLY Coll_Field_1 = MV1CollCheck_Line(modelId_1, -1, startPos, endPos);

    if (Coll_Field_1.HitFlag)
    {
        float groundY = Coll_Field_1.HitPosition.y;

        // プレイヤーが地面より下に落ちていたら補正するだけ
        if (pos.y < groundY)
        {
            pos.y = groundY;
            player->SetPos(pos);
        }
    }

    //int modelId_2 = stage_->GetModelId_2();

    //MV1_COLL_RESULT_POLY Coll_Field_2 = MV1CollCheck_Line(modelId_2, -1, startPos, endPos);

    //if (Coll_Field_2.HitFlag)
    //{
    //    float groundY = Coll_Field_2.HitPosition.y;

    //    // プレイヤーが地面より下に落ちていたら補正するだけ
    //    if (pos.y < groundY)
    //    {
    //        pos.y = groundY;
    //        player->SetPos(pos);
    //    }
    //}

    //int modelId_3 = stage_->GetModelId_3();

    //MV1_COLL_RESULT_POLY Coll_Field_3 = MV1CollCheck_Line(modelId_3, -1, startPos, endPos);

    //if (Coll_Field_3.HitFlag)
    //{
    //    float groundY = Coll_Field_3.HitPosition.y;

    //    // プレイヤーが地面より下に落ちていたら補正するだけ
    //    if (pos.y < groundY)
    //    {
    //        pos.y = groundY;
    //        player->SetPos(pos);
    //    }
    //}
}

// 壁との判定
void GameScene::WallCollision(Player* player)
{

    VECTOR pos = player->GetPos();

    // カプセルのワールド座標を算出
    VECTOR capStart = VAdd(pos, player->GetStartCapsulePos());
    VECTOR capEnd = VAdd(pos, player->GetEndCapsulePos());
    float  radius = player->GetCapsuleRadius();

    // ステージモデルとのカプセル衝突チェック
	int modelId_1 = stage_->GetModelId_1();
    auto hit_1 = MV1CollCheck_Capsule(modelId_1, -1, capStart, capEnd, radius);

    for (int i = 0; i < hit_1.HitNum; i++)
    {
        auto hit_a = hit_1.Dim[i];

        // 当たっていたら、法線方向に押し戻す
        pos = VAdd(pos, VScale(hit_a.Normal, 1.5f));
    }

    // 結果を反映
    player->SetPos(pos);

    //VECTOR pos_2 = player->GetPos();

    //VECTOR capStart_2 = VAdd(pos_2, player->GetStartCapsulePos());
    //VECTOR capEnd_2 = VAdd(pos_2, player->GetEndCapsulePos());

    //// ステージモデルとのカプセル衝突チェック
    //int modelId_2 = stage_->GetModelId_2();
    //auto hit_2 = MV1CollCheck_Capsule(modelId_2, -1, capStart_2, capEnd_2, radius);

    //for (int k = 0; k < hit_2.HitNum; k++)
    //{
    //    auto hit_b = hit_2.Dim[k];

    //    // 当たっていたら、法線方向に押し戻す
    //    pos_2 = VAdd(pos_2, VScale(hit_b.Normal, 2.0f));
    //}

    //// 結果を反映
    //player->SetPos(pos_2);

    //// ステージモデルとのカプセル衝突チェック
    //int modelId_3 = stage_->GetModelId_3();
    //auto hit_3 = MV1CollCheck_Capsule(modelId_3, -1, capStart, capEnd, radius);

    //for (int v = 0; v < hit_3.HitNum; v++)
    //{
    //    auto hit_c = hit_3.Dim[v];

    //    // 当たっていたら、法線方向に押し戻す
    //    pos = VAdd(pos, VScale(hit_c.Normal, 2.0f));
    //}

    //// 結果を反映
    //player->SetPos(pos);

    // 結果の破棄
    //MV1CollResultPolyDimTerminate(hit_1);
    //MV1CollResultPolyDimTerminate(hit_2);
    //MV1CollResultPolyDimTerminate(hit_3);

}