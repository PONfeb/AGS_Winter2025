
#pragma once

#include "Base/StageBase.h"

#include <DxLib.h>

class Stage3_1 : public StageBase
{
public:

	Stage3_1();
	~Stage3_1();

	void Init() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	bool IsClear() const override { return true; }

private:

	VECTOR pos_;
	VECTOR scale_;

};