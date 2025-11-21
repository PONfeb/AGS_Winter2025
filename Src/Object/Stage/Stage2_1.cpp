
#include "Stage2_1.h"

Stage2_1::Stage2_1() : pos_(-1), scale_(-1)
{
}

void Stage2_1::Init()
{

    pos_ = STAGE_POS_2; // ƒŒƒxƒ‹2‚ÌˆÊ’u
    scale_ = STAGE_SCALE;

    int id = MV1LoadModel((Application::PATH_STAGE + "Stage2_1.mv1").c_str());

    MV1SetPosition(id, pos_);
    MV1SetScale(id, scale_);

    MV1SetupCollInfo(id, -1);

    modelIds.push_back(id);

}

void Stage2_1::Update()
{
}
