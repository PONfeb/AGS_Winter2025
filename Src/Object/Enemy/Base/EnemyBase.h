#pragma once

#include <DxLib.h>
#include <vector>

class Player;
class AnimationController;
class ShotBase;
class ShotManager;

class EnemyBase
{
public:

    static constexpr COLOR_F COLOR_EMI_DEFAULT = { 0.6f, 0.6f, 0.6f, 1.0f };
    static constexpr COLOR_F COLOR_DIF_DEFAULT = { 0.4f, 0.4f, 0.4f, 1.0f };
    static constexpr COLOR_F COLOR_DIF_BLINK = { 1.0f, 0.2f, 0.2f, 1.0f };
    static constexpr int TERM_BLINK = 8;

    enum class TYPE { DEMON, WIZARD, GIANT, MAX };
    enum class ANIM_TYPE { ATTACK, DEATH, HIT_REACT, IDLE, JUMP, RUN, WALK, MAX };
    enum class STATE { NONE, STANDBY, ATTACK, HIT_REACT, DEAD_REACT, END };

    EnemyBase();
    virtual ~EnemyBase();

    void Init(TYPE type, int baseModelId, int baseAttackEffectModelId, Player* player);
    void Update();
    void Draw();
    void Release();

    void Damage(int damage);
    bool IsAlive() const { return isAlive_; }
    void SetAlive(bool alive) { isAlive_ = alive; }

    void ChangeState(STATE state);

    VECTOR GetPos() const { return pos_; }
    float GetCollisionRadius() const { return collisionRadius_; }
    float GetCapsuleHeight() const { return capsuleHeight_; }
    std::vector<ShotBase*> GetShots() const { return shots_; }

protected:

    // 基本情報
    int modelId_;
    VECTOR pos_;
    VECTOR angles_;
    VECTOR scales_;

    std::vector<ShotBase*> shots_;
    int baseAttackEffectModelId_;
    float collisionRadius_;
    float capsuleHeight_; // カプセル判定用高さ

    Player* player_;

    ShotManager* shotMgr_;
    AnimationController* animationController_;
    TYPE type_;
    STATE state_;
    VECTOR moveDir_;

    int stateCnt_;
    float speed_;
    int hp_;
    float spawnRange_;
    int cntAttack_;
    bool isAlive_;

    // 内部処理
    void LookPlayer();
    //void Move();
    //void SetSpawnPosition();
    //void UpdateShot();
    //void DrawShot();
    //ShotBase* GetValidShot();

    virtual void SetParam() = 0;
    virtual void ChangeStandby();
    virtual void ChangeAttack();
    virtual void ChangeDead();
    virtual void UpdateStandby();
    virtual void UpdateAttack();
    virtual void DrawStandby();
    virtual void DrawAttack();
    void HitRectUpdate();
    void UpdateDead();
    void UpdateEnd();
    void DrawHitReact();
    void DrawDead();
    void DrawEnd();
};
