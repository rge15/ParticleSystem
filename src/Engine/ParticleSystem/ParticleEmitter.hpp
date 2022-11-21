#pragma once
#include <Engine/GraphicResource/BaseResource.hpp>

namespace ParticleSystem
{
	class Emitter
	{
	private:
		Graphics::BaseResource* _resource { nullptr };
	
	public:
	
		Emitter() = default;
	
		~Emitter() = default;

		void
		setResource( Graphics::BaseResource& p_resource ) noexcept;
	};

}