
#include "Stage2_1.h"

Stage2_1::Stage2_1() : pos_(-1), scale_(-1)
{
}

Stage2_1::~Stage2_1()
{
}

void Stage2_1::Init()
{

	pos_ = { STAGE_POS_2 };
	scale_ = { STAGE_SCALE };

	modelId = MV1LoadModel((Application::PATH_STAGE + "Stage2_1.mv1").c_str());

	MV1SetPosition(modelId, pos_);
	MV1SetScale(modelId, scale_);

	// è’ìÀîªíËèÓïÒÇÃç\íz
	MV1SetupCollInfo(modelId, -1);

}

void Stage2_1::Update()
{
}

void Stage2_1::Draw()
{

	MV1DrawModel(modelId);

}

void Stage2_1::Release()
{

	MV1DeleteModel(modelId);

}
