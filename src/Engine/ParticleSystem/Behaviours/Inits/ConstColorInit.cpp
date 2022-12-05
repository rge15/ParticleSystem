#include "ConstColorInit.hpp"

namespace ParticleSystem
{
	ConstColorInit::ConstColorInit(float p_r, float p_g, float p_b, float p_a ) noexcept
	{
		CHANNELFROMFLOAT(p_r, _initColor.R );
		CHANNELFROMFLOAT(p_g, _initColor.G);
		CHANNELFROMFLOAT(p_b, _initColor.B);
		CHANNELFROMFLOAT(p_a, _initColor.A);
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	ConstColorInit::init(ParticleSlotmap& p_particles, IdPair& p_particleKey) const noexcept
	{
		auto& particleColor = p_particles.getItem<Color>(p_particleKey);
		particleColor = _initColor;
	}

}