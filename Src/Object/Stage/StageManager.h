
#pragma once

#include <vector>
#include <memory>
#include <functional>
#include <random>

#include "Base/StageBase.h"

class StageManager
{
public:

    static constexpr VECTOR STAGE_LEVEL_1 = { 0.f, 0.f, 0.f };
    static constexpr VECTOR STAGE_LEVEL_2 = { 0.f, 0.f, 3300.f };
    static constexpr VECTOR STAGE_LEVEL_3 = { 0.f, 0.f, 8200.f };

    StageManager();
    ~StageManager();

    void Init();       // ステージ抽選＆初期化
    void Update();     // 現在ステージの更新
    void Draw();       // 現在ステージの描画
    void Release();    // ステージ解放

    bool IsAllClear() const; // 全ステージクリア判定

    const std::vector<std::unique_ptr<StageBase>>& GetStages() const { return stages_; }

    int GetCurrentLevel(const VECTOR& playerPos) const;

private:

    std::vector<std::unique_ptr<StageBase>> stages_; // 抽選された3ステージ
    int currentIndex_ = 0;                           // 現在のステージ番号

    std::mt19937 mt_;     // 乱数エンジン

};
