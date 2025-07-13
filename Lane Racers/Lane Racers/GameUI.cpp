#include "GameUI.h"

GameUI::GameUI(Vector2f win){
	WinSize = Vector2f(win.x, win.y);

	EffectsTextures[BonusType::ShieldBoost].loadFromFile("Image/effect1.png");
	EffectsTextures[BonusType::SlowBoost].loadFromFile("Image/effect2.png");
	EffectsTextures[BonusType::ScoreBoost].loadFromFile("Image/effect3.png");

	font.loadFromFile("Font/Ubuntu-Bold.ttf");
	Textscore.setCharacterSize(30);
	Textscore.setFont(font);
	Textscore.setPosition(30, 30);

    TextDefeat.setCharacterSize(50);
    TextDefeat.setFont(font);
    TextDefeat.setFillColor(Color::Red);
    TextDefeat.setString("Press Enter to restart");
    TextDefeat.setOrigin(TextDefeat.getGlobalBounds().width / 2, TextDefeat.getGlobalBounds().height / 2);
    TextDefeat.setPosition(win.x / 2, win.y / 2);
}

void GameUI::update(int score, vector<bonusesEffectsContext::ActiveBonusInfo> ActiveEffects){
	Textscore.setString("Score: " + to_string(score));
	GameUI::ActiveEffects = ActiveEffects;
}

void GameUI::SetGameOver() {
	GameOver = true;
}

void GameUI::draw(RenderWindow& win){
	win.draw(Textscore);

	float startX = 30.f;
	float startY = 70.f;
	float offsetY = 40.f;

	if (ActiveEffects.size() != 0) {
		for (size_t i = 0; i < ActiveEffects.size(); i++) {
			const auto& effect = ActiveEffects[i];

			Sprite icon;
			icon.setTexture(EffectsTextures[effect.type]);
			icon.setScale(Vector2f(2, 2));
			icon.setPosition(startX, startY + offsetY * i);
			win.draw(icon);

			Text TextTimer;
			TextTimer.setFont(font);
			TextTimer.setCharacterSize(24);
			TextTimer.setFillColor(Color::Cyan);
			TextTimer.setPosition(startX + icon.getGlobalBounds().width + 10, startY + (icon.getGlobalBounds().height/2 - TextTimer.getCharacterSize()/2) + offsetY * i);
			TextTimer.setString(to_string_with_precision(effect.timeLeft) + " c");

			win.draw(TextTimer);
		}
	}

	if (GameOver) {
		RectangleShape overlay(WinSize);
		overlay.setFillColor(Color(0, 0, 0, 150));
		win.draw(overlay);
		win.draw(TextDefeat);
	}
}

void GameUI::Reset() {
	GameOver = false;
}

