
#pragma once

#include "../../../Common/Instance.h"
#include <DxLib.h>

class Enemy;

class EnemyStateBase
{
public:
    virtual ~EnemyStateBase() = default;

    virtual void Enter(Enemy& enemy) = 0;
    virtual void Update(Enemy& enemy) = 0;
    virtual void Exit(Enemy& enemy) = 0;
};
