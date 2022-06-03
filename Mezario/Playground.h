#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include "Mezario.h"
#include "Player.h"
#include "Enemy.h"

class Playground
{
public:
	Playground(const int i_height , const int i_width , PlayerPtr& ptr_player , std::vector<EnemyPtr>& vec_enemy);
	~Playground();

public:
	void PrintToConsole();
	void UpdateCreatures();

private:
	void Initialize();
	void SetValue(Position position , enum Cell e_cell);
	char GetValue(Position position);
	bool IsInBounds(Position position);
	void UpdateCreatre(CreaturePtr creature);

private:
	char** mptr_matrix = 0;
	int mi_height = 0;
	int mi_width = 0;
	PlayerPtr mptr_player;
	std::vector<EnemyPtr> mvec_enemy;
};
using PlaygroundPtr = std::shared_ptr<Playground>;

#endif // !PLAYGROUND_H