
#pragma once

#include "Base/StageBase.h"

class RoomType_A : public StageBase
{
public:

    // ステージ生成位置
    static constexpr VECTOR DEFAULT_POS = { 0.0f, -100.0f, 0.0f };

    RoomType_A();
    ~RoomType_A();

    void Init() override;
    void Update() override;
    void Draw() override;
    void Release() override;

private:

    int stageModel_;

    VECTOR scales_;
	VECTOR pos_;

};
