#pragma once
#include "pch.h"
#include <vector>
using namespace DirectX;

struct Vertex 
	{
	  XMFLOAT3 Pos;
	  XMFLOAT4 Color;
	};

class Geometry {
public:

	

	struct GVertex 
	{
	
	  XMFLOAT3 Position;
	  XMFLOAT3 Normal;
	  XMFLOAT3 TangentU;
	  XMFLOAT2 TexC;
	  

	};
	 
	struct MeshData
	 {
		std::vector<GVertex> Vertices;
		std::vector<UINT> Indices;
	 };


		 
	void CreateGrid(float width, float depth, UINT m, UINT n, MeshData& meshData);
	std::vector<Vertex> GetVertices();
	float GetHeight(float x, float z);
private:
	std::vector<Vertex> vs;
	

};