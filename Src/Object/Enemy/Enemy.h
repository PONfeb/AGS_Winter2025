#pragma once

#include "../Player/Player.h"
#include <DxLib.h>

class Enemy
{
public:
    Enemy();
    ~Enemy();

    void Init(const VECTOR& pos, int hp = 3);
    void Update(Player& player, float deltaTime);
    void Draw();
    void Release();

    VECTOR GetPos() const { return pos_; }
    float GetRadius() const { return radius_; }
    int GetHP() const { return hp_; }
    bool IsAlive() const { return isAlive_; }

    void TakeDamage(int damage);

    void CheckCollisionWithPlayer(Player& player)const;

private:
    VECTOR pos_;
    float radius_;
    int hp_;
    bool isAlive_;
    bool speed_;

    float detectRange_;
    int damage_ = 1; // プレイヤーに与えるダメージ
};
