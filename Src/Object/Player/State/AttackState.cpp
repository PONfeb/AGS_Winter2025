
#include "AttackState.h"
#include "IdleState.h"
#include "MoveState.h"
#include "JumpState.h"

AttackState::AttackState(ShotManager* shotMgr)
    : shotMgr_(shotMgr)
{
}

void AttackState::Enter(Player& player)
{

    if (player.GetAnimationController())
        player.GetAnimationController()->Play(4, true);
    player.UpdateRotationByMouse();
    wasJumping_ = player.GetIsJump();

}

void AttackState::Update(Player& player)
{

    player.UpdateRotationByMouse();

    // --- ジャンプ優先 ---
    if (KEY::GetIns().GetInfo(KEY_TYPE::JUMP).now && !player.GetIsJump())
    {
        player.ChangeState<JumpState>();
        return;
    }

    // 横移動（Move関数を使用）
    PlayerStateBase::Move(player);

    // 空中重力
    if (wasJumping_)
    {
        float jumpPow = player.GetJumpPow() - Player::GRAVITY;
        VECTOR pos = player.GetPos();
        pos.y += jumpPow;
        player.SetJumpPow(jumpPow);
        player.SetPos(pos);

        // 着地判定
        if (pos.y <= Player::DEFAULT_POS.y)
        {
            pos.y = Player::DEFAULT_POS.y;
            player.SetPos(pos);
            player.SetIsJump(false);
            wasJumping_ = false;
        }
    }

    // 攻撃ボタン解除で状態遷移
    if (!KEY::GetIns().GetInfo(KEY_TYPE::ATTACK).now)
    {
        if (player.GetIsJump())
            player.ChangeState<JumpState>();
        else if (PlayerStateBase::Move(player))
            player.ChangeState<MoveState>();
        else
            player.ChangeState<IdleState>();
        return;
    }

    // 弾発射
    attackCooldown_ -= Ins::scene().GetDeltaTime();
    if (attackCooldown_ <= 0.f && shotMgr_)
    {
        VECTOR spawnPos = player.GetPos();
        spawnPos.y += 10.f;
        VECTOR forward = player.GetForwardDir();
        shotMgr_->SpawnShot(ShotBase::TYPE::NORMAL, spawnPos, forward);
        attackCooldown_ = 0.2f;
    }

}

void AttackState::Exit(Player& player) {}
