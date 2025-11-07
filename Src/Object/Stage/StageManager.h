
#pragma once

#include <vector>
#include <memory>
#include <functional>

#include "Base/StageBase.h"

// 各ステージをランダムで抽選して順番に実行するマネージャ
class StageManager 
{
private:

    std::vector<std::unique_ptr<StageBase>> stages_; // 抽選された3ステージ
    int currentIndex_ = 0;                           // 現在のステージ番号

public:

    StageManager() = default;
    ~StageManager() = default;

    void Init();       // ステージ抽選＆初期化
    void Update();     // 現在ステージの更新
    void Draw();       // 現在ステージの描画
    //bool IsAllClear() const; // 全ステージクリア判定

};
