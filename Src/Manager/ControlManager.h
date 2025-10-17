#pragma once
#include <DxLib.h>
#include <string>
#include <unordered_map>

class ControllerInputManager
{
public:
    enum class BUTTON
    {
        CONFIRM,    // 決定（A / × / B）
        CANCEL,     // キャンセル（B / ○ / A）
        JUMP,       // ジャンプ（A / × / B）
        ATTACK,     // 攻撃（X / □ / Y）
        MENU,       // メニュー（START / OPTIONS / +）
        NONE
    };

    static ControllerInputManager& GetInstance();

    void Init();
    void Update();

    bool IsPressed(BUTTON btn);
    bool IsTriggered(BUTTON btn);
    bool IsReleased(BUTTON btn);

    // スティック情報
    float GetLeftStickX() const { return leftStickX_; }
    float GetLeftStickY() const { return leftStickY_; }
    float GetRightStickX() const { return rightStickX_; }
    float GetRightStickY() const { return rightStickY_; }

private:
    ControllerInputManager() = default;
    ~ControllerInputManager() = default;

    void DetectControllerType();
    void SetupButtonMap();

    int padNow_ = 0;
    int padOld_ = 0;

    float leftStickX_ = 0.0f;
    float leftStickY_ = 0.0f;
    float rightStickX_ = 0.0f;
    float rightStickY_ = 0.0f;

    std::string controllerName_;
    std::unordered_map<BUTTON, int> buttonMap_; // 共通→実際のボタン入力
};
