#include "Precompiled.h"
#include "Animation.h"

#include "Transform.h"

using namespace BOTE;
using namespace BOTE::Graphics;

Math::Vector3 Animation::GetPosition(float time) const
{
	// TODO
	return Math::Vector3::Zero;
}

Math::Quaternion Animation::GetRotation(float time) const
{
	// TODO
	return Math::Quaternion::Identity;
}

Math::Vector3 Animation::GetScale(float time) const
{
	// TODO
	return Math::Vector3::One;
}

Math::Matrix4 Animation::GetTransform(float time) const
{
	const auto& postion = GetPosition(time);
	const auto& rotation = GetRotation(time);
	const auto& scale = GetScale(time);
	return Transform{ postion, rotation, scale }.GetMatrix4();
}

float Animation::GetDuration() const
{
	// TODO
	return 0.0f;
}
