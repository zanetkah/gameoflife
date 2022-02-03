#pragma once

#include "MapaShow.h"

using namespace sf;

class App
{
public:
	App(); //konstruktor
	void mainLoop(); //deklaracja g��wnej p�tli

private: 
	void input(); //deklaracja funkcji kt�ra umo�liwia zamkni�cie okna
	void update(); //funkcja ktora zmienia stan komorek po okreslonym czasie
	void draw(); //wyswietlenie planszy na ekranie
	
	MapaShow mapaShow; 

	RenderWindow window; 

	Clock clock; //zegar do mierzenia czasu pomiedzy klatkami
	float time; //czas w sekundach od ostatniej zmiany planszy
	const float stepDelay = 1.f; //czas po kt�rym plansza ma si� zmienic
};

