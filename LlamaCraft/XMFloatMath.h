#pragma once
#include "pch.h"
#include "Direct3DBase.h"

class XMFloatMath {

public:
	
	static DirectX::XMFLOAT2 add(DirectX::XMFLOAT2& a, DirectX::XMFLOAT2& b);
	static DirectX::XMFLOAT2 subtract(DirectX::XMFLOAT2& a, DirectX::XMFLOAT2& b);
	static DirectX::XMFLOAT2 multiply(DirectX::XMFLOAT2& a, float f);

	static DirectX::XMFLOAT3 normalize(DirectX::XMFLOAT3& a);
	static DirectX::XMFLOAT3 add(DirectX::XMFLOAT3& a, DirectX::XMFLOAT3& b);
	static DirectX::XMFLOAT3 subtract(DirectX::XMFLOAT3& a, DirectX::XMFLOAT3& b);
	static DirectX::XMFLOAT3 dot(DirectX::XMFLOAT3& a, DirectX::XMFLOAT3& b);
	static DirectX::XMFLOAT3 multiply(DirectX::XMFLOAT3& a, float f);

private:

};