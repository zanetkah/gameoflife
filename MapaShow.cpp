#include "MapaShow.h"

MapaShow::MapaShow(const int szerokosc,const int wysokosc):
	Mapa(szerokosc, wysokosc)
{
	texture.create(szerokosc, wysokosc); //stworzenie tekstury

	sprite.setTexture(texture); //ustawienie tekstury
	sprite.setScale(20, 20); //zmiana skali
	sprite.setColor(Color::Red); //nadanie koloru
}

void MapaShow::draw(RenderTarget& target, RenderStates states) const
{
	texture.update(reinterpret_cast<const Uint8*>(base)); 
	target.draw(sprite, states);
}
