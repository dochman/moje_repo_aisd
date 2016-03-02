#include <iostream>
#include <algorithm>
#include <time.h>

using namespace std;


void wypelnienie_tablicy(int *t, int n)
{
	for (int i = 0; i < n; i++)
	{
		t[i] = i++;
	}
}

int sortowanie_babelkowe(int *t, int n)
{
	int rez,czas;
	clock_t start, stop;

	start = clock();

	for (int i = 0; i < n; i++)
		for (int j = 1; j < n; j++)
		{
			if (t[j - 1] > t[j])
			{
				rez = t[j - 1];
				t[j - 1] = t[j];
				t[j] = rez;
			}
		}

	stop = clock();
	czas = stop - start;
	return czas;
}

int main()
{
	//tablica dynamiczna
	int n=8000; 
	int* t = new int[n];  
	float suma = 0;

	for (int i = 1; i <= 5; i++)
	{
		wypelnienie_tablicy(t, n);
		random_shuffle(t, t + n);
		//cout << "czas w sekundach " <<i<<" pomiar: "<< ((float)sortowanie_babelkowe(t, n)) / CLOCKS_PER_SEC << endl;
		suma = suma + ((float)sortowanie_babelkowe(t, n)) / CLOCKS_PER_SEC;
	}
	cout << "sredni czas-babelkowe: " << suma / 5<<endl;

	/*const int n =1000;
	int t[n];
	wypelnienie_tablicy(t, n);
	random_shuffle(t, t + n);
	cout<<"czas w sekundach: "<<((float)sortowanie_babelkowe(t, n))/CLOCKS_PER_SEC<<endl;
	*/
}