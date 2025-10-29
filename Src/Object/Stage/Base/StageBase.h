
#pragma once

#include <DxLib.h>

class StageBase
{

public:

    // ƒ‚ƒfƒ‹‚Ì‘å‚«‚³
    static constexpr VECTOR STAGE_SCALES = { 2.f, 2.f, 2.f };

    StageBase() {}
    virtual ~StageBase() {}

    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void Release() = 0;

};