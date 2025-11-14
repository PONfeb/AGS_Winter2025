
#pragma once

#include <vector>
#include <DxLib.h>

#include "../../../Application.h"

// ステージの基底クラス
class StageBase
{
public:

    // ステージスケール
    static constexpr VECTOR STAGE_SCALE = { 1.5f, 1.5f, 1.5f };

    // ステージ描画位置
    static constexpr VECTOR STAGE_POS_1 = { 0.f, 0.f, 0.f };
    static constexpr VECTOR STAGE_POS_2 = { 0.f, 0.f, 4800.f };
    static constexpr VECTOR STAGE_POS_3 = { 0.f, 0.f, 9600.f };

    StageBase() = default;
    virtual ~StageBase() { Release(); }

    // 初期化
    virtual void Init() = 0;

    // 更新
    virtual void Update() = 0;

    // 描画
    virtual void Draw() {
        for (auto id : modelIds) {
            if (id != -1) MV1DrawModel(id);
        }
    }

    // 解放
    virtual void Release() {
        for (auto id : modelIds) {
            if (id != -1) MV1DeleteModel(id);
        }
        modelIds.clear();
    }

    // ステージクリア判定
    virtual bool IsClear() const = 0;

    // モデルID取得
    const std::vector<int>& GetModelIds() const { return modelIds; }

protected:

    std::vector<int> modelIds; // 複数モデルを保持可能
};
