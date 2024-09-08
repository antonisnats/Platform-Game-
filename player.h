#pragma once

#include "gameobject.h"
#include "box.h"
#include "sgg/graphics.h"

// Player class derived from GameObject and Box, representing the game's player character
class Player : public GameObject, public Box {
	graphics::Brush m_brush_player; // Brush for rendering the player
	std::vector<std::string> m_sprites; // Vector to store default player sprites
	std::vector<std::string> m_spritesRight; // Vector to store right-facing player sprites
	std::vector<std::string> m_spritesLeft; // Vector to store left-facing player sprites

	const float m_gravity = 10.0f; // Gravity affecting the player's vertical movement
	const float m_accel_vertical = 7.0f; // Vertical acceleration of the player
	const float m_accel_horizontal = 40.0f; // Horizontal acceleration of the player
	const float m_max_velocity = 10.0f; // Maximum velocity of the player
	float life = 1.0f; // Player's life status
	// Function to handle player movement based on user input
	void movePlayer(float dt);
public:
	float m_vx = 0.0f; // Horizontal velocity of the player
	float m_vy = 0.0f; // Vertical velocity of the player
	// Constructor for the Player class, inheriting from GameObject, takes a name parameter
	Player(std::string name) : GameObject(name) {}
	// Override update function to handle player-specific updates
	void update(float dt) override;
	// Override init function for player-specific initialization
	void init() override;
	// Override draw function for rendering the player
	void draw() override;
	// Get the X-coordinate of the player's position
	float getPosX() { return m_pos_x; }
	// Get the Y-coordinate of the player's position
	float getPosY() { return m_pos_y; }
	// Get the collision hull (Disk) of the player
	Disk getCollisionHull() const;
	// Get the remaining life of the player
	float getRemainingLife() const { return life; };
	// Decrease the player's life by a specified amount, ensuring it doesn't go below 0
	void drainLife(float amount) { life = std::max<float>(0.0f, life - amount); }
	// Increase the player's life by a specified amount, ensuring it doesn't exceed 1
	void increaseLife(float amount) { life = std::min<float>(1.0f, life + amount); }
protected:
	// Function to draw debug information related to the player
	void debugDraw();
};