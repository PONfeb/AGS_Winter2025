
#include "Player.h"

#include "../../Utility/Utility.h"
#include "../../Application.h"

#include"../../Manager/KeyManager.h"

#include "State/IdleState.h"
#include "State/MoveState.h"
#include "State/JumpState.h"
#include "State/AttackState.h"

Player::Player() : modelId_(-1), pos_(DEFAULT_POS), angles_{ 0,0,0 }, scales_(SCALES), jumpPow_(0.f), isJump_(false), hp_(250)
{
}

Player::~Player()
{
    if (modelId_ != -1) MV1DeleteModel(modelId_);
}

void Player::Init(const char* modelPath)
{
    modelId_ = MV1LoadModel((Application::PATH_PLAYER + "player.mv1").c_str());

    //if (modelId_ == -1) {
    //    printfDx("Player model load failed\n");
    //}

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

if (Ins::input().IsTrgMouseLeft() && shotMgr_)
{
    currentState_ = std::make_unique<AttackState>(shotMgr_);
    currentState_->Enter(*this);
}

    // 現在の状態更新
    if (currentState_)
        currentState_->Update(*this);

    if (animationController_)
        animationController_->Update();
}

void Player::Draw()
{
    MV1DrawModel(modelId_);

    DrawSphere3D(pos_, collisionRadius_, 16, GetColor(0, 255, 0), GetColor(0, 255, 0), FALSE);
}

void Player::Release()
{
    MV1DeleteModel(modelId_);
}

void Player::UpdateRotationByMouse()
{
    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);

    VECTOR playerScreenPos = ConvWorldPosToScreenPos(GetPos());

    float dx = static_cast<float>(mouseX) - playerScreenPos.x;
    float dy = static_cast<float>(mouseY) - playerScreenPos.y;

    float angle = atan2f(dy, dx);

    VECTOR angles = GetAngles();
    angles.y = angle + DX_PI_F / -2.0f; // モデル向き補正
    SetAngles(angles);
}


void Player::UpdateRotationByKeyboard(const VECTOR& moveDir)
{
    if (moveDir.x == 0.0f && moveDir.z == 0.0f) return;

    float targetY = atan2f(-moveDir.x, -moveDir.z);
    VECTOR ang = GetAngles();
    ang.y = Utility::LerpAngle(ang.y, targetY, 0.3f);
    SetAngles(ang);
}

void Player::TakeDamage(int damage)
{
    hp_ -= damage;
    if (hp_ <= 0) isAlive_ = false;
}

VECTOR Player::GetForwardDir() const
{
    // Y軸回転角（ラジアン）を取得
    float rotY = angles_.y; // プレイヤーのY回転角を保持している変数
    // 前方向ベクトルを計算（XZ平面）
    VECTOR forward = VGet(-sinf(rotY), 0.0f, -cosf(rotY));
    return forward;
}
