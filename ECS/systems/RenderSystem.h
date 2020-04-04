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
			void Draw(Application* app, EntityCoordinator* entityCoordinator);

		};

	}

}

#endif
