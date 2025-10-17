
#include "ControlManager.h"
#include <algorithm>
#include <cmath>

//-------------------------
// シングルトン
//-------------------------
ControllerInputManager& ControllerInputManager::GetInstance()
{
    static ControllerInputManager instance;
    return instance;
}

//-------------------------
// 初期化
//-------------------------
void ControllerInputManager::Init()
{
    DetectControllerType();
    SetupButtonMap();
}

//-------------------------
// コントローラー判定
//-------------------------
void ControllerInputManager::DetectControllerType()
{
    char name[256];
    GetJoypadName(DX_INPUT_PAD1, name, sizeof(name));

    controllerName_ = name;

    // 小文字化
    std::transform(controllerName_.begin(), controllerName_.end(), controllerName_.begin(), ::tolower);
}

//-------------------------
// ボタンマップ設定
//-------------------------
void ControllerInputManager::SetupButtonMap()
{
    buttonMap_.clear();

    if (controllerName_.find("xinput") != std::string::npos || controllerName_.find("xbox") != std::string::npos)
    {
        // 🎮 Xbox系
        buttonMap_[BUTTON::CONFIRM] = PAD_INPUT_A;
        buttonMap_[BUTTON::CANCEL] = PAD_INPUT_B;
        buttonMap_[BUTTON::JUMP] = PAD_INPUT_A;
        buttonMap_[BUTTON::ATTACK] = PAD_INPUT_X;
        buttonMap_[BUTTON::MENU] = PAD_INPUT_START;
    }
    else if (controllerName_.find("dualshock") != std::string::npos ||
        controllerName_.find("dual sense") != std::string::npos ||
        controllerName_.find("ps") != std::string::npos)
    {
        // 🎮 PlayStation系
        buttonMap_[BUTTON::CONFIRM] = PAD_INPUT_2;  // ×
        buttonMap_[BUTTON::CANCEL] = PAD_INPUT_3;  // ○
        buttonMap_[BUTTON::JUMP] = PAD_INPUT_2;
        buttonMap_[BUTTON::ATTACK] = PAD_INPUT_1;  // □
        buttonMap_[BUTTON::MENU] = PAD_INPUT_START;
    }
    else if (controllerName_.find("nintendo") != std::string::npos ||
        controllerName_.find("pro controller") != std::string::npos)
    {
        // 🎮 任天堂系
        buttonMap_[BUTTON::CONFIRM] = PAD_INPUT_B;
        buttonMap_[BUTTON::CANCEL] = PAD_INPUT_A;
        buttonMap_[BUTTON::JUMP] = PAD_INPUT_B;
        buttonMap_[BUTTON::ATTACK] = PAD_INPUT_Y;
        buttonMap_[BUTTON::MENU] = PAD_INPUT_START;
    }
    else
    {
        // 🕹 不明（汎用）
        buttonMap_[BUTTON::CONFIRM] = PAD_INPUT_A;
        buttonMap_[BUTTON::CANCEL] = PAD_INPUT_B;
        buttonMap_[BUTTON::JUMP] = PAD_INPUT_A;
        buttonMap_[BUTTON::ATTACK] = PAD_INPUT_X;
        buttonMap_[BUTTON::MENU] = PAD_INPUT_START;
    }
}

//-------------------------
// 更新
//-------------------------
void ControllerInputManager::Update()
{
    padOld_ = padNow_;
    padNow_ = GetJoypadInputState(DX_INPUT_PAD1);

    // スティック入力
    leftStickX_ = GetJoypadAnalogInputX(DX_INPUT_PAD1) / 1000.0f;
    leftStickY_ = GetJoypadAnalogInputY(DX_INPUT_PAD1) / 1000.0f;
    rightStickX_ = GetJoypadAnalogInputRX(DX_INPUT_PAD1) / 1000.0f;
    rightStickY_ = GetJoypadAnalogInputRY(DX_INPUT_PAD1) / 1000.0f;

    // デッドゾーン処理
    auto deadZone = [](float& v)
        {
            if (std::fabs(v) < 0.2f) v = 0.0f;
        };
    deadZone(leftStickX_);
    deadZone(leftStickY_);
    deadZone(rightStickX_);
    deadZone(rightStickY_);
}

//-------------------------
// ボタン状態
//-------------------------
bool ControllerInputManager::IsPressed(BUTTON btn)
{
    if (buttonMap_.count(btn) == 0) return false;
    return (padNow_ & buttonMap_[btn]) != 0;
}

bool ControllerInputManager::IsTriggered(BUTTON btn)
{
    if (buttonMap_.count(btn) == 0) return false;
    int bit = buttonMap_[btn];
    return ((padNow_ & bit) != 0) && ((padOld_ & bit) == 0);
}

bool ControllerInputManager::IsReleased(BUTTON btn)
{
    if (buttonMap_.count(btn) == 0) return false;
    int bit = buttonMap_[btn];
    return ((padNow_ & bit) == 0) && ((padOld_ & bit) != 0);
}
