#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <random>
using namespace std;
using namespace sf;

struct DifficultySettings {
    float propSpeed;
    float obsSpawnInterval;
    float bonusSpawnChance;
    float changingLineCarSpawnChance;
    float roadSpeedMult;
};

class difficultyManager
{
private:
    Clock GameTime;
    DifficultySettings currentSettings;

    const float bonusSpawnChance = 30.f;
    const float obsSpawnInterval = 5.f;
    const float propSpeed = 1.2f;
    const float roadSpeedMult = 1.5f;
    const float changingLineCarSpawnChance = 10.f;

    float lastPropSpeedUpd;
    float lastObsSpawnIntervalUpd;
    bool IsBonusSpawnChanceDown = false;
    bool IsChangingLineCarSpawnChanceDown = false;
public:
    difficultyManager();
    void update(int currentScore);
    DifficultySettings GetCurrentDifficult() const;
    void Reset();
};

