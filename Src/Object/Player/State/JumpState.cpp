
#include "JumpState.h"
#include "IdleState.h"

void JumpState::Enter(Player& player)
{
    if (player.GetAnimationController())
        player.GetAnimationController()->Play(2, false); // JUMP
    player.SetJumpPow(Player::JUMP_POW);
    player.SetIsJump(true);
}

void JumpState::Update(Player& player)
{
    auto pos = player.GetPos();
    float jumpPow = player.GetJumpPow();

    jumpPow -= Player::GRAVITY;
    pos.y += jumpPow;

    if (pos.y <= Player::DEFAULT_POS.y)
    {
        pos.y = Player::DEFAULT_POS.y;
        jumpPow = 0;
        player.SetIsJump(false);
        player.ChangeState<IdleState>();
    }

    player.SetPos(pos);
    player.SetJumpPow(jumpPow);
}

void JumpState::Exit(Player& player)
{
    // “Á‚É‚È‚µ
}
