
#pragma once

#include <string>

class StageBase 
{
public:

    virtual ~StageBase() = 0;
    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    //virtual bool IsClear() const = 0;

};
