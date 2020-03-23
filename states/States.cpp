#include "States.h"

#include <iostream>

namespace vtx
{
	
	void States::AddState(State* state, const std::string& id)
	{
		// If map already contains that key
		if (states.count(id) > 0) {
			std::cout << "State With id [" + id + "] already exists. See States::AddState(State* state, const std::string&) (States.cpp) line 12" << std::endl;
			throw;
		}

		states[id] = state;
	}

	void States::SetCurrentState(const std::string& id)
	{
		if (states.count(id) < 1) {
			std::cout << "No State exists with id [" + id + "]" + ", See States::SetCurrentState(const std::string&) (States.cpp) line 22" << std::endl;
			throw;
		}

		current = id;
	}

	State& States::GetCurrentState()
	{
		return *(states[current]);
	}

	std::unordered_map<std::string, State*> States::states;
	std::string States::current;

}
