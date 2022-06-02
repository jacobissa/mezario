#ifndef PLAYGROUND_H
#define PLAYGROUND_H
#endif
#include <iostream>

class Playground
{
public:
	Playground(const int i_height , const int i_width);
	~Playground();

	void PrintToConsole();

private:
	void Initialize();
	void SetValue(int y, int x , char value);
	char GetValue(int y , int x);
	bool IsInBounds(int y , int x);

private:
	char** matrix = 0;
	int mi_height = 0;
	int mi_width = 0;
};

