
#include "IdleState.h"
#include "MoveState.h"
#include "JumpState.h"
#include "AttackState.h"

void IdleState::Enter(Player& player)
{
    player.GetAnimationController()->Play(0, true); // IDLEƒAƒjƒÄ¶
}

void IdleState::Update(Player& player)
{
    // UŒ‚
    if (KEY::GetIns().GetInfo(KEY_TYPE::ATTACK).down)
    {
        player.ChangeState<AttackState>();
        return;
    }

    // ˆÚ“®“ü—Í
    VECTOR dir = KEY::GetIns().GetLeftStickVec3D();

    if (Utility::EqualsVZero(dir)) {
        if (KEY::GetIns().GetInfo(KEY_TYPE::MOVE_FORWARD).now) { dir.z++; }
        if (KEY::GetIns().GetInfo(KEY_TYPE::MOVE_BACK).now) { dir.z--; }
        if (KEY::GetIns().GetInfo(KEY_TYPE::MOVE_RIGHT).now) { dir.x++; }
        if (KEY::GetIns().GetInfo(KEY_TYPE::MOVE_LEFT).now) { dir.x--; }
    }

    // ˆÚ“®ˆ—
    if (!Utility::EqualsVZero(dir))
    {
        player.ChangeState<MoveState>();
        return;
    }

    if (KEY::GetIns().GetInfo(KEY_TYPE::JUMP).down)
    {
        player.ChangeState<JumpState>();
        return;
    }
}

void IdleState::Exit(Player& player)
{
    // “Á‚É‚È‚µ
}
