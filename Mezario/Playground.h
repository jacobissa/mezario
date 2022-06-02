#pragma once
#include "Mezario.h"

class Playground
{
public:
	Playground(const int i_height , const int i_width);
	~Playground();

public:
	void PrintToConsole();

private:
	void Initialize();
	void SetValue(Position position , char c_value);
	char GetValue(Position position);
	bool IsInBounds(Position position);

private:
	char** matrix = 0;
	int mi_height = 0;
	int mi_width = 0;
};

