#include "EnemyBase.h"
#include "../../Player/Player.h"
//#include "../Shot/ShotBase.h"
//#include "../Shot/ShotStraight.h"
#include "../../../Application.h"
#include "../../../Common/AnimationController.h"
#include "../../Shot/ShotManager.h"
#include "../../../Utility/Utility.h"

EnemyBase::EnemyBase()
    : modelId_(-1), pos_{ 0,0,0 }, angles_{ 0,0,0 }, scales_{ 1,1,1 },
    baseAttackEffectModelId_(-1), collisionRadius_(40.f), capsuleHeight_(80.f),
    player_(nullptr), animationController_(nullptr),
    type_(TYPE::DEMON), state_(STATE::NONE), speed_(0.f),
    hp_(1), spawnRange_(0.8f), cntAttack_(0), isAlive_(true),
    stateCnt_(0)
{
}

EnemyBase::~EnemyBase()
{
    Release();
}

// --- 初期化 ---
void EnemyBase::Init(TYPE type, int baseModelId, int baseAttackEffectModelId, Player* player)
{
    type_ = type;
    player_ = player;
    modelId_ = MV1DuplicateModel(baseModelId);
    baseAttackEffectModelId_ = baseAttackEffectModelId;

    SetParam();

    MV1SetScale(modelId_, scales_);
    SetSpawnPosition();
    LookPlayer();
    Move();

    MV1SetMaterialEmiColor(modelId_, 0, COLOR_EMI_DEFAULT);

    animationController_ = new AnimationController(modelId_);
    for (int i = 0; i < static_cast<int>(ANIM_TYPE::MAX); i++)
        animationController_->AddInFbx(i, 30.f, i);

    animationController_->Play(static_cast<int>(ANIM_TYPE::WALK));
    ChangeState(STATE::STANDBY);
}

// --- 更新 ---
void EnemyBase::Update()
{
    switch (state_)
    {
    case STATE::STANDBY:
        UpdateStandby();
        break;

    case STATE::ATTACK:
        UpdateAttack(); 
        break;

    case STATE::HIT_REACT:
        HitRectUpdate();
        break;

    case STATE::DEAD_REACT:
        UpdateDead();
        break;

    case STATE::END:
        UpdateEnd();
        break;
    }

    UpdateShot();
    if (animationController_) animationController_->Update();
}

// --- 描画 ---
void EnemyBase::Draw()
{
    if (state_ == STATE::END) return;

    switch (state_)
    {
    case STATE::STANDBY: DrawStandby(); break;
    case STATE::ATTACK: DrawAttack(); break;
    case STATE::HIT_REACT: DrawHitReact(); break;
    case STATE::DEAD_REACT: DrawDead(); break;
    default: break;
    }

    DrawShot();
}

// --- 解放 ---
void EnemyBase::Release()
{
    if (modelId_ >= 0) MV1DeleteModel(modelId_);

    if (animationController_)
    {
        animationController_->Release();
        delete animationController_;
        animationController_ = nullptr;
    }

    for (auto shot : shots_)
    {
        shot->Release();
        delete shot;
    }
    shots_.clear();
}

// --- ダメージ ---
void EnemyBase::Damage(int damage)
{
    if (!isAlive_) return;

    hp_ -= damage;

    if (hp_ > 0)
    {
        ChangeState(STATE::HIT_REACT);
        isAlive_ = true;
    }
    else
    {
        ChangeState(STATE::DEAD_REACT);
        isAlive_ = false;
    }
}

// --- 状態遷移 ---
void EnemyBase::ChangeState(STATE state)
{
    state_ = state;

    switch (state_)
    {
    case STATE::STANDBY: ChangeStandby(); break;
    case STATE::ATTACK:  ChangeAttack(); break;
    case STATE::DEAD_REACT: ChangeDead(); break;
    case STATE::HIT_REACT: break;
    case STATE::END: break;
    }

    stateCnt_ = 0;
}

