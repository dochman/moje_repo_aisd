#include <iostream>
#include <algorithm>
#include <time.h>
#include <iomanip>

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

int h1(int x, int m)
{
	return x % m;
}

int h2(int x, int m)
{
	return (((x / m) % (m / 2)) * 2) + 1;
}

int hd(int x, int i, int m)
{
	return ((h1(x, m) + i*h2(x, m)) % m);
}

bool hash_al_wstaw(int *t, int m, int x, int & wywolan)   //m to rozmiar tablicy mieszajacej
{
	int k;
	
	for (int i = 0; i < m; i++)
	{
		wywolan++;
		//k = h(x, i, m);
		k = hd(x, i, m);
		if (t[k] == -1)
		{
			t[k] = x;
			return true;
		}
	}
	return false;
}

bool hash_al_szukaj(int *t, int m, int x, int & wywolanszukaj)
{
	int k;

	for (int i = 0;i < m;i++)
	{
		wywolanszukaj++;
		//k = h(x, i, m);
		k = hd(x, i, m);
		if (t[k] == x)
		{
			return true;
		}

		if (t[k] == -1)
		{
			return false;
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
    double probka = 10000;
	double liczba_prob = 0;
	int wywolan = 0;
	int wywolanszukaj = 0;
	int nowy_rozmiar=0;
	double sredniaszukaj = 0;
	double liczba_prob_szukaj;
	int32_t r;

	double procentowo=0.1;

	for (int i = 0;i < 9;i++)
	{
		nowy_rozmiar = n_mieszajaca*procentowo;

		for (int j = 0;j < n_mieszajaca;j++)
		{
			t[j] = -1;
		}

		for (int w = 0;w < nowy_rozmiar;w++)
		{
			hash_al_wstaw(t, n_mieszajaca, tab[w], wywolan);
		}

		wywolan = 0;

		start = clock();
		for (int n = nowy_rozmiar; n < (nowy_rozmiar + probka); n++)
		{
			if (hash_al_wstaw(t, n_mieszajaca, tab[n], wywolan) == false)
			{
				cout << "Nie udalo sie wstawic do tablicy" << endl;
				return -1;
			}
		}
		stop = clock();
		czas = (stop - start) / (float)CLOCKS_PER_SEC;
		srednia = czas / probka;
		liczba_prob = wywolan / probka;
		cout.setf(ios::fixed);
		cout << "Sredni czas wstawiania= " << setprecision(7) <<srednia << " s, udalo sie po "<<setprecision(4)<<liczba_prob << " probach" << endl;

		///////////////////////////////////////////////////////////////szukanie
		wywolanszukaj = 0;
		start = clock();
		for (int w = 0;w < probka;w++)
		{
			r = ((rand() & 0x7FFF) << 15) | (rand() & 0x7FFF);
			r = r % nowy_rozmiar;
			hash_al_szukaj(t, n_mieszajaca, tab[r], wywolanszukaj);
		}
		stop = clock();
		czas = (stop - start) / (float)CLOCKS_PER_SEC;
		sredniaszukaj = czas / probka;
		liczba_prob_szukaj = wywolanszukaj / probka;
		cout.setf(ios::fixed);
		cout << "Sredni czas szukania= " << setprecision(7) <<sredniaszukaj << " s, udalo sie po " <<setprecision(4)<<liczba_prob_szukaj << " probach" << endl;

		procentowo = procentowo + 0.1;	
	}

	delete[] t;
	delete[] tab;
	return 0;
}
