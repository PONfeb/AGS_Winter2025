
#include "EnemyManager.h"
//#include "EnemyWarrior.h"
//#include "EnemyWitch.h"
#include "../Player/Player.h"
#include "../../Application.h"

#include <DxLib.h>
#include <algorithm>
#include <random>

EnemyManager::EnemyManager(Player* player)
    : player_(player), level_(LEVEL::LEVEL1), cntSpawn_(0), enemyToSpawn_(0)
{
    std::random_device rd;
    mt_ = std::mt19937(rd());
}

EnemyManager::~EnemyManager()
{
    Release();
}

void EnemyManager::Init(LEVEL level)
{
    level_ = level;
    cntSpawn_ = 0;
    enemys_.clear();

    // モデルロード（必要に応じてロード済みならここでスキップ）
    enemyModelIds_.clear();
    enemyModelIds_.emplace_back(MV1LoadModel((Application::PATH_MODEL + "Enemy/Demon.mv1").c_str()));
    enemyModelIds_.emplace_back(MV1LoadModel((Application::PATH_MODEL + "Enemy/Wizard.mv1").c_str()));
    enemyModelIds_.emplace_back(MV1LoadModel((Application::PATH_MODEL + "Enemy/Giant.mv1").c_str()));

    attackEffectModelIds_.clear();
    attackEffectModelIds_.emplace_back(MV1LoadModel((Application::PATH_MODEL + "Effect/Fireball/Fireball.mv1").c_str()));
    attackEffectModelIds_.emplace_back(MV1LoadModel((Application::PATH_MODEL + "Effect/Fireball/Rock.mv1").c_str()));

    switch (level_)
    {
    case LEVEL::LEVEL1: 
        enemyToSpawn_ = 10; 
        break;
    case LEVEL::LEVEL2: 
        enemyToSpawn_ = 15; 
        break;
    case LEVEL::LEVEL3: 
        enemyToSpawn_ = 25; 
        break; // ボス1体
    }

    // LEVEL3以外は最初に1体だけスポーンしておく
    if (enemyToSpawn_ > 0)
    {
        std::uniform_int_distribution<int> dist(0, 2);
        int typeIdx = dist(mt_);
        EnemyBase* enemy = CreateEnemyByType(static_cast<EnemyBase::TYPE>(typeIdx));
        enemys_.push_back(enemy);
        enemyToSpawn_--;
    }
    //else if (level_ == LEVEL::LEVEL3)
    //{
    //    // ボス生成
    //    EnemyBase* boss = new EnemyBoss();
    //    boss->Init(EnemyBase::TYPE::GIANT,
    //        enemyModelIds_[static_cast<int>(EnemyBase::TYPE::GIANT)],
    //        attackEffectModelIds_[0],
    //        player_);
    //    enemys_.push_back(boss);
    //    enemyToSpawn_--;
    //}
}

void EnemyManager::Update()
{
    // スポーン間隔管理（LEVEL1,2のみ）
    if (enemyToSpawn_ > 0)
    {
        if (cntSpawn_ <= 0)
        {
            std::uniform_int_distribution<int> dist(0, 2);
            int typeIdx = dist(mt_);
            EnemyBase* enemy = CreateEnemyByType(static_cast<EnemyBase::TYPE>(typeIdx));
            enemys_.push_back(enemy);
            enemyToSpawn_--;
            cntSpawn_ = 60; // 1秒間隔
        }
        else
        {
            cntSpawn_--;
        }
    }

    // 既存敵の更新
    for (auto* enemy : enemys_)
    {
        if (enemy) enemy->Update();
    }
}

void EnemyManager::Draw()
{
    for (auto* enemy : enemys_)
    {
        if (enemy) enemy->Draw();
    }
}

void EnemyManager::Release()
{
    for (auto* enemy : enemys_)
    {
        if (enemy)
        {
            enemy->Release();
            delete enemy;
        }
    }
    enemys_.clear();

    for (int id : enemyModelIds_)
    {
        MV1DeleteModel(id);
    }
    for (int id : attackEffectModelIds_)
    {
        MV1DeleteModel(id);
    }
}

EnemyBase* EnemyManager::CreateEnemyByType(EnemyBase::TYPE type)
{
    EnemyBase* enemy = nullptr;

    switch (type)
    {
    case EnemyBase::TYPE::DEMON:
        enemy = new EnemyDemon();
        break;
    case EnemyBase::TYPE::WIZARD:
        enemy = new EnemyWizard();
        break;
    case EnemyBase::TYPE::GIANT:
        enemy = new EnemyBoss(); // LEVEL3用ボスもここで生成可
        break;
    default:
        enemy = new EnemyDemon();
        break;
    }

    if (enemy)
    {
        enemy->Init(type,
            enemyModelIds_[static_cast<int>(type)],
            attackEffectModelIds_[0],
            player_);
    }

    return enemy;
}
