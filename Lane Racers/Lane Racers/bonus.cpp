#include "bonus.h"
#include <iostream>

bonus::bonus(sf::Vector2f startPos, sf::Vector2f size, const Texture* texturePtr, BonusType type, int lineIndex, float speed)
	: speed(speed),
	  lineIndex(lineIndex),
	  type(type)
{
	lineFreed = false;
	unbanedLineForChange = false;

	shape.setSize(sf::Vector2f(size.x, size.y));
	shape.setTexture(texturePtr);
	shape.setPosition(startPos);
}

bool bonus::IsOffScreen(int winHeight) const {
	if (shape.getPosition().y > winHeight)
		return true;
	return false;
}

void bonus::update(float time, float SlowDownMultiplier) {
	shape.move(0, speed * time * SlowDownMultiplier);
}

sf::Vector2f bonus::GetPos() const {
	return shape.getPosition();
}

BonusType bonus::GetBonus() const {
	return type;
}

sf::FloatRect bonus::GetBounds() const {
	FloatRect fullbounds = shape.getGlobalBounds();
	return FloatRect(
		fullbounds.left,
		fullbounds.top,
		fullbounds.width,
		fullbounds.height-10
	);
}

int bonus::GetLineIndex() const{
	return lineIndex;
}

bool bonus::GetLineFreed() const{
	return lineFreed;
}

bool bonus::GetUnbanedLineForChange() const {
	return unbanedLineForChange;
}

void bonus::SetLineFreed(){
	lineFreed = true;
}

void bonus::SetUnbanedLineForChange() {
	unbanedLineForChange = true;
}

void bonus::draw(RenderWindow& win) const {
	win.draw(shape);
}
