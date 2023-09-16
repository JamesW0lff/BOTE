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

	BOTE::Graphics::StandardEffect mStandardEffect;
	BOTE::Graphics::ShadowEffect mShadowEffect;

	BOTE::Graphics::RenderObject mGroundPlane;
	BOTE::Graphics::RenderObject mBall;
	BOTE::Graphics::RenderObject mDuck;

	float mBounceSpeed = 1.0f;
	float mDuckSpeed = 1.0f;

	bool mPause = false;
};