#pragma once

#ifndef SANDBOX_STATES_H
#define SANDBOX_STATES_H

#include <unordered_map>
#include <string>

namespace vtx {

	class State;

	class States
	{

	public:
		static void AddState(State* state, const std::string& id);

		static void SetCurrentState(const std::string& id);
		static State& GetCurrentState();
		static const std::string& GetCurrentStateId() { return current; }

		static void RemoveState(const std::string& id) { states.erase(id); }

		static bool IsEmpty() { return states.empty(); }

	private:
		static std::unordered_map<std::string, State*> states;
		static std::string current;

	};

}

#endif
