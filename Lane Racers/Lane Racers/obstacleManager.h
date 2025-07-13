#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "obstacle.h"
#include "player.h"
#include "bonusesEffectsContext.h"
#include "laneManager.h"
#include "difficultyManager.h"
#include <iostream>
#include <random>
using namespace std;
using namespace sf;

class obstacleManager
{
private:
	vector<obstacle> obstacles;
	vector<Texture> obstacleTextures;
	const int ObsVariants = 3; 
	const int obsHeight = 135;
	const int obsWidth = 105;
	sf::Clock spawnClock;
	float spawnInterval;
	int ChangingLineChance;
	const float baseX;
	const float laneWidth;
	mt19937 gen;
	uniform_int_distribution<> distTexture;
	uniform_int_distribution<> distLine;
	uniform_int_distribution<> distOffset;
	uniform_real_distribution<> distIntervalOffset;
	uniform_int_distribution<> distChangingLineChance;
	float nextObsSpawnIn;
	bonusesEffectsContext& effects;
	laneManager& laneMng;

	std::vector<float> lanePositions = {
		baseX,
		baseX + laneWidth,
		baseX + 2 * laneWidth
	};

public:
	obstacleManager(float baseX, float laneWidth, bonusesEffectsContext& effects, laneManager& laneMng);

	void update(float time, float winHeight, DifficultySettings difSettings);
	void draw(RenderWindow& win) const;

	int GetRandomObsPosition(int line);

	bool checkCollisionsWithPlayer(const player& p);
	int checkPlayerOvertakedObstacle(const player& p);

	void checkPlayerNear(const player& p);

	void RemoveObstaclesTouched(const player& p);
	void Reset();
};

