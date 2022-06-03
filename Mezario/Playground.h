#pragma once
#include "Mezario.h"
#include "Player.h"
#include "Enemy.h"

class Playground
{
public:
	Playground(const int i_height , const int i_width , Player* ptr_player , Enemy* ptr_enemy);
	~Playground();

public:
	void PrintToConsole();
	void UpdatePlayer();
	void UpdateEnemy();

private:
	void Initialize();
	void SetValue(Position position , enum Cell e_cell);
	char GetValue(Position position);
	bool IsInBounds(Position position);

private:
	char** mptr_matrix = 0;
	int mi_height = 0;
	int mi_width = 0;
	Player* mptr_player;
	Enemy* mptr_enemy;
};

