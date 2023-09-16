namespace BOTE
{
	class AppState;

	struct AppConfig
	{
		std::wstring appName = L"BOTE";
		uint32_t windowWidth = 1280;
		uint32_t windowHeight = 720;
		uint32_t debugDrawLimit = 100000;
	};

	class App
	{
	public:
		template<class StateType>
		void AddState(std::string stateName)
		{
			mAppStates[stateName] = std::make_unique<StateType>();
			if (mCurrentState == nullptr)
			{
				mCurrentState = mAppStates[stateName].get();
			}
		}

		void ChangeState(const std::string& stateName);

		void Run(AppConfig appConfig);
		void Quit();

	private:
		using AppStateMap = std::map<std::string, std::unique_ptr<AppState>>;
		
		AppStateMap mAppStates;
		AppState* mCurrentState = nullptr;
		AppState* mNextState = nullptr;

		bool mRunning = false;
	};
}