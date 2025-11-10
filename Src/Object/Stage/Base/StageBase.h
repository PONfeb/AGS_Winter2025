
#pragma once

#include <string>

#include "../../../Application.h"

class StageBase 
{
public:

    // ステージスケール
	static constexpr VECTOR STAGE_SCALE = { 1.5f, 1.5f, 1.5f };

	// ステージ描画位置
    static constexpr VECTOR STAGE_POS_1 = { 0.f, 0.f, 0.f };
    static constexpr VECTOR STAGE_POS_2 = { 0.f, 0.f, 1000.f };
    static constexpr VECTOR STAGE_POS_3 = { 0.f, 0.f, 2000.f };

    StageBase();
    virtual ~StageBase() = 0;

    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
	virtual void Release() = 0;

    virtual bool IsClear() const = 0;

    // 縦連結用 Zオフセット管理
    void SetOffsetZ(float z) { offsetZ_ = z; }
    float GetOffsetZ() const { return offsetZ_; }

    // ステージの奥行きを返す（次ステージのオフセット計算用）
    virtual float GetDepth() const = 0;

protected:

    int modelId;

    float offsetZ_ = 0.0f; // Z方向のオフセット

};
