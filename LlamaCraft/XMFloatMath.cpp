#include "pch.h"
#include "XMFloatMath.h"

DirectX::XMFLOAT2 XMFloatMath::add(DirectX::XMFLOAT2& a, DirectX::XMFLOAT2& b){
	return DirectX::XMFLOAT2(a.x+b.x, a.y+b.y);
}
	DirectX::XMFLOAT2 XMFloatMath::subtract(DirectX::XMFLOAT2& a, DirectX::XMFLOAT2& b){
		return DirectX::XMFLOAT2(a.x-b.x, a.y-b.y);
}

		DirectX::XMFLOAT2 XMFloatMath::multiply(DirectX::XMFLOAT2& a, float f){
		return DirectX::XMFLOAT2(a.x*f, a.y*f);
}

DirectX::XMFLOAT3 XMFloatMath::normalize(DirectX::XMFLOAT3& a) {
	DirectX::XMFLOAT3 c;
	XMStoreFloat3(&c, DirectX::XMVector3Normalize(XMLoadFloat3(&a)));
	return c;
}

DirectX::XMFLOAT3 XMFloatMath::add(DirectX::XMFLOAT3& a, DirectX::XMFLOAT3& b){
	return DirectX::XMFLOAT3(a.x+b.x, a.y+b.y, a.z + b.z);
}
	DirectX::XMFLOAT3 XMFloatMath::subtract(DirectX::XMFLOAT3& a, DirectX::XMFLOAT3& b){
		return DirectX::XMFLOAT3(a.x-b.x, a.y-b.y, a.z - b.z);
}

	DirectX::XMFLOAT3 XMFloatMath::dot(DirectX::XMFLOAT3& a, DirectX::XMFLOAT3& b){
		DirectX::XMFLOAT3 c;
		XMStoreFloat3(&c, DirectX::XMVector3Dot(XMLoadFloat3(&a), XMLoadFloat3(&b)));
	return c;
}

		DirectX::XMFLOAT3 XMFloatMath::multiply(DirectX::XMFLOAT3& a, float f){
		return DirectX::XMFLOAT3(a.x*f, a.y*f, a.z *f);
}

