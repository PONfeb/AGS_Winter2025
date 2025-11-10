
#include "Stage3_2.h"

Stage3_2::Stage3_2() : pos_(-1), scale_(-1)
{
}

Stage3_2::~Stage3_2()
{
}

void Stage3_2::Init()
{

	pos_ = { STAGE_POS_3 };
	scale_ = { STAGE_SCALE };
	
	modelId = MV1LoadModel((Application::PATH_STAGE + "Stage3_2.mv1").c_str());
	
	MV1SetPosition(modelId, pos_);
	MV1SetScale(modelId, scale_);
	
	// è’ìÀîªíËèÓïÒÇÃç\íz
	MV1SetupCollInfo(modelId, -1);

}

void Stage3_2::Update()
{
}

void Stage3_2::Draw()
{

	MV1DrawModel(modelId);

}

void Stage3_2::Release()
{

	MV1DeleteModel(modelId);

}
