#pragma once
#include <string>
#include "sgg/graphics.h"
#include "Enemy.h"
#include "LifeBoost.h"

// Class representing the game state
class GameState {
	std::string m_asset_path = "assets\\"; // Path to game assets

	float m_canvas_width = 8.0f; // Width of the game canvas
	float m_canvas_height = 6.0f; // Height of the game canvas

	static GameState* m_unique_instance;  // Unique instance of the game state

	GameState(); // Private constructor to enforce singleton pattern
	class Player* m_player = 0; // Pointer to the player object
	class Level* m_current_level = 0; // Pointer to the current game level
	class Enemy* mouse = nullptr; // Pointer to the enemy object
	class LifeBoost* m_baguette = nullptr; // Pointer to the life boost object
public:
	float m_global_offset_x = 0.0f; // Global offset in the x-axis
	float m_global_offset_y = 0.0f; // Global offset in the y-axis
	bool m_debugging = false; // Debugging flag

	// Initialize the game state
	void init();
	// Draw the game state
	void draw();
	// Update the game state based on the time elapsed
	void update(float dt);
	// Get the singleton instance of the GameState
	static GameState* getInstance();
	// Destructor for cleaning up resources
	~GameState();  //distractor

	// Get the width of the game canvas
	float getCanvasWidth() { return m_canvas_width; };
	// Get the height of the game canvas
	float getCanvasHeight() { return m_canvas_height; };

	// Get the asset directory path
	std::string getAssetDir();
	// Get the full path to a specific asset
	std::string getFullAssetPath(const std::string& asset);
	// Get a pointer to the player object
	class Player* getPlayer() { return m_player; }
};
