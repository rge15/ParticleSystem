#pragma once

#include <utilities/alias.hpp>
#include <Engine/utils/Timer.hpp>
#include <Engine/DrawerSrc.hpp>
#include <Engine/ParticleSystem/ParticleSystem.hpp>

class Drawer
{
	private:
		Timer	_timer { 60 };

		Vector<uniqPtr<ParticleSystem::ParticleSystem>> _pSystems {};

	public:
		uniqPtr<DrawerSrc> _src = std::make_unique<DrawerSrc>();

		/**	@brief Constructor of Drawer class */
		Drawer() = default;

		/**	@brief Default destructor for Drawe class */
		~Drawer() = default;

		/**
		 * 	@brief It draws all the FXs on _FXs
		*/
		void
		Draw( uint32_t& p_buffer ) noexcept;

		ParticleSystem::ParticleSystem&
		addParticleSystem() noexcept;
};