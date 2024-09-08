#pragma once

#include "gameobject.h"
#include "sgg/graphics.h"
#include "level.h"
#include "util.h"

class Enemy : public GameObject, public Collidable {

	float pos_x, pos_y;
	float speed;
	float size; 
	graphics::Brush brush; 
	bool active = true; 

public:
	void update();
	
	void draw() override;
	
	void init() override;
	
	bool isActive() { return active; }
	
	Enemy(const std::string& name = "Enemy");
	~Enemy();

	Disk getCollisionHull() const;
};