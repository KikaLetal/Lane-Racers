#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "bonus.h"
#include "player.h"
#include "bonusType.h"
#include "difficultyManager.h"
#include "bonusesEffectsContext.h"
#include "laneManager.h"
#include <iostream>
#include <random>

using namespace std;
using namespace sf;

class bonusManager
{
private:
	vector<bonus> bonuses;
	map<BonusType, Texture> bonusTextures;
	const int bonusHeight = 80;
	const int bonusWidth = 80;
	const int PlayerHeight;
	sf::Clock spawnClock;
	float spawnChanceInterval = 2.0f;
	float spawnChance;
	const float baseX;
	const float laneWidth;
	mt19937 gen;
	uniform_int_distribution<> distTexture;
	uniform_int_distribution<> distLine;
	uniform_int_distribution<> distOffset;
	uniform_real_distribution<> distSpawnChance;
	bonusesEffectsContext& effects;
	laneManager& laneMng;

	std::vector<float> lanePositions = {
		baseX,
		baseX + laneWidth,
		baseX + 2 * laneWidth
	};

public:
	bonusManager(float baseX, float laneWidth, int PlayerHeight, bonusesEffectsContext& effects, laneManager& laneMng);
	void update(float time, float winHeight, DifficultySettings difSettings);
	void draw(RenderWindow& win) const;
	int GetRandomBonusPosition(int line);
	bool checkCollisionsWithPlayer(const player& p, BonusType& outType);
	void Reset();
};

