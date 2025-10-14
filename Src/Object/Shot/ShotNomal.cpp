
#include "ShotNomal.h"

ShotNormal::ShotNormal(TYPE type)
    : ShotBase(type)
{
}

ShotNormal::~ShotNormal(void)
{
}

void ShotNormal::SetParam(void)
{
    scl_ = { 10.0f, 10.0f, 10.0f };
    rot_ = { 0.0f, 0.0f, 0.0f };
    speed_ = 8.0f;
    cntAlive_ = 200;
    collisionRadius_ = 20.0f;
}
