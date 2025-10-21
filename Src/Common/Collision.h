
#pragma once

#include "Vector2.h"
#include <DxLib.h>

// 画像との判定が特殊な奴用
struct Rect {
	float left, top, right, bottom;

	bool Contains(float x, float y) const {
		return (top < y && bottom > y &&
			left < x && right > x);
	}
};

struct Box
{
	Vector2I pos;		// 位置座標
	Vector2I gimmicPos; 	// ギミックの位置座標
	Vector2I size;		// サイズ（幅と高さ）
	Vector2I area;		// 画像のでかさと判定が違うとき用

	Rect GetRect() const {
		return {
			static_cast<float>(pos.x),
			static_cast<float>(pos.y),
			static_cast<float>(pos.x + size.x),
			static_cast<float>(pos.y + size.y)
		};
	}
};

//drawgrahf用
static bool CheckMousePoint(Box box)
{
	int mousePosX = 0;
	int mousePosY = 0;

	GetMousePoint(&mousePosX, &mousePosY);

	return (box.pos.x < mousePosX &&
		box.pos.x + box.size.x > mousePosX &&
		box.pos.y < mousePosY &&
		box.pos.y + box.size.y > mousePosY);
}

//DrawRota用当たり判定関数
static bool CheckMousePointA(Box box)
{
	int mousePosX = 0;
	int mousePosY = 0;

	GetMousePoint(&mousePosX, &mousePosY);

	return (box.pos.x - box.size.x / 2 < mousePosX &&
		box.pos.x + box.size.x / 2 > mousePosX &&
		box.pos.y - box.size.y / 2 < mousePosY &&
		box.pos.y + box.size.y / 2 > mousePosY);
}

inline bool IsMouseInside(const Rect& rect) {
	int x = 0, y = 0;
	GetMousePoint(&x, &y);
	return rect.Contains(x, y);
}