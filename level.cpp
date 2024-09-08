#include "level.h"
#include "gamestate.h"
#include "player.h"
#include "util.h"
#include"LifeBoost.h"
#include <cstdlib>

void Level::drawBlock(int i)
{
	
	Box& box = m_blocks[i];
	float x = box.m_pos_x + m_state->m_global_offset_x;
	float y = box.m_pos_y + m_state->m_global_offset_y;
	
	m_block_brush.texture = m_state->getFullAssetPath(m_block_names[i]);
	
	graphics::drawRect(x, y, box.m_width, box.m_height, m_block_brush);
	
	if (m_state->m_debugging) {
		graphics::drawRect(x, y, box.m_width, box.m_height, m_block_brush_debug);
	}
}


void Level::generateLifeBoosts() // Generate life boosts based on player's position
{
	// Initialize a LifeBoost if not already present
	if (!baguette) {
		baguette = new LifeBoost();
		baguette->init();
	}

	// Check if the player's vertical position is below a certain threshold for generating a life boost
	if (m_state->getPlayer()->m_pos_y < t) {
		p -= 6.5;
		
		int randomValue = 1 + rand() % 12;

		// Update and draw the life boost at a specific position
		baguette->update(randomValue, p);
		baguette->draw();

		// Adjust the threshold for the next life boost
		t -= 6;
	}
}


void Level::generateNewBlocks()
{
	// Check if the player's vertical position requires generating new blocks
	if (m_state->getPlayer()->m_pos_y < j + 3.0f) {

		int h = j;
		for (j; j >= h - 5; j--) {
			m_blocks.push_back(Box(0, j, m_block_size, m_block_size));
			m_block_names.push_back("brickwall.png");
		}
		y -= 2.3f;
		// Generate blocks in a staggered pattern
		for (k = 1; k < 15; k++) {
			if (k != 12 && k != 13) {
				m_blocks.push_back(Box(k, y, m_block_size, m_block_size));
				m_block_names.push_back("brickwall.png");
			}
		}
		y -= 2.3f;
		// Generate blocks in a staggered pattern
		for (k = 1; k < 15; k++) {
			if (k != 5 && k != 6) {
				m_blocks.push_back(Box(k, y, m_block_size, m_block_size));
				m_block_names.push_back("brickwall.png");
			}
		}
		y -= 2.3f;
		// Generate blocks in a staggered pattern
		for (k = 1; k < 15; k++) {
			if (k != 2 && k != 3) {
				m_blocks.push_back(Box(k, y, m_block_size, m_block_size));
				m_block_names.push_back("brickwall.png");
			}
		}
		int g = h;
		for (h; h >= g - 5; h--) {
			m_blocks.push_back(Box(15, h, m_block_size, m_block_size));
			m_block_names.push_back("brickwall.png");
		}
		// Draw the generated blocks
		for (int i = m_blocks.size() - (k - 1) * 3 + (h - 1) * 2; i < m_blocks.size(); i++)
		{
			drawBlock(i);
		}
	}
}


void Level::spawnMouse() // Spawn an enemy 
{
	// Check if an enemy does not exist
	if (!mouse) {
	
		mouse = new Enemy();
		
		mouse->init();
	}
}


