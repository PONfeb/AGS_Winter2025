
#include "MoveState.h"

#include "../../../Utility/Utility.h"

#include "IdleState.h"
#include "JumpState.h"
#include "AttackState.h"

void MoveState::Enter(Player& player)
{
    if (player.GetAnimationController())
        player.GetAnimationController()->Play(1, true); // WALK
}

void MoveState::Update(Player& player)
{
    // 攻撃
    if (KEY::GetIns().GetInfo(KEY_TYPE::ATTACK).down)
    {
        player.ChangeState<AttackState>();
        return;
    }

    // 横移動（共通関数を使用）
    bool isMoving = PlayerStateBase::Move(player);

    // 移動入力がない場合はIdleに
    if (!isMoving)
    {
        player.ChangeState<IdleState>();
        return;
    }

    // ジャンプ
    if (KEY::GetIns().GetInfo(KEY_TYPE::JUMP).down)
    {
        player.ChangeState<JumpState>();
        return;
    }
}

void MoveState::Exit(Player& player)
{
    // 特になし
}
