#include "ParticleSprite.hpp"

namespace Graphics
{
	ParticleSprite::ParticleSprite( std::string p_fileSrc )
	: Sprite { p_fileSrc }
	{
	}

	void
	ParticleSprite::drawParticle(
		uint32_t* p_buffer, uint32_t p_width, uint32_t p_height, 
		float p_x, float p_y, float p_r,
		float p_g , float p_b, float p_a 
	) const noexcept
	{
		//Lógica de dibujado con el blendeo de sprites
	}


}