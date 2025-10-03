
#pragma once

#include <chrono>
#include "../Scene/SceneBase.h"

class Camera;

class SceneBase;

class SceneManager
{
public:

    enum SceneId
    {
        TITLE,
        GAME,
        GAME_CLEAR,
        GAME_OVER,
    };

    static void CreateInstance();
    static SceneManager& GetInstance();

	void Init();

    void ChangeScene(SceneId id);

    void Update();
    void Draw();
    void Destroy();

    float GetDeltaTime(void) const;

    void ResetDeltaTime(void);

    Camera* GetCamera(void);

    void Init3D(void);

private:

    static SceneManager* instance_;
    SceneBase* currentScene_;
    int currentSceneId_;

    SceneManager();
    ~SceneManager();

    // カメラ
    Camera* camera_;

	SceneBase* scene_;

    // デルタタイム
    std::chrono::system_clock::time_point preTime_;
    float deltaTime_;
};
