
#pragma once

#include "State/Base/PlayerStateBase.h"
#include "../../Common/AnimationController.h"
#include <memory>
#include <DxLib.h>

class Player
{
public:
    static constexpr VECTOR DEFAULT_POS = { 0, 100, 0 };
    static constexpr VECTOR SCALES = { 1.f, 1.f, 1.f };
    static constexpr float SPEED_MOVE = 10.0f;
    static constexpr float JUMP_POW = 20.0f;
    static constexpr float GRAVITY = 0.8f;

    static constexpr int MOUSE_IDLE_THRESHOLD_FRAMES = 20; // 2秒 * 60FPS

    Player();
    ~Player();

    void Init(const char* modelPath);
    void Update();
    void Draw();

    void Release();

    VECTOR GetPos() const { return pos_; }
    void SetPos(const VECTOR& pos) { pos_ = pos; }

    VECTOR GetAngles() const { return angles_; }
    void SetAngles(const VECTOR& angles) { angles_ = angles; }

    AnimationController* GetAnimationController() { return animationController_.get(); }

    float GetJumpPow() const { return jumpPow_; }
    void SetJumpPow(float pow) { jumpPow_ = pow; }
    bool GetIsJump() const { return isJump_; }
    void SetIsJump(bool val) { isJump_ = val; }

    void UpdateRotationByMouse();
    void UpdateRotationByKeyboard();

	bool IsMouseControlActive() const { return isMouseControlActive_; }

    template<typename StateType>
    void ChangeState()
    {
        if (currentState_) currentState_->Exit(*this);
        currentState_ = std::make_unique<StateType>();
        currentState_->Enter(*this);
    }



private:

    VECTOR pos_;
    VECTOR angles_;
    VECTOR scales_;

	VECTOR playerScreenPos;

	int modelId_;   // MV1モデルID
	float jumpPow_; // ジャンプ力
	bool isJump_;   // ジャンプ中かどうか

	bool isMouseControlActive_; // マウスによる視点操作が有効かどうか

    int mouseIdleFrame_ = 0;                 // マウス操作が止まってからの経過フレーム

    std::unique_ptr<AnimationController> animationController_;
    std::unique_ptr<PlayerStateBase> currentState_;
};
