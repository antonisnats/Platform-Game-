#include "player.h"
#include "sgg/graphics.h"
#include "gamestate.h"

void Player::movePlayer(float dt)
{
	float delta_time = dt / 1000.0f;
	float move = 0.0f;

	// Check if the A key is pressed, update movement accordingly
	if (graphics::getKeyState(graphics::SCANCODE_A))
		move -= 1.0f;

	// Check if the D key is pressed, update movement accordingly
	if (graphics::getKeyState(graphics::SCANCODE_D))
		move += 1.0f;

	// Horizontal movement (X-axis)
	m_vx = std::min(m_max_velocity, m_vx + delta_time * move * m_accel_horizontal);
	m_vx = std::max(-m_max_velocity, m_vx);

	m_vx -= 0.2f * m_vx / (0.1f + fabs(m_vx));


	if (fabs(m_vx) < 0.01f)
		m_vx = 0.0f;

	// Update player's position based on the horizontal velocity
	m_pos_x += delta_time * m_vx;

	// Vertical movement (Y-axis)
	if (m_vy == 0.0f)
		m_vy -= graphics::getKeyState(graphics::SCANCODE_W) ? m_accel_vertical : 0.0f;

	// Apply gravity to the player's vertical velocity
	m_vy += delta_time * m_gravity;

	// Update player's position based on the vertical velocity
	m_pos_y += m_vy * delta_time;
}

void Player::update(float dt)
{
	movePlayer(dt); 
	// Update offset for other game objects to keep the player centered on the screen
	m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.0f - m_pos_x;
	m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.0f - m_pos_y;
	GameObject::update(dt); 
}

void Player::init()
{
	
	m_pos_x = 5.0f;
	m_pos_y = 5.0f;
	m_width /= 2.0f;

	// Initialize global offset to center the player on the screen
	m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.0f - m_pos_x;
	m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.0f - m_pos_y;
	
	m_brush_player.fill_opacity = 1.0f;
	m_brush_player.outline_opacity = 0.0f;
	m_brush_player.texture = m_state->getFullAssetPath("pngegg.png");
	
	m_sprites.push_back(m_state->getFullAssetPath("pngegg.png"));

	// Define sprite names for m_spritesRight animation frames
	const char* rightSpriteNames[] = {
		"figure1.png", "figure2.png", "figure3.png", "figure4.png",
		"figure5.png", "figure6.png", "figure7.png", "figure8.png",
		"figure9.png", "figure10.png", "figure11.png", "figure12.png",
		"figure13.png", "figure14.png"
	};

	// Populate m_spritesRight with right-facing animation frames
	for (const char* spriteName : rightSpriteNames) {
		m_spritesRight.push_back(m_state->getFullAssetPath(spriteName));
	}
	// Define sprite names for m_spritesLeft animation frames
	const char* leftSpriteNames[] = {
		"figure15.png", "figure16.png", "figure17.png", "figure18.png",
		"figure19.png", "figure20.png", "figure21.png", "figure22.png",
		"figure23.png", "figure24.png", "figure25.png", "figure26.png",
		"figure27.png", "figure28.png"
	};

	// Populate m_spritesLeft with left-facing animation frames
	for (const char* spriteName : leftSpriteNames) {
		m_spritesLeft.push_back(m_state->getFullAssetPath(spriteName));
	}
}

// Get the collision hull for the player
Disk Player::getCollisionHull() const
{
	
	Disk disk;
	
	disk.cx = m_state->getCanvasWidth() * 0.5f;
	disk.cy = m_state->getCanvasHeight() * 0.5f;
	
	disk.radius = 0.5f;
	
	return disk;
}


void Player::debugDraw() // Debug draw function to visualize the player's position and collision area
{
	
	graphics::Brush debug_brush;
	SETCOLOR(debug_brush.fill_color, 1, 0.3f, 0);
	SETCOLOR(debug_brush.outline_color, 1, 0.1f, 0);
	debug_brush.fill_opacity = 0.1f;
	debug_brush.outline_opacity = 0.0f;

	graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f, m_width, m_height, debug_brush);
	
	char s[20];
	sprintf_s(s, "(%5.2f, %5.2f)", m_pos_x, m_pos_y);
	
	SETCOLOR(debug_brush.fill_color, 1, 0, 0);
	debug_brush.fill_opacity = 1.0f;
	
	graphics::drawText(m_state->getCanvasWidth() * 0.5f - 0.4f, m_state->getCanvasHeight() * 0.5f - 0.6f, 0.15f, s, debug_brush);
}


void Player::draw() // Draw function for rendering the player's character on the screen
{
	int s;

	// Determine which set of sprites to use based on the player's movement direction
	if (m_vx > 0) {
		// Moving right, use right-facing sprites
		s = (int)fmodf(m_pos_x * 8.f, m_spritesRight.size());
		m_brush_player.texture = m_spritesRight[s];
	}
	else if (m_vx < 0) {
		// Moving left, use left-facing sprites
		s = (int)fmodf(m_pos_x * 8.f, m_spritesLeft.size());
		m_brush_player.texture = m_spritesLeft[s];
	}
	else {
		// Not moving, use default sprites
		s = (int)fmodf(m_pos_x * 8.f, m_sprites.size());
		m_brush_player.texture = m_sprites[s];
	}
	// Draw the player's character at the center of the canvas
	graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f, 1.0f, 1.0f, m_brush_player);
	
	graphics::resetPose();
}