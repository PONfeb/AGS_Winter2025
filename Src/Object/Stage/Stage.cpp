
#include "Stage.h"

#include "../../Application.h"

Stage::Stage() : modelId_1(-1), modelId_2(-1), modelId_3(-1)
{
}

Stage::~Stage()
{
}

void Stage::Init()
{

	// ステージモデル
	modelId_1 = MV1LoadModel((Application::PATH_STAGE + "Stage1_1.mv1").c_str());
	modelId_2 = MV1LoadModel((Application::PATH_STAGE + "Stage2_1.mv1").c_str());
	modelId_3 = MV1LoadModel((Application::PATH_STAGE + "Stage3_1.mv1").c_str());

	pos_1 = STAGE_POS_1;
	pos_2 = STAGE_POS_2;
	pos_3 = STAGE_POS_3;

	scale_ = STAGE_SCALE;

	//// マテリアルの数を取得
	//int num = MV1GetMaterialNum(modelId_1);
	//for (int i = 1; i < num; i++)
	//{
	//	// 0は地面なので、1から設定する
	//	MV1SetMaterialEmiColor(modelId_1, i, GetColorF(0.2f, 0.2f, 0.2f, 1.0f));
	//}

	// 先にスケールを設定
	MV1SetScale(modelId_1, scale_);
	MV1SetScale(modelId_2, scale_);
	MV1SetScale(modelId_3, scale_);

	// 衝突判定情報の構築
	MV1SetupCollInfo(modelId_1, -1);
	MV1SetupCollInfo(modelId_2, -1);
	MV1SetupCollInfo(modelId_3, -1);

}

void Stage::Update()
{
}

void Stage::Draw()
{

	// ステージ１描画
	MV1SetPosition(modelId_1, pos_1);
	MV1DrawModel(modelId_1);
	
	// ステージ２描画
	MV1SetPosition(modelId_2, pos_2);
	MV1SetRotationMatrix(modelId_2, MGetRotY(DX_PI_F / 2.f));
	MV1DrawModel(modelId_2);
	
	// ステージ３描画
	MV1SetPosition(modelId_3, pos_3);
	MV1SetRotationMatrix(modelId_3, MGetRotY(DX_PI_F / 2.f));
	MV1DrawModel(modelId_3);
	
}

void Stage::Release()
{

	MV1DeleteModel(modelId_1);
	MV1DeleteModel(modelId_2);
	MV1DeleteModel(modelId_3);

}
