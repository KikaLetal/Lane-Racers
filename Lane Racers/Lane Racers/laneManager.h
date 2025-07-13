#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <string>
#include <iostream>
using namespace std;
using namespace sf;

class laneManager
{
private:
	array<bool, 3> laneOccupied;
	array<bool, 3> ChangeLanes;
public:
	laneManager();
	bool IsLineFree(int Line) const;
	void SetLineOccupied(int Line);
	void FreeLine(int Line);
	int GetFreeLine() const;

	bool IsCanChangeLine(int Line) const;
	void SetLineNonChangable(int Line);
	void SetLineChangable(int Line);

	void Reset();
};

