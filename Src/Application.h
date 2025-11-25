
#pragma once

#include <DxLib.h>
#include <string>
#include "Manager/InputManager.h"
#include "Manager/SceneManager.h"

class Application
{
public:

    // フルスクリーンに合わせた画面サイズ（動的）
    static constexpr int SCREEN_SIZE_X = 1920;
    static constexpr int SCREEN_SIZE_Y = 1080;

    // FPS制御
    static constexpr float FRAME_RATE = 1000.0f / 60.0f;

    int currentTime = 0;
    int lastFrameTime = 0;
    int frameCnt = 0;
    int updateFrameRateTime = 0;
    float frameRate = 0.0f;

    // データパス
    static const std::string PATH_DATA;
    static const std::string PATH_MODEL;
    static const std::string PATH_IMAGE;
    static const std::string PATH_SOUND;
    static const std::string PATH_STAGE;
    static const std::string PATH_PLAYER;
    static const std::string PATH_ENEMY;
    static const std::string PATH_TITLE;
    static const std::string PATH_UI;
    static const std::string PATH_PAUSE;
    static const std::string PATH_SE;
    static const std::string PATH_BGM;

    // インスタンス生成・取得
    static void CreateInstance();
    static Application& GetInstance();

    // 初期化・ゲームループ・破棄
    void Init();
    void Run();
    void Destroy();

    bool IsInitFail() const;
    bool IsReleaseFail() const;

    void CalcFrameRate();
    void DrawFrameRate();

private:

    static Application* instance_;
    bool isInitFail_;
    bool isReleaseFail_;

    Application();
    ~Application() = default;
};
