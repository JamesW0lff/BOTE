#pragma once
#include "BlendState.h"

namespace BOTE::Graphics
{
	class BlendStateManager final
	{
	public:
		static void StaticInitialize();
		static void StaticTerminate();
		static BlendStateManager* Get();
	public:
		void Initialize();
		void Terminate();
		void Set(BlendState::Mode mode);
	private:
		std::array<BlendState, 4> mBlendStates;

	};
}