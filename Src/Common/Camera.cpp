
#include "Camera.h"
#include "../Object/Player/Player.h"
#include "../Common/Instance.h"
#include "../Utility/Utility.h"
#include <EffekseerForDXLib.h>

Camera::Camera(void)
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

   SetCameraPositionAndAngle(pos_, angles_.x, angles_.y, angles_.z);
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
	// 何もしない
}
void Camera::SetBeforeDrawFree(void)
{
}

void Camera::SetBeforeDrawFollow(Player* player)
{
	player_ = player;

	if (player_ != nullptr)
	{
		VECTOR playerPos = player_->GetPos();
		pos_.x = playerPos.x;
		pos_.z = playerPos.z - 1000.0f;
	}
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
