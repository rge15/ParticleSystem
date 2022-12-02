#pragma once
#include <utilities/chronoTypeAlias.hpp>

struct Life
{
    timePoint _initLife = demoClock::now();
    float _totalLifeTime{ 0.f };
    
    float _currNormalizedLifeTime{ 0.f };
    float _currLifeTime{ 0.f };
};