
#include "AttackState.h"
#include "IdleState.h"

#include "MoveState.h"
#include "JumpState.h"

void AttackState::Enter(Player& player)
{
    // 攻撃アニメ再生（例：4番が攻撃アニメ）
    if (player.GetAnimationController())
        player.GetAnimationController()->Play(4, true);

    // 攻撃開始時にマウス方向に向く
    player.UpdateRotationByMouse();

    // 空中だったかを記録
    wasJumping_ = player.GetIsJump();
}

void AttackState::Update(Player& player)
{
    // --- 攻撃中も常にマウス方向を向く ---
    player.UpdateRotationByMouse();

    // --- 攻撃中でも移動可能 ---
    VECTOR moveDir = { 0, 0, 0 };
    bool w = Ins::input().IsNew(KEY_INPUT_W);
    bool s = Ins::input().IsNew(KEY_INPUT_S);
    bool a = Ins::input().IsNew(KEY_INPUT_A);
    bool d = Ins::input().IsNew(KEY_INPUT_D);

    if (w) moveDir.z += 1;
    if (s) moveDir.z -= 1;
    if (a) moveDir.x -= 1;
    if (d) moveDir.x += 1;

    if (moveDir.x != 0 || moveDir.z != 0)
    {
        float len = sqrtf(moveDir.x * moveDir.x + moveDir.z * moveDir.z);
        moveDir.x /= len;
        moveDir.z /= len;

        VECTOR pos = player.GetPos();
        pos.x += moveDir.x * Player::SPEED_MOVE;
        pos.z += moveDir.z * Player::SPEED_MOVE;
        player.SetPos(pos);
    }

    // --- 空中での重力処理 ---
    if (wasJumping_)
    {
        float jumpPow = player.GetJumpPow() - Player::GRAVITY;
        VECTOR pos = player.GetPos();
        pos.y += jumpPow;
        player.SetJumpPow(jumpPow);
        player.SetPos(pos);

        // 地面に着いたらジャンプ終了
        if (pos.y <= Player::DEFAULT_POS.y)
        {
            pos.y = Player::DEFAULT_POS.y;
            player.SetPos(pos);
            player.SetIsJump(false);
            wasJumping_ = false;
        }
    }

    // --- 攻撃ボタンを離したら次の状態へ遷移 ---
    if (!Ins::input().IsClickMouseLeft())
    {
        if (player.GetIsJump())
        {
            player.ChangeState<JumpState>();
        }
        else if (moveDir.x != 0 || moveDir.z != 0)
        {
            player.ChangeState<MoveState>();
        }
        else
        {
            player.ChangeState<IdleState>();
        }
        return;
    }
}

void AttackState::Exit(Player& player)
{
    // 必要なら後処理（例：武器エフェクト停止など）
}
