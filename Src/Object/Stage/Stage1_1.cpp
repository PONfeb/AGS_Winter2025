
#include "Stage1_1.h"
#include "../../Utility/Utility.h"
#include "../../Application.h"

Stage1_1::Stage1_1() : stageModel_(-1), pos_(-1), scales_(-1) {}

Stage1_1::~Stage1_1() {}

void Stage1_1::Init()
{

    stageModel_ = MV1LoadModel((Application::PATH_STAGE + "Stage1_1.mv1").c_str());

	pos_ = DEFAULT_POS;
	scales_ = STAGE_SCALES;

    MV1SetScale(stageModel_, scales_);
    MV1SetPosition(stageModel_, pos_);

    MV1SetupCollInfo(stageModel_, -1);

}
        
void Stage1_1::Update()
{
}

void Stage1_1::Draw()
{
    if (stageModel_ != -1)
    {
        MV1DrawModel(stageModel_);
    }
}

void Stage1_1::Release()
{
    if (stageModel_ != -1)
    {
        MV1DeleteModel(stageModel_);
        stageModel_ = -1;
    }
}

int Stage1_1::GetModelId(void)
{
    return stageModel_;
}
