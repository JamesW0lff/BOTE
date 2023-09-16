#pragma once

#include <BOTE/Inc/BOTE.h>

class GameState : public BOTE::AppState
{
public:
	void Initialize() override;
	void Terminate() override;

	void Update(float deltaTime) override;
	void Render() override;
	void DebugUI() override;

private:
	BOTE::Graphics::Camera mCamera;
	BOTE::Graphics::DirectionalLight mDirectionalLight;

	BOTE::Graphics::RenderTarget mBaseRenderTarget;
	BOTE::Graphics::RenderTarget mBloomRenderTarget;

	BOTE::Graphics::StandardEffect mStandardEffect;
	BOTE::Graphics::TexturingEffect mTexturingEffect;
	BOTE::Graphics::GaussianBlurEffect mGaussianBlurEffect;
	BOTE::Graphics::PostProcessingEffect mPostProcessingEffect;

	BOTE::Graphics::RenderObject mSkydome;
	BOTE::Graphics::RenderObject mEarth;
	BOTE::Graphics::RenderObject mCloud;
	BOTE::Graphics::RenderObject mSun;
	BOTE::Graphics::RenderObject mScreenQuad;

	float mEarthDistance = 0.0f;
	float mEarthRotation = 0.0f;
	float mEarthRevolution = 0.0f;

	float mCloudRotation = 0.0f;
};