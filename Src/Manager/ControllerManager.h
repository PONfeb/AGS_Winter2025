
#pragma once

#include <DxLib.h>

class ControllerManager
{
public:
    static ControllerManager& GetInstance();

    void Update();  // 毎フレーム呼ぶ
    void Init();    // 初期化

    // ボタン関連
    bool IsPres(int button) const;        // 押されている
    bool IsTrg(int button) const;         // 押した瞬間
    bool IsRelease(int button) const;     // 離した瞬間

    // スティック関連
    VECTOR GetLeftStick() const;           // 左スティック（-1.0f ～ 1.0f）
    VECTOR GetRightStick() const;          // 右スティック（-1.0f ～ 1.0f）

private:
    ControllerManager() = default;
    ~ControllerManager() = default;

    int currentState_;     // 現在のボタン状態
    int prevState_;        // 1フレーム前のボタン状態

    int leftStickX_;
    int leftStickY_;
    int rightStickX_;
    int rightStickY_;
};
