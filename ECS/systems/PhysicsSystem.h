#pragma once

#ifndef VTX_PHYSICS_SYSTEM_H
#define VTX_PHYSICS_SYSTEM_H

#include <box2d/box2d.h>

#include <iostream>
#include <memory>

#include "SystemManager.h"

namespace vtx
{
    class Application;
    class EntityCoordinator;

    class CollisionHandler : public b2ContactListener
    {
    public:
        void BeginContact(b2Contact* contact);
        void EndContact(b2Contact* contact);
    };

    namespace systems
    {

        class PhysicsSystem : public System
        {

        public:
            PhysicsSystem(Application* app, EntityCoordinator* ec, float gravity, int velocityIterations = 8, int positionIterations = 3);

            void OnMemberAddition(Entity entity);
            void FixedUpdate();

        private:
            b2World world;
            int velocityIterations, positionIterations;

            std::shared_ptr<CollisionHandler> collisionHandler;  // Smart Pointer because it uses virtual inheritance

        };

    }
}

#endif
