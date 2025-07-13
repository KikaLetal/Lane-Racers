#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "bonusType.h"
using namespace std;
using namespace sf;
class bonus
{
private:
	RectangleShape shape;
	const Texture* texture;
	float speed;
	BonusType type;
	int lineIndex;
	bool lineFreed;
	bool unbanedLineForChange;

public:
	bonus(sf::Vector2f startPos, sf::Vector2f size, const Texture* texturePtr, BonusType type, int lineIndex, float speed);

	void update(float time, float SlowDownMultiplier);
	void draw(RenderWindow& win) const;

	bool IsOffScreen(int winHeight) const;

	sf::Vector2f GetPos() const;
	BonusType GetBonus() const;
	sf::FloatRect GetBounds() const;
	int GetLineIndex() const;
	bool GetLineFreed() const;
	bool GetUnbanedLineForChange() const;

	void SetLineFreed();
	void SetUnbanedLineForChange();
};
