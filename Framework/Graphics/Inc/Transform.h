#pragma once

#include "Common.h"

namespace BOTE::Graphics
{
	struct Transform
	{
		void TDebugUI();

		Math::Vector3 position = Math::Vector3::Zero;
		Math::Quaternion rotation = Math::Quaternion::Identity;
		Math::Vector3 scale = Math::Vector3::One;

		[[nodiscard]] Math::Matrix4 GetMatrix4() const
		{
			Math::Matrix4 matTrans = Math::Matrix4::Translation(position);
			Math::Matrix4 matRot = Math::Matrix4::RotationQuaternion(rotation);
			Math::Matrix4 matScale = Math::Matrix4::Scaling(scale);

			return matScale * matRot * matTrans;
		}
	};
}