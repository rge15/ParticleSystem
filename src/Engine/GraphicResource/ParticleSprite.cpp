#include "ParticleSprite.hpp"

namespace Graphics
{
	ParticleSprite::ParticleSprite( std::string p_fileSrc )
	: Sprite { p_fileSrc }
	{
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	ParticleSprite::drawParticle(
		uint32_t* p_buffer, const Position& p_emitterPos ,const ParticleSystem::Particle& p_particle
	) const noexcept
	{
		int iStart, jStart, iEnd{ _height }, jEnd{ _width };
		int i, j;
		int finalX, finalY;

		int _posX = p_emitterPos.x + p_particle._pos.x;
		int _posY = p_emitterPos.y + p_particle._pos.y;

		finalX = DemoMath::max<int>( _posX, 0 );
		finalY = DemoMath::max<int>( _posY, 0 );

		jStart = abs(DemoMath::min<int>( _posX, 0 ));
		iStart = abs(DemoMath::min<int>( _posY, 0 ));

		if( finalX + _width > Demoengine::Config::_widthScr )
			jEnd = Demoengine::Config::_widthScr - finalX;

		if( finalY + _height > Demoengine::Config::_heightScr )
			iEnd = Demoengine::Config::_heightScr - finalY;

		for( i = iStart ; i < iEnd ; i++)
			for( j = jStart ; j< jEnd ; j++)
			{
				//TODO : Aquí pillar el {_data[ i * _width + j]} y procesarlo con el color de la particula

				//TODO : Tambien pillar le valor de p_buffer y hacer el alphaBlend con el valor calculado arriba

				p_buffer[ (finalY + i - iStart) * Demoengine::Config::_widthScr + (finalX + j - jStart) ] = _data[ i * _width + j];
			}
		//Lógica de dibujado con el blendeo de sprites
	}

}