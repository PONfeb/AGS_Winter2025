#pragma once
#include "Base/PlayerStateBase.h"
#include "../Player.h"
#include "../../Shot/ShotManager.h"

class AttackState : public PlayerStateBase
{
public:
    AttackState() : shotMgr_(nullptr) {}
    AttackState(ShotManager* shotMgr);

    void Enter(Player& player) override;
    void Update(Player& player) override;
    void Exit(Player& player) override;

private:
    ShotManager* shotMgr_ = nullptr;
    bool wasJumping_ = false;
    float attackCooldown_ = 0.f;
};
