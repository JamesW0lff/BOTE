#include "Precompiled.h"
#include "LightTypes.h"

using namespace BOTE;
using namespace BOTE::Graphics;

void DirectionalLight::DebugUI()
{
	if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::ColorEdit3("Ambient##Light", &ambient.r);
		ImGui::ColorEdit3("Diffuse##Light", &diffuse.r);
		ImGui::ColorEdit3("Specular##Light", &specular.r);
		ImGui::Separator();
		if (ImGui::DragFloat3("Direction##Light", &direction.x, 0.01f, -1.0f, 1.0f))
			direction = Normalize(direction);
	}
}