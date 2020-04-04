#include "State.h"

#include "../core/Application.h"

namespace vtx
{

	/*
		Entity Coordinator will be completely reset
		every time states are switched. This is a 
		tradeoff between loading times and saving 
		memory while states are running.
	*/
	void State::ChangeState(const std::string& id)
	{
		States::SetCurrentState(id);
	}

	// Define Method from STATES to avoid forward decleration error
	void States::SetCurrentState(const std::string& id)
	{
		if (states.count(id) < 1) {
			std::cout << "No State exists with id [" + id + "]" + ". See vtx::States::SetCurrentState(const std::string&) (States.cpp)" << std::endl;
			throw;
		}

		// If the current states exists
		if (states.count(current) > 0) {
			states[current]->Unload();
		}

		current = id;
		states[current]->Load();
	}

}
