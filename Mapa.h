#pragma once
class Mapa
{
public:
	Mapa(const int szerokosc, const int wysokosc);
	~Mapa(); //destruktor
	void ustaw(int x, int y, bool status);
	void randomizeMapa();
	void niechSieToczyZycie();
protected:
	unsigned int* base;
private:
	const int szerokosc;
	const int wysokosc;
	void lewyGornyRog();
	void gornaLinia();
	void prawyGornyRog();
	void srodek();
	void lewyDolnyRog();
	void dolnaLinia();
	void prawyDolnyRog();

	void swap(); //zamiana tablic

	static unsigned int stanKomorki(unsigned int stan, int sasiedzi);

	unsigned int *tmp;
};
