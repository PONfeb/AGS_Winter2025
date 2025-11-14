
#pragma once

#include "Base/StageBase.h"

class Stage1_3 : public StageBase
{
public:

    Stage1_3();
    ~Stage1_3() override = default;

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
