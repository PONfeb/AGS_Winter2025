
#include "Enemy.h"

#include "../../Application.h"

Enemy::Enemy() : pos_(VGet(0, 0, 0)), radius_(100.0f), detectRange_(1500.f), speed_(3.0f), hp_(3), isAlive_(true)
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

    // モデル読み込み（まだ読み込んでいなければ）
    if (modelHandle_ == -1)
    {
        modelHandle_ = MV1LoadModel(
            (Application::PATH_ENEMY + "Mutant/Mutant.mv1").c_str()
        );
    }

    // モデルの初期設定
    MV1SetPosition(modelHandle_, pos_);
    MV1SetScale(modelHandle_, scale_);
}

void Enemy::Update(Player& player, float deltaTime)
{
    if (!isAlive_) return;

    VECTOR diff = VSub(player.GetPos(), pos_);
    float dist = sqrtf(diff.x * diff.x + diff.z * diff.z);

    if (dist <= detectRange_)
    {
        VECTOR dir = VGet(diff.x, 0.0f, diff.z);
        dir = VNorm(dir);

        pos_.x += dir.x * speed_ * deltaTime;
        pos_.z += dir.z * speed_ * deltaTime;
    }

    // ★ モデル位置を更新
    MV1SetPosition(modelHandle_, pos_);

    CheckCollisionWithPlayer(player);
}

void Enemy::Draw()
{
    if (!isAlive_) return;

    // ★ モデル描画
    MV1DrawModel(modelHandle_);

    // 追跡範囲の可視化（半透明の青色）
    DrawSphere3D(pos_, detectRange_, 16, GetColor(0, 0, 255), GetColor(0, 0, 255), false);
}

void Enemy::Release()
{
    if (modelHandle_ != -1)
    {
        MV1DeleteModel(modelHandle_);
        modelHandle_ = -1;
    }
}

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