void Level::checkCollisions() // Check collisions between the player and blocks
{
	// Check and handle collisions for player's vertical movement
	for (auto& box : m_blocks)
	{
		float offset = 0.0f;

		// Check if there is a collision below the player
		if (offset = m_state->getPlayer()->intersectDown(box))
		{
			m_state->getPlayer()->m_pos_y += offset; 
			m_state->getPlayer()->m_vy = 0.0f; 
			
			if (m_state->getPlayer()->m_vy > 1.0f)
				graphics::playSound(m_state->getFullAssetPath(""), 0.5f);
			break;
		}
	}
	// Check and handle collisions for player's horizontal movement
	for (auto& box : m_blocks)
	{
		float offset = 0.0f;

		// Check if there is a collision sideways with the player
		if (offset = m_state->getPlayer()->intersectSideways(box))
		{
			m_state->getPlayer()->m_pos_x += offset; 
			m_state->getPlayer()->m_vx = 0.0f; 
			break; 
		}
	}
	// Check and handle collisions for player's upward movement
	for (auto& box : m_blocks)
	{
		float offset = 0.0f;

		// Check if there is a collision above the player
		if (offset = m_state->getPlayer()->intersectUp(box))
		{
			m_state->getPlayer()->m_pos_y -= offset; 
			m_state->getPlayer()->m_vy = 0.0f; 
			break; 
		}
	}

	// Ensure player does not go beyond the left boundary of the canvas
	float canvasLeft = m_state->getCanvasWidth() - m_state->getCanvasWidth();
	if (m_state->getPlayer()->m_pos_x < canvasLeft) {
		m_state->getPlayer()->m_pos_x = canvasLeft; 
		m_state->getPlayer()->m_vx = 0.0f;
	}
}


void Level::updateStartScreen()
{
	
	if (graphics::getKeyState(graphics::SCANCODE_RETURN)) {
		status = STATUS_PLAYING; // Change the status to STATUS_PLAYING when 'RETURN' key is pressed
		return;
	}
	
	if (graphics::getKeyState(graphics::SCANCODE_H)) {
		status = STATUS_RULES; // Change the status to STATUS_RULES when 'H' key is pressed
		return;
	}
}


void Level::updateLevelScreen(float dt)
{
	
	if (m_state->getPlayer()->isActive()) {
		m_state->getPlayer()->update(dt);
	}
	
	checkMeteorite();
	spawnMouse();

	
	if (mouse) {
		mouse->update();
	}
	
	checkCollisions();
	
	if (mouseColl()) {
		delete mouse;
		mouse = nullptr;
	}
	
	if (boostColl()) {
		delete baguette;
		baguette = nullptr;
	}
	
	if (m_state->getPlayer()) {
		m_state->getPlayer()->getRemainingLife();
	}
	
	if (m_state->getPlayer()) {
		if (m_state->getPlayer()->getRemainingLife() <= 0.0f) {
			status = STATUS_DONE;  // Change the status to STATUS_DONE when player's life runs out
			return;
		}
	}
	
	generateLifeBoosts();
	generateNewBlocks();
	GameObject::update(dt);
}


void Level::updateEndScreen()
{
	
	if (graphics::getKeyState(graphics::SCANCODE_R)) {
		status = STATUS_START; // Change the status to STATUS_START when R key is pressed
		GameState::getInstance()->init();
		return;
	}
}


void Level::updateRulesScreen()
{
	
	if (graphics::getKeyState(graphics::SCANCODE_H)) {
		status = STATUS_RULES; // Change the status to STATUS_RULES when H key is pressed
		return;
	}
	
	if (graphics::getKeyState(graphics::SCANCODE_B)) {
		status = STATUS_START; // Change the status to STATUS_START when B key is pressed
		return;
	}
}


void Level::drawStartScreen()
{
	
	graphics::Brush br;
	
	br.outline_opacity = 0.0f;
	br.texture = m_state->getFullAssetPath("background_start.png");
	
	graphics::drawRect(m_state->getCanvasWidth() / 2, m_state->getCanvasHeight() / 2, m_state->getCanvasWidth(), m_state->getCanvasHeight(), br);
}


void Level::drawLevelScreen()
{
	
	graphics::Brush br;

	float w = m_state->getCanvasWidth();
	float h = m_state->getCanvasHeight();
	
	float offset_x = m_state->m_global_offset_x / 2.0f + w / 2.0f;
	float offset_y = m_state->m_global_offset_y / 2.0f + h / 2.0f;
	
	graphics::drawRect(w / 2.0f, h / 2.0f, w, w, m_brush_background);

	// Draw the player if active
	if (m_state->getPlayer()->isActive())
		m_state->getPlayer()->draw();
	
	// Draw the baguette if present 
	if (baguette) {
		baguette->draw();
	}

	// Draw the blocks
	for (int i = 0; i < m_blocks.size(); i++)
	{
		drawBlock(i);
	}

	// Draw the enemy if present
	if (mouse) {
		mouse->draw();
	}

	// Draw the player's life bar
	drawBarLife();

	// Draw static game objects
	for (auto p_gob : m_static_objects)
		if (p_gob) p_gob->draw();

	// Draw dynamic game objects
	for (auto p_gob : m_dynamic_objects)
		if (p_gob) p_gob->draw();
}


