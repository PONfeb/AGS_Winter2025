
#pragma once

#include "Base/StageBase.h"

class Stage1_2 : public StageBase
{
public:

    Stage1_2();
    ~Stage1_2() override = default;

    void Init() override;
    void Update() override;
    // Draw ‚Æ Release ‚Í Base ‚Ìˆ—‚Å\•ª
    // void Draw() override;
    // void Release() override;

    bool IsClear() const override { return true; }

private:

    VECTOR pos_;
    VECTOR scale_;
};
