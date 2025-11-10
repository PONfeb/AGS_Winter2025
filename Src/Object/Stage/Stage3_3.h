
#pragma once

#include "Base/StageBase.h"
#include <DxLib.h>

class Stage3_3 : public StageBase
{
public:

	Stage3_3();
	~Stage3_3();

	void Init() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	bool IsClear() const override { return true; }

private:

	VECTOR pos_;
	VECTOR scale_;

};