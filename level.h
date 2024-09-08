#pragma once
#include "gameobject.h"
#include "sgg/graphics.h"
#include <list>
#include <vector>
#include <string>
#include "player.h"
#include "Enemy.h"
#include "LifeBoost.h"

class Level : public GameObject {
	graphics::Brush m_brush_background; // Background brush for the level

	float m_center_x = 5.0f; // X-coordinate of the level center
	float m_center_y = 5.0f; // Y-coordinate of the level center
	float m_backgroundOffset = 0.0f; // Offset for background scrolling
	float m_scrollSpeed = 50.0f; // Speed at which the background scrolls
	// Enumeration for different status states of the level
	typedef enum { STATUS_START, STATUS_PLAYING, STATUS_RULES, STATUS_DONE } status_t;

	std::vector<GameObject*> m_static_objects; // Collection of static game objects
	std::list<GameObject*> m_dynamic_objects; // Collection of dynamic game objects

	std::vector<Box> m_blocks; // Collection of block objects
	std::vector<std::string> m_block_names; // Names of block textures
	const float m_block_size = 1.0f; // Size of each block
	graphics::Brush m_block_brush; // Brush for drawing blocks
	graphics::Brush m_block_brush_debug; // Brush for debug outlines of blocks


	graphics::Brush m_lifeBoost_brush; // Brush for drawing life boosts
	const float m_lifeBoost_size = 1.0f; // Size of each life boost

	class Enemy* mouse = nullptr; // Pointer to an enemy object
	class LifeBoost* baguette = nullptr; // Pointer to a life boost object

	status_t status = STATUS_START; // Current status state of the level

	// Private methods for managing game objects and screens
	void spawnMouse();
	void generateLifeBoosts();
	void generateNewBlocks();
	void drawBlock(int i);
	void checkCollisions();
	// Private methods for updating different screens and states
	void updateStartScreen();
	void updateLevelScreen(float dt);
	void updateEndScreen();
	void updateRulesScreen();
	// Private methods for drawing different screens
	void drawStartScreen();
	void drawLevelScreen();
	void drawEndScreen();
	void drawRulesScreen();
	// Private methods for handling collisions with enemies and life boosts
	bool mouseColl();    // Check collision between player and enemy
	bool boostColl();  // Check collision between player and life boost
	// Private method for checking the need to remove an enemy
	void checkMeteorite();
	// Private method for drawing the player's life bar
	void drawBarLife();
public:
	// Public methods overridden from the base class
	void update(float dt) override; // Update method for the level
	void init() override; // Initialization method for the level
	void draw() override; // Draw method for the level
	// Public variables related to the level layout
	int k = 0;     // Variable 'k' used in the level layout
	int j = 0;     // Variable 'j' used in the level layout
	int p = 0.0;   // Variable 'p' used in the level layout
	float t = -6.0f;  // Variable 't' used in the level layout
	float y = 0.0f;   // Variable 'y' used in the level layout
	// Constructor for the Level class
	Level(const std::string& name = "Level0");
	// Destructor for the Level class
	~Level() override;
};