#include <windows.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <iostream>

using namespace std;
using namespace DirectX;
using namespace DirectX::PackedVector;

// XMVECTOR 객체를 벡터 (x, y, z, w)로 출력한다.
ostream& XM_CALLCONV operator<<(ostream& os, FXMVECTOR v)
{
	XMFLOAT4 dest;
	XMStoreFloat4(&dest, v);

	os << "(" << dest.x << ", " << dest.y << ", " << dest.z << ", " << dest.w << ")";
	return os;
}

// XMMATRIX 객체를 4X4행렬로 출력한다.
ostream& XM_CALLCONV operator<<(ostream& os, FXMMATRIX m)
{
	for (int i = 0; i < 4; ++i)
	{
		os << XMVectorGetX(m.r[i]) << "\t"; // m.r[i] : i번째 행벡터
		os << XMVectorGetY(m.r[i]) << "\t";
		os << XMVectorGetZ(m.r[i]) << "\t";
		os << XMVectorGetW(m.r[i]) << endl;
	}
	return os;
}

int main()
{
	cout.setf(ios_base::boolalpha);

	// SSE2를 지원하는지 확인한다.
	if (!XMVerifyCPUSupport()) {
		cout << "DirectXMath를 지원하지 않음" << endl;
		return 0;
	}
	
	// 벡터 초기화
	XMVECTOR init1 = XMVectorZero();
	XMVECTOR init2 = XMVectorSplatOne();
	XMVECTOR init3 = XMVectorSet(1.0f, 2.0f, 0.0f, 0.0f);
	XMVECTOR init4 = XMVectorReplicate(-2.0f);
	XMVECTOR init5 = XMVectorSplatZ(init3);
	XMVECTOR init6 = XMVectorSet(0.0f, XM_PIDIV4, XM_PIDIV2, XM_PI);
	XMVECTOR u = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR v = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	// 벡터 연산
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
	// 속도를 위해 정확성을 희생할수 잇는 상황에 사용한다.
	XMVECTOR estL = XMVector3LengthEst(u);
	XMVECTOR estN = XMVector3NormalizeEst(v);

	// 부동소수점 오차의 누적
	XMVECTOR f1 = XMVectorSet(1.0f, 1.0f, 1.0f, 0.0f);
	XMVECTOR f2 = XMVector3Normalize(f1);
	float LU = XMVectorGetX(XMVector3Length(f2)); // 길이가 1.0f에 근사된다.
	cout << (LU == 1.0f) << endl; // false
	cout << powf(LU, 1.0e6f) << endl; // (1.0f)^(10^6) = 0.942137 != 1.0f

	// 부동소수점의 상등
	auto Equals = [](float lhs, float rhs) {
		static const float Epsilon = 1.0e-5f;
		return fabs(lhs - rhs) < Epsilon ? true : false;
	};
	XMVECTOR epsilonVec = XMVectorReplicate(1.0e-5f);
	bool equal = XMVector3NearEqual(u, XMVectorSet(1.0f, 1.0f, 1.0f, 0.0f), epsilonVec);
	cout << equal << endl;

	// 행렬 초기화
	XMMATRIX A(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 2.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 4.0f, 0.0f,
		1.0f, 2.0f, 3.0f, 1.0f);
	XMMATRIX B = XMMatrixIdentity();

	// 행렬 계산
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
참고 사항

1. 코드에서 벡터를 효율적으로 다루기 위해 SIMD 연산들을 사용하는 XMVECTOR, XMMATRIX 형식을 이용한다.
2. 클래스 자료 멤버는 XMFLOATn, XMFLOATnXn 클래스를 사용한다. 계산처리할 때만 XMVECTOR, XMMATRIX로 변환하고 다시 XMFLOAT~으로 변환한다.
3. Do not use initializer lists directly with XMVECTOR (that is, XMVECTOR v = { 1.0f, 2.0f, 3.0f, 4.0f }). Use XMVECTORF32.
4. XMVECTOR 인스턴스를 인수로써 함수를 호출할 때, 인수 값을 스택이 아닌 SSE/SSE2 레지스터를 통해서 함수에 전달한다.
   그런데 SSE/SSE2 레지스터에 전달할 수 있는 인수의 개수는 플랫폼과 컴파일러에 따라 다르다. (나머지 인수들은 스택을 사용한다.)
   이러한 의존성을 없애기 위해서,
   순서대로 [F 3개, G 1개, H 2개, C +개] 매개변수 형식을 사용한다.
   XMMATRIX 인스턴스도 같은 규칙을 적용한다. XMMATRIX 매개변수 하나가 XMVECTOR 매개변수 4개에 해당한다.
   순서대로 [F 1개, C +개] 매개변수 형식을 사용한다.
   또한, 함수 이름 앞에 XM_CALLCONV 호출 규약 지시자를 붙여야한다.

*/