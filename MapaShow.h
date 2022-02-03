#pragma once
#include "Mapa.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class MapaShow:
    public Mapa, //dziedziczenie klasy Mapa
    public Drawable //klasa bazowa dla obiektów które mog¹ byæ narysowane
{
public:
    MapaShow(const int szerokosc, const int wysokosc);
protected:
    void draw(RenderTarget& target, RenderStates states) const override; //metoda rysujaca mape
private:
    mutable Texture texture;
    Sprite sprite;
};

