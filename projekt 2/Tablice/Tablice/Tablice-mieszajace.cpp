#include <iostream>
#include <algorithm>
#include <time.h>

using namespace std;

//Daniel Ochman Teleinformatyka sem.2 sroda nieparzysta

void wypelnienie_tablicy_mieszajacej(int *t, int n)
{
	for (int i = 0; i < n; i++)
	{
		t[i] = -1;
	}
	return;
}

void wypelnienie_tablicy_dane(int *t, int n)
{
	for (int i = 0; i < n; i++)
	{
		t[i] = i;
	}
	return;
}

int h(int x, int i, int m) //m to rozmiar tablicy mieszajacej
{
	if (i == 0) return (x % m);
	else if (i>0) return (((x % m) + i) % m);
	return -1;
}

int hash_al_wstaw(int *t, int m, int x)   //m to rozmiar tablicy mieszajacej
{
	int k;

	for (int i = 0; i < m; i++)
	{
		k = h(x, i, m);
		if (t[i] == -1)
		{
			t[i] = k;
			return i++;
		}
	}
	return -1;
}

int main()
{
	//tablica dynamiczna mieszajaca
	int n_mieszajaca = 1048576;
	int* t = new int[n_mieszajaca];
	wypelnienie_tablicy_mieszajacej(t, n_mieszajaca);

	const int n_dane = 10000000;
	int*tab =new int[n_dane];
	wypelnienie_tablicy_dane(tab, n_dane);
	random_shuffle(tab, tab + n_dane);

	float suma = 0;
	float srednia = 0;
	int czas = 1;
	clock_t start, stop;
	int probka = 10000;
	int liczba_prob = 0;

	start = clock();

	for (int i = 0; i < probka; i++)
	{
		liczba_prob = hash_al_wstaw(t, n_mieszajaca, tab[i]);
	}

	stop = clock();
	czas = stop - start;
	cout << liczba_prob/probka << endl;
	cout<< (czas /(float)CLOCKS_PER_SEC);

	delete[] t;
	return 0;
}
