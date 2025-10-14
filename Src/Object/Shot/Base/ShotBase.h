#pragma once
#include <DxLib.h>

class ShotBase
{
public:
    enum class TYPE
    {
        NORMAL
    };

    enum class STATE
    {
        NONE,
        SHOT,
        END
    };

    ShotBase(TYPE type);
    virtual ~ShotBase(void);

    virtual void CreateShot(VECTOR pos, VECTOR dir);
    virtual void Update(void);
    virtual void Draw(void);

    void Release(void);
    bool IsAlive(void);
    VECTOR GetPos(void);
    float GetCollisionRadius(void);
    TYPE GetType(void);
    bool IsCollisionState(void);
    VECTOR GetCollisionPos(void) const;
    int GetDamage(void) const;

    void SetEnd() { state_ = STATE::END; }

protected:
    TYPE type_;
    STATE state_;

    VECTOR dir_;
    VECTOR scl_;
    VECTOR rot_;
    VECTOR pos_;
    float speed_;
    bool isAlive_;
    int cntAlive_;
    float collisionRadius_;
    float gravityPow_;

    virtual void SetParam(void) = 0;
    void ReduceCntAlive(void);
};
