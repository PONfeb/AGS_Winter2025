
#include "MoveState.h"
#include "IdleState.h"
#include "JumpState.h"
#include "../../../Common/Instance.h"
#include <DxLib.h>

void MoveState::Enter(Player& player)
{
    if (player.GetAnimationController())
        player.GetAnimationController()->Play(1, true); // WALK
}

void MoveState::Update(Player& player)
{
    VECTOR dir = VGet(0, 0, 0);

    if (Ins::input().IsNew(KEY_INPUT_W)) dir.z += 1;
    if (Ins::input().IsNew(KEY_INPUT_S)) dir.z -= 1;
    if (Ins::input().IsNew(KEY_INPUT_A)) dir.x -= 1;
    if (Ins::input().IsNew(KEY_INPUT_D)) dir.x += 1;

    if (dir.x != 0 || dir.z != 0)
    {
        float len = sqrtf(dir.x * dir.x + dir.z * dir.z);
        dir.x /= len;
        dir.z /= len;

        auto pos = player.GetPos();
        pos.x += dir.x * Player::SPEED_MOVE;
        pos.z += dir.z * Player::SPEED_MOVE;
        player.SetPos(pos);

        // ‰ñ“]
        player.SetAngles(VGet(player.GetAngles().x, atan2f(dir.x, dir.z) + DX_PI_F, player.GetAngles().z));
    }
    else
    {
        player.ChangeState<IdleState>();
        return;
    }

    if (Ins::input().IsTrgDown(KEY_INPUT_SPACE))
    {
        player.ChangeState<JumpState>();
        return;
    }
}

void MoveState::Exit(Player& player)
{
    // “Á‚É‚È‚µ
}
