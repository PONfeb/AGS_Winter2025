
#include "Stage1_3.h"

Stage1_3::Stage1_3() : pos_(-1), scale_(-1)
{
}

Stage1_3::~Stage1_3()
{
}

void Stage1_3::Init()
{

	pos_ = { STAGE_POS_1 };
	scale_ = { STAGE_SCALE };

	modelId = MV1LoadModel((Application::PATH_STAGE + "Stage1_3.mv1").c_str());

	// モデルの位置とスケールを設定
	MV1SetPosition(modelId, pos_);
	MV1SetScale(modelId, scale_);

	// 衝突判定情報の構築
	MV1SetupCollInfo(modelId, -1);

}

void Stage1_3::Update()
{
}

void Stage1_3::Draw()
{

	MV1DrawModel(modelId);

}

void Stage1_3::Release()
{

	MV1DeleteModel(modelId);

}
