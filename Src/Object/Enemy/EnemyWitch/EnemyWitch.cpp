#include "EnemyWitch.h"
#include "../../Shot/ShotManager.h"
#include "../../Player/Player.h"

EnemyWitch::EnemyWitch()
{
}

EnemyWitch::~EnemyWitch()
{
}

void EnemyWitch::SetParam(void)
{
    hp_ = 3;
    isAlive_ = true;

    // Witch の大きさ
    scales_ = { 0.8f, 0.8f, 0.8f };

    // 動きは遅め
    speed_ = 0.4f;

    // 攻撃カウンタ初期化
    cntAttack_ = 0;

    // スポーン範囲
    spawnRange_ = 1.0f;

    // カプセル判定の半径
    collisionRadius_ = 40.0f;
}

void EnemyWitch::UpdateStandby(void)
{
    // プレイヤーの方向を向く
    LookPlayer();

    cntAttack_++;

    // 一定間隔で攻撃モーションへ
    if (cntAttack_ % TEAM_ATTACK == 0)
    {
        cntAttack_ = 0;
        ChangeState(STATE::ATTACK);
    }
}

//void EnemyWitch::UpdateAttack(void)
//{
//    // Witch は魔法弾を撃つ
//    if (shotMgr_)
//    {
//        // プレイヤー方向への弾
//        VECTOR dir = VNorm(VSub(player_->GetPos(), pos_));
//
//        shotMgr_->SpawnEnemyShot(ShotBase::TYPE::NORMAL, pos_, dir);
//    }
//
//    // 攻撃が終わったらスタンバイへ戻る
//    ChangeState(STATE::STANDBY);
//}
