#include "LevelDisplay.h"

LevelDisplay::LevelDisplay()
    : state_(NONE), currentLevel_(0), timer_(0), alpha_(0)
{
}

void LevelDisplay::ShowLevel(int level)
{
    currentLevel_ = level;
    timer_ = 0;
    alpha_ = 0;
    state_ = FADE_IN;
}

void LevelDisplay::Update()
{
    switch (state_)
    {
    case NONE:
        return;

    case FADE_IN:
        timer_++;
        alpha_ = 255 * timer_ / FADE_IN_TIME;
        if (timer_ >= FADE_IN_TIME)
        {
            timer_ = 0;
            state_ = HOLD;
        }
        break;

    case HOLD:
        timer_++;
        alpha_ = 255;
        if (timer_ >= HOLD_TIME)
        {
            timer_ = 0;
            state_ = FADE_OUT;
        }
        break;

    case FADE_OUT:
        timer_++;
        alpha_ = 255 - (255 * timer_ / FADE_OUT_TIME);
        if (timer_ >= FADE_OUT_TIME)
        {
            state_ = NONE;
        }
        break;
    }
}

void LevelDisplay::Draw()
{
    if (state_ == NONE) return;

    int screenX = 1280 / 2;
    int screenY = 720 / 2;

    int color = GetColor(255, 255, 255);

    // でかく描画
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_);
    DrawFormatStringToHandle(
        screenX - 200, screenY - 50,
        color,
        0,  // フォントハンドル（0ならデフォルト）
        "LEVEL %d",
        currentLevel_
    );
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
