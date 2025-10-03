
#include "JumpState.h"
#include "IdleState.h"
#include "../../../Utility/Utility.h"
#include "../../../Common/Instance.h"

void JumpState::Enter(Player& player)
{
    if (player.GetAnimationController())
        player.GetAnimationController()->Play(2, false); // JUMP
    player.SetJumpPow(Player::JUMP_POW);
    player.SetIsJump(true);
}

void JumpState::Update(Player& player)
{
    auto& input = Ins::input();

    // 横移動（空中でも可能）
    VECTOR moveDir = { 0, 0, 0 };
    if (input.IsNew(KEY_INPUT_W)) moveDir.z += 1.0f;
    if (input.IsNew(KEY_INPUT_S)) moveDir.z -= 1.0f;
    if (input.IsNew(KEY_INPUT_A)) moveDir.x -= 1.0f;
    if (input.IsNew(KEY_INPUT_D)) moveDir.x += 1.0f;

    if (moveDir.x != 0.0f || moveDir.z != 0.0f)
    {
        float len = sqrtf(moveDir.x * moveDir.x + moveDir.z * moveDir.z);
        moveDir.x /= len;
        moveDir.z /= len;

        // 移動速度を掛けて位置更新
        player.SetPos({
            player.GetPos().x + moveDir.x * Player::SPEED_MOVE,
            player.GetPos().y,
            player.GetPos().z + moveDir.z * Player::SPEED_MOVE
            });

        // 向きを更新
        float angle = atan2f(moveDir.x, moveDir.z);
        VECTOR angles = player.GetAngles();
        angles.y = angle + Utility::Deg2RadF(180.0f);
        player.SetAngles(angles);
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
