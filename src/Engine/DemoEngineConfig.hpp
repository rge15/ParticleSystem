#pragma once

namespace Demoengine::Config
{
	constexpr int _widthScr { 720 };
	constexpr int _heightScr { 480 };
	constexpr int _halfWidthScr { _widthScr >> 1 };
	constexpr int _halfHeightScr { _heightScr >> 1 };
	constexpr int _pixelCount { _widthScr * _heightScr };
}