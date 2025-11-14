
#include "StageManager.h"

#include "Stage1_1.h"
#include "Stage1_2.h"
#include "Stage1_3.h"
#include "Stage2_1.h"
#include "Stage2_2.h"
#include "Stage2_3.h"
#include "Stage3_1.h"
#include "Stage3_2.h"
#include "Stage3_3.h"

StageManager::StageManager()
{

    // ランダムシードで初期化
    std::random_device rd;
    mt_ = std::mt19937(rd());

}

StageManager::~StageManager()
{
}

void StageManager::Init()
{

    currentIndex_ = 0;
    stages_.clear();

    // レベル1候補ステージ
    std::vector<std::function<std::unique_ptr<StageBase>()>> level1 = {
        []() { return std::make_unique<Stage1_1>(); },
        []() { return std::make_unique<Stage1_2>(); },
        []() { return std::make_unique<Stage1_3>(); },
    };

    // レベル2候補ステージ
    std::vector<std::function<std::unique_ptr<StageBase>()>> level2 = {
        []() { return std::make_unique<Stage2_1>(); },
        []() { return std::make_unique<Stage2_2>(); },
        []() { return std::make_unique<Stage2_3>(); },
    };

    // レベル3候補ステージ
    std::vector<std::function<std::unique_ptr<StageBase>()>> level3 = {
        []() { return std::make_unique<Stage3_1>(); },
        []() { return std::make_unique<Stage3_2>(); },
        []() { return std::make_unique<Stage3_3>(); },
    };

    // 抽選用の分布（0?2）
    std::uniform_int_distribution<int> dist(0, 2);

    // 各レベルからランダム抽選して確定ステージに追加
    stages_.push_back(level1[dist(mt_)]());
    stages_.push_back(level2[dist(mt_)]());
    stages_.push_back(level3[dist(mt_)]());

    // 最初のステージだけ初期化
    if (!stages_.empty()) {
        stages_[0]->Init();
    }

}

void StageManager::Update()
{

    if (currentIndex_ >= static_cast<int>(stages_.size())) return;

    auto& stage = stages_[currentIndex_];
    stage->Update();

    // クリアしたら次のステージへ
    if (stage->IsClear()) {
        currentIndex_++;

        if (currentIndex_ < static_cast<int>(stages_.size())) {
            stages_[currentIndex_]->Init();
        }
    }

}

void StageManager::Draw()
{

    for (auto& stage : stages_) {
        stage->Draw();
    }

}


void StageManager::Release()
{

    for (auto& stage : stages_) {
        stage->Release();
    }
    stages_.clear();

}

bool StageManager::IsAllClear() const
{
    return currentIndex_ >= static_cast<int>(stages_.size());
}
