
#pragma once

#include "Base/StageBase.h"

class Stage2_2 : public StageBase
{
public:

    Stage2_2();
    ~Stage2_2() override = default;

    void Init() override;
    void Update() override;

    bool IsClear() const override { return true; }

private:

    VECTOR pos_;
    VECTOR scale_;
};
