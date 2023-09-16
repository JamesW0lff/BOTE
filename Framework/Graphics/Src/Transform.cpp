#include "Precompiled.h"
#include "Transform.h"

using namespace BOTE;
using namespace BOTE::Graphics;

void Transform::TDebugUI()
{
	if (ImGui::CollapsingHeader("Position", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::DragFloat("Position X##Position", &position.x, 0.1f, -10.0f, 10.0f);
		ImGui::DragFloat("Position Y##Position", &position.y, 0.1f, -10.0f, 10.0f);
		ImGui::DragFloat("Position Z##Position", &position.z, 0.1f, -10.0f, 10.0f);

		if (ImGui::Button("Reset##Position"))
		{
			position.x = 0.0f;
			position.y = 0.0f;
			position.z = 0.0f;
		}
	}

	ImGui::Separator();

	if (ImGui::CollapsingHeader("Rotation", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::DragFloat("Position X##Rotation", &rotation.x, 0.1f, -10.0f, 10.0f);
		ImGui::DragFloat("Position Y##Rotation", &rotation.y, 0.1f, -10.0f, 10.0f);
		ImGui::DragFloat("Position Z##Rotation", &rotation.z, 0.1f, -10.0f, 10.0f);

		if (ImGui::Button("Reset##Rotation"))
		{
			rotation.x = 0.0f;
			rotation.y = 0.0f;
			rotation.z = 0.0f;
		}
	}

	ImGui::Separator();

	if (ImGui::CollapsingHeader("Scale", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::DragFloat("Scale X##Scale", &scale.x, 0.1f, 0.1f, 10.0f);
		ImGui::DragFloat("Scale Y##Scale", &scale.y, 0.1f, 0.1f, 10.0f);
		ImGui::DragFloat("Scale Z##Scale", &scale.z, 0.1f, 0.1f, 10.0f);
		if (ImGui::Button("Reset##Scale"))
		{
			scale.x = 1.0f;
			scale.y = 1.0f;
			scale.z = 1.0f;
		}
	}
}