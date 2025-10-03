
#pragma once

#include "Base/PlayerStateBase.h"
#include "../Player.h"

class IdleState : public PlayerStateBase
{
public:
    void Enter(Player& player) override;
    void Update(Player& player) override;
    void Exit(Player& player) override;
};
