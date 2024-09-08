#include "gameobject.h"
#include "gamestate.h"
int GameObject::m_next_id = 1;

// Constructor for the GameObject class
GameObject::GameObject(const std::string& name)
    : m_name(name),  
    m_id(m_next_id++),  
    m_state(GameState::getInstance())  
{

}
