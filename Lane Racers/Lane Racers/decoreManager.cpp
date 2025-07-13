#include "decoreManager.h"

decoreManager::decoreManager(float baseX, float laneWidth)
	: baseX(baseX),
	  laneWidth(laneWidth),
	  gen(random_device{}()),
	  distTexture(0, 3),
	  distLine(0, 2),
	  distOffset(-30, 30),
	  distIntervalOffset(-0.2f, 0.2f)
{
	for (int i = 1; i <= 4; i++) {
		Texture T;
		if (!T.loadFromFile("Image/decor" + to_string(i) + ".png")) {
			cerr << "SFML не смог загрузить иконку из файла!\n";
		}
		decorTextures.push_back(move(T));
	}
}

void decoreManager::update(float time, float winHeight, DifficultySettings difSettings){
	if (spawnClock.getElapsedTime().asSeconds() >= nextObsSpawnIn) {
		int curLine = distLine(gen);
		Sprite sp;
		sp.setTexture(decorTextures[distTexture(gen)]);
		sp.setScale(Vector2f(5.f, 5.f));
		sp.setPosition(Vector2f(GetRandomObsPosition(curLine), -sp.getGlobalBounds().getSize().y - 10));
		decores.push_back(sp);
		spawnClock.restart();
		nextObsSpawnIn = ObsSpawnIn + distIntervalOffset(gen);
	}

	// изменение чего-то с препятствиями каждый кадр
	for (auto& dec : decores) {
		dec.move(0, time * difSettings.roadSpeedMult);
	}

	// удаление препятствий 
	decores.erase(
		remove_if(decores.begin(), decores.end(),
			[winHeight](const Sprite& dec) {
				return dec.getPosition().y > winHeight;
			}),
		decores.end()
	);
}

void decoreManager::draw(RenderWindow& win) const{
	for (auto& dec : decores) {
		win.draw(dec);
	}
}

int decoreManager::GetRandomObsPosition(int line) {
	int spawnX = lanePositions[line] + distOffset(gen);
	if (spawnX < baseX - 10)
		spawnX = baseX - 10;
	if (spawnX > lanePositions[2] + 5)
		spawnX = lanePositions[2] + 5;
	return spawnX;
}

void decoreManager::Reset(){
	decores.clear();
}
