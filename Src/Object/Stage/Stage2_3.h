
#pragma once

#include "Base/StageBase.h"

class Stage2_3 : public StageBase
{
public:

    Stage2_3();
    ~Stage2_3() override = default;

    void Init() override;
    void Update() override;

    bool IsClear() const override { return true; }

private:

    VECTOR pos_;
    VECTOR scale_;
};
