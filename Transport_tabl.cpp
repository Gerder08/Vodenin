#include "stdafx.h"
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <conio.h>
#include <algorithm>

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
		cout<<B[i]<<" ";
	}
}
void NWcornerMethod(int m, int n, double *A, double *B, double **D, int a, int b){
	//cout << "NWcornerMethod";
	int aNW = a; int bNW = b;
	int i = 0, j = 0;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			int buf = min(A[i], B[j]);
			//cout <<A[i]<<" "<<B[j]<<" "<< buf;
			D[i][j] = buf;
			A[i] -= buf;
			B[j] -= buf;
			cout << D[i][j];
		}
		cout << endl;
	}
	int df = min(a, b);
	//while (df != 0) {

	//}
	/*cout << "Sklad ";
	for (int i = 0; i < n; i++) {
		cout << "B[" << i << "] ";
	}
	cout << "Zapas" << endl;
	for (int i = 0; i < m; i++) {
		cout << "D[" << i << "]";
		for (int j = 0; j < n; j++) {
			printf("%lf %s", D[i][j], " ");
		}
		cout << A[i] << endl;
	}*/
}

int main()
{
	int choice,m, n,f1=0,f2=0, fl=0;
	cout << "PRI-o-16 German Dergunov" << endl;
	cout << "Transportnya zadacha_metod potencialov" << endl;
	cout << "Kol-vo Postavschikov m = "; cin >> m;cout << endl;
	cout << "Kol-vo Potrebiteley n = "; cin >> n;cout << endl;
	int i, j;
    double a=0;
    double b=0;
	double *A = new double[m];
    //double **C;
	double *B = new double[n];
	double **C = new double*[m]; // ������ ��������� ���������
	for (int i = 0; i<n; i++)
	{
		C[i] = new double[n];
	}
	double **D = new double*[m]; // ������� �������� � �� ������
	for (int i = 0; i<n; i++)
	{
		D[i] = new double[n];
	}
	
    //cout<<"n= ";cin >> n;
    //create_matrix(n);
    //create_vect(n);


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
			<< "9. Vyhod" << endl;
		printf("=============================================================================================");cout << endl;
		//cin >> sw;
		switch (choice = _getch()) {

			case '1': {
				a = 0;
				cout << "Postavschiki" << endl;
				//double *A = new double[m];
				set_Post(m, A);
				for (i = 0; i < n; i++) {
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
					//double **C = new double*[m];
					/*for (int i = 0; i<n; i++)
					{
						C[i] = new double[n];
					}*/
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
				system("pause");
				break;
			}
			case '5':{
				cout <<"NWcornerMethod"<<endl;
				NWcornerMethod(m, n, A, B, D, a, b);
				system("pause");
				break;

			}/*
			case 6:
			{
				cout <<"Detremenant matr"<<endl;
				matr.det();
				system("pause");
				break;
			}
			case 7:
			{
				cout<<"slae"<<endl;
				matr.get_slae();
				system("pause");

				break;

			}
			case 8:
			{
				cout<<"obr"<<endl;
				matr.get_obr();
				system("pause");
				break;

			}
			case 9:
			{
				cout<<"Obras"<<endl;
				matr.get_obras();
				system("pause");
				break;

			}*/
			case '9': {
				delete []B;
				
					delete A;
						//delete []A;
				return 0;

			}
		}
	}
	return 0;
}
