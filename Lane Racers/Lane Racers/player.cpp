#include "player.h"
#include <iostream>

player::player(sf::Vector2f startPos, sf::Vector2f size, int WorkPlaceSize, bonusesEffectsContext& effects, float speed) 
	: speed(speed), 
	  WorkPlaceSize(WorkPlaceSize),
	  effects(effects)
{
	if (!texture.loadFromFile("Image/player.png")) {
		std::cerr << "SFML не смог загрузить иконку из файла!\n";
	}

	shape.setSize(sf::Vector2f(size.x, size.y));
	shape.setTexture(&texture);
	shape.setPosition(startPos);
	velocity = sf::Vector2f(0.f, 0.f);
}

void player::handleInput(float time) {
	velocity.x = 0;
	if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left))
		velocity.x = -speed * time;
	if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right))
		velocity.x = speed * time;
}

void player::update(float time, float winWidth){
	if (CanMove)
		shape.move(velocity);
	sf::Vector2f pos = shape.getPosition();
	int border = 60;

	if (pos.x < ((winWidth - WorkPlaceSize)/2) + border + 5)
		shape.setPosition(((winWidth - WorkPlaceSize) / 2) + border + 5, pos.y);

	if (pos.x > (((winWidth - WorkPlaceSize) / 2) + WorkPlaceSize) - shape.getSize().x - border)
		shape.setPosition((((winWidth - WorkPlaceSize) / 2) + WorkPlaceSize) - shape.getSize().x - border, pos.y);
}

void player::draw(RenderWindow& win) const {
	win.draw(shape);
}

sf::FloatRect player::GetBounds() const {
	FloatRect fullbounds = shape.getGlobalBounds();
	return FloatRect(
		fullbounds.left,
		fullbounds.top,
		fullbounds.width - 17,
		fullbounds.height
		);
}

int player::GetScore() const {
	return score;
}

sf::Vector2f player::GetSize() const {
	return shape.getSize();
}

sf::Vector2f player::GetPos() const {
	return shape.getPosition();
}

bool player::IsCanMove() const {
	return CanMove;
}

void player::AddScore(int value){
	if (effects.IsDoubleScoreActive())
		score += value * 2;
	else
		score += value;
}

void player::ChangeMovePosible(bool state) {
	CanMove = state;
}

void player::Reset(Vector2f StartPos) {
	shape.setPosition(StartPos);
	CanMove = true;
	score = 0;
}
