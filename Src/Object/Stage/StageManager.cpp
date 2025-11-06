
#include "StageManager.h"

#include <DxLib.h>

StageManager::StageManager()
    : currentStageIndex_(0)
{
}

void StageManager::Init()
{

    stageGroups_ = {
        { StageType::Stage1_1, StageType::Stage1_2, StageType::Stage1_3 },
        { StageType::Stage2_1, StageType::Stage2_2, StageType::Stage2_3 },
        { StageType::Stage3_1, StageType::Stage3_2, StageType::Stage3_3 },
    };

    selectedStages_.clear();
    for (const auto& group : stageGroups_)
    {
        selectedStages_.push_back(RandomSelectStage(group));
    }

    currentStageIndex_ = 0;

}

StageType StageManager::RandomSelectStage(const std::vector<StageType>& group)
{

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, static_cast<int>(group.size()) - 1);
    return group[dist(mt)];

}

void StageManager::Update()
{
}

void StageManager::Draw()
{

#ifdef _DEBUG
    DrawFormatString(50, 50, GetColor(255, 255, 255),
        "Stage %d / 3  (Type = %d)", currentStageIndex_ + 1, (int)GetCurrentStageType());
#endif

}

void StageManager::Release()
{

    selectedStages_.clear();
    stageGroups_.clear();

}

StageType StageManager::GetCurrentStageType() const
{

    if (selectedStages_.empty()) return StageType::None;
    return selectedStages_[currentStageIndex_];

}

void StageManager::NextStage()
{

    if (currentStageIndex_ < (int)selectedStages_.size() - 1)
        currentStageIndex_++;

}

bool StageManager::IsLastStage() const { return currentStageIndex_ >= (int)selectedStages_.size() - 1; }