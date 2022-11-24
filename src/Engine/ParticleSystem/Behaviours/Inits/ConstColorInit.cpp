#include "ConstColorInit.hpp"

namespace ParticleSystem
{
	ConstColorInit::ConstColorInit(float p_r, float p_g, float p_b, float p_a ) noexcept
	{
		uint8_t A,R,G,B;
		
		CHANNELFROMFLOAT(p_r,R);
		CHANNELFROMFLOAT(p_g,G);
		CHANNELFROMFLOAT(p_b,B);
		CHANNELFROMFLOAT(p_a,A);

		_ARGB = A;
		_ARGB <<= 8;
		_ARGB += R;
		_ARGB <<= 8;
		_ARGB += G;
		_ARGB <<= 8;
		_ARGB += B;

	}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

	void
	ConstColorInit::init(Particle& p_particle) const noexcept
	{
		p_particle._ARGBMask = _ARGB;
	}

}