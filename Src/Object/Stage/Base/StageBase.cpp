
#include "StageBase.h"

void StageBase::Draw()
{

	for (auto id : modelIds) 
	{
		if (id != -1) MV1DrawModel(id);
	}

}

void StageBase::Release() 
{

	for (auto id : modelIds) 
	{
		if (id != -1) MV1DeleteModel(id);
	}

	modelIds.clear();

}