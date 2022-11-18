#include <utilities/concepts.hpp>

namespace DemoMath
{

	template<numericType numT>
	numT
	min( numT a, numT b) noexcept
	{
		if( a < b )
			return a;
		return b;
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	template<numericType numT>
	float
	remap( numT value, float actualMax, float targetMax ) noexcept
	{
		return (value * (targetMax / actualMax));
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	template<numericType numT>
	numT
	max( numT a, numT b) noexcept
	{
		if( a > b )
			return a;
		return b;
	}

}