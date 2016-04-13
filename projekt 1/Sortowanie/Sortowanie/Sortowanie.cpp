#include <iostream>
#include <algorithm>
#include <time.h>

using namespace std;


void wypelnienie_tablicy(int *t, int n)
{
	for (int i = 0; i < n; i++)
	{
		t[i] = i;
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

bool weryfikacja(int *t, int n)
{
	for (int i = 0; i < n-1; i++)
	{
		if (t[i] > t[i + 1]) return false;
	}
	return true;
}

void sortowanie_babelkowe(int *t, int n)
{
	int rez;

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
	return;
}

void proste_wstawianie1(int *t, int n)
{
	int x;
	int j;

	for (int i = 1; i < n; i++)
	{
	    x = t[i];
	    j = i - 1;
		while ((j >= 0) && (x < t[j]))
		{
			t[j + 1] = t[j];
			j = j - 1;
		}
		t[j + 1] = x;
	}
	return;
}

void proste_wybieranie(int *t, int n)
{
	int k, x;
	for (int i = 0; i < n;i++)
	{
		k = i;
		x = t[i];

		for (int j = i + 1;j <= n; j++)
		{
			if (t[j] < x)
			{
				j = j;
				x = t[j];
			}
		}
		t[k] = t[i];
		t[i] = x;
	}
	return;
}

void shell(int *t, int n)
{
	int h = 1;
	int x,j;
	while (h < (n / 9))
	{
		h = (3 * h) + 1;
	}
	while (h > 0)
	{
		for (int i = h; i < n;i++)
		{
			x = t[i];
			j = i;
			while ((j >= h) && (x < t[j - h]))
			{
				t[j] = t[j - h];
				j = j - h;
			}
			t[j] = x;
		}
		h = h / 3;
	}
	return;
}

void sortowanie_szybkie(int* t, int d, int g)
{
	int klucz;
	int s;

	if (d < g)
	{
		klucz = t[d];
		s = d;

		for (int i = d + 1; i < g; i++)
		{
			if (t[i] < klucz)
			{
				s = s + 1;
				swap(t[s], t[i]);
			}
		}
		swap(t[d], t[s]);
		sortowanie_szybkie(t, d, s);
		sortowanie_szybkie(t, s + 1, g);
	}
	return;
}

void szybkie_wst(int *t, int d, int g) 
{
	int klucz;
	int s;
	int k, x;

	if (d < g)
	{
		klucz = t[d];
		s = d;

		if ((g - d) < 30)
		{
			int x;
			int j;

			for (int i = d; i < g; i++)
			{
				x = t[i];
				j = i - 1;
				while ((j >= 0) && (x < t[j]))
				{
					t[j + 1] = t[j];
					j = j - 1;
				}
				t[j + 1] = x;
			}
			return;
		}

		for (int i = d + 1; i < g; i++)
		{
			if (t[i] < klucz)
			{
				s = s + 1;
				swap(t[s], t[i]);
			}
		}
		swap(t[d], t[s]);
		szybkie_wst(t, d, s);
		szybkie_wst(t, s + 1, g);


	}
}

void mediana()
{

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
	bool weryf;

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
			//sortowanie_babelkowe(t, n);
			//proste_wstawianie1(t, n);
			//proste_wybieranie(t, n);
			//shell(t, n);
			sortowanie_szybkie(t, 0, n);
			//szybkie_wst(t, 0, n);

			stop = clock();
			czas = stop-start;

			weryf = weryfikacja(t, n);
			if (weryf == true)
			{
				cout << "Weryfikacja: OK" << endl;
			}
			else if (weryf==false) cout << "Weryfikacja: BAD" << endl;

			suma += czas / (float)CLOCKS_PER_SEC;
		}


		srednia = suma /= 5;
		//cout <<licznik<<"*10^3: "<<"sredni czas-babelkowe= " << srednia << endl;
		//cout << licznik << "*10^3: " << "sredni czas-wstawianie1 " << srednia << endl;
		//cout << licznik << "*10^3: " << "sredni czas-wybieranie= " << srednia << endl;
		//cout << licznik << "*10^3: " << "sredni czas-shell= " << srednia << endl;
		cout << licznik << "*10^3: " << "sredni czas-szybkie= " << srednia << endl;

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