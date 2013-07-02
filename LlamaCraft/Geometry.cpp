#include "pch.h"
#include "Geometry.h"

using namespace DirectX;
using namespace Microsoft::WRL;
using namespace Windows::Foundation;
using namespace Windows::UI::Core;

std::vector<Vertex> Geometry::GetVertices() {
	return vs;
}

//This is still the wrong function.  I want fractals.
float Geometry::GetHeight(float x, float z) {
	return 0.05f*(z*sinf(0.1f*x) + x*cosf(0.1f*z));
}

void Geometry::CreateGrid(float width, float depth, UINT m, UINT n, MeshData& meshdata) {
		float baseHeight=-1.5f;
		

		UINT vertexCount=m*n;
		UINT faceCount = (m-1)*(n-1)*2;
		float halfWidth = 0.5f * width;
		float halfDepth = 0.5f*depth;

		float dx= width/(n-1);
		float dz = depth / (m-1);
		float du = 1.0f / (n-1);
		float dv = 1.0f / (m-1);

		meshdata.Vertices.resize(vertexCount);
		for(UINT i=0; i < m;++i)
		{
			float z = halfDepth - i*dz;
			for(UINT j = 0; j < n; ++j) {
				float x =-halfWidth + j*dx;
				meshdata.Vertices[i*n+j].Position=XMFLOAT3(x,0.0f,z);
				//for lighting --
				meshdata.Vertices[i*n+j].Normal=XMFLOAT3(0.0f,1.0f,0.0f);
				meshdata.Vertices[i*n+j].TangentU=XMFLOAT3(1.0f,0.0f,0.0f);

				meshdata.Vertices[i*n+j].TexC.x=j*du;
				meshdata.Vertices[i*n+j].TexC.y=i*dv;

			}
		}

		meshdata.Indices.resize(faceCount*3);
		UINT k = 0;
		for(UINT i = 0; i < m-1; ++i) {
			for(UINT j = 0; j < n-1; ++j) {
				meshdata.Indices[k] = i*n+j;
				meshdata.Indices[k+1] = i*n+j+1;
				meshdata.Indices[k+2] = (i+1)*n+j;
				meshdata.Indices[k+3] = (i+1)*n+j;
				meshdata.Indices[k+4] =  i*n+j+1;
				meshdata.Indices[k+5] = (i+1)*n+j+1;
				k+=6;
			}
		}

		vs.resize(meshdata.Vertices.size());
		for(size_t i = 0; i <meshdata.Vertices.size(); ++i) {
			XMFLOAT3 p = meshdata.Vertices[i].Position;
			p.y=GetHeight(p.x, p.z) + baseHeight;
			vs[i].Pos.x=p.x;
			vs[i].Pos.y=p.y;
			vs[i].Pos.z=p.z;
			vs[i].Color=XMFLOAT4(0.45f, 0.39f, 0.34f, 1.0f);
		}

}
