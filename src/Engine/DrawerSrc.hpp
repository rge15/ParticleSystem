#pragma once
#include <cmath>

constexpr int _sinusTableIndices = 360;
constexpr int _cosOffsetTable = _sinusTableIndices * 3/4; 

struct DrawerSrc
{
	int _colourSinus[ _sinusTableIndices ];
	float _normalizedSinus[ _sinusTableIndices ];

	DrawerSrc() noexcept
	{
		init();
	}

	void
	init() noexcept
	{
		float rad { 0.f }, resul;

		constexpr float conversion = 360/_sinusTableIndices;
		
		for(int i = 0; i < _sinusTableIndices ; i++)
		{
			rad = (i * conversion) * 0.0174533;
			resul = sin(rad);
			//Range for a color channel
			_colourSinus[i] = resul*255;
			_normalizedSinus[i] = resul;
		}
	}
};
