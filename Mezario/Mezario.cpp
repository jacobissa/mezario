#include "Mezario.h"
#include "Playground.h"

/// <summary>
/// The main function, where the program execution begins and ends.
/// </summary>
/// <returns></returns>
int main()
{
    Playground* playground = new Playground( 25 , 50);
    playground->PrintToConsole();

}
