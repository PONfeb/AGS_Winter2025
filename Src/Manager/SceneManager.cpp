
#include "SceneManager.h"
#include "../Common/Camera.h"
#include "../Scene/TitleScene.h"
#include "../Scene/GameScene.h"
#include "../Scene/GameClear.h"
#include "../Scene/GameOver.h"

SceneManager* SceneManager::instance_ = nullptr;

SceneManager::SceneManager() : currentScene_(nullptr), currentSceneId_(-1)
{
    // デルタタイム
    deltaTime_ = 1.0f / 60.0f;
}

SceneManager::~SceneManager()
{
    if (currentScene_)
    {
        currentScene_->Release();
        delete currentScene_;
        currentScene_ = nullptr;
    }
}

void SceneManager::CreateInstance()
{
    if (instance_ == nullptr)
    {
        instance_ = new SceneManager();
    }
    instance_->Init();
}

SceneManager& SceneManager::GetInstance()
{
    return *instance_;
}

void SceneManager::Init()
{
    // カメラ機能の初期化
    camera_ = new Camera();
    camera_->Init();

    Init3D();

    instance_->ChangeScene(TITLE); // 最初はタイトルシーンにしておく
}

void SceneManager::ChangeScene(SCENE_ID id)
{
    // 現在のシーンを解放
    if (currentScene_)
    {
        currentScene_->Release();
        delete currentScene_;
        currentScene_ = nullptr;
    }

    currentSceneId_ = id;

    // 新しいシーンを生成
    switch (id)
    {
    case TITLE:
        currentScene_ = new TitleScene();
        break;
    case GAME:
        currentScene_ = new GameScene();
        break;
    case GAME_CLEAR:
        currentScene_ = new GameClear();
        break;
    case GAME_OVER:
        currentScene_ = new GameOver();
        break;
    }

    if (currentScene_)
    {
        currentScene_->Init();
    }

    ResetDeltaTime();

}

void SceneManager::Update()
{

    // デルタタイム
    auto nowTime = std::chrono::system_clock::now();
    deltaTime_ = static_cast<float>(
        std::chrono::duration_cast<std::chrono::nanoseconds>(nowTime - preTime_).count() / 1000000000.0);
    preTime_ = nowTime;

    if (currentScene_)
    {
        currentScene_->Update();

        int next = currentScene_->GetNextScene();
        if (next != -1 && next != currentSceneId_)
        {
            ChangeScene(static_cast<SCENE_ID>(next));
        }
    }
}

void SceneManager::Draw()
{
    SetDrawScreen(DX_SCREEN_BACK);

    // 画面を初期化
    ClearDrawScreen();

    camera_->SetBeforeDraw();

    if (currentScene_)
    {
        currentScene_->Draw();
    }

    camera_->DrawDebug();
}

void SceneManager::Destroy()
{
    if (currentScene_)
    {
        currentScene_->Release();
        delete currentScene_;
        currentScene_ = nullptr;
    }

    // シーンの解放
    camera_->Release();
    delete camera_;

    delete instance_;
    instance_ = nullptr;
}

float SceneManager::GetDeltaTime(void) const
{
    //return 1.0f / 60.0f;
    return deltaTime_;
}

void SceneManager::ResetDeltaTime(void)
{
    deltaTime_ = 0.016f;
    preTime_ = std::chrono::system_clock::now();
}

Camera* SceneManager::GetCamera(void)
{
    return camera_;
}

void SceneManager::Init3D(void)
{
    // 背景色設定
    SetBackgroundColor(0, 139, 139);

    // Zバッファを有効にする
    SetUseZBuffer3D(true);

    // Zバッファへの書き込みを有効にする
    SetWriteZBuffer3D(true);

    // バックカリングを有効にする
    SetUseBackCulling(true);

    // ライトを有効にする
    SetUseLighting(true);

    // ディレクショナルライト方向の設定(正規化されていなくても良い)
    // 正面から斜め下に向かったライト
    ChangeLightTypeDir(VGet(-100.f, -200.f, -200.f));
}