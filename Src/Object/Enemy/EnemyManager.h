#pragma once

#include <vector>
#include <random>
#include <memory>
#include "Base/EnemyBase.h"

class Player;

class EnemyManager
{
public:
    enum class LEVEL
    {
        LEVEL1,
        LEVEL2,
        LEVEL3
    };

    EnemyManager(Player* player);
    ~EnemyManager();

    // ステージ開始時に呼ぶ
    void Init(LEVEL level);

    // 更新
    void Update();

    // 描画
    void Draw();

    // メモリ解放
    void Release();

    // 生成中の敵リスト取得
    std::vector<EnemyBase*> GetEnemys() const { return enemys_; }

private:
    Player* player_;
    LEVEL level_;
    std::vector<EnemyBase*> enemys_;

    // モデルIDリスト（Demon, Wizard, Giant）
    std::vector<int> enemyModelIds_;
    std::vector<int> attackEffectModelIds_;

    // スポーン管理
    int cntSpawn_;       // スポーン間隔カウンタ
    int enemyToSpawn_;   // 残りスポーン数

    // ランダム生成用
    std::mt19937 mt_;

    // 型に応じた敵生成
    EnemyBase* CreateEnemyByType(EnemyBase::TYPE type);
};
