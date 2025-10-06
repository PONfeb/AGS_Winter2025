
#include "MoveState.h"
#include "IdleState.h"
#include "JumpState.h"
#include "../../../Utility/Utility.h"
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

	bool w = Ins::input().IsNew(KEY_INPUT_W);
	bool s = Ins::input().IsNew(KEY_INPUT_S);
	bool a = Ins::input().IsNew(KEY_INPUT_A);
	bool d = Ins::input().IsNew(KEY_INPUT_D);

    if (w && s)
    {
		if (Ins::input().IsLaterPressed(KEY_INPUT_W, KEY_INPUT_S)) dir.z += 1;
		else dir.z -= 1;
    }
	else if (w) dir.z += 1;
    else if (s) dir.z -= 1;

    if (a && d)
    {
        if (Ins::input().IsLaterPressed(KEY_INPUT_A, KEY_INPUT_D)) dir.x -= 1;
        else dir.x += 1;
    }
    else if (a) dir.x -= 1;
    else if (d) dir.x += 1;

    // ---- 移動処理 ----
    if (dir.x != 0.0f || dir.z != 0.0f)
    {
        float len = sqrtf(dir.x * dir.x + dir.z * dir.z);
        dir.x /= len;
        dir.z /= len;

        auto pos = player.GetPos();
        pos.x += dir.x * Player::SPEED_MOVE;
        pos.z += dir.z * Player::SPEED_MOVE;
        player.SetPos(pos);

        // 滑らかに回転（slerp風補間）
        float targetY = atan2f(-dir.x, -dir.z); // + DX_PI_F は不要
        VECTOR ang = player.GetAngles();
		ang.y = Utility::LerpAngle(ang.y, targetY, 0.3f);
        player.SetAngles(ang);
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
    // 特になし
}
