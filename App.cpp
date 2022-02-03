#include "App.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<iostream>
#include <array>

App::App():
	window(VideoMode(800, 600), "Gra w zycie", Style::Titlebar | Style::Close), 
    mapaShow(40, 30)
{
    mapaShow.randomizeMapa();
}

void App::mainLoop()
{
    clock.restart(); //zresetowanie zegaru

    while (window.isOpen())
    {
        input();
        update();
        draw();
    }
}

void App::input()
{
    static Event event;

    while(window.pollEvent(event))
    {
        switch (event.type)
        {
        case Event::Closed:
            window.close();
            break;
        }
    }
}

void App::update()
{
    for (time += clock.restart().asSeconds(); time >= stepDelay; time -= stepDelay) 
    {
        if (clock.getElapsedTime().asSeconds() >= 0.1f) //okreslenie maksymalnego czasu przeliczania gry
        {
            time = 0.f;
            break;
        }

        mapaShow.niechSieToczyZycie(); //przeliczenie s¹siadów i nadanie stanu komórkom
    }
}

void App::draw()
{    
    window.clear(); //czysci bufor klatki
    
    window.draw(mapaShow); //rysuje mape w klatce
    
    window.display(); //wyswietla klatke w oknie
}