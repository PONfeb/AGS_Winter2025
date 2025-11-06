
#pragma once

#include "Base/StageBase.h"

class Stage1_1 : public StageBase
{
public:

    // ステージ生成位置
    static constexpr VECTOR DEFAULT_POS = { 0.0f, -100.0f, 0.0f };

    Stage1_1();
    ~Stage1_1();

    void Init() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    int GetModelId(void);

private:

    int stageModel_;

    VECTOR scales_;
	VECTOR pos_;

};
