//#pragma once
//
//#ifndef VTX_COLLISION_SYSTEM_H
//#define VTX_COLLISION_SYSTEM_H
//
//#include <vector>
//
//#include "SystemManager.h"
//
//namespace vtx
//{
//    class Application;
//    class EntityCoordinator;
//
//    namespace systems
//    {
//
//        class CollisionSystem : public System
//        {
//
//        public:
//            void Initialize(Application* app, int zoneSize=100);
//            void FixedUpdate(Application* app, EntityCoordinator* entityCoordinator);
//
//        private:
//            void handleCollisions(std::vector<Entity> zone, EntityCoordinator* entityCoordinator);
//
//            // 1 dimensional vector that encapsulates 2 dimensional grid
//            std::vector<std::vector<Entity>> zones;
//            int zoneSize;
//
//        };
//
//    }
//}
//
//#endif