
#pragma once

#include "Base/StageBase.h"

class Stage3_3 : public StageBase
{
public:

    Stage3_3();
    ~Stage3_3() override = default;

    void Init() override;
    void Update() override;

    bool IsClear() const override { return true; }

private:

    VECTOR pos_;
    VECTOR scale_;
};
