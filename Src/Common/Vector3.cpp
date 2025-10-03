
#include "Vector3.h"

// デフォルトコンストラクタ
Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f)
{
}

// 値指定コンストラクタ
Vector3::Vector3(float vX, float vY, float vZ) : x(vX), y(vY), z(vZ)
{
}

// デストラクタ
Vector3::~Vector3()
{
}