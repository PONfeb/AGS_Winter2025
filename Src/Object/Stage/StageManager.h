
#pragma once

#include <vector>
#include <random>

enum class StageType {

    Stage1_1,
    Stage1_2,
    Stage1_3,
    Stage2_1,
    Stage2_2,
    Stage2_3,
    Stage3_1,
    Stage3_2,
    Stage3_3,

    None

};

class StageManager
{
public:

    static StageManager& GetInstance()
    {
        static StageManager instance;
        return instance;
    }

    // コピー禁止・代入禁止
    StageManager(const StageManager&) = delete;
    StageManager& operator=(const StageManager&) = delete;

    // メイン処理
    void Init();
    void Update();
    void Draw();
    void Release();

    StageType GetCurrentStageType() const;
    void NextStage();
    bool IsLastStage() const;

private:

    StageManager();
    ~StageManager() = default;

    StageType RandomSelectStage(const std::vector<StageType>& group);

private:

    std::vector<std::vector<StageType>> stageGroups_;   // 各ステージグループ（1, 2, 3）
    std::vector<StageType> selectedStages_;             // 抽選で決まったステージ
    int currentStageIndex_;                             // 現在のステージ番号
};
