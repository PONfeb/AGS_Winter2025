#pragma once
#include <DxLib.h>

class LevelDisplay
{
public:
    LevelDisplay();

    // V‚µ‚¢ƒŒƒxƒ‹‚ğ•\¦
    void ShowLevel(int level);

    // XV
    void Update();

    // •`‰æ
    void Draw();

private:
    enum STATE {
        NONE,
        FADE_IN,
        HOLD,
        FADE_OUT
    };

    STATE state_;
    int currentLevel_;
    int timer_;          // ŠÔŠÇ—
    int alpha_;          // •`‰æ“§–¾“x (0`255)

    static constexpr int FADE_IN_TIME = 30;   // 0.5•b
    static constexpr int HOLD_TIME = 90;   // 1.5•b
    static constexpr int FADE_OUT_TIME = 30;   // 0.5•b
};
