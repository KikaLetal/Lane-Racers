#include "obstacle.h"
#include <iostream>

obstacle::obstacle(sf::Vector2f startPos, sf::Vector2f size, const Texture* texturePtr, bool changeLine, float speed, int lineIndex, int newLine)
	: changeLine(changeLine), 
	  speed(speed),
	  lineIndex(lineIndex),
	  newLine(newLine)
{
	lineFreed = false;

	shape.setSize(sf::Vector2f(size.x, size.y));
	shape.setTexture(texturePtr);
	shape.setTextureRect(IntRect(0, 0, 21, 27));
	shape.setPosition(startPos);
}

obstacle::obstacle(sf::Vector2f startPos, sf::Vector2f size, const Texture* texturePtr, bool changeLine, float speed, int lineIndex)
	: changeLine(changeLine),
	  speed(speed),
	  lineIndex(lineIndex)
{
	lineFreed = false;

	shape.setSize(sf::Vector2f(size.x, size.y));
	shape.setTexture(texturePtr);
	shape.setPosition(startPos);
}

bool obstacle::IsOffScreen(int winHeight) const{
	if (shape.getPosition().y > winHeight)
		return true;
	return false;
}

bool obstacle::isCounted() const {
	return counted;
}

bool obstacle::isChangingLine() const {
	return changeLine;
}

bool obstacle::isStartedChange() const { return startChangeLine; }

void obstacle::StartChangeLine() {
	startChangeLine = true;
}

void obstacle::update(float time, float SlowDownMultiplier) {
	if (changeLine && AnimClock.getElapsedTime().asMilliseconds() >= 200) {
		AnimClock.restart();
		Frame += stepAnim;
		shape.setTextureRect(IntRect(0, ArrAnim[Frame], 21, 27));
		if (Frame == 0) stepAnim = 1;
		if (Frame == 1) stepAnim = -1;
	}
	if (changeLine && startChangeLine) {
		float maxStep = 1.5f;
		if (abs(newLine - shape.getPosition().x) <= maxStep * time) {
			changeLine = false;
			startChangeLine = false;
			shape.setPosition(newLine, shape.getPosition().y);
			shape.setTextureRect(IntRect(0, ArrAnim[1], 21, 27));
		}
		float dx = (newLine - shape.getPosition().x > 0) ? maxStep : -maxStep;
		shape.move(dx * time * SlowDownMultiplier, speed * time * SlowDownMultiplier);
	}
	else
	{
		shape.move(0, speed * time * SlowDownMultiplier);
	}
}

sf::Vector2f obstacle::GetPos() const {
	return shape.getPosition();
}

sf::FloatRect obstacle::GetBounds() const {
	FloatRect fullbounds = shape.getGlobalBounds();
	return FloatRect(
		fullbounds.left,
		fullbounds.top,
		fullbounds.width - 17,
		fullbounds.height
	);
}

int obstacle::GetLineIndex() const {
	return lineIndex;
}

bool obstacle::GetLineFreed() const {
	return lineFreed;
}

void obstacle::draw(RenderWindow& win) const {
	win.draw(shape);
}

void obstacle::SetCounted() {
	counted = true;
}

void obstacle::SetLineFreed() {
	lineFreed = true;
}
