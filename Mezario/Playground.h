#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include "Mezario.h"
#include "Player.h"
#include "Enemy.h"
#include "Alpha.h"

class Playground
{
public:
	Playground(const int i_height , const int i_width , const int i_hearts , const int i_probability_wall , const int i_quantity_enemy , const int i_time_max);
	~Playground();

public:
	void PlayerMove(enum Action e_action);
	void PlayerShot();
	void UpdateCreatures();
	void PrintToConsole(const HANDLE& h_console);
	int GetTimeLeft();
	int GetHearts();
	int GetEnemies();
	bool IsWin();
	bool IsLose();

private:
	void Initialize();
	void SetValue(const PositionPtr& ptr_position , enum Cell e_cell);
	char GetValue(const PositionPtr& ptr_position);
	bool IsInBounds(const PositionPtr& ptr_position);
	void UpdateEnemyMove(const EnemyPtr& ptr_enemy);
	void UpdateEnemyShot(const EnemyPtr& ptr_enemy);
	void UpdatePlayerShot();
	void UpdateCreatre(const CreaturePtr& ptr_creature);
	void PrintCell(const HANDLE& h_console , enum Cell e_cell);
	int GetTimeCounter();

private:
	char** mptr_matrix = 0;
	int mi_height = 0;
	int mi_width = 0;
	int mi_hearts = 0;
	int mi_probability_wall = 0;
	int mi_quantity_enemy = 0;
	int mi_time_max = 0;
	PositionPtr mptr_position_exit = nullptr;
	PlayerPtr mptr_player = nullptr;
	std::vector<EnemyPtr> mvec_enemy;
	std::chrono::steady_clock::time_point mtime_start;

};
using PlaygroundPtr = std::shared_ptr<Playground>;

#endif // !PLAYGROUND_H