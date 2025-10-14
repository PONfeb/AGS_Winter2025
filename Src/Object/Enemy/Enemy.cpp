
#include "Enemy.h"

Enemy::Enemy() : pos_(VGet(0, 0, 0)), radius_(100.0f), hp_(3), isAlive_(true)
{
}

Enemy::~Enemy()
{
    Release();
}

void Enemy::Init(const VECTOR& pos, int hp)
{
    pos_ = pos;
    hp_ = hp;
    isAlive_ = true;
}

void Enemy::Update()
{
    if (!isAlive_) return;
    // ç°ÇÕìÆÇ©Ç≥Ç»Ç¢
}

void Enemy::Draw()
{
    if (!isAlive_) return;
    DrawSphere3D(pos_, radius_, 16, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);
}

void Enemy::Release() {}

void Enemy::TakeDamage(int damage)
{
    hp_ -= damage;
    if (hp_ <= 0) isAlive_ = false;
}

void Enemy::CheckCollisionWithPlayer(Player& player)
{
    VECTOR diff = VSub(pos_, player.GetPos());
    float dist = sqrtf(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);

    if (dist <= radius_ + player.GetCollisionRadius())
    {
        player.TakeDamage(damage_); // damage_ ÇÕìGÇ≤Ç∆ÇÃê›íËíl
        // ïKóvÇ»ÇÁìGÇÃè’ìÀå„ãììÆÇ‡Ç±Ç±Ç≈èàóù
    }
}