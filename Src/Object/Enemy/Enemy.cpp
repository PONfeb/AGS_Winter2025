
#include "Enemy.h"

#include "../../Application.h"

Enemy::Enemy() : pos_(VGet(0, 0, 0)), radius_(100.0f), detectRange_(1500.0f), speed_(3.0f), hp_(3), isAlive_(true)
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

	modelid = MV1LoadModel((Application::PATH_ENEMY + "Mutant.mv1").c_str());

    MV1SetPosition(modelid, pos_);

}

void Enemy::Update(Player& player, float deltaTime)
{
    if (!isAlive_) return;

    MV1SetPosition(modelid, pos_);
    MV1SetRotationXYZ(modelid, angles_);

    VECTOR diff = VSub(player.GetPos(), pos_);
    float dist = sqrtf(diff.x * diff.x + diff.z * diff.z); // XZ距離

    if (dist <= detectRange_)
    {
        VECTOR dir = VGet(diff.x, 0.0f, diff.z);
        dir = VNorm(dir);

        pos_.x += dir.x * speed_ * deltaTime;
        pos_.z += dir.z * speed_ * deltaTime;
    }

    CheckCollisionWithPlayer(player);
}

void Enemy::Draw()
{
    if (!isAlive_) return;

    MV1DrawModel(modelid);

    // 敵本体
    DrawSphere3D(pos_, radius_, 16, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);

    // 追跡範囲の可視化（半透明の青色）
    DrawSphere3D(pos_, detectRange_, 16, GetColor(0, 0, 255), GetColor(0, 0, 255), false);
}

void Enemy::Release() {}

void Enemy::TakeDamage(int damage)
{
    hp_ -= damage;
    if (hp_ <= 0) isAlive_ = false;
}

void Enemy::CheckCollisionWithPlayer(Player& player)const
{
    VECTOR diff = VSub(pos_, player.GetPos());
    float dist = sqrtf(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);

    if (dist <= radius_ + player.GetCollisionRadius())
    {
        player.TakeDamage(damage_); // damage_ は敵ごとの設定値
        // 必要なら敵の衝突後挙動もここで処理
    }
}