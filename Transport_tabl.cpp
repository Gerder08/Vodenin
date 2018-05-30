#include "stdafx.h"
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <conio.h>
#include <algorithm>
#include <cstdlib>
#include "Transport_tabl.h"

//#include "transport.h"
//#include "vect.cpp"
//#include <vector>

using namespace std;

//transport tran;
void set_Post(int m, double *A) {
	for (int i = 0; i < m; i++) {
		printf("A[ %d %s", i, "] = ");cin >> A[i];
	}
}

void set_Potr(int n, double *B) {
	for (int i = 0; i < n; i++) {
		printf("B[ %d %s", i, "] = ");cin >> B[i];
	}
}

void set_trtabl(int n, int m, double **C) {
	
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			printf("A[ %d %s %d %s", i, "][", j, "] = ");cin>> C[i][j];
			//cout << C[i][j] << endl;
		}
	}
}
void print_trtabl(int n, int m, double *A, double *B, double **C) {
	cout << "Sklad ";
	for (int i = 0; i < n; i++) {
		cout << "B[" << i << "] ";
	}
	cout << "Zapas" << endl;
	for (int i = 0; i < m; i++) {
		cout << "A[" << i << "]";
		for (int j = 0; j < n; j++) {
			printf("%lf %s", C[i][j], " ");
		}
		cout << A[i] << endl;
	}
	cout << "Nado ";
	for (int i = 0; i < n; i++) {
		cout<<B[i]<<" test";
	}
}
int NWcornerMethod(int m, int n, double *A, double *B, double **C, double **D, int a, int b){
	//cout << "NWcornerMethod";
	int i = 0, j = 0;
	double S = 0;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			int buf = min(A[i], B[j]);
			//cout <<A[i]<<" "<<B[j]<<" "<< buf;
			D[i][j] = buf;
			A[i] -= buf;
			B[j] -= buf;
			S += C[i][j] * D[i][j];
			//cout << D[i][j]<<" ";
		}
		cout << endl;
	}
	
	return S;
}
bool OptResh(int m, int n, double **DeltaC, double **Ba, double **C, double *U, double *V) {
	bool fl = true;
	for (int j = 0; j < n; j++) {
		for (int i = 0; i < m; i++) {
			if (Ba[i][j] != 1) {
				DeltaC[i][j] = C[i][j] - (U[i] + V[j]);  //
				if (DeltaC[i][j] <= 0) {
					return false;
				}
			}
		}
	}
	return true;
}
int PotencialMethod(int m, int n, double *A, double *B, double **C, double **D, double **Ba, double **Z, double *U, double *V, double **DeltaC) {
	int i = 0, j = 0, s = 0;
	
	int kBa = 0;  // количество базисных клеток
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (D[i][j] != 0) {
				Ba[i][j] = 1; // определяем базисные клетки
				cout << Ba[i][j] << " ";
				kBa++;
			}
		}
		cout << endl;
	}
	if (kBa < m + n - 1) {
		cout << "plan vyrojden";
		system("pause");
		return -1;
	}
	
	double *fU = new double[m];  // флаги векторов
	double *fV = new double[n];
	for (int i = 0; i < m; i++) {
		fU[i] = 0;  // устанавливаем значения по умолчанию
	}
	for (int j = 0; j < n; j++) {
		fV[j] = 0;  // устанавливаем значения по умолчанию
	}
	int pcount = 0; // счетчик помеченных потенциалов
	V[0] = 0; j = 0; fV[j] = 1; pcount = 1;
	//while (pcount < n + m) {
	for (int k = 0;k < max(n, m);k++) {  // чтобы наверняка
		for (int i = 0; i < m; i++) {
			if (Ba[i][j] == 1 && fV[j] == 1 && fU[i] != 1) {
				U[i] = C[i][j] - V[j];  // расставляем потенциалы
				fU[i] = 1;
				pcount++;
			}
			for (int j = 0; j < n; j++) {
				if (Ba[i][j] == 1 && fU[i] == 1 && fV[j] != 1) {
					V[j] = C[i][j] - U[i];  // расставляем потенциалы
					fV[j] = 1;
					pcount++;
				}
			}
		}
		for (int j = 0; j < n; j++) {
			if (Ba[i][j] == 1 && fU[i] == 1 && fV[j] != 1) {
				V[j] = C[i][j] - U[i];  // расставляем потенциалы
				fV[j] = 1;
				pcount++;
			}
			for (int i = 0; i < m; i++) {
				if (Ba[i][j] == 1 && fV[j] == 1 && fU[i] != 1) {
					U[i] = C[i][j] - V[j];  // расставляем потенциалы
					fU[i] = 1;
					pcount++;
				}
			}
		}
		/*cout << "k =" << k << endl;  // отладочная печать
		cout << "pc = " << pcount;
		for (int i = 0; i < m; i++) {
			cout << fU[i] << " ";
		}
		cout << endl;
		for (int j = 0; j < n; j++) {
			cout << fV[i] << " ";
		}
		cout << endl;*/
		//}
	}
	

	//for (int i = 0; i < m; i++) {
	//	cout << U[i] << " ";
	//}
	//cout << endl;
	//for (int j = 0; j < n; j++) {
	//	cout<<V[j]<< " ";  // распечатываем потенциалы
	//}
	cout << endl;
	while (OptResh(m, n, DeltaC, Ba, C, U, V) != true) { // пока не оптимальное решение
		int mini = 0;
		int minj = 0;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				if (DeltaC[i][j] < DeltaC[mini][minj]) {
					mini = i;// выбираем свободную клетку с наименьшим отрицательным значением дельтаЦ (наибольшим по абсолютной величине)
					minj = j;
				}
			}
		}
		for (i = 0;i < m;i++) {
			if (Ba[i][minj] == 1) {
				for (j = 0;j < n; j++) {
					if (Ba[i][j] == 1) {
						for (int i1 = 0; i1 < n; i1++) {
							if (Ba[mini][j] == 1) { // цикл найден
								double lymbd = min(D[mini][j], D[i][minj]);
								D[mini][j] -= lymbd;
								D[i][minj] -= lymbd;
								D[i][j] += lymbd;
								D[mini][minj] = lymbd;
							}
						}
					}
				}
			}
		}
		for (i = 0;i < m;i++) {
			for (j = 0;j < n;j++) {
				Ba[i][j] = -1;
				if (C[i][j] != 0) {
					Ba[i][j] = 1;
				}
			}
		}
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			s += C[i][j] * D[i][j];
		}
	}
	return s;
}
void ex1(int m, int n, double *A, double *B, double **C, double **D, double **Ba, double **Z, double *U, double *V, double **DeltaC, double a, double b) {
	double S, s;
	for (int j = 0; j < n; j++) {
		B[j] = rand() % 100;
	}
	for (int i = 0;i < m;i++) {
		A[i] = rand() % 100;

		for (int j = 0; j < n; j++) {
			C[i][j] = rand() % 10;
		}
	}
	print_trtabl(n, m, A, B, C);
	for (int i = 0; i < m; i++) {
		 a = a+ A[i];
	}
	for (int j = 0; j < n; j++) {
		 b = b+B[j];
	}
	S = NWcornerMethod(m, n, A, B, C, D, a, b);
	s = PotencialMethod(m, n, A, B, C, D, Ba, Z, U, V, DeltaC);
	//return S, s;
}
void ex2(int m, int n, double *A, double *B, double **C, double **D, double **Ba, double **Z, double *U, double *V, double **DeltaC, double a, double b) {
	double S, s;
	
	for (int j = 0; j < n; j++) {
		B[j] =2;
	}
	
	print_trtabl(n, m, A, B, C);
	
	for (int j = 0; j < n; j++) {
		b = b + B[j];
	}
	a = b;
	for (int i = 0;i < m;i++) {
		A[i] = b/m;

		for (int j = 0; j < n; j++) {
			C[i][j] = rand() % 10;
		}
	}
	S = NWcornerMethod(m, n, A, B, C, D, a, b);
	s = PotencialMethod(m, n, A, B, C, D, Ba, Z, U, V, DeltaC);
	//return S, s;
}
int main()
{
	int choice, m, n;
	int f1 = 0, f2 = 0, fl = 0, fll = 0; // флаги
	cout << "PRI-o-16 German Dergunov" << endl;
	cout << "Transportnya zadacha_metod potencialov" << endl;
	cout << "Kol-vo Postavschikov m = "; cin >> m;cout << endl;
	cout << "Kol-vo Potrebiteley n = "; cin >> n;cout << endl;
	ofstream f("data.txt");
	int i, j;
    double a=0; //  сумма поставок в ед товара
    double b=0; //  сумма потребления в ед товара
	double S = 0; // общая стоимость доставки для NW метода
	double s = 0; // общая стоимость доставки для метода потенциалов
	double *A = new double[m];
    //double **C;
	double *B = new double[n];
	double **C = new double*[m]; // марица стоимости перевозок
	for (int i = 0; i<m; i++)
	{
		C[i] = new double[n];
	}
	double **D = new double*[m]; // матрица доставок в ед товара
	for (int i = 0; i<m; i++)
	{
		D[i] = new double[n];
	}
	double *U = new double[m];
	double *V = new double[n];
	double **Ba = new double*[m]; // марица базисных клеток
	for (int i = 0; i<m; i++)
	{
		Ba[i] = new double[n];
	}
	double **Z = new double*[m]; // марица знаков
	for (int i = 0; i<m; i++)
	{
		Z[i] = new double[n];
	}
	//for (int i = 0; i < m; i++) {
	//	for (int j = 0; j < n; j++) {
	//		Z[i][j] = 1; // устанавлиаем знаки на "+" по умолчанию
	//	}
	//}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			Ba[i][j] = -1; // базисных клеток пока нет
		}
	}
	double **DeltaC = new double*[m]; // значения в верхнем левом уголке
	for (int i = 0; i<m; i++)
	{
		DeltaC[i] = new double[n];
	}
	//for (int i = 0; i < m; i++) {
	//	U[i] = 0;  // устанавливаем значения по умолчанию
	//}
	//for (int j = 0; j < n; j++) {
	//	V[j] = 0;  // устанавливаем значения по умолчанию
	//}
    


	while (1)
	{
		system("CLS");
		cout << "PRI-o-16 German Dergunov" << endl;
		cout << "Transportnya zadacha_metod potencialov" << endl;
		cout << "Vybirite punkt" << endl;
		cout
			<< "1. Postavschiki" << endl
			<< "2. Potrebiteli" << endl
			<< "3. Transportnaya tablica" << endl
			<< "4. Print transport tabl" << endl
			<< "5. NWcornerMethod" << endl
			<< "6. PotencialMethod" << endl
			<< "7. all random Experiment" << endl
			<< "8. partly random Experiment(good)" << endl
			<< "9. Vyhod" << endl;
		printf("=============================================================================================");cout << endl;
		//cin >> sw;
		switch (choice = _getch()) {

			case '1': {
				a = 0;
				cout << "Postavschiki" << endl;
				//double *A = new double[m];
				set_Post(m, A);
				for (i = 0; i < m; i++) {
					a += A[i];
				}
				f1 = 1;
				_getch();
				break;
			}
			case '2': {
				b = 0;
				cout << "Potrebiteli" << endl;
				//double *B = new double[n];
				set_Potr(n, B);
				for (i = 0; i < n; i++) {
					b += B[i];
				}
				_getch();
				f2 = 1;
				break;
			}
			case '3': {
				if (f1 == 0 || f2 == 0) {
					cout << "Vvedite Potrebiteley i Postaschikov p. 1, 2";
				}
				else {
					cout << "Transportnaya tablica" << endl;
					set_trtabl(n, m, C);
					fl = 1;
				}
				system("pause");
				break;
			}
			case '4': {
				if (fl == 0) {
					cout << "Zapolnite trasport tabl p. 3";
				}
				else {
					cout << "Transport tabl" << endl;
					print_trtabl(n, m, A, B, C);
				}
				fll = 1;
				system("pause");
				break;
			}
			case '5':{
				if (fll == 0) {
					cout << "Zapolnite predyduschie punkty p.1,2,3,4";
				}
				else{
					cout <<"NWcornerMethod"<<endl;
					S = NWcornerMethod(m, n, A, B, C, D, a, b);
					cout << "Obschaya stoimost dostavki S = " << S<<endl;
					cout << "Izlishek tovara = " << a - b<<endl;
				}
				system("pause");
				break;

			}
			case '6':{
				if (fll == 0) {
					cout << "Zapolnite predyduschie punkty p.1,2,3,4";
				}
				else {
					cout <<"PotencialMethod"<<endl;
					s = PotencialMethod(m, n, A, B, C, D, Ba, Z, U, V, DeltaC);
				}
				cout << "Obschaya stoimost dostavki S = " << s << endl;
				cout << "Izlishek tovara = " << a - b << endl;
				system("pause");
				break;
			}
			case '7': {
					cout << "Random experiment" << endl;
					ex1(m, n, A, B, C, D, Ba, Z, U, V, DeltaC, a, b);
					//S = NWcornerMethod(m, n, A, B, C, D, a, b);
					//s = PotencialMethod(m, n, A, B, C, D, Ba, Z, U, V, DeltaC);
				cout << "Obschaya stoimost dostavki S NW= " << S << endl;
				cout << "Obschaya stoimost dostavki s PM= " << s << endl;
				cout << "Izlishek tovara = " << a - b << endl;
				system("pause");
				break;
			}
			case '8': {
				cout << "Partly rndom experiment" << endl;
				ex1(m, n, A, B, C, D, Ba, Z, U, V, DeltaC, a, b);
				//S = NWcornerMethod(m, n, A, B, C, D, a, b);
				//s = PotencialMethod(m, n, A, B, C, D, Ba, Z, U, V, DeltaC);
				cout << "Obschaya stoimost dostavki S NW= " << S << endl;
				cout << "Obschaya stoimost dostavki s PM= " << s << endl;
				cout << "Izlishek tovara = " << a - b << endl;
				system("pause");
				break;
			}
			case '9': {
				f << "PRI-o-16 German Dergunov" << endl;
				f << "Transportnya zadacha_metod potencialov" << endl;
				f << "Sklad ";
				for (int i = 0; i < n; i++) {
					f << "B[" << i << "] ";
				}
				f << "Zapas" << endl;
				for (int i = 0; i < m; i++) {
					f << "A[" << i << "]";
					for (int j = 0; j < n; j++) {
						f << C[i][j]<< " ";
					}
					f << A[i] << endl;
				}
				f << "Nado ";
				for (int i = 0; i < n; i++) {
					f << B[i] << " ";
				}
				f<<endl;
				f << "D "<<endl;;
				for (i = 0;i < m;i++) {
					for (j = 0;j < n;j++) {
						f << D[i][j]<<" ";
					}
					f << endl;
				}
				f << "NWcornerMethod" << endl;
				f << "Obschaya stoimost dostavki S = " << S << endl;
				f << "Izlishek tovara = " << a - b << endl;
				f << "PotencialMethod" << endl;
				f << "Obschaya stoimost dostavki s = " << s << endl;
				f << "Izlishek tovara = " << a - b << endl;
				f.close();
				delete []B;
				
					delete []A;
					delete[]D;
					
					/*delete[]C;
					delete[]Z;
					delete[]Ba;*/
					/*delete[]U;
					delete[]V;
					delete[]DeltaC;
					delete[]Z;*/
					
				return 0;

			}
		}
	}
	return 0;
}
