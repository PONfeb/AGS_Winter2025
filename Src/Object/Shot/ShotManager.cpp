#include "ShotManager.h"
#include "ShotNomal.h"
#include <algorithm>

ShotManager::ShotManager() {}
ShotManager::~ShotManager() { Release(); }

void ShotManager::Update()
{
    for (auto& s : shots_) if (s->IsAlive()) s->Update();

    shots_.erase(
        std::remove_if(shots_.begin(), shots_.end(),
            [](const std::unique_ptr<ShotBase>& s) { return !s->IsAlive(); }),
        shots_.end()
    );
}

void ShotManager::Draw()
{
    for (auto& s : shots_) if (s->IsAlive()) s->Draw();
}

void ShotManager::Release()
{
    shots_.clear();
}

void ShotManager::SpawnShot(ShotBase::TYPE type, VECTOR pos, VECTOR dir)
{
    // 進行方向を正規化（大事！）
    dir = VNorm(dir);

    auto shot = std::make_unique<ShotNormal>(type);
    shot->CreateShot(pos, dir);
    shots_.push_back(std::move(shot));
}
