#include "App.h"

int main()
{
    srand(time(NULL));
    App app; //inicjalizacja obiektu
    app.mainLoop();
    
    return 0;
}