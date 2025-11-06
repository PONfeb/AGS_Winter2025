
#pragma once

#include <DxLib.h>

class Player;

class Camera
{
public:

	// カメラモード
	enum class MODE
	{
		NONE,

		FIXED_POINT, // 定点カメラ
		FREE,		 // フリーモード
		FOLLOW,		 // 追従モード
	};

	// カメラの初期位置
	static constexpr VECTOR DEFAULT_POS = { 0.0f, 1600.0f, -2100.0f };

	// カメラの初期角度
	static constexpr VECTOR DEFAULT_ANGLES = { 45.0f * DX_PI_F / 180.0f, 0.0f, 0.0f };

	// カメラクリップ：NEAR
	static constexpr float CAMERA_NEAR = 1000.0f;

	// カメラクリップ：FAR
	static constexpr float CAMERA_FAR = 5500.0f;

	// コンストラクタ
	Camera(void);
	// デストラクタ
	~Camera(void);

	// 初期化
	void Init(void);

	// 更新
	void Update(void);

	// 描画前のカメラ設定
	void SetBeforeDraw(void);

	// デバッグ用描画
	void DrawDebug(void);

	// 解放
	void Release(void);

	// カメラモードの変更
	void ChangeMode(MODE mode);

	void SetBeforeDrawFollow(Player* player);

	void SetFollow(Player* player);

private:

	Player* player_;

	// カメラモード
	MODE mode_;

	// カメラの位置
	VECTOR pos_;

	// カメラの角度
	VECTOR angles_;

	float smoothSpeed = 0.1f;

	// カメラモード別の制御処理
	void SetBeforeDrawFixedPoint(void);
	void SetBeforeDrawFree(void);
};
