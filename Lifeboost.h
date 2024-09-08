#pragma once
#include "gameobject.h"
#include "level.h"
#include "util.h"


class LifeBoost : public GameObject, public Collidable2 {
	float m_pos_x; 
	float m_pos_y; 
	graphics::Brush brush; 
	bool active = true; 
public:
	
	void draw();
	
	void init() override;
	
	void update(float newPosX, float newPosY);
	
	bool isActive() { return active; }

	// Constructor for the life boost
	LifeBoost(const std::string& name = "Baguette");
	
	Disk getCollisionBoost() const;

	// Destructor for the life boost
	~LifeBoost();
};