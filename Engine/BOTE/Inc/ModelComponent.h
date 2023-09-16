// #pragma once
// 
// #include "Component.h"
// 
// namespace BOTE
// {
// 	class ModelComponent final : public Component
// 	{
// 	public:
// 		SET_TYPE_ID(ComponentId::Model);
// 
// 		void Initialize() override;
// 		void Terminate() override;
// 
// 		void SetFileName(const char* fileName) { mFileName = fileName; }
// 
// 		const Graphics::Model& GetModel() const
// 		{
// 			return *Graphics::ModelManager::Get()->Getmodel(mModelID);
// 		}
// 
// 	private:
// 		std::string mFileName;
// 		Graphics::ModelID mModelID = 0;
// 	};
// }