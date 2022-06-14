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
	void PlayerMove(const Action e_action);
	void PlayerShot() const;
	void UpdateCreatures();
	void PrintToConsole(const HANDLE& h_console) const;
	int GetTimeLeft() const;
	int GetHearts() const;
	int GetEnemies() const;
	bool IsWin() const;
	bool IsLose() const;

private:
	void Initialize();
	void SetValue(const PositionPtr& ptr_position , const Cell e_cell) const;
	char GetValue(const PositionPtr& ptr_position) const;
	bool IsInBounds(const PositionPtr& ptr_position) const;
	void UpdateEnemyMove(const EnemyPtr& ptr_enemy) const;
	void UpdateEnemyShot(const EnemyPtr& ptr_enemy);
	void UpdatePlayerShot();
	void UpdateCreature(const CreaturePtr& ptr_creature) const;
	static void PrintCell(const HANDLE& h_console , const Cell e_cell);
	int GetTimeCounter() const;

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