
#pragma once

#include "SceneBase.h"
#include "../Application.h"

class SceneManager;

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

};
