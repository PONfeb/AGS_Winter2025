
#pragma once

#include <vector>
#include <memory>

#include "Base/ShotBase.h"

class ShotManager
{
public:

    ShotManager();
    ~ShotManager();

    void Update();
    void Draw();
    void Release();

    void SpawnShot(ShotBase::TYPE type, VECTOR pos, VECTOR dir);

    const std::vector<std::unique_ptr<ShotBase>>& GetShots() const { return shots_; }

private:

    std::vector<std::unique_ptr<ShotBase>> shots_;
};
