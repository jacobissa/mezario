#include "Mezario.h"
#include "Playground.h"

int main()
{
    Playground* playground = new Playground( 25 , 50);

    playground->PrintToConsole();
    delete playground;
}
