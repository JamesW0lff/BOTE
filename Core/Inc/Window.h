#pragma once

namespace BOTE::Core
{
	class Window
	{
	public:
		void Initialize(HINSTANCE instance, std::wstring appName, uint32_t width, uint32_t height);
		void Terminate();

		HWND GetWindowHandle() const { return mWindow; }
		void ProcessMessage();

		bool IsActive() const { return mActive; }

	private:
		HINSTANCE mInstance = nullptr;
		HWND mWindow = nullptr;
		std::wstring mAppName;
		bool mActive = false;
	};
}