#pragma once

#include "SceneBase.h"
#include "../Application.h"

class SceneManager;

class GameClear : public SceneBase
{
public:

	GameClear(void);
	~GameClear(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:

};
