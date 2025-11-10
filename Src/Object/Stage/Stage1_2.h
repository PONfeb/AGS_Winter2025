
#pragma once

#include "Base/StageBase.h"

#include <DxLib.h>

class Stage1_2 : public StageBase
{
public:

	Stage1_2();
	~Stage1_2();

	void Init() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	bool IsClear() const override { return true; }

private:

	VECTOR pos_;
	VECTOR scale_;

};

