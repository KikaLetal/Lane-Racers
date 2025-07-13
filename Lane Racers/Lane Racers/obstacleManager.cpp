#include "obstacleManager.h"

obstacleManager::obstacleManager(float baseX, float laneWidth, bonusesEffectsContext& effects, laneManager& laneMng)
	: baseX(baseX), 
	  laneWidth(laneWidth),
	  effects(effects),
	  laneMng(laneMng),
	  gen(random_device{}()),
	  distTexture(0, 2),
	  distLine(0, 2),
	  distOffset(-30, 30),
	  distIntervalOffset(-1.5f, 1.5f),
	  distChangingLineChance(1, 100)
{

	for (int i = 1; i <= 3; i++) {
		Texture T;
		if (!T.loadFromFile("Image/obstacle" + to_string(i) + ".png")) {
			cerr << "SFML не смог загрузить иконку из файла!\n";
		}
		obstacleTextures.push_back(move(T));
	}

	for (int i = 1; i <= 3; i++) {
		Texture T;
		if (!T.loadFromFile("Image/obstacle" + to_string(i) + "CLAnim.png")) {
			cerr << "SFML не смог загрузить иконку из файла!\n";
		}
		obstacleTextures.push_back(move(T));
	}
}


void obstacleManager::update(float time, float winHeight, DifficultySettings difSettings) {
	//настройка
	spawnInterval = difSettings.obsSpawnInterval;
	ChangingLineChance = difSettings.changingLineCarSpawnChance;

	// спавн препятствий
	if (spawnClock.getElapsedTime().asSeconds() >= nextObsSpawnIn) {
		bool IsChangingLine = distChangingLineChance(gen) >= 100 - ChangingLineChance;
		int curLine = distLine(gen);
		int direction = (curLine == 0) ? 1 : (curLine == 2) ? 1 : (rand() % 2 == 0 ? 0 : 2);
		if (!laneMng.IsCanChangeLine(direction))
			IsChangingLine = false;
		if (laneMng.IsLineFree(curLine)) {
			laneMng.SetLineOccupied(curLine);
			if (IsChangingLine) {
				obstacles.push_back(obstacle(Vector2f(GetRandomObsPosition(curLine), -obsHeight - 10), Vector2f(obsWidth, obsHeight), &obstacleTextures[distTexture(gen) + ObsVariants], IsChangingLine, difSettings.propSpeed, curLine, GetRandomObsPosition(direction)));
			}
			else
				obstacles.push_back(obstacle(Vector2f(GetRandomObsPosition(curLine), -obsHeight - 10), Vector2f(obsWidth, obsHeight), &obstacleTextures[distTexture(gen)], IsChangingLine, difSettings.propSpeed, curLine));
			
			spawnClock.restart();
			nextObsSpawnIn = spawnInterval + distIntervalOffset(gen);
		}
		else {
			curLine = laneMng.GetFreeLine();
			if (curLine != -1) {
				laneMng.SetLineOccupied(curLine);
				if (IsChangingLine) {
					int direction = (curLine == 0) ? 1 : (curLine == 2) ? 1 : (rand() % 2 == 0 ? 0 : 2);
					cout << "cur: " << curLine << " dir: " << direction << endl;
					obstacles.push_back(obstacle(Vector2f(GetRandomObsPosition(curLine), -obsHeight - 10), Vector2f(obsWidth, obsHeight), &obstacleTextures[distTexture(gen) + ObsVariants], IsChangingLine, difSettings.propSpeed, curLine, GetRandomObsPosition(direction)));
				}
				else
					obstacles.push_back(obstacle(Vector2f(GetRandomObsPosition(curLine), -obsHeight - 10), Vector2f(obsWidth, obsHeight), &obstacleTextures[distTexture(gen)], IsChangingLine, difSettings.propSpeed, curLine));

				spawnClock.restart();
				nextObsSpawnIn = spawnInterval + distIntervalOffset(gen);
			}
			else {
				spawnClock.restart();
				nextObsSpawnIn = spawnInterval + distIntervalOffset(gen);
			}
		}
		
	}

	// изменение чего-то с препятствиями каждый кадр
	for (auto& obs : obstacles) {
		obs.update(time, effects.GetSlowDownMultiplier());

		if (!obs.GetLineFreed() && obs.GetPos().y > 120) {
			laneMng.FreeLine(obs.GetLineIndex());
			obs.SetLineFreed();
		}
	}

	// удаление препятствий 
	obstacles.erase(
		remove_if(obstacles.begin(), obstacles.end(),
			[winHeight](const obstacle& obs) {
				return obs.IsOffScreen(winHeight);
			}), 
		obstacles.end()
	);
}

void obstacleManager::draw(RenderWindow& win) const {
	for (auto& obs : obstacles) {
		obs.draw(win);
	}
}

int obstacleManager::GetRandomObsPosition(int line){
	int spawnX = lanePositions[line] + distOffset(gen);
	if (spawnX < baseX - 10)
		spawnX = baseX - 10;
	if (spawnX > lanePositions[2] + 5)
		spawnX = lanePositions[2] + 5;
	return spawnX;
}

bool obstacleManager::checkCollisionsWithPlayer(const player& p) {
	for (const obstacle& obs : obstacles) {
		if (obs.GetBounds().intersects(p.GetBounds())) {
			return true;
		}
	}
	return false;
}

int obstacleManager::checkPlayerOvertakedObstacle(const player& p) {
	int count = 0;
	for (obstacle& obs : obstacles) {
		if (!obs.isCounted() && obs.GetPos().y > p.GetPos().y + p.GetSize().y) {
			obs.SetCounted();
			count++;
		}
	}
	return count;
}

void obstacleManager::checkPlayerNear(const player& p) {
	for (auto& obs : obstacles) {
		float distanceToPlayer = p.GetPos().y - (obs.GetPos().y + obs.GetBounds().getSize().y);
		if (obs.isChangingLine() && !obs.isStartedChange() && distanceToPlayer <= 340) {
			obs.StartChangeLine();
		}
	}
}

void obstacleManager::RemoveObstaclesTouched(const player& p) {
	obstacles.erase(
		remove_if(obstacles.begin(), obstacles.end(),
			[&p](const obstacle& obs) {
				return obs.GetBounds().intersects(p.GetBounds());
			}),
		obstacles.end()
	);
}

void obstacleManager::Reset() {
	obstacles.clear();
	spawnClock.restart();
}