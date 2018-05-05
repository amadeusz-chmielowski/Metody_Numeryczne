#include "Equation.h"
#include <time.h>
#define N 905

using namespace std;

float time(Equation &eq, void(Equation::*initF)(), int(Equation::*methodF)()) {
	(eq.*initF)();
	int start = clock();
	(eq.*methodF)();
	return (float)(clock() - start) / CLOCKS_PER_SEC;
}
int main() {
	Equation E(N);
////////////////////////////////////////////////////////////
	///cout << "Zadanie A+B" << endl;
////////////////////////////////////////////////////////////
	//E.initA();
	//cout <<"Jacobi: "<<  E.metodaJacobiego() << endl;
	//E.initA();
	//cout << "Gauss-Seidl: " << E.metodaGaussaSeidla() << endl;

////////////////////////////////////////////////////////////
	///cout << "Zadanie C" << endl;
////////////////////////////////////////////////////////////
	/*E.initC();
	cout << E.metodaJacobiego();		/// NIE ZBIEGAJA
	E.initC();							///		SIE
	cout << E.metodaGaussaSeidla();*/

////////////////////////////////////////////////////////////
	///cout << "Zadanie D" << endl;
////////////////////////////////////////////////////////////
	E.initC();
	cout << "Norma z residuum w przpadku LU wynosi: " << E.metodaLU() << endl;

////////////////////////////////////////////////////////////
	///cout << "Zadanie E" << endl;
////////////////////////////////////////////////////////////
	//int Ns[] = { 100, 500, 1000, 2000, 3000 };
	//int nSize = 5;
	//cout << "Metoda Jacobiego" << endl;
	//for (int i = 0; i < nSize; i++) {
	//	Equation X(Ns[i]);
	//	cout << "N = " << Ns[i] << " czas: " << time(X, &Equation::initA, &Equation::metodaJacobiego) << "s" << endl;
	//}
	//cout << "\nMetoda Gaussa-Seidla" << endl;
	//for (int i = 0; i < nSize; i++) {
	//	Equation X(Ns[i]);
	//	cout << "N = " << Ns[i] << " czas: " << time(X, &Equation::initA, &Equation::metodaGaussaSeidla) << "s" << endl;
	//}
	//cout << "\nMetoda LU" << endl;
	//for (int i = 0; i < nSize; i++) {
	//	Equation X(Ns[i]);
	//	cout << "N = " << Ns[i] << "\ czas: " << time(X, &Equation::initA, &Equation::metodaLU) << "s" << endl;
	//}
	system("pause");
}