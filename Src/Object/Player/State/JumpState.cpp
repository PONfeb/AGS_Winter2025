
#include "JumpState.h"
#include "IdleState.h"
#include "AttackState.h"
#include "../../../Utility/Utility.h"

void JumpState::Enter(Player& player)
{
    // 既にジャンプ中でなければ初速を設定
    if (!player.GetIsJump())
    {
        player.SetJumpPow(Player::JUMP_POW);
        player.SetIsJump(true);

        if (player.GetAnimationController())
            player.GetAnimationController()->Play(2, false); // JUMP
    }
    else
    {
        // 空中で戻ってきた場合はアニメだけ切り替え
        if (player.GetAnimationController())
            player.GetAnimationController()->Play(2, true); // ループなし空中アニメ
    }
}

void JumpState::Update(Player& player)
{
    // 攻撃
    if (Ins::input().IsTrgMouseLeft())
    {
        player.ChangeState<AttackState>();
        return;
    }

    // 横移動（MoveStateと共通）
    PlayerStateBase::Move(player);

    // ジャンプの縦移動
    VECTOR pos = player.GetPos();
    float jumpPow = player.GetJumpPow() - Player::GRAVITY;
    pos.y += jumpPow;
    player.SetJumpPow(jumpPow);
    player.SetPos(pos);

    // 着地判定
    if (pos.y <= Player::DEFAULT_POS.y)
    {
        pos.y = Player::DEFAULT_POS.y;
        player.SetPos(pos);
        player.SetJumpPow(0.0f);
        player.SetIsJump(false); // ←着地したのでジャンプフラグリセット
        player.ChangeState<IdleState>();
        return;
    }
}


void JumpState::Exit(Player& player)
{
    // 特になし
}
