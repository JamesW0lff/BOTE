#pragma once

#include "Service.h"

namespace BOTE
{
	class CameraService;
	class ModelCmponent;
	class TransformComponent;

	class RenderService final : public Service
	{
	public:
		SET_TYPE_ID(ServiceId::Render);

		void Initialize() override();
		void Terminate() override();

		void Update(float deltaTime) override;
		void Render() override;
		void DebugUI() override;

	private:
		friend class ModelComponent;
		
		void Register(const ModelComponent* modelComponent);
		void Unregister(const ModelComponent* modelComponent);

		struct Entry
		{
			const ModelComponent* modelComponent = nullptr;
			const TransformComponent* transformComponent = nullptr;
			Graphics::RenderGroup renderGroup;
		};

		std::vector<Entry> mRenderEntries;

		const CameraService* mCameraService = nullptr;

		Graphics::DirectionalLight mDirectionalLight;

		Graphics::StandardEffect mStandardEffect;
		Graphics::ShadowEffect mShadowEffect;

		float mFPS = 0.0f;

	};
}