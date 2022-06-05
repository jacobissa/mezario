#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include "Mezario.h"
#include "Player.h"
#include "Enemy.h"

class Playground
{
public:
	Playground(const int i_height , const int i_width , const int i_probability_wall , const int i_quantity_enemy);
	~Playground();

public:
	void PlayerMove(enum Action e_action);
	void PlayerShot();
	void UpdateCreatures();
	void PrintToConsole();

private:
	void Initialize();
	void SetValue(const PositionPtr& ptr_position , enum Cell e_cell);
	char GetValue(const PositionPtr& ptr_position);
	bool IsInBounds(const PositionPtr& ptr_position);
	void UpdateEnemyMove(const EnemyPtr& ptr_enemy);
	void UpdateCreatureShot(const CreaturePtr& ptr_creature);
	void UpdateCreatre(const CreaturePtr& ptr_creature);

private:
	char** mptr_matrix = 0;
	int mi_height = 0;
	int mi_width = 0;
	int mi_probability_wall = 0;
	int mi_quantity_enemy = 0;
	PositionPtr mptr_position_exit = nullptr;
	PlayerPtr mptr_player = nullptr;
	std::vector<EnemyPtr> mvec_enemy;
};
using PlaygroundPtr = std::shared_ptr<Playground>;

#endif // !PLAYGROUND_H