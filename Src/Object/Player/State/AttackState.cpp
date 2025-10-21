
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

    // à⁄ìÆ
    VECTOR moveDir = { 0,0,0 };
    if (Ins::input().IsNew(KEY_INPUT_W)) moveDir.z += 1;
    if (Ins::input().IsNew(KEY_INPUT_S)) moveDir.z -= 1;
    if (Ins::input().IsNew(KEY_INPUT_A)) moveDir.x -= 1;
    if (Ins::input().IsNew(KEY_INPUT_D)) moveDir.x += 1;

    if (moveDir.x != 0 || moveDir.z != 0)
    {
        float len = sqrtf(moveDir.x * moveDir.x + moveDir.z * moveDir.z);
        moveDir.x /= len; moveDir.z /= len;
        VECTOR pos = player.GetPos();
        pos.x += moveDir.x * Player::SPEED_MOVE;
        pos.z += moveDir.z * Player::SPEED_MOVE;
        player.SetPos(pos);
    }

    // ãÛíÜèdóÕ
    if (wasJumping_)
    {
        float jumpPow = player.GetJumpPow() - Player::GRAVITY;
        VECTOR pos = player.GetPos();
        pos.y += jumpPow;
        player.SetJumpPow(jumpPow);
        player.SetPos(pos);
        if (pos.y <= Player::DEFAULT_POS.y)
        {
            pos.y = Player::DEFAULT_POS.y;
            player.SetPos(pos);
            player.SetIsJump(false);
            wasJumping_ = false;
        }
    }

    // çUåÇÉ{É^ÉìâèúÇ≈èÛë‘ëJà⁄
    if (!KEY::GetIns().GetInfo(KEY_TYPE::ATTACK).now)
    {
        if (player.GetIsJump())
            player.ChangeState<JumpState>();
        else if (moveDir.x != 0 || moveDir.z != 0)
            player.ChangeState<MoveState>();
        else
            player.ChangeState<IdleState>();
        return;
    }

    // íeî≠éÀ
    attackCooldown_ -= Ins::scene().GetDeltaTime();
    if (attackCooldown_ <= 0.f && shotMgr_)
    {
        VECTOR spawnPos = player.GetPos(); spawnPos.y += 10.f;
        VECTOR forward = player.GetForwardDir();
        shotMgr_->SpawnShot(ShotBase::TYPE::NORMAL, spawnPos, forward);
        attackCooldown_ = 0.2f;
    }
}

void AttackState::Exit(Player& player) {}
