#include "Precompiled.h"
#include "TimeUtil.h"

#pragma region GET TIME SECONDS
float BOTE::Core::TimeUtil::GetTimeSeconds()
{
	// Ctrl + F3 
	using namespace std::chrono;
	// static means not on the stack and the variable will stay around
	static const auto startTime = high_resolution_clock::now();
	const auto currentTime = high_resolution_clock::now();
	const auto ms = duration_cast<milliseconds>(currentTime - startTime).count();
	return ms / 1000.0f;
}
#pragma endregion 

#pragma region GET DELTA TIME
float BOTE::Core::TimeUtil::GetDeltaTimeSeconds()
{
	// Ctrl + F3 
	using namespace std::chrono;
	// static means not on the stack and the variable will stay around
	static auto lastTime = high_resolution_clock::now();
	const auto currentTime = high_resolution_clock::now();
	const auto ms = duration_cast<milliseconds>(currentTime - lastTime).count();
	lastTime = currentTime;
	return ms / 1000.0f;
}
#pragma endregion