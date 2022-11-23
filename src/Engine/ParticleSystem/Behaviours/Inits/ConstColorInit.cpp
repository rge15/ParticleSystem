#include "ConstColorInit.hpp"

namespace ParticleSystem
{
	ConstColorInit::ConstColorInit(float p_r, float p_g, float p_b, float p_a ) noexcept
	: _r { p_r }, _g { p_g }, _b { p_b }, _a { p_a }
	{
	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	ConstColorInit::init(Particle& p_particle) const noexcept
	{
		p_particle._R = _r;
		p_particle._G = _g;
		p_particle._B = _b;
		p_particle._A = _a;
	}

}