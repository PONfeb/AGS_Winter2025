
#include "Stage3_3.h"

Stage3_3::Stage3_3() : pos_(-1), scale_(-1)
{
}

Stage3_3::~Stage3_3()
{
}

void Stage3_3::Init()
{

	pos_ = { STAGE_POS_3 };
	scale_ = { STAGE_SCALE };
	
	modelId = MV1LoadModel((Application::PATH_STAGE + "Stage3_3.mv1").c_str());
	
	MV1SetPosition(modelId, pos_);
	MV1SetScale(modelId, scale_);
	
	// è’ìÀîªíËèÓïÒÇÃç\íz
	MV1SetupCollInfo(modelId, -1);

}

void Stage3_3::Update()
{
}

void Stage3_3::Draw()
{

	MV1DrawModel(modelId);

}

void Stage3_3::Release()
{

	MV1DeleteModel(modelId);

}