// --- 移動とプレイヤー方向 ---
void EnemyBase::LookPlayer()
{
    if (!player_) return;

    VECTOR diff = VSub(player_->GetPos(), pos_);
    diff.y = 0.f;
    moveDir_ = VNorm(diff);

    angles_.y = atan2(moveDir_.x, moveDir_.z) + Utility::Deg2RadF(180.f);
    angles_.x = angles_.z = 0.f;
    MV1SetRotationXYZ(modelId_, angles_);
}

//void EnemyBase::Move()
//{
//    VECTOR movePow = VScale(moveDir_, speed_);
//    pos_ = VAdd(pos_, movePow);
//
//    // ワールド制限
//    if (pos_.x < 0.f) pos_.x = 0.f;
//    if (pos_.x > BlockManager::WORLD_SIZE) pos_.x = BlockManager::WORLD_SIZE;
//    if (pos_.z < 0.f) pos_.z = 0.f;
//    if (pos_.z > BlockManager::WORLD_SIZE) pos_.z = BlockManager::WORLD_SIZE;
//
//    MV1SetPosition(modelId_, pos_);
//}

// --- 出現位置 ---
//void EnemyBase::SetSpawnPosition()
//{
//    float radius = BlockManager::WORLD_SIZE / 2.f;
//    VECTOR centerPos = { radius, 0.f, radius };
//    radius *= spawnRange_;
//
//    float radian = static_cast<float>(GetRand(360)) * DX_PI_F / 180.f;
//    VECTOR dir = { sinf(radian), 0.f, cosf(radian) };
//    pos_ = VAdd(centerPos, VScale(dir, radius));
//
//    MV1SetPosition(modelId_, pos_);
//}

//// --- ショット ---
//void EnemyBase::UpdateShot() { for (auto shot : shots_) shot->Update(); }
//void EnemyBase::DrawShot() { for (auto shot : shots_) shot->Draw(); }

//ShotBase* EnemyBase::GetValidShot()
//{
//    for (auto shot : shots_)
//        if (!shot->IsAlive()) return shot;
//
//    ShotBase* shot = new ShotStraight(ShotBase::TYPE::STRAIGHT, baseAttackEffectModelId_);
//    shots_.push_back(shot);
//    return shot;
//}

// --- Hit / Dead ---
void EnemyBase::HitRectUpdate()
{
    stateCnt_++;
    if (stateCnt_ > 20)
        ChangeState(hp_ > 0 ? STATE::STANDBY : STATE::DEAD_REACT);
}

void EnemyBase::UpdateDead()
{
    stateCnt_++;
    if (stateCnt_ > 30 && animationController_->IsEnd())
        ChangeState(STATE::END);
}

void EnemyBase::UpdateEnd() {}

// --- 状態別変更 ---
void EnemyBase::ChangeStandby() 
{ 

    animationController_->Play(static_cast<int>(ANIM_TYPE::WALK)); 

}

void EnemyBase::ChangeAttack()
{
    animationController_->Play(static_cast<int>(ANIM_TYPE::ATTACK), false);
    ShotBase* shot = GetValidShot();
    shot->CreateShot(pos_, moveDir_);
}
void EnemyBase::ChangeDead()
{
    animationController_->Play(static_cast<int>(ANIM_TYPE::DEATH), false);
    stateCnt_ = 0;
}

// --- 状態別更新 ---
void EnemyBase::UpdateStandby()
{
    if (!isAlive_) return;
    LookPlayer();
    Move();
}

void EnemyBase::UpdateAttack()
{
    if (animationController_->IsEnd()) ChangeState(STATE::STANDBY);
}

// --- 描画 ---
void EnemyBase::DrawStandby() { MV1DrawModel(modelId_); }
void EnemyBase::DrawAttack() { MV1DrawModel(modelId_); }

void EnemyBase::DrawHitReact()
{
    MV1SetMaterialEmiColor(modelId_, 0, (stateCnt_ / TERM_BLINK) % 2 == 0 ? COLOR_DIF_BLINK : COLOR_DIF_DEFAULT);
    MV1SetPosition(modelId_, pos_);
    MV1DrawModel(modelId_);
}

void EnemyBase::DrawDead() { MV1DrawModel(modelId_); }
void EnemyBase::DrawEnd() {}
