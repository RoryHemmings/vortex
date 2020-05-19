#pragma once

#ifndef VTX_RENDER_SYSTEM_H
#define VTX_RENDER_SYSTEM_H

#include "SystemManager.h"

namespace vtx
{
	class Application;
	class EntityCoordinator;

	namespace systems
	{

		class RenderSystem : public System
		{

		public:
			RenderSystem(Application* app, EntityCoordinator* ec, float pixelToMeterRatio=100.0f)
				: System(app, ec)
				, pixelToMeterRatio(pixelToMeterRatio)
				, xOffset(0.0f)
				, yOffset(0.0f)
				, numEntitiesRendered(0)
			{}

			void OnMemberAddition(Entity entity);
			void OnMemberDestruction(Entity entity);

			void FixedUpdate();
			void Draw();

			float PixelsToMeters(int pixels) { return pixels / pixelToMeterRatio; }
			float MetersToPixels(int meters) { return meters * pixelToMeterRatio; }

			int GetNumEntitiesRendered() const { return numEntitiesRendered; }

		private:
			int numEntitiesRendered;
			float pixelToMeterRatio;

			// In Pixels
			int xOffset, yOffset;

		};

	}

}

#endif
