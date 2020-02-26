#pragma once

#ifndef VTX_STATE_H
#define VTX_STATE_H

namespace vtx {

	class State
	{

	public:
		virtual void Init() = 0;
		virtual void Cleanup() = 0;

		virtual void Pause() = 0;
		virtual void Resume() = 0;

		//virtual void HandleEvents() = 0;
		virtual void FixedUpdate() = 0;
		virtual void VariableUpdate(float delta) = 0;
		virtual void Draw() = 0;

		void ChangeState()
		{

		}

	protected:
		State() { }
		// GameObject Vector

	};
}

#endif
