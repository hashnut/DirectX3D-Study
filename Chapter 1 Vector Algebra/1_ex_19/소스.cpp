#include <Windows.h> // XMVerifyCPUSupport�� �ʿ���
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <iostream>

using namespace std;
using namespace DirectX;
using namespace DirectX::PackedVector;

// XMVECTOR ��ü�� cout���� ����ϱ� ����
// "<<" �����ڸ� overloading �Ѵ�.

ostream& XM_CALLCONV operator<<(ostream& os, FXMVECTOR v)
{
	XMFLOAT4 dest;
	XMStoreFloat4(&dest, v);

	os << "(" << dest.x << ", " << dest.y << ", "
		<< dest.z << ", " << dest.w << ")";
	
	return os;
}

int main()
{
	// set flag�� ���Ӹ�. ��� ���� ����
	cout.setf(ios_base::boolalpha);

	// SSE2�� �����ϴ��� (Pentinum4, AMD K8 �̻�) Ȯ���Ѵ�.
	if (!XMVerifyCPUSupport())
	{
		cout << "DirectXMath�� �������� ����" << endl;
		return 0;
	}
	
	XMVECTOR p = XMVectorSet(2.0f, 2.0f, 1.0f, 0.0f);
	XMVECTOR q = XMVectorSet(2.0f, -0.5f, 0.5f, 1.0f);
	XMVECTOR u = XMVectorSet(1.0f, 2.0f, 4.0f, 8.0f);
	XMVECTOR v = XMVectorSet(-2.0f, 1.0f, -3.0f, 2.5f);
	XMVECTOR w = XMVectorSet(0.0f, XM_PIDIV4, XM_PIDIV2, XM_PI);

	cout << "XMVECTORAbs(v)					= " << XMVectorAbs(v) << endl;
	cout << "XMVECTORCos(w)					= " << XMVectorCos(w) << endl;	
	cout << "XMVECTORLog(u)					= " << XMVectorLog(u) << endl;
	cout << "XMVECTORExp(p)					= " << XMVectorExp(p) << endl;

	cout << "XMVECTORPow(u, p)				= " << XMVectorPow(u, p) << endl;
	cout << "XMVECTORSqrt(u)					= " << XMVectorSqrt(u) << endl;

	cout << "XMVectorSwizzle(u, 2, 2, 1, 3)			= " << XMVectorSwizzle(u, 2, 2, 1, 3) << endl;
	cout << "XMVectorSwizzle(u, 2, 2, 0, 3)			= " << XMVectorSwizzle(u, 2, 2, 0, 3) << endl;

	cout << "XMVectorMultiply(u, v)				= " << XMVectorMultiply(u, v) << endl;
	cout << "XMVectorSaturate(q)				= " << XMVectorSaturate(q) << endl;
	cout << "XMVectorMin(p, v)				= " << XMVectorMin(p, v) << endl;
	cout << "XMVectorMax(p, v)				= " << XMVectorMax(p, v) << endl;

}
