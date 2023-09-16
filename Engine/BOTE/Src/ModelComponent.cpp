// #include "Precompiled.h"
// #include "ModelComponent.h"
// 
// #include "RenderService.h"
// #include "GameWorld.h"
// #include "RenderService.h"
// 
// using namespace BOTE;
// using namespace BOTE::Graphics;
// 
// void ModelComponent::Initialize()
// {
// 	auto modelManager = ModelManager::Get();
// 	mModelID = modelManager->GetModelID(mFileName);
// 	if (modelManager->GetModel(mModelID) == nullptr)
// 	{
// 		modelManager->LoadModel(mFileName);
// 		for (const auto& animationFileName : mAnimationFileNames)
// 			modelManager->AddAnimation(mModelID, animationFileName);
// 	}
// 
// 	auto renderServvice = GetOwner().GetWorld().GetService<RenderService>();
// 	renderService->Register(this);
// }
// 
// void ModelComponent::Terminate()
// {
// 	auto renderService = GetOwner().GetWorld().GetService<RenderService>();
// 	renderService->Unregister(this);
// }