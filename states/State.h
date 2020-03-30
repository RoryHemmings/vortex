#pragma once

#ifndef VTX_STATE_H
#define VTX_STATE_H

#include <string>

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

		virtual void Cleanup() = 0;

		virtual void Pause() = 0;
		virtual void Resume() = 0;

		//virtual void HandleEvents() = 0;
		virtual void FixedUpdate() = 0;
		virtual void VariableUpdate(float delta) = 0;
		virtual void Draw() = 0;

		void ChangeState(const std::string& id);
		// Entity Manager

	protected:
		Application* app;

	};
}

#endif
