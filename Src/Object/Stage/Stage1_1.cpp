
#include "Stage1_1.h"

Stage1_1::Stage1_1() : pos_(-1), scale_(-1)
{
}

void Stage1_1::Init()
{

    pos_ = STAGE_POS_1;
    scale_ = STAGE_SCALE;

    int id = MV1LoadModel((Application::PATH_STAGE + "Stage1_1.mv1").c_str());

    MV1SetPosition(id, pos_);
    MV1SetScale(id, scale_);

    // マテリアルの数を取得
    int num = MV1GetMaterialNum(id);
    for (int i = 1; i < num; i++)
    {
        // 0は地面なので、1から設定する
        MV1SetMaterialEmiColor(id, i, GetColorF(0.2f, 0.2f, 0.2f, 1.0f));
    }

    // 衝突判定情報の構築
    MV1SetupCollInfo(id, -1);

    modelIds.push_back(id);

}

void Stage1_1::Update()
{
}
