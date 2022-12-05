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
		uint32_t* p_buffer, const Position& p_emitterPos ,const Position& p_particlePos, const Color& p_particleColor
	) const noexcept
	{
		int iStart, jStart, iEnd{ _height }, jEnd{ _width };
		int i, j;
		int finalX, finalY;

		int _posX = p_emitterPos.x + p_particlePos.x;
		int _posY = p_emitterPos.y + p_particlePos.y;

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
				Color pColor = p_particleColor;
				//TODO : Aquí pillar el {_data[i * _width + j]} y procesarlo con el color de la particula

				uint32_t particleSprite = _data[i * _width + j];
				uint8_t srcA, srcR, srcG, srcB;
				srcB = particleSprite;
				particleSprite >>= 8;
				srcG = particleSprite;
				particleSprite >>= 8;
				srcR = particleSprite;
				particleSprite >>= 8;
				srcA = particleSprite;
				
				//NEW ALPHA
				srcA = uint16_t(srcA * pColor.A) >> 8;
				//NEW COLOR
				srcR = uint16_t(srcR * pColor.R) >> 8;
				srcG = uint16_t(srcG * pColor.G) >> 8;
				srcB = uint16_t(srcB * pColor.B) >> 8;

				srcR = uint16_t(srcR * srcA) >> 8;
				srcG = uint16_t(srcG * srcA) >> 8;
				srcB = uint16_t(srcB * srcA) >> 8;

				//TODO : Tambien pillar le valor de p_buffer y hacer el alphaBlend con el valor calculado arriba
				uint32_t* pScreen = &p_buffer[ (finalY + i - iStart) * Demoengine::Config::_widthScr + (finalX + j - jStart) ];
				uint32_t valScreen = *pScreen;
				uint8_t dstA, dstR, dstG, dstB;

				dstB = valScreen;
				valScreen >>= 8;
				dstG = valScreen;
				valScreen >>= 8;
				dstR = valScreen;

				dstA = uint8_t(srcA^0XFF);
				
				dstR = uint16_t(dstR * dstA) >> 8;
				dstG = uint16_t(dstG * dstA) >> 8;
				dstB = uint16_t(dstB * dstA) >> 8;

				srcR += dstR;
				if(srcR < dstR)
					srcR = 255;

				srcG += dstG;
				if(srcG < dstG)
					srcG = 255;
				
				srcB += dstB;
				if(srcB < dstB)
					srcB = 255;
				
				uint32_t finalCol = srcA;
				finalCol <<= 8;
				finalCol |= srcR;
				finalCol <<= 8;
				finalCol |= srcG;
				finalCol <<= 8;
				finalCol |= srcB;

				*pScreen = finalCol; 
			}
		//Lógica de dibujado con el blendeo de sprites
	}

}