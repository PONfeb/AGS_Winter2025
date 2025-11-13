
#include "Camera.h"

#include "../Utility/Utility.h"

#include "../Common/Instance.h"

#include "../Object/Player/Player.h"

Camera::Camera(void) : pos_(-1), angles_(-1), mode_(MODE::NONE)
{
}

Camera::~Camera()
{
}

void Camera::Init(void)
{

	pos_ = DEFAULT_POS;
	angles_ = DEFAULT_ANGLES;

}

void Camera::Update(void)
{
}

void Camera::SetBeforeDraw(void)
{

   // クリップ距離を設定する(SetDrawScreenでリセットされる)
   SetCameraNearFar(CAMERA_NEAR, CAMERA_FAR);

   switch (mode_)
   {
   case Camera::MODE::FIXED_POINT:
       SetBeforeDrawFixedPoint();
       break;
   case Camera::MODE::FREE:
       SetBeforeDrawFree();
       break;
   case Camera::MODE::FOLLOW:
       SetBeforeDrawFollow(player_);
       break;
   }

}

void Camera::DrawDebug(void)
{

	DrawFormatString(
		0, 10, 0xffffff,
		"カメラ座標　 ：(%.1f, %.1f, %.1f)",
		pos_.x, pos_.y, pos_.z
	);

	DrawFormatString(
		0, 30, 0xffffff,
		"カメラ角度　 ：(%.1f, %.1f, %.1f)",
		Utility::Rad2DegF(angles_.x),
		Utility::Rad2DegF(angles_.y),
		Utility::Rad2DegF(angles_.z)
	);

}

void Camera::Release(void)
{
}

void Camera::SetBeforeDrawFixedPoint(void)
{

	// カメラの設定(位置と角度による制御)
	SetCameraPositionAndAngle(
		pos_,
		angles_.x,
		angles_.y,
		angles_.z
	);

}
void Camera::SetBeforeDrawFree(void)
{
}

void Camera::SetBeforeDrawFollow(Player* player)
{

	// プレイヤーの座標を取得
	VECTOR playerPos = player->GetPos();

	// 固定方向のオフセット（例：後方斜め上から見る）
	const VECTOR offset = DEFAULT_POS;

	// カメラ座標をプレイヤー基準に設定
	pos_ = VAdd(playerPos, offset);

	// カメラの注視点（プレイヤーの中心少し上）
	VECTOR target = VAdd(playerPos, VGet(0.0f, 40.0f, 0.0f));

	// カメラ設定
	SetCameraPositionAndTarget_UpVecY(pos_, target);

}

void Camera::SetFollow(Player* player)
{
	player_ = player;
}

void Camera::ChangeMode(MODE mode)
{
	// カメラモードの変更
	mode_ = mode;

	// 変更時の初期化処理
	switch (mode_)
	{
	case Camera::MODE::FIXED_POINT:
		break;
	case Camera::MODE::FREE:
		break;
	case Camera::MODE::FOLLOW:
		break;
	}
}
