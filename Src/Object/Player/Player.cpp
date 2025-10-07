
#include "Player.h"
#include "State/IdleState.h"
#include "State/MoveState.h"
#include "State/JumpState.h"
#include "../../Manager/InputManager.h"
#include "../../Application.h"

Player::Player() : modelId_(-1), pos_(DEFAULT_POS), angles_{ 0,0,0 }, scales_(SCALES), jumpPow_(0.f), isJump_(false)
{
}

Player::~Player()
{
    if (modelId_ != -1) MV1DeleteModel(modelId_);
}

void Player::Init(const char* modelPath)
{
    modelId_ = MV1LoadModel((Application::PATH_PLAYER + "player.mv1").c_str());

    if (modelId_ == -1) {
        printfDx("Player model load failed\n");
    }

    //int animNum = MV1GetAnimNum(modelId_);
    //printfDx("Anim num: %d\n", animNum);
    //for (int i = 0; i < animNum; i++) {
    //    double totalTime = MV1GetAnimTotalTime(modelId_, i);
    //    printfDx("Anim %d time: %f\n", i, totalTime);
    //}

    MV1SetPosition(modelId_, pos_);
    MV1SetScale(modelId_, scales_);

    animationController_ = std::make_unique<AnimationController>(modelId_);

    // アニメーション登録（例）
    animationController_->AddInFbx(0, 30.f, 36); // IDLE
    animationController_->AddInFbx(1, 30.f, 73); // WALK
    animationController_->AddInFbx(2, 30.f, 39); // JUMP
    animationController_->AddInFbx(3, 30.f, 6);  // SHOT
    animationController_->AddInFbx(4, 30.f, 7);  // SHOT
    animationController_->AddInFbx(5, 30.f, 16);  // SHOT
    animationController_->AddInFbx(6, 30.f, 17);  // SHOT

    // 初期状態 Idle
    ChangeState<IdleState>();
}

void Player::Update()
{
    MV1SetPosition(modelId_, pos_);
    MV1SetRotationXYZ(modelId_, angles_);

    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);

    static int prevMouseX = mouseX;
    static int prevMouseY = mouseY;

    if (mouseX != prevMouseX || mouseY != prevMouseY)
    {
        // マウス操作があったらマウスで回転
        UpdateRotationByMouse();
        mouseIdleFrame_ = 0; // タイマーリセット
        isMouseControlActive_ = true;
    }
    else
    {
        // マウス操作なし
        mouseIdleFrame_++;
        if (mouseIdleFrame_ >= MOUSE_IDLE_THRESHOLD_FRAMES)
        {
            // 2秒以上操作がない → キーボード回転に切り替え
            UpdateRotationByKeyboard();
            isMouseControlActive_ = false;
        }
    }

    prevMouseX = mouseX;
    prevMouseY = mouseY;

    // ---- デバッグ用アニメーションテスト ----
#ifdef _DEBUG
    if (CheckHitKey(KEY_INPUT_1)) {
        animationController_->Play(0, true); // IDLE
    }
    else if (CheckHitKey(KEY_INPUT_2)) {
        animationController_->Play(1, true); // WALK
    }
    else if (CheckHitKey(KEY_INPUT_3)) {
        animationController_->Play(2, false); // JUMP
	}
	else if (CheckHitKey(KEY_INPUT_4)) {
		animationController_->Play(3, false); // SHOT
	}
	else if (CheckHitKey(KEY_INPUT_5)) {
		animationController_->Play(4, false); // SHOT
	}
	else if (CheckHitKey(KEY_INPUT_6)) {
		animationController_->Play(5, false); // SHOT
	}
	else if (CheckHitKey(KEY_INPUT_7)) {
		animationController_->Play(6, false); // SHOT
	}
    else
#endif
    {
        // 通常の状態管理を使う
        if (currentState_) currentState_->Update(*this);
    }

    if (animationController_) animationController_->Update();
}

void Player::Draw()
{
    MV1DrawModel(modelId_);
}

void Player::Release()
{
    MV1DeleteModel(modelId_);
}

void Player::UpdateRotationByMouse()
{
    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);

    static int prevMouseX = mouseX;
    static int prevMouseY = mouseY;

    // マウス移動を検知
    if (mouseX != prevMouseX || mouseY != prevMouseY)
    {
        isMouseControlActive_ = true;

        VECTOR playerScreenPos = ConvWorldPosToScreenPos(GetPos());

        float dx = static_cast<float>(mouseX) - playerScreenPos.x;
        float dy = static_cast<float>(mouseY) - playerScreenPos.y;

        float angle = atan2f(dy, dx);

        VECTOR angles = GetAngles();
        angles.y = angle + DX_PI_F / -2.0f; // モデルの向きに応じて調整
        SetAngles(angles);
    }

    prevMouseX = mouseX;
    prevMouseY = mouseY;
}

void Player::UpdateRotationByKeyboard()
{
}
