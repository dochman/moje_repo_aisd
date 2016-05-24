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

bool hash_al_wstaw(int *t, int m, int x, int & wywolan)   //m to rozmiar tablicy mieszajacej
{
	int k;
	
	for (int i = 0; i < m; i++)
	{
		wywolan++;
		k = h(x, i, m);
		if (t[k] == -1)
		{
			t[k] = x;
			return true;
		}
	}
	return false;
}

int main()
{
	srand(time(NULL));
	//tablica dynamiczna mieszajaca
	int n_mieszajaca = 1048576;
	int* t = new int[n_mieszajaca];
	wypelnienie_tablicy_mieszajacej(t, n_mieszajaca);

	const int n_dane = 10000000;
	int*tab =new int[n_dane];
	wypelnienie_tablicy_dane(tab, n_dane);
	random_shuffle(tab, tab + n_dane);

	double srednia = 0;
	double czas = 1;
	clock_t start, stop;
	int probka = 10000;
	double liczba_prob = 0;
	int wywolan = 0;
	int nowy_rozmiar;

	double procentowo = 0.0;

	while (procentowo != 0.9)
	{
		nowy_rozmiar = n_mieszajaca*procentowo;

		for (int i = 0;i < n_mieszajaca;i++)
		{
			t[i] = -1;
		}

		for (int i = 0;i < nowy_rozmiar;i++)
		{
			hash_al_wstaw(t, n_mieszajaca, tab[i], wywolan);
		}

		wywolan = 0;

		start = clock();
		for (int i = nowy_rozmiar; i < (nowy_rozmiar+probka); i++)
		{
			if (hash_al_wstaw(t, n_mieszajaca, tab[i], wywolan) == false)
			{
				cout << "Nie udalo sie wstawic do tablicy" << endl;
				return -1;
			}
		}
		stop = clock();
		czas = (stop - start) / CLOCKS_PER_SEC;
		srednia = czas / probka;
		liczba_prob = wywolan / probka;
		cout << "Sredni czas wstawiania= " << srednia << " s, udalo sie po " << wywolan << " probach" << endl;

		procentowo += 0.1;

	}


	delete[] t;
	delete[] tab;
	return 0;
}

/* musze jeszcze podzielic przez 10000 i zadbac o ilosc miesjc po przecinku

Sredni czas wstawiania= 0 s, udalo sie po 10035 probach
Sredni czas wstawiania= 0 s, udalo sie po 11064 probach
Sredni czas wstawiania= 0 s, udalo sie po 12726 probach
Sredni czas wstawiania= 0 s, udalo sie po 15020 probach
Sredni czas wstawiania= 0 s, udalo sie po 18274 probach
Sredni czas wstawiania= 0 s, udalo sie po 24141 probach
Sredni czas wstawiania= 0 s, udalo sie po 34910 probach
Sredni czas wstawiania= 0 s, udalo sie po 59649 probach
Sredni czas wstawiania= 0 s, udalo sie po 140649 probach
Sredni czas wstawiania= 0 s, udalo sie po 1058731 probach
Aby kontynuowaæ, naciœnij dowolny klawisz . . .
*/ 