void Level::drawEndScreen()
{
	
	graphics::Brush br1;
	
	br1.outline_opacity = 0.0f;
	br1.texture = m_state->getFullAssetPath("game_over.png");
	
	graphics::drawRect(m_state->getCanvasWidth(), m_state->getCanvasHeight() , m_state->getCanvasWidth() , m_state->getCanvasHeight() , br1);
}


void Level::drawRulesScreen()
{
	
	graphics::Brush br;
	
	br.outline_opacity = 0.0f;
	br.texture = m_state->getFullAssetPath("background_rules.png");
	
	graphics::drawRect(m_state->getCanvasWidth() / 2, m_state->getCanvasHeight() / 2, m_state->getCanvasWidth(), m_state->getCanvasHeight(), br);
}


void Level::init()
{
	
	m_brush_background.outline_opacity = 0.0f;
	m_brush_background.texture = m_state->getFullAssetPath("background.png");
	
	// Initialize static game objects
	for (auto p_gob : m_static_objects)
		if (p_gob) p_gob->init();
	
	// Initialize dynamic game objects
	for (auto p_gob : m_dynamic_objects)
		if (p_gob) p_gob->init();
	
	// Create and initialize baguette
	baguette = new LifeBoost();
	baguette->init();
	
	// Set initial values for positioning and block generation
	y = 1.5f;
	for (j = 0; j <= 5; j++) {
		m_blocks.push_back(Box(0, j, m_block_size, m_block_size));
		m_block_names.push_back("brickwall.png");
	}
	for (k = 0; k <= 15; k++) {
		if (k != 12 && k != 13) {
			m_blocks.push_back(Box(k, y, m_block_size, m_block_size));
			m_block_names.push_back("brickwall.png");
		}
		m_blocks.push_back(Box(k, j, m_block_size, m_block_size));
		m_block_names.push_back("brickwall.png");
		if (k != 5 && k != 6) {
			m_blocks.push_back(Box(k, y + 2.3, m_block_size, m_block_size));
			m_block_names.push_back("brickwall.png");
		}
	}

	// Generate blocks in a specific pattern
	for (j = 5; j >= 0; j--) {
		m_blocks.push_back(Box(k - 1, j, m_block_size, m_block_size));
		m_block_names.push_back("brickwall.png");
	}

	// Set initial position for baguette
	p = -2.5f;

	
	m_block_brush.outline_opacity = 0.0f;
	m_block_brush_debug.fill_opacity = 0.1f;
	SETCOLOR(m_block_brush_debug.fill_color, 0.2f, 1.0f, 0.1f);
	SETCOLOR(m_block_brush_debug.outline_color, 0.3f, 1.0f, 0.2f);

	// Play background music with a specific volume
	graphics::playSound(m_state->getFullAssetPath("backgroundMusic.mp3"), 0.3f);
}


void Level::draw()
{
	

	// If the game is in the start state
	if (status == STATUS_START) {
		drawStartScreen(); // Calls the specific method for drawing the start state screen
		return; 
	}

	// If the game is in the done state
	if (status == STATUS_DONE) {
		drawEndScreen(); // Calls the specific method for drawing the end state screen
		return; 
	}

	// If the game is in the rules state
	if (status == STATUS_RULES) {
		drawRulesScreen(); // Calls the specific method for drawing the rules state screen
		return;
	}

	// If none of the above states, assume it's the playing state
	else {
		drawLevelScreen(); // Calls the specific method for drawing the playing state screen
		return;  
	}
}


