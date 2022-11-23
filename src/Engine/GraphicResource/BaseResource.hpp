#pragma once
#include <utilities/alias.hpp>

namespace Graphics
{
	class BaseResource
	{
	public:
		explicit BaseResource() = default;
	
		virtual ~BaseResource() = default;

		void
		virtual Draw( uint32_t* bufferStart, uint32_t p_width, uint32_t p_height ) const noexcept = 0;
	};

}