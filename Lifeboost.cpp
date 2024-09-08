#include "LifeBoost.h"
#include"gamestate.h"
#include "sgg/graphics.h"

// Initialization function for the LifeBoost
void LifeBoost::init()
{
	
	m_pos_x = 12.0f;
	m_pos_y = 2.0f;
	
	brush.outline_opacity = 0.0f;
}

// Update function for the LifeBoost
void LifeBoost::update(float newX, float newY)
{
	
	m_pos_x = newX;
	m_pos_y = newY;
}

// Draw function for the LifeBoost
void LifeBoost::draw()
{
	
	float x = m_pos_x + m_state->m_global_offset_x;
	float y = m_pos_y + m_state->m_global_offset_y;
	
	brush.texture = std::string(m_state->getFullAssetPath("baguette.png"));
	
	brush.fill_opacity = 1.0f;
	
	graphics::drawRect(x, y, 0.5f, 0.5f, brush);
	//graphics::resetPose();
}

// Constructor for the LifeBoost
LifeBoost::LifeBoost(const std::string& name)
	:GameObject(name)
{
}

// Destructor for the LifeBoost class
LifeBoost::~LifeBoost()
{
}

Disk LifeBoost::getCollisionBoost() const
{
	
	Disk disk;
	
	disk.cx = m_pos_x + m_state->m_global_offset_x;
	disk.cy = m_pos_y + m_state->m_global_offset_y;
	
	disk.radius = 0.2f;
	
	return disk;
}
