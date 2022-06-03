#include "Mezario.h"
#include "Playground.h"
#include "Player.h"

int main()
{
	const int i_width = 100;
	const int i_height = 25;
	Player* ptr_player = new Player(Position( 1,10 ));
	Playground* ptr_playground = new Playground(i_height , i_width , ptr_player);

	for ( int y = 1; y < i_height - 1; y++ )
	{
		for ( int x = 1; x < i_width - 1; x++ )
		{			
			ptr_player->MoveTo(Position( x,y ));
			ptr_playground->PrintToConsole();
			
		}
	}

	delete ptr_playground;
}
