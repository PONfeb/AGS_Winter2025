
#pragma once

#include "Base/StageBase.h"

#include <DxLib.h>

class Stage2_2 : public StageBase
{
public:

	Stage2_2();
	~Stage2_2();

	void Init() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	bool IsClear() const override { return true; }

private:

	VECTOR pos_;
	VECTOR scale_;

};