
#pragma once

#include "Base/SceneBase.h"

#include "../Application.h"

class SceneManager;

class PauseMenu;

class TitleScene : public SceneBase
{
public:

	TitleScene(void);
	~TitleScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:

	PauseMenu* pauseMenu_;

	int img_;

};
