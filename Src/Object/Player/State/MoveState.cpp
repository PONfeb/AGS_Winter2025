
#include "MoveState.h"
#include "IdleState.h"
#include "JumpState.h"
#include "AttackState.h"
#include "../../../Utility/Utility.h"

void MoveState::Enter(Player& player)
{
    if (player.GetAnimationController())
        player.GetAnimationController()->Play(1, true); // WALK
}

void MoveState::Update(Player& player)
{
    // 攻撃
    if (Ins::input().IsTrgMouseLeft())
    {
        player.ChangeState<AttackState>();
        return;
    }

    // 移動入力
    VECTOR dir = VGet(0, 0, 0);
    bool w = Ins::input().IsNew(KEY_INPUT_W);
    bool s = Ins::input().IsNew(KEY_INPUT_S);
    bool a = Ins::input().IsNew(KEY_INPUT_A);
    bool d = Ins::input().IsNew(KEY_INPUT_D);

    if (w && s) dir.z += (Ins::input().IsLaterPressed(KEY_INPUT_W, KEY_INPUT_S) ? 1 : -1);
    else if (w) dir.z += 1;
    else if (s) dir.z -= 1;

    if (a && d) dir.x += (Ins::input().IsLaterPressed(KEY_INPUT_D, KEY_INPUT_A) ? 1 : -1);
    else if (a) dir.x -= 1;
    else if (d) dir.x += 1;

    // 移動処理
    if (dir.x != 0.0f || dir.z != 0.0f)
    {
        float len = sqrtf(dir.x * dir.x + dir.z * dir.z);
        dir.x /= len;
        dir.z /= len;

        VECTOR pos = player.GetPos();
        pos.x += dir.x * Player::SPEED_MOVE;
        pos.z += dir.z * Player::SPEED_MOVE;
        player.SetPos(pos);

        // 攻撃中でなければキーボード方向に回転
        if (!player.IsMouseControlActive())
        {
            player.UpdateRotationByKeyboard(dir);
        }
    }
    else
    {
        player.ChangeState<IdleState>();
        return;
    }

    // ジャンプ
    if (Ins::input().IsTrgDown(KEY_INPUT_SPACE))
    {
        player.ChangeState<JumpState>();
        return;
    }
}

void MoveState::Exit(Player& player)
{
    // 特になし
}
