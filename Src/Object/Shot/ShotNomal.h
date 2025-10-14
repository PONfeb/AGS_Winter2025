#pragma once
#include "Base/ShotBase.h"

class ShotNormal : public ShotBase
{
public:
    ShotNormal(TYPE type);
    ~ShotNormal(void);
    void SetParam(void) override;
};
