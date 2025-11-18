
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
}

void Player::Init()
{

    modelId_ = MV1LoadModel((Application::PATH_PLAYER + "player.mv1").c_str());

    //// マテリアルの数を取得
    //int num = MV1GetMaterialNum(modelId_);
    //for (int i = 1; i < num; i++)
    //{
    //    // 0は地面なので、1から設定する
    //    MV1SetMaterialEmiColor(modelId_, i, GetColorF(0.2f, 0.2f, 0.2f, 1.0f));
    //}

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

    animationController_ = std::make_unique<AnimationController>(modelId_);

    // アニメーション登録（例）
    animationController_->AddInFbx(0, 30.f, 36); // IDLE
    animationController_->AddInFbx(1, 30.f, 73); // WALK
    animationController_->AddInFbx(2, 30.f, 39); // JUMP
    animationController_->AddInFbx(3, 30.f, 6);  // SHOT
    animationController_->AddInFbx(4, 30.f, 7);  // SHOT
    animationController_->AddInFbx(5, 30.f, 16);  // SHOT
    animationController_->AddInFbx(6, 30.f, 17);  // SHOT

    // 当たり判定を作成
    startCapsulePos_ = { 0.0f, 180.f, 0.0f };
    endCapsulePos_ = { 0.0f, 30.0f, 0.0f };
    capsuleRadius_ = 40.0f;

    // 初期状態 Idle
    ChangeState<IdleState>();

}

void Player::Update()
{
    MV1SetPosition(modelId_, pos_);
    MV1SetRotationXYZ(modelId_, angles_);

if (KEY::GetIns().GetInfo(KEY_TYPE::ATTACK).down && shotMgr_)
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

    DrawFormatString(20, 600, GetColor(255, 255, 255), "PlayerPos: (%.1f, %.1f, %.1f)", pos_.x, pos_.y, pos_.z);

}

void Player::DrawDebug()
{

    // ローカル → ワールド変換
    VECTOR startWorld = VAdd(pos_, startCapsulePos_);
    VECTOR endWorld = VAdd(pos_, endCapsulePos_);

    // カプセル可視化（スフィア + ライン）
    DrawSphere3D(startWorld, capsuleRadius_, 16, GetColor(0, 255, 0), GetColor(0, 255, 0), FALSE);
    DrawSphere3D(endWorld, capsuleRadius_, 16, GetColor(0, 255, 0), GetColor(0, 255, 0), FALSE);
    DrawLine3D(startWorld, endWorld, GetColor(0, 255, 0));

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

void Player::UpdateRotationByControllerStick()
{
    // 右スティックの入力を取得
    Vector2 rightStick = KEY::GetIns().GetRightStickVec();

    // 入力がない場合は回転処理をスキップ
    if (rightStick.x == 0.0f && rightStick.y == 0.0f) return;

    // atan2f は y, x の順
    float targetY = atan2f(-rightStick.x, -rightStick.y);

    VECTOR ang = GetAngles();
    ang.y = Utility::LerpAngle(ang.y, targetY, 0.3f); // 滑らかに補間
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
