
#pragma once

#include <DxLib.h>

class Stage
{
public:

    // ステージスケール
    static constexpr VECTOR STAGE_SCALE = { 1.5f, 1.5f, 1.5f };

    // ステージ描画位置
    static constexpr VECTOR STAGE_POS_1 = { 0.f, -0.5f, 0.f };
    static constexpr VECTOR STAGE_POS_2 = { 0.f, -0.5f, 4900.f };
    static constexpr VECTOR STAGE_POS_3 = { 0.f, -0.5f, 9700.f };

    Stage();
    ~Stage();

    void Init();
    void Update();
    void Draw();
    void Release();

	int GetModelId_1() const { return modelId_1; }
	int GetModelId_2() const { return modelId_2; }
	int GetModelId_3() const { return modelId_3; }

protected:

    int modelId_1;
	int modelId_2;
	int modelId_3;

    VECTOR pos_1;
    VECTOR pos_2;
    VECTOR pos_3;

	VECTOR scale_;

};
