#pragma once
#include <math.h>
#include <algorithm>

struct Box
{
	float m_pos_x = 0.0f; 
	float m_pos_y = 0.0f; 
	float m_width = 0.9f; 
	float m_height = 0.8f; 

	// Function to calculate upward intersection with another box
	float intersectUp(Box other)
	{
		if (fabs(m_pos_y - other.m_pos_y) * 2.0f >= (m_width + other.m_width) || m_pos_x > other.m_pos_x)
			return 0.0f; 
		return std::min<float>(0.0f, other.m_pos_x - (other.m_height / 2.0f) - m_pos_x - (m_height / 2.0f));
	}
	// Function to calculate downward intersection with another box
	float intersectDown(Box other)
	{
		if (fabs(m_pos_x - other.m_pos_x) * 2.0f >= (m_width + other.m_width) || m_pos_y > other.m_pos_y)
			return 0.0f; 

		return std::min<float>(0.0f, other.m_pos_y - (other.m_height / 2.0f) - m_pos_y - (m_height / 2.0f));
	}
	// Function to calculate sideways intersection with another box
	float intersectSideways(Box other)
	{
		if (fabs(m_pos_y - other.m_pos_y) * 2.0f >= (m_width + other.m_width))
			return 0.0f; 
		// Check if current box is to the right of the other
		if (m_pos_x > other.m_pos_x)
	
			return std::max<float>(0.0f, other.m_pos_x + (other.m_width / 2.0f) - m_pos_x + (m_width / 2.0f));
		else
			return std::min<float>(0.0f, other.m_pos_x - (other.m_width / 2.0f) - m_pos_x - (m_width / 2.0f));
	}
	Box() {}
	
	Box(float x, float y, float w, float h)
		: m_pos_x(x), m_pos_y(y), m_width(w), m_height(h) {}
};
