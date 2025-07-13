#include "difficultyManager.h"

difficultyManager::difficultyManager() {
	currentSettings.bonusSpawnChance = bonusSpawnChance;
	currentSettings.obsSpawnInterval = obsSpawnInterval;
	currentSettings.propSpeed = propSpeed;
	currentSettings.roadSpeedMult = roadSpeedMult;
	currentSettings.changingLineCarSpawnChance = changingLineCarSpawnChance;
}

void difficultyManager::update(int currentScore){
	float elapsed = GameTime.getElapsedTime().asSeconds();

	if (elapsed - lastPropSpeedUpd >= 10) {
		currentSettings.propSpeed = min(4.5f, currentSettings.propSpeed + 0.1f);
		currentSettings.roadSpeedMult = min(4.5f, currentSettings.roadSpeedMult + 0.1f);
		lastPropSpeedUpd = elapsed;
	}

	if (elapsed - lastObsSpawnIntervalUpd >= 10) {
		currentSettings.obsSpawnInterval = max(2.f, currentSettings.obsSpawnInterval - 0.1f);
		lastObsSpawnIntervalUpd = elapsed;
	}

	if (((currentScore % 10) == 0) && currentScore != 0 && !IsBonusSpawnChanceDown) {
		currentSettings.bonusSpawnChance = max(20.f, currentSettings.bonusSpawnChance - 1.f);
		IsBonusSpawnChanceDown = true;
	}

	else if(IsBonusSpawnChanceDown && (currentScore % 10) != 0)
		IsBonusSpawnChanceDown = false;

	if (((currentScore % 10) == 0) && currentScore != 0 && !IsChangingLineCarSpawnChanceDown) {
		currentSettings.changingLineCarSpawnChance = min(25.f, currentSettings.changingLineCarSpawnChance + 1.f);
		IsChangingLineCarSpawnChanceDown = true;
	}

	else if (IsChangingLineCarSpawnChanceDown && (currentScore % 10) != 0)
		IsChangingLineCarSpawnChanceDown = false;

}

DifficultySettings difficultyManager::GetCurrentDifficult() const{
	return currentSettings;
}

void difficultyManager::Reset() {
	currentSettings.bonusSpawnChance = bonusSpawnChance;
	currentSettings.obsSpawnInterval = obsSpawnInterval;
	currentSettings.propSpeed = propSpeed;
	currentSettings.roadSpeedMult = roadSpeedMult;
	currentSettings.changingLineCarSpawnChance = changingLineCarSpawnChance;
}
