#include "Precompiled.h"
#include "SimpleDraw.h"

#include "Camera.h"
#include "ConstantBuffer.h"
#include "MeshBuffer.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "VertexTypes.h"

using namespace BOTE;
using namespace BOTE::Graphics;

namespace
{
	// Private implementation - a strong encapsulation technique to hide details from the user
	class SimpleDrawImpl
	{
	public:
		void Initialize(uint32_t maxVertexCount)
		{
			mVertexShader.Initialize(L"../../Assets/Shaders/SimpleDraw.fx", VertexPC::Format);
			mPixelShader.Initialize(L"../../Assets/Shaders/SimpleDraw.fx");
			mConstantBuffer.Initialize(sizeof(Math::Matrix4));
			mMeshBuffer.Initialize(nullptr, sizeof(VertexPC), maxVertexCount, true);

			mLineVertices = std::make_unique<VertexPC[]>(maxVertexCount);
			mFaceVertices = std::make_unique<VertexPC[]>(maxVertexCount);
			mMaxVertexCount = maxVertexCount;
		}

		void Terminate()
		{
			mMeshBuffer.Terminate();
			mConstantBuffer.Terminate();
			mPixelShader.Terminate();
			mVertexShader.Terminate();
		}

		void AddLine(const Math::Vector3& v0, const Math::Vector3& v1, Color color)
		{
			if (mLineVertexCount + 2 <= mMaxVertexCount)
			{
				mLineVertices[mLineVertexCount++] = VertexPC{ v0, color };
				mLineVertices[mLineVertexCount++] = VertexPC{ v1, color };
			}
		}

		void AddFace(const Math::Vector3& v0, const Math::Vector3& v1, const Math::Vector3& v2, Color color)
		{
			if (mFaceVertexCount + 2 <= mMaxVertexCount)
			{
				mFaceVertices[mFaceVertexCount++] = VertexPC{ v0, color };
				mFaceVertices[mFaceVertexCount++] = VertexPC{ v1, color };
				mFaceVertices[mFaceVertexCount++] = VertexPC{ v2, color };
			}
		}

		void Render(const Camera& camera)
		{
			auto viewMatrix = camera.GetViewMatrix();
			auto projMatrix = camera.GetProjectionMatrix();

			mVertexShader.Bind();
			mPixelShader.Bind();

			Math::Matrix4 transform = Math::Transpose(viewMatrix * projMatrix);
			mConstantBuffer.Update(&transform);
			mConstantBuffer.BindVS(0);

			mMeshBuffer.SetTopology(MeshBuffer::Topology::Lines);
			mMeshBuffer.Update(mLineVertices.get(), mLineVertexCount);
			mMeshBuffer.Render();

			mMeshBuffer.SetTopology(MeshBuffer::Topology::Triangles);
			mMeshBuffer.Update(mFaceVertices.get(), mFaceVertexCount);
			mMeshBuffer.Render();

			// Rewind buffer so we start collecting vertices from the beginning
			mLineVertexCount = 0;
			mFaceVertexCount = 0;
		}

	private:
		VertexShader mVertexShader;
		PixelShader mPixelShader;

		ConstantBuffer mConstantBuffer;
		MeshBuffer mMeshBuffer;

		std::unique_ptr<VertexPC[]> mLineVertices;
		std::unique_ptr<VertexPC[]> mFaceVertices;
		uint32_t mLineVertexCount = 0;
		uint32_t mFaceVertexCount = 0;
		uint32_t mMaxVertexCount = 0;
	};

	std::unique_ptr<SimpleDrawImpl> sInstance;
}

void SimpleDraw::StaticInitialize(uint32_t maxVertexCount)
{
	sInstance = std::make_unique<SimpleDrawImpl>();
	sInstance->Initialize(maxVertexCount);
}

void SimpleDraw::StaticTerminate()
{
	sInstance->Terminate();
	sInstance.reset();
}

void SimpleDraw::AddLine(const Math::Vector3& v0, const Math::Vector3& v1, Color color)
{
	sInstance->AddLine(v0, v1, color);
}

void SimpleDraw::AddFace(const Math::Vector3& v0, const Math::Vector3& v1, const Math::Vector3& v2, Color color)
{
	sInstance->AddFace(v0, v1, v2, color);
}

void SimpleDraw::AddTransform(const Math::Matrix4& transform)
{
	Math::Vector3 right(transform._11, transform._12, transform._13);
	Math::Vector3 up(transform._21, transform._22, transform._23);
	Math::Vector3 look(transform._31, transform._32, transform._33);
	Math::Vector3 position(transform._41, transform._42, transform._43);

	SimpleDraw::AddLine(position, position + right, Colors::Red);
	SimpleDraw::AddLine(position, position + up, Colors::Green);
	SimpleDraw::AddLine(position, position + look, Colors::Blue);

}

void SimpleDraw::Render(const Camera& camera)
{
	sInstance->Render(camera);
}