
#include "JumpState.h"
#include "IdleState.h"
#include "AttackState.h"
#include "../../../Utility/Utility.h"

void JumpState::Enter(Player& player)
{
    if (player.GetAnimationController())
        player.GetAnimationController()->Play(2, false); // JUMP
    player.SetJumpPow(Player::JUMP_POW);
    player.SetIsJump(true);
}

void JumpState::Update(Player& player)
{

    // 攻撃
    if (Ins::input().IsTrgMouseLeft())
    {
        player.ChangeState<AttackState>();
        return;
    }

    // 横移動（空中でも可能）
    VECTOR moveDir = { 0, 0, 0 };
    bool w = Ins::input().IsNew(KEY_INPUT_W);
    bool s = Ins::input().IsNew(KEY_INPUT_S);
    bool a = Ins::input().IsNew(KEY_INPUT_A);
    bool d = Ins::input().IsNew(KEY_INPUT_D);

	// 同時押しは後に押した方優先
    if (w && s)
    {
        if (Ins::input().IsLaterPressed(KEY_INPUT_W, KEY_INPUT_S)) moveDir.z += 1;
        else moveDir.z -= 1;
    }
    else if (w) moveDir.z += 1;
    else if (s) moveDir.z -= 1;

    if (a && d)
    {
        if (Ins::input().IsLaterPressed(KEY_INPUT_A, KEY_INPUT_D)) moveDir.x -= 1;
        else moveDir.x += 1;
    }
    else if (a) moveDir.x -= 1;
    else if (d) moveDir.x += 1;

    if (moveDir.x != 0.0f || moveDir.z != 0.0f)
    {
        float len = sqrtf(moveDir.x * moveDir.x + moveDir.z * moveDir.z);
        moveDir.x /= len;
        moveDir.z /= len;

        // 移動速度を掛けて位置更新
        player.SetPos({
            player.GetPos().x + moveDir.x * Player::MOVE_SPEED,
            player.GetPos().y,
            player.GetPos().z + moveDir.z * Player::MOVE_SPEED
            });

        // 向きを更新
        float targetY = atan2f(-moveDir.x, -moveDir.z);
        VECTOR ang = player.GetAngles();
        ang.y = Utility::LerpAngle(ang.y, targetY, 0.3f);
        player.SetAngles(ang);
    }

    // ジャンプの重力処理
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
        player.ChangeState<IdleState>();
    }
}

void JumpState::Exit(Player& player)
{
    // 特になし
}