void Level::drawBarLife() {

	
	graphics::Brush br;
	
	float player_life = m_state->getPlayer() ? m_state->getPlayer()->getRemainingLife() : 0.0f;
	
	br.outline_opacity = 0.0f;
	br.fill_color[0] = 1.0f; 
	br.fill_color[1] = 0.2f; 
	br.fill_color[2] = 0.2f; 
	br.texture = ""; 
	br.fill_secondary_color[0] = 1.0f * (1.0f - player_life) + player_life * 0.2f; 
	br.fill_secondary_color[1] = 0.2f; 
	br.fill_secondary_color[2] = 0.2 * (1.0f - player_life) + player_life * 1.0f;
	br.gradient = true; 
	br.gradient_dir_u = 1.0f; 
	br.gradient_dir_v = 0.0f; 
	
	graphics::drawRect(6.9 - ((1.0f - player_life) * 2 / 2), 0.28, player_life * 2, 0.5, br);
	
	br.outline_opacity = 1.0f; 
	br.gradient = false; 
	br.fill_opacity = 0.0f; 
	
	graphics::drawRect(6.9, 0.28, 2, 0.5, br);
}


bool Level::mouseColl() // Check collision between player and enemy
{
	// Check if the player or enemy object is not present
	if (!m_state->getPlayer() || !mouse) {
		return false;
	}

	// Retrieve collision hulls for player and enemy
	Disk d1 = m_state->getPlayer()->getCollisionHull();
	Disk d2 = mouse->getCollisionHull();

	// Calculate the vector difference between the centers of the collision hulls
	float dx = d1.cx - d2.cy;
	float dy = d2.cx - d2.cy;

	
	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {

		// If collision occurs, drain player's life by a certain amount and return true
		m_state->getPlayer()->drainLife(0.1f);
		return true;
	}
	else {
		
		return false;
	}
}


void Level::update(float dt)
{
	// If the game is in the start state
	if (status == STATUS_START) {
		updateStartScreen(); // Calls the specific method for updating the start state screen
		return; 
	}

	// If the game is in the done state
	if (status == STATUS_DONE) {
		updateEndScreen(); // Calls the specific method for updating the end state screen
		return; 
	}

	// If the game is in the rules state
	if (status == STATUS_RULES) {
		updateRulesScreen(); // Calls the specific method for updating the rules state screen
		return; 
	}

	// If none of the above states, assume it's the playing state
	else {
		updateLevelScreen(dt); // Calls the specific method for updating the playing state screen
		return; 
	}
}


bool Level::boostColl() // Check collision between player and baguette
{
	// Check if the player or life boost object is not present
	if (!m_state->getPlayer() || !baguette) {
		return false;
	}
	// Retrieve collision hulls for player and life boost
	Disk d1 = m_state->getPlayer()->getCollisionHull();
	Disk d2 = baguette->getCollisionBoost();

	// Calculate the vector difference between the centers of the collision hulls
	float dx = d1.cx - d2.cy;
	float dy = d2.cx - d2.cy;
	

	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {
		// Increase player's life and return true to indicate successful collision
		m_state->getPlayer()->increaseLife(0.1f);
		return true;
	}
	else {
		
		return false;
	}
}


void Level::checkMeteorite() // Check if the enemy needs to be removed
{
	// Check if the enemy object is not present
	if (mouse == nullptr) {
		return;
	}

	// Check if the enemy is no longer active
	if (!mouse->isActive()) {
		delete mouse;
		mouse = nullptr;
	}
}

// Constructor of the level class
Level::Level(const std::string& name)
{
	
	m_brush_background.outline_opacity = 0.0f;
	m_brush_background.texture = m_state->getFullAssetPath("background.png");

	// Set the initial status of the level to start
	status = STATUS_START;
}

// Destructor for the Level class
Level::~Level()
{
	
	if (mouse) {
		delete mouse;
		mouse = nullptr;
	}
	
	for (auto p_gob : m_static_objects)
		if (p_gob) delete p_gob;
	
	for (auto p_gob : m_dynamic_objects)
		if (p_gob) delete p_gob;
	
	if (baguette) {
		delete baguette;
		baguette = nullptr;
	}
}