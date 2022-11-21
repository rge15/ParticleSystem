#pragma once


namespace Graphics
{
	class BaseResource
	{
	public:
		explicit BaseResource() = default;
	
		virtual ~BaseResource();
	
		void
		virtual Init() noexcept = 0;

		void
		virtual Draw() noexcept = 0;
	};

}