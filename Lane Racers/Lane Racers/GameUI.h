#pragma once
#include <SFML/Graphics.hpp>
#include "bonusesEffectsContext.h"
#include "Utils.h"
using namespace sf;
using namespace std;

class GameUI
{
private:
	Vector2f WinSize;
	Font font;
	Text Textscore;
	Text TextDefeat;
	bool GameOver = false;
	vector<bonusesEffectsContext::ActiveBonusInfo> ActiveEffects;
	map<BonusType, Texture> EffectsTextures;
public:
	GameUI(Vector2f win);
	void update(int score, vector<bonusesEffectsContext::ActiveBonusInfo> ActiveEffects);
	void SetGameOver();
	void draw(RenderWindow& win);
	void Reset();
};

