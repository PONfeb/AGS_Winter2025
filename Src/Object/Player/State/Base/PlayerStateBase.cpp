
#include "PlayerStateBase.h"

#include "../../Player.h"

bool PlayerStateBase::Move(Player& player)
{

    VECTOR dir = KEY::GetIns().GetLeftStickVec3D();

    if (Utility::EqualsVZero(dir)) {
        if (KEY::GetIns().GetInfo(KEY_TYPE::MOVE_FORWARD).now) { dir.z++; }
        if (KEY::GetIns().GetInfo(KEY_TYPE::MOVE_BACK).now) { dir.z--; }
        if (KEY::GetIns().GetInfo(KEY_TYPE::MOVE_RIGHT).now) { dir.x++; }
        if (KEY::GetIns().GetInfo(KEY_TYPE::MOVE_LEFT).now) { dir.x--; }
    }

    if (!Utility::EqualsVZero(dir))
    {
        float len = sqrtf(dir.x * dir.x + dir.z * dir.z);
        dir.x /= len;
        dir.z /= len;

        VECTOR pos = player.GetPos();
        pos.x += dir.x * Player::MOVE_SPEED;
        pos.z += dir.z * Player::MOVE_SPEED;
        player.SetPos(pos);

        // マウス操作が有効でなければ、方向入力に応じて向きを変える
        if (!player.IsMouseControlActive())
        {
            player.UpdateRotationByKeyboard(dir);
        }

        return true; // 移動があった
    }

    return false; // 移動なし

}
