
#include "Stage1_2.h"

Stage1_2::Stage1_2() : pos_(-1), scale_(-1)
{
}

Stage1_2::~Stage1_2()
{
}

void Stage1_2::Init()
{

	pos_ = { STAGE_POS_1 };
	scale_ = { STAGE_SCALE };

	modelId = MV1LoadModel((Application::PATH_STAGE + "Stage1_2.mv1").c_str());

	// モデルの位置とスケールを設定
	MV1SetPosition(modelId, pos_);
	MV1SetScale(modelId, scale_);

	// 衝突判定情報の構築
	MV1SetupCollInfo(modelId, -1);

}

void Stage1_2::Update()
{
}

void Stage1_2::Draw()
{

	MV1DrawModel(modelId);

}

void Stage1_2::Release()
{

	modelId = MV1DeleteModel(modelId);

}
