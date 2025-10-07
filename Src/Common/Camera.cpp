
#include "Camera.h"
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

	// 定点カメラを初期状態にする
   	ChangeMode(MODE::FREE);
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
	}

	SetCameraPositionAndAngle(pos_, angles_.x, angles_.y, angles_.z);
}

void Camera::DrawDebug(void)
{
	DrawFormatString(
		0, 0, 0x000000, "カメラ座標：(%.2f, %.2f, %.2f)",
		pos_.x, pos_.y, pos_.z);
	DrawFormatString(
		0, 20, 0x000000, "カメラ角度：(%.2f, %.2f, %.2f)",
		angles_.x * 180.0f / DX_PI_F,
		angles_.y * 180.0f / DX_PI_F,
		angles_.z * 180.0f / DX_PI_F);
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

	// カメラの回転角度
	float rotPow = 1.0f * DX_PI_F / 180.0f;
	if (Ins::input().IsNew(KEY_INPUT_UP))    angles_.x -= rotPow; // 上下回転
	if (Ins::input().IsNew(KEY_INPUT_DOWN))  angles_.x += rotPow;
	if (Ins::input().IsNew(KEY_INPUT_LEFT))  angles_.y -= rotPow; // 左右回転
	if (Ins::input().IsNew(KEY_INPUT_RIGHT)) angles_.y += rotPow;

	// 移動速度
	float movePow = 3.0f;

	// カメラ向きの前方向ベクトル（XZ平面のみ）
	VECTOR forward = VGet(sinf(angles_.y), 0, cosf(angles_.y));
	// 右方向ベクトル（XZ平面）
	VECTOR right = VGet(cosf(angles_.y), 0, -sinf(angles_.y));

	// 前後左右移動
	if (Ins::input().IsNew(KEY_INPUT_W)) pos_ = VAdd(pos_, VScale(forward, movePow));
	if (Ins::input().IsNew(KEY_INPUT_S)) pos_ = VAdd(pos_, VScale(forward, -movePow));
	if (Ins::input().IsNew(KEY_INPUT_A)) pos_ = VAdd(pos_, VScale(right, -movePow));
	if (Ins::input().IsNew(KEY_INPUT_D)) pos_ = VAdd(pos_, VScale(right, movePow));

	// Q/Eで上下移動
	if (Ins::input().IsNew(KEY_INPUT_Q)) pos_.y += movePow;
	if (Ins::input().IsNew(KEY_INPUT_E)) pos_.y -= movePow;
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
