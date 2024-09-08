#include "Enemy.h"
#include "util.h"
#include "gamestate.h"
#include "level.h"
#include "sgg/graphics.h"
#include <random>

void Enemy::update()
{
	// Move the enemy to the left based on its speed and elapsed time
	pos_x -= speed * graphics::getDeltaTime();
	// Check if the enemy is off the screen, deactivate it if true
	if (pos_x < -size) {
		active = false;
	}
}

void Enemy::draw()
{
	// Set the texture and fill opacity for drawing the enemy
	brush.texture = std::string(m_state->getFullAssetPath("mouse.png"));
	brush.fill_opacity = 1.0f;

	graphics::drawRect(pos_x, pos_y, size, size, brush);
	graphics::resetPose();
}

void Enemy::init()
{
	speed = 0.001f; 
	pos_x = 12.0f + 1.1f * rand() / (float)RAND_MAX; 
	pos_y = 4.0f * rand() / (float)RAND_MAX; 
	size = 1.0f; 
	brush.outline_opacity = 0.0f; 
}

Enemy::Enemy(const std::string& name)
	:GameObject(name) 
{
	init(); 
}

// Destructor for the Enemy class
Enemy::~Enemy()
{
}

Disk Enemy::getCollisionHull() const
{
	// Get the collision hull for the enemy
	Disk disk;
	disk.cx = pos_x; 
	disk.cy = pos_y; 
	disk.radius = size * 0.5f; 
	return disk; 
}