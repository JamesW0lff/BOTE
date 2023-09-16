#include "Precompiled.h"
#include "BlendStateManager.h"

using namespace BOTE;
using namespace BOTE::Graphics;

namespace
{
	std::unique_ptr<BlendStateManager> sInstance;
}

void BlendStateManager::StaticInitialize()
{
	ASSERT(sInstance == nullptr, "BlendStateManager -- System already initialized!");
	sInstance = std::make_unique<BlendStateManager>();
	sInstance->Initialize();
}

void BlendStateManager::StaticTerminate()
{
	if (sInstance != nullptr)
	{
		sInstance->Terminate();
		sInstance.reset();
	}
}

BlendStateManager* BlendStateManager::Get()
{
	ASSERT(sInstance != nullptr, "BlendStateManager -- No system registered.");
	return sInstance.get();
}

void BlendStateManager::Initialize()
{
	mBlendStates[0].Initialize(BlendState::Mode::Opaque);
	mBlendStates[1].Initialize(BlendState::Mode::AlphaBlend);
	mBlendStates[2].Initialize(BlendState::Mode::AlphaPremultiplied);
	mBlendStates[3].Initialize(BlendState::Mode::Additive);
}

void BlendStateManager::Terminate()
{
	for (auto& blendState : mBlendStates)
	{
		blendState.Terminate();
	}
}

void BlendStateManager::Set(BlendState::Mode mode)
{
	// mode	
	//	 0		-> Opaque
	//	 1		-> Alphablend
	//	 2		-> AlphapreMultiplied
	//	 3		-> Additive
	const int index = static_cast<int>(mode);
	mBlendStates[index].Set();
}