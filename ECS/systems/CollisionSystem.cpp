//#include "CollisionSystem.h"
//
//#include "../../core/Application.h"
//#include "../EntityCoordinator.h"
//
//namespace vtx
//{
//	namespace systems
//	{
//		void CollisionSystem::Initialize(Application* app, int zs)
//		{
//			zoneSize = zs;
//
//			// Create empty vector with x amount of zones
//			std::vector<int>::size_type length = ceil(app->GetWidth() / zoneSize) * ceil(app->GetHeight() / zoneSize);
//			
//			for (std::vector<int>::size_type i = 0; i != length; ++i) {
//				std::vector<Entity> temp;
//				zones.push_back(temp);
//			}
//
//			for (const auto& entity : entities) {
//
//			}
//
//			whenTheyMoveUpdateZones();
//		}
//
//		void CollisionSystem::handleCollisions(std::vector<Entity> zone, EntityCoordinator* entityCoordinator)
//		{
//			for (auto& entityA : zone) {
//				const auto& a = entityCoordinator->GetComponent<vtx::components::Collider>(entityA).boundingBox;
//				for (auto& entityB : zone) {
//					if (entityB != entityA) {
//						const auto& b = entityCoordinator->GetComponent<vtx::components::Collider>(entityB).boundingBox;
//						if (a.intersects(b)) {
//							doSomething();
//						}
//					}
//				}
//			}
//		}
//
//		void CollisionSystem::FixedUpdate(Application* app, EntityCoordinator* entityCoordinator)
//		{
//			for (auto& zone : zones) {
//				// If zone has more than one entity in it
//				if (zone.size() > 1) {
//					handleCollisions(zone, entityCoordinator);
//				}
//			}
//		}
//
//	}
//}
