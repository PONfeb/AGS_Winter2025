
#include "Stage3_1.h"

Stage3_1::Stage3_1() : pos_(-1), scale_(-1)
{
}

Stage3_1::~Stage3_1()
{
}

void Stage3_1::Init()
{

	pos_ = { STAGE_POS_3 };
	scale_ = { STAGE_SCALE };
	
	modelId = MV1LoadModel((Application::PATH_STAGE + "Stage3_1.mv1").c_str());
	
	MV1SetPosition(modelId, pos_);
	MV1SetScale(modelId, scale_);
	
	// è’ìÀîªíËèÓïÒÇÃç\íz
	MV1SetupCollInfo(modelId, -1);

}

void Stage3_1::Update()
{
}

void Stage3_1::Draw()
{

	MV1DrawModel(modelId);

}

void Stage3_1::Release()
{

	MV1DeleteModel(modelId);

}
