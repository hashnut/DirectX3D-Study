#include <Windows.h> // for XMVerifyCPUSupport
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <iostream>
#include <array>
#include <algorithm>
#include <vector>

#define N 4

using namespace std;
using namespace DirectX;
using namespace DirectX::PackedVector;


// Overload the "<<" operators so that we can use cout to
// output XMVECTOR and XMMATRIX objects.
ostream& XM_CALLCONV operator << (ostream& os, FXMVECTOR v)
{
	XMFLOAT4 dest;
	XMStoreFloat4(&dest, v);

	os << "(" << dest.x << ", " << dest.y << ", " << dest.z << ", " << dest.w << ")";

	return os;
}

ostream& XM_CALLCONV operator << (ostream& os, FXMMATRIX m)
{
	for (int i = 0; i < 4; ++i)
	{
		os << XMVectorGetX(m.r[i]) << "\t";
		os << XMVectorGetY(m.r[i]) << "\t";
		os << XMVectorGetZ(m.r[i]) << "\t";
		os << XMVectorGetW(m.r[i]);
		os << endl;
	}

	return os;
}

template <typename T, int m, int n>
void printTranspose(array<array<T, m>, n> arr)
{
	int m = arr.size();
	int n = arr[0].size();

	T** arrT = new T*[n];
	for (int i = 0; i < n; ++i)
		arrT[i] = new T[m];

	for (int i = 0; i < m; ++i)
		for (int j = 0; j < n; ++j)
			arrT[j][i] = arr[i][j];


	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			cout << arrT[i][j] << " ";
		}
		cout << endl;
	}

	for (int i = 0; i < n; ++i)
		delete[] arrT[i];

	delete[] arrT;


}

void getCofactor(int mat[N][N], int temp[N][N], int p,
	int q, int n)
{
	int i = 0, j = 0;

	// Looping for each element of the matrix
	for (int row = 0; row < n; row++)
	{
		for (int col = 0; col < n; col++)
		{
			//  Copying into temporary matrix only those
			//  element which are not in given row and
			//  column
			if (row != p && col != q)
			{
				temp[i][j++] = mat[row][col];

				// Row is filled, so increase row index and
				// reset col index
				if (j == n - 1)
				{
					j = 0;
					i++;
				}
			}
		}
	}
}

/* Recursive function for finding determinant of matrix.
   n is current dimension of mat[][]. */
int determinantOfMatrix(int mat[N][N], int n)
{
	int D = 0; // Initialize result

	//  Base case : if matrix contains single element
	if (n == 1)
		return mat[0][0];

	int temp[N][N]; // To store cofactors

	int sign = 1; // To store sign multiplier

	// Iterate for each element of first row
	for (int f = 0; f < n; f++)
	{
		// Getting Cofactor of mat[0][f]
		getCofactor(mat, temp, 0, f, n);
		D += sign * mat[0][f]
			* determinantOfMatrix(temp, n - 1);

		// terms are to be added with alternate sign
		sign = -sign;
	}

	return D;
}


void printInverse(int arr[N][N])
{
	int det;


	det = determinantOfMatrix(arr, N);

	cout << "DeterminantOfMatrix : " << det << endl;

	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j)
			arr[i][j] /= det;


	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}

}


int main() 
{


	//// Check support for SSE2 (Pentinum4, AMD K8, and above)
	//if (!XMVerifyCPUSupport())
	//{
	//	cout << "directx math not supported" << endl;
	//	return 0;
	//}

	//XMMATRIX A(1.0f, 0.0f, 0.0f, 0.0f,
	//	0.0f, 2.0f, 0.0f, 0.0f,
	//	0.0f, 0.0f, 4.0f, 0.0f,
	//	1.0f, 2.0f, 3.0f, 1.0f);

	//XMMATRIX B = XMMatrixIdentity();

	//XMMATRIX C = A * B;

	//XMMATRIX D = XMMatrixTranspose(A);

	//XMVECTOR det = XMMatrixDeterminant(A);
	//XMMATRIX E = XMMatrixInverse(&det, A);
	//
	//XMMATRIX F = A * E;

	//cout << "A = " << endl << A << endl;
	//cout << "B = " << endl << B << endl;
	//cout << "C = A*B = " << endl << C << endl;
	//cout << "D = transpose(A) = " << endl << D << endl;
	//cout << "det = determinant(A) = " << det << endl << endl;
	//cout << "E = inverse(A) = " << endl << E << endl;
	//cout << "F = A*E = " << endl << F << endl;


	array<array<int, 5>, 4> arr;

	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 5; ++j)
			arr[i][j] = i * j * j+ 1;

	//int** arr = new int*[5];

	//for (int i = 0; i < 4; ++i)
	//	arr[i] = new int[5];

	//for (int i = 0; i < 4; ++i)
	//	for (int j = 0; j < 5; ++j)
	//		arr[i][j] = i * j + 1;

	cout << "Original : " << endl;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}

	cout << "Transpose : " << endl;

	printTranspose(arr);

	//for (int i = 0; i < 4; ++i)
	//	delete[] arr[i];
	//delete[] arr;

	int arr2[N][N] = { { 1, 0, 2, -1 },
					  { 3, 0, 0, 5 },
					  { 2, 1, 4, -3 },
					  { 1, 0, 5, 0 } };

	printInverse(arr2);

	return 0;

}