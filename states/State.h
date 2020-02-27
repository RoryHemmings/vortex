#pragma once

#ifndef VTX_STATE_H
#define VTX_STATE_H

namespace vtx {

	class Application;

	class State
	{

	public:
		virtual void Init() = 0;
		virtual void Cleanup() = 0;

		virtual void Pause() = 0;
		virtual void Resume() = 0;

		//virtual void HandleEvents() = 0;
		virtual void FixedUpdate(Application*) = 0;
		virtual void VariableUpdate(Application*, float delta) = 0;
		virtual void Draw(Application*) = 0;

		void ChangeState(Application* app, State* state);

	protected:
		State() { }
		// GameObject Vector

	};
}

#endif
