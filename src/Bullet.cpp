#pragma once
#include "Bullet.h"

Bullet::Bullet(sf::Vector2f pos, float deg, int damage, bool team)
	: AirUnites(pos, team, damage), m_deg(deg) {}

void Bullet::move() {
	m_position.x = m_position.x + 4 * cos(m_deg * PI / 180) * (m_objectTeam ? 1 : -1);
	m_position.y = m_position.y + 4 * sin(m_deg * PI / 180) * (m_objectTeam ? 1 : -1);
}

bool Bullet::collied(std::list <std::shared_ptr <Fighter>>& enemies, const sf::Vector2f& floorPosition) {
	return AirUnites::collied(enemies, floorPosition);
}

void Bullet::draw(float delta) const {
	Window::instance().get_window()->draw(create(delta));
}

sf::Sprite Bullet::create(float) const {
	auto sprite = sf::Sprite(*Textures::instance().get_bullet());
	sprite.setPosition(m_position);
	sprite.setScale(0.5, 0.5);
	sf::FloatRect spriteRect = sprite.getLocalBounds();
	sprite.setOrigin(spriteRect.left + spriteRect.width / 2.0f,
		spriteRect.top + spriteRect.height / 2.0f);
	sprite.rotate(m_deg);
	if (WorldObject::get_object_team() == RIGHT_TEAM)
		sprite.scale(-1.f, 1.f);
	return sprite;
}