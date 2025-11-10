
#include "Stage1_1.h"

Stage1_1::Stage1_1() : pos_(-1), scale_(-1)
{
}

Stage1_1::~Stage1_1()
{
}

void Stage1_1::Init()
{

	pos_ = { STAGE_POS_1 };
	scale_ = { STAGE_SCALE };

	modelId = MV1LoadModel((Application::PATH_STAGE + "Stage1_1.mv1").c_str());

	MV1SetPosition(modelId, pos_);
	MV1SetScale(modelId, scale_);

	// è’ìÀîªíËèÓïÒÇÃç\íz
	MV1SetupCollInfo(modelId, -1);

}

void Stage1_1::Update()
{
}

void Stage1_1::Draw()
{

	MV1DrawModel(modelId);
}

void Stage1_1::Release()
{

	modelId = MV1DeleteModel(modelId);

}