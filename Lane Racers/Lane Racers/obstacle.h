#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;
using namespace sf;
class obstacle
{
private:
	RectangleShape shape;
	const Texture* texture;
	float speed;
	bool counted = false;
	bool changeLine;
	bool startChangeLine = false;
	float newLine;
	int lineIndex;
	bool lineFreed;
	Clock AnimClock;
	int ArrAnim[2]{ 0, 27};
	int Frame = 0;
	int stepAnim = 1;

public:
	obstacle(sf::Vector2f startPos, sf::Vector2f size, const Texture* texturePtr, bool changeLine, float speed, int lineIndex, int newLine);
	obstacle(sf::Vector2f startPos, sf::Vector2f size, const Texture* texturePtr, bool changeLine, float speed, int lineIndex);

	void update(float time, float SlowDownMultiplier);
	void draw(RenderWindow& win) const;

	bool IsOffScreen(int winHeight) const;
	bool isCounted() const;
	bool isChangingLine() const;
	bool isStartedChange() const;

	void StartChangeLine();

	sf::Vector2f GetPos() const;
	sf::FloatRect GetBounds() const;
	int GetLineIndex() const;
	bool GetLineFreed() const;

	void SetCounted();
	void SetLineFreed();
};

