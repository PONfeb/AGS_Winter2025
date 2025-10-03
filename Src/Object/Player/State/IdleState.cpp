
#include "IdleState.h"
#include "../../../Common/Instance.h"
#include "MoveState.h"
#include "JumpState.h"
#include <DxLib.h>

void IdleState::Enter(Player& player)
{
    if (player.GetAnimationController())
        player.GetAnimationController()->Play(0, true); // IDLE
}

void IdleState::Update(Player& player)
{
    if (Ins::input().IsNew(KEY_INPUT_W) || Ins::input().IsNew(KEY_INPUT_A) ||
        Ins::input().IsNew(KEY_INPUT_S) || Ins::input().IsNew(KEY_INPUT_D))
    {
        player.ChangeState<MoveState>();
        return;
    }

    if (Ins::input().IsTrgDown(KEY_INPUT_SPACE))
    {
        player.ChangeState<JumpState>();
        return;
    }
}

void IdleState::Exit(Player& player)
{
    // “Á‚É‚È‚µ
}
