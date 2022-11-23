#pragma once
#include <Engine/GraphicResource/Sprite.hpp>

namespace Graphics
{
	class ParticleSprite : public Sprite
	{
	private:
	public:
		ParticleSprite(std::string p_fileSrc);
		~ParticleSprite() = default;
	
		void
		drawParticle(
			uint32_t* p_buffer, uint32_t p_width, uint32_t p_height, 
			float p_x, float p_y, float p_r,
			float p_g , float p_b, float p_a 
		) const noexcept;
	
	};

}
