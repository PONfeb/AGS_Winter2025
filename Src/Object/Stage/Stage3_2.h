
#pragma once

#include "Base/StageBase.h"

class Stage3_2 : public StageBase
{
public:

    Stage3_2();
    ~Stage3_2() override = default;

    void Init() override;
    void Update() override;

    bool IsClear() const override { return true; }

private:

    VECTOR pos_;
    VECTOR scale_;
};
