
#include "Application.h"
#include "Common/Instance.h"

Application* Application::instance_ = nullptr;

const std::string Application::PATH_DATA   = "Data/";
const std::string Application::PATH_MODEL  = PATH_DATA + "Model/";
const std::string Application::PATH_IMAGE  = PATH_DATA + "Image/ ";
const std::string Application::PATH_SOUND  = PATH_DATA + "Sound/";
const std::string Application::PATH_STAGE  = PATH_MODEL + "Stage/";
const std::string Application::PATH_PLAYER = PATH_MODEL + "Player/";
const std::string Application::PATH_ENEMY  = PATH_MODEL + "Enemy/";
const std::string Application::PATH_UI     = PATH_IMAGE + "UI/";
const std::string Application::PATH_SE     = PATH_SOUND + "SE/";
const std::string Application::PATH_BGM    = PATH_SOUND + "BGM/";

void Application::CreateInstance()
{
    if (instance_ == nullptr)
    {
        instance_ = new Application();
    }
    instance_->Init();
}

Application& Application::GetInstance()
{
    return *instance_;
}

Application::Application()
{
    isInitFail_ = false;
    isReleaseFail_ = false;
}

void Application::Init()
{

    // DxLibに解像度設定
    SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);
    ChangeWindowMode(true); // ウィンドウモード

    SetWindowText("AGS_WINTER");

    // DxLib初期化
    SetUseDirect3DVersion(DX_DIRECT3D_11);
    if (DxLib_Init() == -1)
    {
        isInitFail_ = true;
        return;
    }

    // 乱数初期化
    DATEDATA date;
    GetDateTime(&date);
    SRand(date.Year + date.Mon + date.Day + date.Hour + date.Min + date.Sec);

    // 入力初期化
    SetUseDirectInputFlag(true);
    InputManager::CreateInstance();

    // シーン管理初期化
    SceneManager::CreateInstance();
}


void Application::Run()
{
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        Sleep(1);

        currentTime = GetNowCount();

        if (currentTime - lastFrameTime >= FRAME_RATE)
        {
            lastFrameTime = currentTime;
            frameCnt++;

            // 1. 入力更新
            Ins::input().Update();

            // 2. シーン更新（NextScene もここで判定）
            Ins::scene().Update();

            // 3. 3D描画など
            Ins::scene().Draw();

            // 4. FPS表示など
            CalcFrameRate();

            ScreenFlip();
        }
    }
}

void Application::Destroy()
{
    // DxLib終了
    if (DxLib_End() == -1)
        isReleaseFail_ = true;

    // SceneManager解放
    Ins::scene().Destroy();

    // InputManager解放
    Ins::input().Destroy();

    // インスタンス削除
    delete instance_;
}

bool Application::IsInitFail() const { return isInitFail_; }

bool Application::IsReleaseFail() const { return isReleaseFail_; }

void Application::CalcFrameRate()
{
    int nDifTime = currentTime - updateFrameRateTime;
    if (nDifTime > 1000)
    {
        float fFrameCnt = static_cast<float>(frameCnt * 1000);
        frameRate = fFrameCnt / nDifTime;
        frameCnt = 0;
        updateFrameRateTime = currentTime;
    }
}

void Application::DrawFrameRate()
{
    DrawFormatString(SCREEN_SIZE_X - 90, 0, GetColor(255, 30, 30), "FPS[%.2f]", frameRate);
}
