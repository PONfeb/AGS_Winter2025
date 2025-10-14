#pragma once

#include "Collision.h"
#include "../Application.h"

class PauseMenu {

public:
	const float PAUSE_OFFSET_X = 400;
	const float PAUSE_OFFSET_Y = 56;

	const float PAUSE_SPACE = 10;

	const int DEFAULT_POS_X = Application::SCREEN_SIZE_X / 2;
	const int DEFAULT_POS_Y = Application::SCREEN_SIZE_Y / 2;

	PauseMenu();
	~PauseMenu();

	void Init(void);             // ‰æ‘œ‚È‚Ç‚Ì“Ç‚İ‚İ
	void LoadInit();
	void Update(void);           // “ü—Íˆ—
	void Draw(void);             // •`‰æˆ—
	void Release(void);

	void Show();				// •\¦ó‘Ô‚É‚·‚é
	void Hide();				// ”ñ•\¦ó‘Ô‚É‚·‚é
	bool IsVisible() const;		// •\¦’†‚©‚Ç‚¤‚©

private:

	Box PauseContinue_;
	Box PauseExit_;

	bool visible_;

	int PauseContinueImg_;
	int PauseContinueHoverImg_;
	int PauseExitImg_;
	int PauseExitHoverImg_;
};
