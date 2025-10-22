
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
    if (KEY::GetIns().GetInfo(KEY_TYPE::ATTACK).down)
    {
        player.ChangeState<AttackState>();
        return;
    }

    // 移動入力
    VECTOR dir = KEY::GetIns().GetLeftStickVec3D();

    if (Utility::EqualsVZero(dir)) {
        if (KEY::GetIns().GetInfo(KEY_TYPE::MOVE_FORWARD).now) { dir.z++; }
        if (KEY::GetIns().GetInfo(KEY_TYPE::MOVE_BACK).now) { dir.z--; }
        if (KEY::GetIns().GetInfo(KEY_TYPE::MOVE_RIGHT).now) { dir.x++; }
        if (KEY::GetIns().GetInfo(KEY_TYPE::MOVE_LEFT).now) { dir.x--; }
    }
	
    // 移動処理
    if (!Utility::EqualsVZero(dir))
    {
        float len = sqrtf(dir.x * dir.x + dir.z * dir.z);
        dir.x /= len;
        dir.z /= len;

        VECTOR pos = player.GetPos();
        pos.x += dir.x * Player::MOVE_SPEED;
        pos.z += dir.z * Player::MOVE_SPEED;
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
