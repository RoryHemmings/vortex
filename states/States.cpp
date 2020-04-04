#include "States.h"

#include <iostream>

namespace vtx
{
	
	// Puts hollow state into memory
	void States::AddState(State* state, const std::string& id)
	{
		// If map already contains that key
		if (states.count(id) > 0) {
			std::cout << "State With id [" + id + "] already exists. See vtx::States::AddState(vtx::State* state, const std::string&) (States.cpp)" << std::endl;
			throw;
		}

		states[id] = state;
	}

	State& States::GetCurrentState()
	{
		return *(states[current]);
	}

	std::unordered_map<std::string, State*> States::states;
	std::string States::current;

}
