#include "Mapa.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

Mapa::Mapa(const int szerokosc, const int wysokosc):
	szerokosc(szerokosc),
	wysokosc(wysokosc)
{
	base = new unsigned int[szerokosc * wysokosc]; //alokacja pamieci 

	for (int i = 0; i < szerokosc * wysokosc; ++i) //czyszczenie mapy
		base[i] = 0;

	tmp = new unsigned int[szerokosc * wysokosc]; //alokacja pamieci
}

Mapa::~Mapa()
{
	delete[] base;
	delete[] tmp;
}

void Mapa::randomizeMapa()
{
	for (int i = 0; i < szerokosc * wysokosc;i++)
	{
		base[i] = rand() % 2 * static_cast<unsigned int>(-1); //bia³y w RGBA
	}
}

void Mapa::niechSieToczyZycie()
{
	prawyGornyRog();
	gornaLinia();
	lewyGornyRog();
	srodek();
	prawyDolnyRog();
	dolnaLinia();
	lewyDolnyRog();

	swap();
}

void Mapa::lewyGornyRog()
{
	auto sasiedzi = base[1] + base[szerokosc - 1] + base[szerokosc] + base[szerokosc + 1] + base[szerokosc * 2 - 1] + base[szerokosc * (wysokosc - 1)] + base[szerokosc * (wysokosc - 1) + 1] + base[szerokosc * wysokosc - 1];
	tmp[0] = stanKomorki(base[0], sasiedzi);
}

void Mapa::gornaLinia()
{
	for (int i = 1; i < szerokosc-1; ++i)
	{
		auto sasiedzi = base[i-1] + base[i+1] + base[szerokosc+i-1] + base[szerokosc + i] + base[szerokosc + i +1] + base[szerokosc*(wysokosc-1) + i - 1] + base[szerokosc * (wysokosc - 1) + i] + base[szerokosc * (wysokosc - 1)+i+1];
		tmp[i] = stanKomorki(base[i], sasiedzi);
	}
}

void Mapa::prawyGornyRog()
{
	auto sasiedzi = base[0] + base[szerokosc-2] + base[szerokosc] + base[szerokosc*2-2] + base[szerokosc * 2 - 1] + base[szerokosc*(wysokosc-1)] + base[szerokosc * wysokosc -2]+ base[szerokosc * wysokosc - 1];
	tmp[szerokosc-1] = stanKomorki(base[szerokosc-1], sasiedzi);
}

void Mapa::srodek()
{
	for (int i = szerokosc; i < szerokosc * (wysokosc - 1); i += szerokosc)
	{
		auto sasiedzi = base[i - szerokosc] + base[i - szerokosc + 1] + base[i - 1] + base[i + 1] + base[i + szerokosc - 1] + base[i + szerokosc] + base[i + szerokosc + 1] + base[i + szerokosc * 2 - 1];
		tmp[i] = stanKomorki(base[i], sasiedzi);
		
		for (int j = 1; j < szerokosc-1; ++j)
		{
			sasiedzi = base[i-szerokosc+j-1]+ base[i-szerokosc+j]+base[i-szerokosc+j+1]+base[i+j-1]+base[i+j+1]+base[i+szerokosc+j-1]+base[i+szerokosc+j]+base[i+szerokosc+j+1];
			tmp[i+j] = stanKomorki(base[i+j], sasiedzi);
		}

		sasiedzi = base[i - szerokosc] + base[i -2] + base[i - 1] + base[i] + base[i + szerokosc - 2] + base[i + szerokosc] + base[i + szerokosc*2 -2] + base[i + szerokosc*2 -1];
		tmp[i+szerokosc-1] = stanKomorki(base[i+szerokosc-1], sasiedzi);		
	}
}

void Mapa::lewyDolnyRog()
{
	auto sasiedzi = base[0] + base[1] + base[szerokosc - 1] + base[szerokosc * (wysokosc - 2)] + base[szerokosc * (wysokosc - 2) + 1] + base[szerokosc * (wysokosc - 1) - 1] + base[szerokosc * (wysokosc - 1) + 1] + base[szerokosc * wysokosc - 1];
	tmp[szerokosc*(wysokosc-1)] = stanKomorki(base[szerokosc * (wysokosc - 1)], sasiedzi);
}

void Mapa::dolnaLinia()
{
	for (int i = 1; i < szerokosc - 1; ++i)
	{
		auto sasiedzi = base[i - 1] + base[i] + base[i + 1] + base[szerokosc * (wysokosc - 2) + i - 1] + base[szerokosc * (wysokosc - 2) + i] + base[szerokosc * (wysokosc - 2) + i + 1] + base[szerokosc * (wysokosc - 1) + i - 1] + base[szerokosc * (wysokosc - 1) + i + 1];
		tmp[szerokosc * (wysokosc - 1) + i] = stanKomorki(base[szerokosc * (wysokosc - 1) + i], sasiedzi);
	}
}

void Mapa::prawyDolnyRog()
{
	auto sasiedzi = base[0] + base[szerokosc - 2] + base[szerokosc - 1] + base[szerokosc * (wysokosc - 2)] + base[szerokosc * (wysokosc - 1) - 2] + base[szerokosc * (wysokosc - 1) - 1] + base[szerokosc * (wysokosc - 1)] + base[szerokosc * wysokosc - 2];
	tmp[szerokosc * wysokosc - 1] = stanKomorki(base[szerokosc * wysokosc - 1], sasiedzi);
}

void Mapa::swap() 
{
	auto t = base;
	base = tmp;
	tmp = t;
}

unsigned int Mapa::stanKomorki(unsigned int stan, int sasiedzi)
{
	if (sasiedzi == static_cast<unsigned int>(-3)) //wartoœci tablicy to 0 i -1 dlatego podczas zliczania s¹siadów wynik jest ujemny
		return static_cast<unsigned int>(-1);
	else if (sasiedzi == static_cast<unsigned int>(-2))
		return stan;
	else
		return 0;
}

void Mapa::ustaw(int x, int y, bool status)
{
	base[y*szerokosc+x]=status*static_cast<unsigned int>(-1);
}


