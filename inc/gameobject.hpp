#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "utils.hpp"

class GameObject {
public:
	GameObject() {};
	virtual ~GameObject() {};

	virtual void event(unsigned char key, int x, int y) {};	
	virtual void update() {};
	virtual void draw() {};
};

#endif