#include <windows.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <iostream>

using namespace std;
using namespace DirectX;
using namespace DirectX::PackedVector;

// XMVECTOR ��ü�� ���� (x, y, z, w)�� ����Ѵ�.
ostream& XM_CALLCONV operator<<(ostream& os, FXMVECTOR v)
{
	XMFLOAT4 dest;
	XMStoreFloat4(&dest, v);

	os << "(" << dest.x << ", " << dest.y << ", " << dest.z << ", " << dest.w << ")";
	return os;
}

// XMMATRIX ��ü�� 4X4��ķ� ����Ѵ�.
ostream& XM_CALLCONV operator<<(ostream& os, FXMMATRIX m)
{
	for (int i = 0; i < 4; ++i)
	{
		os << XMVectorGetX(m.r[i]) << "\t"; // m.r[i] : i��° �຤��
		os << XMVectorGetY(m.r[i]) << "\t";
		os << XMVectorGetZ(m.r[i]) << "\t";
		os << XMVectorGetW(m.r[i]) << endl;
	}
	return os;
}

int main()
{
	cout.setf(ios_base::boolalpha);

	// SSE2�� �����ϴ��� Ȯ���Ѵ�.
	if (!XMVerifyCPUSupport()) {
		cout << "DirectXMath�� �������� ����" << endl;
		return 0;
	}
	
	// ���� �ʱ�ȭ
	XMVECTOR init1 = XMVectorZero();
	XMVECTOR init2 = XMVectorSplatOne();
	XMVECTOR init3 = XMVectorSet(1.0f, 2.0f, 0.0f, 0.0f);
	XMVECTOR init4 = XMVectorReplicate(-2.0f);
	XMVECTOR init5 = XMVectorSplatZ(init3);
	XMVECTOR init6 = XMVectorSet(0.0f, XM_PIDIV4, XM_PIDIV2, XM_PI);
	XMVECTOR u = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR v = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	// ���� ����
	XMVECTOR a1 = u + v;
	XMVECTOR a2 = u - v;
	XMVECTOR a3 = 10.0f * u;
	XMVECTOR a4 = XMVector3Length(u);
	XMVECTOR a5 = XMVector3Normalize(u);
	XMVECTOR a6 = XMVector3Dot(u, v);
	XMVECTOR a7 = XMVector3Cross(u, v);
	XMVECTOR a8 = XMVectorAbs(init4);
	XMVECTOR a9 = XMVectorCos(init5);
	XMVECTOR a10 = XMVectorLog(init5);
	XMVECTOR a11 = XMVectorExp(init5);



	// Calculate projectional and perpendicular vector
	XMVECTOR w = XMVector3Normalize(XMVectorSet(1.0f, 2.0f, 0.0f, 0.0f));
	XMVECTOR proj = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR projW, perpW;
	XMVector3ComponentsFromNormal(&projW, &perpW, w, proj);
	XMVECTOR angleVec = XMVector3AngleBetweenVectors(projW, perpW);
	float angleRadians = XMVectorGetX(angleVec);
	float angleDegrees = XMConvertToDegrees(angleRadians);
	cout << w << endl;
	cout << proj << endl;
	cout << projW << endl;
	cout << perpW << endl;
	cout << (XMVector3Equal(projW + perpW, w) != 0) << endl;
	cout << angleDegrees << endl;

	// estimation functions
	// �ӵ��� ���� ��Ȯ���� ����Ҽ� �մ� ��Ȳ�� ����Ѵ�.
	XMVECTOR estL = XMVector3LengthEst(u);
	XMVECTOR estN = XMVector3NormalizeEst(v);

	// �ε��Ҽ��� ������ ����
	XMVECTOR f1 = XMVectorSet(1.0f, 1.0f, 1.0f, 0.0f);
	XMVECTOR f2 = XMVector3Normalize(f1);
	float LU = XMVectorGetX(XMVector3Length(f2)); // ���̰� 1.0f�� �ٻ�ȴ�.
	cout << (LU == 1.0f) << endl; // false
	cout << powf(LU, 1.0e6f) << endl; // (1.0f)^(10^6) = 0.942137 != 1.0f

	// �ε��Ҽ����� ���
	auto Equals = [](float lhs, float rhs) {
		static const float Epsilon = 1.0e-5f;
		return fabs(lhs - rhs) < Epsilon ? true : false;
	};
	XMVECTOR epsilonVec = XMVectorReplicate(1.0e-5f);
	bool equal = XMVector3NearEqual(u, XMVectorSet(1.0f, 1.0f, 1.0f, 0.0f), epsilonVec);
	cout << equal << endl;

	// ��� �ʱ�ȭ
	XMMATRIX A(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 2.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 4.0f, 0.0f,
		1.0f, 2.0f, 3.0f, 1.0f);
	XMMATRIX B = XMMatrixIdentity();

	// ��� ���
	XMMATRIX C = A * B;
	XMMATRIX D = XMMatrixTranspose(A);
	XMVECTOR det = XMMatrixDeterminant(A);
	XMMATRIX E = XMMatrixInverse(&det, A);
	XMMATRIX F = A * E;

	cout << "A= " << endl << A << endl;
	cout << "B= " << endl << B << endl;
	cout << "C=A*B=" << endl << C << endl;
	cout << "D=transpose(A)= " << endl << D << endl;
	cout << "E=inverse(A)= " << endl << E << endl;
	cout << "F=A*E=I= " << endl << F << endl;

	return 0;
}

/*
���� ����

1. �ڵ忡�� ���͸� ȿ�������� �ٷ�� ���� SIMD ������� ����ϴ� XMVECTOR, XMMATRIX ������ �̿��Ѵ�.
2. Ŭ���� �ڷ� ����� XMFLOATn, XMFLOATnXn Ŭ������ ����Ѵ�. ���ó���� ���� XMVECTOR, XMMATRIX�� ��ȯ�ϰ� �ٽ� XMFLOAT~���� ��ȯ�Ѵ�.
3. Do not use initializer lists directly with XMVECTOR (that is, XMVECTOR v = { 1.0f, 2.0f, 3.0f, 4.0f }). Use XMVECTORF32.
4. XMVECTOR �ν��Ͻ��� �μ��ν� �Լ��� ȣ���� ��, �μ� ���� ������ �ƴ� SSE/SSE2 �������͸� ���ؼ� �Լ��� �����Ѵ�.
   �׷��� SSE/SSE2 �������Ϳ� ������ �� �ִ� �μ��� ������ �÷����� �����Ϸ��� ���� �ٸ���. (������ �μ����� ������ ����Ѵ�.)
   �̷��� �������� ���ֱ� ���ؼ�,
   ������� [F 3��, G 1��, H 2��, C +��] �Ű����� ������ ����Ѵ�.
   XMMATRIX �ν��Ͻ��� ���� ��Ģ�� �����Ѵ�. XMMATRIX �Ű����� �ϳ��� XMVECTOR �Ű����� 4���� �ش��Ѵ�.
   ������� [F 1��, C +��] �Ű����� ������ ����Ѵ�.
   ����, �Լ� �̸� �տ� XM_CALLCONV ȣ�� �Ծ� �����ڸ� �ٿ����Ѵ�.

*/