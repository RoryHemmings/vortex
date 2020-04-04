#pragma once

#ifndef VTX_STATE_H
#define VTX_STATE_H

#include <string>

#include "../ECS/EntityCoordinator.h"
#include "../States/States.h"

namespace vtx {

	class Application;

	class State
	{

	public:
		State(Application* app)
			: app(app)
		{ }

		virtual ~State() = default;

		/* 
			Fills state (Adds entity cooridinator).

			Register all components, all systems, 
			all entities, all everything here
		*/
		virtual void Load() = 0;

		// Makes state hollow (removes entity coordiator)
		virtual void Unload() = 0;

		virtual void Pause() = 0;
		virtual void Resume() = 0;

		//virtual void HandleEvents() = 0;
		virtual void FixedUpdate() = 0;
		virtual void VariableUpdate(float delta) = 0;
		virtual void Draw() = 0;

		void ChangeState(const std::string& id);

	protected:
		Application* app;
		EntityCoordinator entityCoordinator;

	};
}

#endif
