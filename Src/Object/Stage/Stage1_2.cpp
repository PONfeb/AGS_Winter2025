
#include "Stage1_2.h"

Stage1_2::Stage1_2() : pos_(-1), scale_(-1)
{
}

void Stage1_2::Init()
{

    pos_ = STAGE_POS_1;
    scale_ = STAGE_SCALE;

    int id = MV1LoadModel((Application::PATH_STAGE + "Stage1_2.mv1").c_str());

    MV1SetPosition(id, pos_);
    MV1SetScale(id, scale_);

    // è’ìÀîªíËèÓïÒÇÃç\íz
    MV1SetupCollInfo(id, -1);

    // Base ÇÃ vector Ç…ìoò^
    modelIds.push_back(id);

}

void Stage1_2::Update()
{
}
