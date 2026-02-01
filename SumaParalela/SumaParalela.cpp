// SumaParalela.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>
#include <omp.h>

#define N 1000				//Definision del numero de elementos en cada arreglo
#define SEGMENTOS 100		//Definicion del tamano de los segmentos en que se dividira el trabajo
#define MOSTRAR 20			//Definicion del nuemero de elementos que se mostraran

void imprimeArreglos(float* a, float* b, float* c, float* d);

using namespace std;

int main()
{
	cout << "Sumando arreglos en Paralelo!!\n";
	float a[N], b[N], c[N], cpus[N];		// Se declaran los arreglos que se utilizaran en la actividad
											// a primer operando de la suma, b segundo operando de la suma, c resultado de la suma
											// cpus es un arreglo adicional que contendra el # de CPU que ejecuta la suma
	srand(time(0));
	int i; 
	/*
	for (i = 0;i < N;i++)					// Opcion para llenar los arreglos manualmente
	{
		cout << "Iternacion " << i+1 << endl;
		cout << "Valor del operando A:" << endl;
		cin >> a[i];								 
		cout << "Valor del operando B:" << endl;
		cin >> b[i];
	}
	*/

	for (i = 0;i < N;i++) 
	{
		a[i] = (rand() % 100);				// Los arreglos a y b se inicializan con valores aleatorios. 
		b[i] = (rand() % 100);
	}

	int segmentos = SEGMENTOS;

	//Utilizando las directivas de OpenMP se genera un for paralelo que procesaran particiones de trabajo definidas en la variable segmentos.
	//Al no definir un limite se estarian utilizando todos los hilos disponibles en el sistema.  

	#pragma omp parallel for shared(a,b,c,cpus,segmentos) private(i) schedule (static,segmentos)
	for (i = 0; i < N; i++)
	{
		c[i] = a[i] + b[i];							//Suma de los arreglos A y B, guardando el resultado en C
		cpus[i] = omp_get_thread_num();				//Para claridad del ejercicio, se guarda el ID del hilo que ejecuta la suma
	}

	imprimeArreglos(a,b,c,cpus);					//Impresion de los arrelgos  
}

void imprimeArreglos(float* a, float* b, float* c, float* d )
{

	cout << endl << "Mostrando "<< MOSTRAR << " valores de los arreglos" << endl << endl;
	cout << "Array C = Array A + Array B" << endl << endl;

	cout << "Index\tArray A\tArray B\tArray C\tCPU" << endl;

	int x_rand;
	for (int x = 0; x < MOSTRAR; x++)
	{
		x_rand = (rand() % N);						//Para mejor visualizacion del ejercicio se agrega la opcion de desplegar los elementos de forma aleatoria
		//x_rand = x;								//Ayudando a ver como diferentes segmentos son ejecutados por diferentes hilos. 
		cout << x_rand << "\t" << a[x_rand] << "\t" << b[x_rand] << "\t" << c[x_rand] << "\t" << d[x_rand] << "\t" << endl;
	}
	cout << endl;
}
