#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "bonus.h"
#include "bonusType.h"
#include <iostream>
#include <random>
class bonusesEffectsContext
{
private:
	// замедление
	float SlowDownMultiplier = 1.f;
	Clock SlowDownTimer;
	float SlowDownDur = 10.f;
	bool SlowDown = false;

	// щит
	bool hasShield = false;
	float ShieldDur = 10.f;
	Clock ShieldTimer;
	bool ShieldJustEnded = false;

	// удвоение очков
	bool DoubleScore = false;
	float DoubleScoreDur = 10.f;
	Clock DoubleScoreTimer;
public:	
	
	struct ActiveBonusInfo {
		BonusType type;
		float timeLeft;
		float duration;
	};

	bonusesEffectsContext();
	void update();
	vector<ActiveBonusInfo> GetActiveBonuses() const;
	void Reset();

	// замедление
	void SetSlowDown();
	bool IsSlowDownActive() const;
	float GetSlowDownMultiplier() const;
	float GetSlowDownTimer() const;

	// щит
	void SetShield();
	bool IsShieldActive() const;
	bool IsShieldJustEnded() const;
	void ResetShieldJustEnded();
	float GetShieldTimer() const;

	// удвоение очков
	void SetDoubleScore();
	bool IsDoubleScoreActive() const;
	float GetDoubleScoreTimer() const;

};

