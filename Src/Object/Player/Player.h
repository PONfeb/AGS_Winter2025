
#pragma once

#include <DxLib.h>
#include <memory>

#include "State/Base/PlayerStateBase.h"

#include "../Shot/ShotManager.h"
#include "../../Common/AnimationController.h"

class Player
{
public:

    static constexpr VECTOR DEFAULT_POS = { 0, -100, 0 };
    static constexpr VECTOR SCALES = { 1.f, 1.f, 1.f };

    static constexpr float MOVE_SPEED = 10.0f;

    static constexpr float JUMP_POW = 20.0f;
    static constexpr float GRAVITY = 0.8f;

    static constexpr int MOUSE_IDLE_THRESHOLD_FRAMES = 10.0f;

    Player();
    ~Player();

    void Init(const char* modelPath);
    void Update();
    void Draw();

    void DrawDebug();

    void Release();

    VECTOR GetPos() const { return pos_; }
    void SetPos(const VECTOR& pos) { pos_ = pos; }

    // カプセルの当たり判定を取得
    const VECTOR& GetStartCapsulePos(void) const { return startCapsulePos_; }
    const VECTOR& GetEndCapsulePos(void) const { return endCapsulePos_; }
    const float& GetCapsuleRadius(void) const { return capsuleRadius_; }

    VECTOR GetAngles() const { return angles_; }
    void SetAngles(const VECTOR& angles) { angles_ = angles; }

    AnimationController* GetAnimationController() { return animationController_.get(); }

    float GetJumpPow() const { return jumpPow_; }
    void SetJumpPow(float pow) { jumpPow_ = pow; }
    bool GetIsJump() const { return isJump_; }
    void SetIsJump(bool val) { isJump_ = val; }

    int GetHP() const { return hp_; }

    void UpdateRotationByMouse();
    void UpdateRotationByKeyboard(const VECTOR& moveDir);
    void UpdateRotationByControllerStick();

    void TakeDamage(int damage);

	bool IsMouseControlActive() const { return isMouseControlActive_; }

    template<typename StateType>
    void ChangeState()
    {
        if (currentState_) currentState_->Exit(*this);
        currentState_ = std::make_unique<StateType>();
        currentState_->Enter(*this);
    }

    float GetCollisionRadius() const { return collisionRadius_; }

    VECTOR GetForwardDir() const;

    void SetShotManager(ShotManager* mgr) { shotMgr_ = mgr; }

    float collisionRadius_ = 24.0f; // 判定用半径

private:

    ShotManager* shotMgr_;

    VECTOR pos_;
    VECTOR angles_;
    VECTOR scales_;

	VECTOR startCapsulePos_; // カプセル当たり判定開始位置
	VECTOR endCapsulePos_;   // カプセル当たり判定終了位置
	float capsuleRadius_;    // カプセル当たり判定半径

	VECTOR playerScreenPos;

	int modelId_;   // MV1モデルID
	float jumpPow_; // ジャンプ力
	bool isJump_;   // ジャンプ中かどうか

	bool isMouseControlActive_; // マウスによる視点操作が有効かどうか

    int mouseIdleFrame_ = 0;                 // マウス操作が止まってからの経過フレーム

    int hp_;
    bool isAlive_;
    int damage_ = 1; // プレイヤーに与えるダメージ

    std::unique_ptr<AnimationController> animationController_;
    std::unique_ptr<PlayerStateBase> currentState_;
};
