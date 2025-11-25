
#pragma once

#include "Base/SceneBase.h"
#include "../Application.h"

class SceneManager;

class PauseMenu;

class GameOver : public SceneBase
{
public:

	GameOver(void);
	~GameOver(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:

	PauseMenu* pauseMenu_;

};
