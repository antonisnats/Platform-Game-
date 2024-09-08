#pragma once
#include <random>

#define SETCOLOR(c, r, g, b) {c[0]=r; c[1]=g; c[2]=b;}


struct Disk
{
	float cx, cy;
	float radius;
};