
#include "Player.h"
#include "State/IdleState.h"
#include "State/MoveState.h"
#include "State/JumpState.h"
#include "../../Manager/InputManager.h"
#include "../../Application.h"

Player::Player()
    : modelId_(-1), pos_(DEFAULT_POS), angles_{ 0,0,0 }, scales_(SCALES),
    jumpPow_(0.f), isJump_(false)
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
    MV1SetPosition(modelId_, pos_);
    MV1SetScale(modelId_, scales_);

    animationController_ = std::make_unique<AnimationController>(modelId_);

    // アニメーション登録（例）
    animationController_->AddInFbx(0, 30.f, 0); // IDLE
    animationController_->AddInFbx(1, 30.f, 1); // WALK
    animationController_->AddInFbx(2, 30.f, 2); // JUMP

    // 初期状態 Idle
    ChangeState<IdleState>();
}

void Player::Update()
{

	MV1SetPosition(modelId_, pos_);
	MV1SetRotationXYZ(modelId_, angles_);
    if (currentState_) currentState_->Update(*this);
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