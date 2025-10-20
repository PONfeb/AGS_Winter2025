
#include "ControllerManager.h"
#include <algorithm>

ControllerManager& ControllerManager::GetInstance()
{
    static ControllerManager instance;
    return instance;
}

void ControllerManager::Init()
{
    currentState_ = 0;
    prevState_ = 0;
    leftStickX_ = leftStickY_ = 0.0f;
    rightStickX_ = rightStickY_ = 0.0f;
}

void ControllerManager::Update()
{
    prevState_ = currentState_;
    currentState_ = GetJoypadInputState(DX_INPUT_PAD1);

    // スティック入力の取得
    GetJoypadAnalogInput(&leftStickX_, &leftStickY_, DX_INPUT_PAD1);
    GetJoypadAnalogInputRight(&rightStickX_, &rightStickY_, DX_INPUT_PAD1);

    // -1000 ～ 1000 の範囲を -1.0 ～ 1.0 に正規化
    leftStickX_ = std::clamp(leftStickX_ / 1000.0f, -1.0f, 1.0f);
    leftStickY_ = std::clamp(leftStickY_ / 1000.0f, -1.0f, 1.0f);
    rightStickX_ = std::clamp(rightStickX_ / 1000.0f, -1.0f, 1.0f);
    rightStickY_ = std::clamp(rightStickY_ / 1000.0f, -1.0f, 1.0f);
}

bool ControllerManager::IsPres(int button) const
{
    return (currentState_ & button) != 0;
}

bool ControllerManager::IsTrg(int button) const
{
    return ((currentState_ & button) != 0) && ((prevState_ & button) == 0);
}

bool ControllerManager::IsRelease(int button) const
{
    return ((currentState_ & button) == 0) && ((prevState_ & button) != 0);
}

VECTOR ControllerManager::GetLeftStick() const
{
    return VGet(leftStickX_, leftStickY_, 0.0f);
}

VECTOR ControllerManager::GetRightStick() const
{
    return VGet(rightStickX_, rightStickY_, 0.0f);
}
