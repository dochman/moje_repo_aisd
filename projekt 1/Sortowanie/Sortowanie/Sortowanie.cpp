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
	return;
}

void zwieksz_ilosc_danych(int *&t, int &rozmiar)
{
	delete[] t;
	rozmiar = rozmiar * 2;
	t = new int[rozmiar];
	wypelnienie_tablicy(t, rozmiar);
	return;
}

void sortowanie_babelkowe(int *t, int n)
{
	int rez;

	for (int i = 0; i < n; i++)
		for (int j = 1; j < n; j++)
		{
			if (t[j - 1] > t[j])
			{
				/*rez = t[j - 1];
				t[j - 1] = t[j];
				t[j] = rez;*/
				swap(t[j], t[j - 1]);
			}
		}
	return;
}

int main()
{
	//tablica dynamiczna
	int n=1000; 
	int* t = new int[n];  
	float suma = 0;
	float srednia = 0;
	int czas,licznik=1;
	clock_t start, stop;

	wypelnienie_tablicy(t, n);

	while (true)
	{
		suma = 0;
		for (int i = 1; i <= 5; ++i)
		{
			//wypelnienie_tablicy(t, n);
			random_shuffle(t, t + n);
			//czas = 0;

			start = clock();
			sortowanie_babelkowe(t, n);
			stop = clock();
			czas = stop-start;

			suma += czas / (float)CLOCKS_PER_SEC;
		}
		srednia = suma /= 5;
		cout <<licznik<<"*10^3: "<<"sredni czas-babelkowe= " << srednia << endl;
		licznik *= 2;

		if (srednia > 30)
		{
			cout << "Przekroczono 30 sekund" << endl;
			break;
		}
		zwieksz_ilosc_danych(t, n);
	}

	delete[] t;
	return 0;
}