#pragma once

#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <iostream>

#include <box2d/box2d.h>

#include "SFML/Graphics.hpp"
#include "../../ECS/EntityCoordinator.h" 

struct ObstacleInfo
{
	float relativeX;	// Distance from Block x
	float absoluteY;
	float friction;

	b2BodyType type;
	sf::Texture* texture;
};

class Block
{

public:
	Block(vtx::EntityCoordinator* ec, float x, int width, const std::vector<ObstacleInfo>& info, sf::Texture* floorTexture);
	void ClearEntities();

private:
	float x;
	int width;

	vtx::Entity floor;
	std::vector<vtx::Entity> obstacles;

	vtx::EntityCoordinator* ec;


};

#endif
