#include "ConstColorInit.hpp"

namespace ParticleSystem
{
	ConstColorInit::ConstColorInit(float p_r, float p_g, float p_b, float p_a ) noexcept
	{
		uint8_t a,r,g,b;
		CHANNELFROMFLOAT(p_r, r );
		CHANNELFROMFLOAT(p_g, g);
		CHANNELFROMFLOAT(p_b, b);
		CHANNELFROMFLOAT(p_a, a);

		_ARGB |= a;
		_ARGB << 8;
		_ARGB |= r;
		_ARGB << 8;
		_ARGB |= g;
		_ARGB << 8;
		_ARGB |= b;

	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	ConstColorInit::init(ParticleSlotmap& p_particles, IdPair& p_particleKey) const noexcept
	{
		auto& particleColor = p_particles.getItem<Color>(p_particleKey);
		particleColor._color = _ARGB;
	}

}