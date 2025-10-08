
#pragma once

#include <DxLib.h>

class Player;

class PlayerStateBase
{
public:
    virtual ~PlayerStateBase() = default;

    virtual void Enter(Player& player) = 0;
    virtual void Update(Player& player) = 0;
    virtual void Exit(Player& player) = 0;
};
