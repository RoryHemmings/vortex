#include "PhysicsSystem.h"

#include "../../core/Application.h"
#include "../EntityCoordinator.h"

namespace vtx
{
	void CollisionHandler::BeginContact(b2Contact* contact)
	{
		components::Physics* a = static_cast<components::Physics*>(contact->GetFixtureA()->GetBody()->GetUserData());
		components::Physics* b = static_cast<components::Physics*>(contact->GetFixtureB()->GetBody()->GetUserData());

		if (a->bottom == contact->GetFixtureA() || a->bottom == contact->GetFixtureB())
			a->bottomTouching = true;
		if (b->bottom == contact->GetFixtureA() || b->bottom == contact->GetFixtureB())
			b->bottomTouching = true;
	}

	void CollisionHandler::EndContact(b2Contact* contact)
	{
		components::Physics* a = static_cast<components::Physics*>(contact->GetFixtureA()->GetBody()->GetUserData());
		components::Physics* b = static_cast<components::Physics*>(contact->GetFixtureB()->GetBody()->GetUserData());

		if (a->bottom == contact->GetFixtureA() || a->bottom == contact->GetFixtureB())
			a->bottomTouching = false;
		if (b->bottom == contact->GetFixtureA() || b->bottom == contact->GetFixtureB())
			b->bottomTouching = false;
	}

	namespace systems
	{

		PhysicsSystem::PhysicsSystem(Application* app, EntityCoordinator* ec, float gravity, int velocityIterations, int positionIterations)
			: System(app, ec)
			, world(b2Vec2(0.0f, gravity))
			, velocityIterations(velocityIterations)
			, positionIterations(positionIterations)
		{
			collisionHandler = std::make_shared<CollisionHandler>();

			world.SetContactListener(collisionHandler.get());
		}

		void PhysicsSystem::OnMemberAddition(Entity entity)
		{
			auto& physics = entityCoordinator->GetComponent<vtx::components::Physics>(entity);
			const auto& transform = entityCoordinator->GetComponent<vtx::components::Transfrom>(entity);

			float x = transform.position.x;
			float y = transform.position.y;
			float width = transform.scale.x;
			float height = transform.scale.y;

			float hx = width / 2;
			float hy = height / 2;

			b2BodyDef bd;
			bd.position.Set(x, y);
			bd.type = physics.type;
			bd.userData = &physics;
			physics.body = world.CreateBody(&bd);

			b2PolygonShape hitBox;
			hitBox.SetAsBox(hx, hy, { hx, hy }, 0.0f);

			//b2PolygonShape topBox;
			b2PolygonShape bottomBox;
			//b2PolygonShape leftBox;
			//b2PolygonShape rightBox;

			//topBox.SetAsBox(hx, 0.1f, {hx, 0}, 0.0f);
			bottomBox.SetAsBox(hx, 0.1f, {hx, height}, 0.0f);
			//leftBox.SetAsBox(0.1f, hy, {0, hy}, 0.0f);
			//rightBox.SetAsBox(0.1f, hy, {width, hy}, 0.0f);

			b2FixtureDef fd;
			fd.shape = &hitBox;
			fd.density = physics.density;
			fd.friction = physics.friction;

			//b2FixtureDef top;
			b2FixtureDef bottomDef;
			//b2FixtureDef left;
			//b2FixtureDef right;

			//top.isSensor = true;
			bottomDef.isSensor = true;
			bottomDef.shape = &bottomBox;
			//left.isSensor = true;
			//right.isSensor = true;*/

			physics.body->CreateFixture(&fd);
			//physics.body->CreateFixture(&top);
			physics.bottom = physics.body->CreateFixture(&bottomDef);
			std::cout << physics.bottom << std::endl;
			//physics.body->CreateFixture(&left);
			//physics.body->CreateFixture(&right);
		}

		void PhysicsSystem::FixedUpdate()
		{
			world.Step(app->GetFixedDelta(), velocityIterations, positionIterations);

			for (const auto& entity : entities) {
				auto& physics = entityCoordinator->GetComponent<vtx::components::Physics>(entity);
				auto& transform = entityCoordinator->GetComponent <vtx::components::Transfrom>(entity);

				transform.position.x = physics.body->GetPosition().x;
				transform.position.y = physics.body->GetPosition().y;
			}
		}

		//void PhysicsSystem::FixedUpdate(EntityCoordinator* entityCoordinator)
		//{
		//	for (const auto& entity : entities) {
		//		auto& physics = entityCoordinator->GetComponent<vtx::components::Physics>(entity);
		//		auto& transform = entityCoordinator->GetComponent <vtx::components::Transfrom>(entity);

		//		// Increase y velocity by gravity
		//		// If moving down, accelerate faster, makes object feel heavier
		//		if (physics.gravity > 0)
		//			physics.velocity.y += physics.gravity * 1.4;
		//		else
		//			physics.velocity.y += physics.gravity;

		//		/*if (transform.position.y > app->GetHeight() - 100) {
		//			physics.velocity.y = -750;
		//		}*/

		//		// Update Position based on velocity
		//		transform.position.x += physics.velocity.x * app->GetFixedDelta();
		//		transform.position.y += physics.velocity.y * app->GetFixedDelta();
		//	}
		//}
	}
}
