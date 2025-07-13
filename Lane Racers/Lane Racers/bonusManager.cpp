#include "bonusManager.h"

bonusManager::bonusManager(float baseX, float laneWidth, int PlayerHeight, bonusesEffectsContext& effects, laneManager& laneMng)
	: baseX(baseX),
	  laneWidth(laneWidth),
	  PlayerHeight(PlayerHeight),
	  effects(effects),
	  laneMng(laneMng),
	  gen(random_device{}()),
	  distTexture(0, 2),
	  distLine(0, 2),
	  distOffset(-30, 30),
	  distSpawnChance(1, 100)
{
	bonusTextures[BonusType::ScoreBoost].loadFromFile("Image/bonus3.png");
	bonusTextures[BonusType::ShieldBoost].loadFromFile("Image/bonus1.png");
	bonusTextures[BonusType::SlowBoost].loadFromFile("Image/bonus2.png");
}

void bonusManager::update(float time, float winHeight, DifficultySettings difSettings) {
	//настройка
	spawnChance = difSettings.bonusSpawnChance;

	// спавн бонусов
	if (spawnClock.getElapsedTime().asSeconds() >= spawnChanceInterval) { 
		int curLine = distLine(gen);
		if (laneMng.IsLineFree(curLine)) {
			if (distSpawnChance(gen) > 100 - spawnChance) {
				laneMng.SetLineOccupied(curLine);
				BonusType randomBonus = static_cast<BonusType>(distTexture(gen));
				bonuses.push_back(bonus(Vector2f(GetRandomBonusPosition(curLine), -bonusHeight - 10), Vector2f(bonusWidth, bonusHeight), &bonusTextures[randomBonus], randomBonus, curLine, difSettings.propSpeed));
				laneMng.SetLineNonChangable(curLine);
			}
			spawnClock.restart();
		}
		else {
			curLine = laneMng.GetFreeLine();
			if (curLine != -1) {
				if (distSpawnChance(gen) > 100 - spawnChance) {
					laneMng.SetLineOccupied(curLine);
					BonusType randomBonus = static_cast<BonusType>(distTexture(gen));
					bonuses.push_back(bonus(Vector2f(GetRandomBonusPosition(curLine), -bonusHeight - 10), Vector2f(bonusWidth, bonusHeight), &bonusTextures[randomBonus], randomBonus, curLine, difSettings.propSpeed));
					laneMng.SetLineNonChangable(curLine);
				}
				spawnClock.restart();
			}
			else 
				spawnClock.restart();
		}
	}

	// изменение чего-то с препятствиями каждый кадр
	for (auto& bon : bonuses) {
		bon.update(time, effects.GetSlowDownMultiplier());

		if (!bon.GetLineFreed() && bon.GetPos().y > 120) {
			laneMng.FreeLine(bon.GetLineIndex());
			bon.SetLineFreed();
		}

		if (!bon.GetUnbanedLineForChange() && bon.GetPos().y >= (winHeight / 2)) {
			laneMng.SetLineChangable(bon.GetLineIndex());
			bon.SetUnbanedLineForChange();
		}
	}

	// удаление препятствий 
	bonuses.erase(
		remove_if(bonuses.begin(), bonuses.end(),
			[winHeight](const bonus& bon) {
				return bon.IsOffScreen(winHeight);
			}),
		bonuses.end()
				);
}

void bonusManager::draw(RenderWindow& win) const {
	for (auto& bon : bonuses) {
		bon.draw(win);
	}
}

int bonusManager::GetRandomBonusPosition(int line) {
	int spawnX = lanePositions[line] + distOffset(gen);
	if (spawnX < baseX - 10)
		spawnX = baseX - 10;
	if (spawnX > lanePositions[2] + 5)
		spawnX = lanePositions[2] + 5;
	return spawnX;
}

bool bonusManager::checkCollisionsWithPlayer(const player& p, BonusType& outType) {
	for (auto bon = bonuses.begin(); bon != bonuses.end(); bon++) {
		if (bon->GetBounds().intersects(p.GetBounds())) {
			outType = bon->GetBonus();
			bonuses.erase(bon);
			return true;
		}
	}
	return false;
}

void bonusManager::Reset() {
	bonuses.clear();
	spawnClock.restart();
}