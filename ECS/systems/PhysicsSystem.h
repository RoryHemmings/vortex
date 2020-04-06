#pragma once

#ifndef VTX_PHYSICS_SYSTEM_H
#define VTX_PHYSICS_SYSTEM_H

#include "SystemManager.h"

namespace vtx
{
    class Application;
    class EntityCoordinator;

    namespace systems
    {

        class PhysicsSystem : public System
        {

        public:
            void FixedUpdate(Application* app, EntityCoordinator* entityCoordinator);

        };

    }
}

#endif
