
#include "ShotBase.h"
#include "../../Player/Player.h"
#include "../../../Common/Instance.h"

ShotBase::ShotBase(TYPE type)
{
    type_ = type;
}

ShotBase::~ShotBase(void)
{
}

void ShotBase::CreateShot(VECTOR pos, VECTOR dir)
{
    pos_ = pos;
    dir_ = dir;
    gravityPow_ = 0.0f;
    state_ = STATE::SHOT;
    cntAlive_ = 100;

    SetParam();
}

void ShotBase::Update(void)
{
    if (!IsAlive()) return;

    pos_ = VAdd(pos_, VScale(dir_, speed_));

    ReduceCntAlive();
}

void ShotBase::Draw(void)
{
    if (!IsAlive()) return;

    // DrawSphere3D‚Å’e‚ð•`‰æ
    DrawSphere3D(pos_, collisionRadius_, 8, GetColor(255, 255, 0), GetColor(0, 0, 0), true);
}

void ShotBase::Release(void) {}

bool ShotBase::IsAlive(void)
{
    return state_ != STATE::END;
}

VECTOR ShotBase::GetPos(void)
{
    return pos_;
}

float ShotBase::GetCollisionRadius(void)
{
    return collisionRadius_;
}

ShotBase::TYPE ShotBase::GetType(void)
{
    return type_;
}

void ShotBase::ReduceCntAlive(void)
{
    cntAlive_--;
    if (cntAlive_ < 0)
    {
        state_ = STATE::END;
    }
}

bool ShotBase::IsCollisionState(void)
{
    return state_ == STATE::SHOT;
}

VECTOR ShotBase::GetCollisionPos(void) const
{
    return pos_;
}

int ShotBase::GetDamage(void) const
{
    return 1;
}
