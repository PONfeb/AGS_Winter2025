
#pragma once

#include <DxLib.h>

class SceneBase
{
public:
    SceneBase() : nextScene_(-1) {}
    virtual ~SceneBase() {}

    // シーンライフサイクル
    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void Release() = 0;

    // シーン遷移
    int GetNextScene() const { return nextScene_; }
    void SetNextScene(int sceneId) { nextScene_ = sceneId; }

protected:
    int nextScene_; // -1 の場合は遷移なし
};
