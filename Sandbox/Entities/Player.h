#pragma once

#ifndef SANDBOX_PLAYER_H
#define SANDBOX_PLAYER_H

#include  "../../core/Application.h"

#include "../../entities/Entity.h"
#include "../../components/TransformComponent.h"

#include <iostream>

class Player : public vtx::Entity, public vtx::TransformComponent
{

public:
	Player(vtx::Application* app, double x, double y) 
		: Entity(app)
		, vtx::TransformComponent(x, y)
	{

		tree = sf::Sprite();
		tree.setTexture(app->GetAssetHolder().textures.Get("Abe"));
		tree.scale(sf::Vector2f(10, 10));
		tree.setPosition(GetX(), 100);
	};

	void FixedUpdate() 
	{
		SetX(GetX() + 1);

		tree.setPosition(GetX(), GetY());
	}

	void VariableUpdate(float delta)
	{
		
	}

	void Draw() 
	{
		app->GetRenderWindow().draw(tree);
	}

private:
	sf::Sprite tree;

};

#endif
