
#include "Stage3_3.h"

Stage3_3::Stage3_3() : pos_(-1), scale_(-1)
{
}

void Stage3_3::Init()
{

    pos_ = STAGE_POS_3;
    scale_ = STAGE_SCALE;

    int id = MV1LoadModel((Application::PATH_STAGE + "Stage3_3.mv1").c_str());

    MV1SetPosition(id, pos_);
    MV1SetScale(id, scale_);

    MV1SetupCollInfo(id, -1);

    modelIds.push_back(id);

}

void Stage3_3::Update()
{
}
