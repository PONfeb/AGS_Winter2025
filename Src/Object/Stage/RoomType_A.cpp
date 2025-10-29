
#include "RoomType_A.h"
#include "../../Utility/Utility.h"
#include "../../Application.h"

RoomType_A::RoomType_A() : stageModel_(-1), pos_{ DEFAULT_POS }, scales_ { STAGE_SCALES } {}

RoomType_A::~RoomType_A() {}

void RoomType_A::Init()
{

    stageModel_ = MV1LoadModel((Application::PATH_STAGE + "Stage_Base_3.mv1").c_str());

    MV1SetScale(stageModel_, scales_);
    MV1SetPosition(stageModel_, pos_);

    MV1SetupCollInfo(stageModel_, -1);

}
        
void RoomType_A::Update()
{
}

void RoomType_A::Draw()
{
    if (stageModel_ != -1)
    {
        MV1DrawModel(stageModel_);
    }
}

void RoomType_A::Release()
{
    if (stageModel_ != -1)
    {
        MV1DeleteModel(stageModel_);
        stageModel_ = -1;
    }
}

int RoomType_A::GetModelId(void)
{
    return stageModel_;
}
