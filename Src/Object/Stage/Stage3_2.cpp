
#include "Stage3_2.h"

#include "../../Application.h"

Stage3_2::Stage3_2() : pos_(-1), scale_(-1)
{
}

void Stage3_2::Init()
{

    pos_ = STAGE_POS_3;
    scale_ = STAGE_SCALE;

    int id = MV1LoadModel((Application::PATH_STAGE + "Stage3_2.mv1").c_str());

    MV1SetPosition(id, pos_);
    MV1SetScale(id, scale_);

    MV1SetupCollInfo(id, -1);

    modelIds.push_back(id);

}

void Stage3_2::Update()
{
}
