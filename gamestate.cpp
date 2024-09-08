#include "gamestate.h"
#include "sgg/graphics.h"
#include "level.h"
#include "player.h"
#include <thread>
#include <chrono>
#include "Enemy.h"
#include "LifeBoost.h"

using namespace std::chrono_literals;

// Constructor for the GameState class
GameState::GameState()
{
}


void GameState::init()
{
	// Create a new Level and initialize it
	m_current_level = new Level();
	m_current_level->init();
	// Create a new Player and initialize it
	m_player = new Player("Player");
	m_player->init();
	// Create a new Enemy and initialize it
	mouse = new Enemy("Enemy");
	mouse->init();
	// Create a new LifeBoost  and initialize it
	m_baguette = new LifeBoost("Baguette");
	m_baguette->init();

	graphics::preloadBitmaps(getAssetDir());
}

void GameState::draw()
{

	if (!m_current_level)
		return;

	m_current_level->draw();
}

void GameState::update(float dt)
{
	// Skip an update if a long delay is detected to avoid messing up collision simulation
	if (dt > 500) //ms
		return;

	float sleep_time = std::max(0.0f, 17.0f - dt);
	
	std::this_thread::sleep_for(std::chrono::duration<float, std::milli>(sleep_time));
	
	if (!m_current_level)
		return;
	
	m_current_level->update(dt);
	
	m_debugging = graphics::getKeyState(graphics::SCANCODE_0);
}

GameState* GameState::getInstance()
{
	// Check if the unique instance is not created yet
	if (m_unique_instance == nullptr)
		// Create a new instance of the GameState class
		m_unique_instance = new GameState();
	// Return the unique instance of the GameState class
	return m_unique_instance;
}

// Destructor for the GameState class
GameState::~GameState()
{

	if (m_player)
		delete m_player;

	if (m_current_level)
		delete m_current_level;
}

std::string GameState::getAssetDir()
{
	return m_asset_path;
}


std::string GameState::getFullAssetPath(const std::string& asset)
{
	return m_asset_path + asset;
}


GameState* GameState::m_unique_instance = nullptr;