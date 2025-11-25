#pragma once

#include "../Base/EnemyBase.h"

class EnemyWitch : public EnemyBase
{
public:

    // 攻撃間隔（例：120フレームごと）
    static constexpr int TEAM_ATTACK = 120;

    EnemyWitch();
    ~EnemyWitch() override;

protected:

    // ステータス設定（HP、速度、スケールなど）
    void SetParam(void) override;

    // 待機状態の処理
    void UpdateStandby(void) override;

    // Witch は攻撃状態も独自に書きたいならここに書ける
    void UpdateAttack(void) override;

};
