#pragma once
#include "Mezario.h"
#include "Player.h"
#include "Enemy.h"

class Playground
{
public:
	Playground(const int i_height , const int i_width , PlayerPtr ptr_player , EnemyPtr ptr_enemy);
	~Playground();

public:
	void PrintToConsole();
	void UpdateCreatre(CreaturePtr creature);

private:
	void Initialize();
	void SetValue(Position position , enum Cell e_cell);
	char GetValue(Position position);
	bool IsInBounds(Position position);

private:
	char** mptr_matrix = 0;
	int mi_height = 0;
	int mi_width = 0;
	PlayerPtr mptr_player;
	EnemyPtr mptr_enemy;
};
using PlaygroundPtr = std::shared_ptr<Playground>;

