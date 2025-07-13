#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "difficultyManager.h"
#include <iostream>
#include <random>
using namespace std;
using namespace sf;

class decoreManager
{
private:
	vector<Texture> decorTextures;
	vector<Sprite> decores;
	mt19937 gen;
	uniform_int_distribution<> distTexture;
	uniform_int_distribution<> distLine;
	uniform_int_distribution<> distOffset;
	uniform_real_distribution<> distIntervalOffset;
	Clock spawnClock;
	int nextObsSpawnIn;
	int ObsSpawnIn = 2;
	const float baseX;
	const float laneWidth;

	vector<float> lanePositions = {
		baseX,
		baseX + laneWidth,
		baseX + 2 * laneWidth
	};
public:
	decoreManager(float baseX, float laneWidth);
	void update(float time, float winHeight, DifficultySettings difSettings);
	void draw(RenderWindow& win) const;
	int GetRandomObsPosition(int line);
	void Reset();
};

