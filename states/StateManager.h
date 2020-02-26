#pragma once

#ifndef VTX_STATE_MANAGER_H
#define VTX_STATE_MANAGER_H

#include <vector>
#include <memory>

#include "State.h"

namespace vtx {

	class StateManager
	{

	public:
		State& GetCurrentState() const { return *currentState; }
		//void setCurrentState(const State& s) { currentState = s; }
		// check whether or not current state exists

	protected:
		std::unique_ptr<State> currentState;
		// Ref to application

	};

}

#endif

