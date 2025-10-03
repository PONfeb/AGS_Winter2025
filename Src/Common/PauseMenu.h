#pragma once

//#include "../Common/Collision.h"
#include "../Application.h"

class PauseMenu {

public:
	static constexpr int PAUSE_OFFSET_X = 400;
	static constexpr int PAUSE_OFFSET_Y = 56;

	static constexpr int PAUSE_SPACE = 10;

	const int DEFAULT_POS_X = Application::SCREEN_SIZE_X / 2;
	const int DEFAULT_POS_Y = Application::SCREEN_SIZE_Y / 2;

	PauseMenu();
	~PauseMenu();

	void Init(void);             // ‰æ‘œ‚È‚Ç‚Ì“Ç‚İ‚İ
	void Update(void);           // “ü—Íˆ—
	void Draw(void);             // •`‰æˆ—
	void Release(void);

	void Show();				// •\¦ó‘Ô‚É‚·‚é
	void Hide();				// ”ñ•\¦ó‘Ô‚É‚·‚é
	bool IsVisible() const;		// •\¦’†‚©‚Ç‚¤‚©

private:

	Box pauseSelect_;
	Box pauseExit_;

	bool visible_;

	int pauseSelectImg_;
	int pauseSelectHoverImg_;
	int pauseExitImg_;
	int pauseExitHoverImg_;
};
