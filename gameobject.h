#pragma once
#include <string>
#include"util.h"

// Interface class for objects that can be collided with
class Collidable {
public:

	virtual Disk getCollisionHull() const = 0;
};

// Interface class for objects that have a collision boost (additional to the main collision hull)
class Collidable2 {
	
	virtual Disk getCollisionBoost() const = 0;
};

class GameObject {

	static int m_next_id;

protected:
	
	class GameState* m_state;
	std::string m_name;

	int m_id = 0;

	bool m_active = true;

public:

	GameObject(const std::string& name = "");

	virtual void update(float dt) {}
	virtual void init() {}
	virtual void draw() {}
	virtual ~GameObject() {}
	bool isActive() { return m_active; }
	void setActive(bool a) { m_active = a; }
};