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
	ConstColorInit::init(Particle& p_particle) const noexcept
	{
		p_particle._color = _initColor;
	}

}