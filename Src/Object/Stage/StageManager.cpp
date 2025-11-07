
#include "StageManager.h"

#include <random>

#include "Stage1_1.h"
#include "Stage1_2.h"
#include "Stage1_3.h"
#include "Stage2_1.h"
#include "Stage2_2.h"
#include "Stage2_3.h"
#include "Stage3_1.h"
#include "Stage3_2.h"
#include "Stage3_3.h"

void StageManager::Init()
{
    // 各レベルごとの候補ステージリスト
    std::vector<std::function<StageBase* ()>> level1 = {
        []() { return new Stage1_1(); },
        []() { return new Stage1_2(); },
        []() { return new Stage1_3(); },
    };
    std::vector<std::function<StageBase* ()>> level2 = {
        []() { return new Stage2_1(); },
        []() { return new Stage2_2(); },
        []() { return new Stage2_3(); },
    };
    std::vector<std::function<StageBase* ()>> level3 = {
        []() { return new Stage3_1(); },
        []() { return new Stage3_2(); },
        []() { return new Stage3_3(); },
    };

    // 乱数エンジン
    std::random_device rd;
    std::mt19937 mt(rd());

    // 各レベルから1つずつランダム抽選
    std::uniform_int_distribution<int> dist1(0, static_cast<int>(level1.size()) - 1);
    std::uniform_int_distribution<int> dist2(0, static_cast<int>(level2.size()) - 1);
    std::uniform_int_distribution<int> dist3(0, static_cast<int>(level3.size()) - 1);

    stages_.emplace_back(level1[dist1(mt)]());
    stages_.emplace_back(level2[dist2(mt)]());
    stages_.emplace_back(level3[dist3(mt)]());

    // 最初のステージを初期化
    if (!stages_.empty()) {
        stages_[0]->Init();
    }
}

void StageManager::Update()
{
    if (currentIndex_ >= static_cast<int>(stages_.size())) return;

    auto& stage = stages_[currentIndex_];
    stage->Update();

    // ステージクリアしたら次へ
    if (stage->IsClear()) {
        currentIndex_++;
        if (currentIndex_ < static_cast<int>(stages_.size())) {
            stages_[currentIndex_]->Init();
        }
    }
}

void StageManager::Draw()
{
    if (currentIndex_ < static_cast<int>(stages_.size())) {
        stages_[currentIndex_]->Draw();
    }
}

//bool StageManager::IsAllClear() const
//{
//    return currentIndex_ >= static_cast<int>(stages_.size());
//}
