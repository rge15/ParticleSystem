#pragma once
#include <concepts>
#include <utilities/concepts.hpp>

namespace DemoMath
{

	constexpr float PI = 3.14159265359;
	
	template<numericType numT>
	numT
	min( numT a, numT b) noexcept;

	float
	remap( float value, float actualMax, float targetMax ) noexcept;

	template<numericType numT>
	float
	remap( numT value, float actualMax, float targetMax ) noexcept;

	template<numericType numT>
	numT
	max(numT val1, numT val2) noexcept;

}

#include "DemoMath.tpp"