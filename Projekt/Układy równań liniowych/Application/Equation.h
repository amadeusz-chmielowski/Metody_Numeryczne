#pragma once
#include "Matrix.h"
#include <iostream>
#define f 6
#define a1A 5+1
#define a1C 3
#define a2 -1
#define a3 -1
#define e 1e-9

class Equation {
private:
	matrix A;
	matrix x;
	matrix b;
	int N;
public:

	double metodaJacobiego() {
		matrix xtemp(x);
		for (int t = 1; ; t++) {
			for (int i = 0; i < N; i++) {
				double val = b[i][0];
				for (int k = 0; k < N; k++) {
					if (k != i)
						val -= A[i][k] * x[k][0];
				}
				val /= A[i][i];
				xtemp[i][0] = val;
			}
			x = xtemp;

			if (matrix::norm(A * x - b) <= e)
				return t;
		}
	}
	double metodaGaussaSeidla() {
		for (int t = 1; ; t++) {
			for (int i = 0; i < N; i++) {
				double val = b[i][0];
				for (int k = 0; k < N; k++) {
					if (k != i)
						val -= A[i][k] * x[k][0];
				}
				val /= A[i][i];
				x[i][0] = val;
			}
			if (matrix::norm(A * x - b) <= e)
				return t;
		}
	}
	double metodaLU() {
		matrix L(N, N);
		matrix U(N, N);
		//Podzia³
		for (int i = 0; i < N; i++)
			L[i][i] = 1.0;

		for (int j = 0; j < N; j++) {
			for (int i = 0; i <= j; i++) {
				U[i][j] += A[i][j];
				for (int k = 0; k <= i - 1; k++)
					U[i][j] -= L[i][k] * U[k][j];

			}

			for (int i = j+1; i < N; i++) {
				for (int k = 0; k <= j - 1; k++)
					L[i][j] -= L[i][k] * U[k][j];

				L[i][j] += A[i][j];
				L[i][j] /= U[j][j];
			}
		}
		matrix y(N, 1);
		//Podstawienie w przód dla Ly = b
		for (int i = 0; i < N; i++) {
			double val = b[i][0];
			for (int j = 0; j < i; j++) {
				if (j != i) val -= L[i][j] * y[j][0];
			}

			y[i][0] = val / L[i][i];
		}

		//Podstawienie wstecz dla Ux = y
		for (int i = N - 1; i >= 0; i--) {
			double val = y[i][0];
			for (int j = i; j < N; j++) {
				if (j != i) val -= U[i][j] * x[j][0];
			}

			x[i][0] = val / U[i][i];
		}

		return matrix::norm(A * x - b);
	}

	void initA() {
		A.init(a1A, a2, a3);

		for (int i = 0; i < N; i++) {
			x[i][0] = 1.0;

			double elem = sin(i  * (f + 1));
			b[i][0] = elem;
		}
	}
	void initC() {
		A.init(a1C, a2, a3);

		for (int i = 0; i < N; i++) {
			x[i][0] = 1.0;

			double elem = sin(i  * (f + 1));
			b[i][0] = elem;
		}
	}

	Equation(int _N) {
		N = _N;
		A = matrix(N, N);
		x = matrix(N, 1);
		b = matrix(N, 1);
	}
};