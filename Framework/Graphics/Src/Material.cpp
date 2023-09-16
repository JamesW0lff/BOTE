#include "Precompiled.h"
#include "Material.h"

using namespace BOTE;
using namespace BOTE::Graphics;

void Material::MDebugUI()
{
	if (ImGui::CollapsingHeader("Material", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::ColorEdit3("Ambient##Material", &ambient.r);
		ImGui::ColorEdit3("Diffuse##Material", &diffuse.r);
		ImGui::ColorEdit3("Specular##Material", &specular.r);
		ImGui::Separator();
		ImGui::DragFloat("Power##Material", &power, 0.1f, 1.0f, 100.0f);
	}
}