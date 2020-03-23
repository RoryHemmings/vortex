#include "State.h"

#include "../core/Application.h"

namespace vtx
{

	void State::ChangeState(const std::string& id)
	{
		States::SetCurrentState(id);
	}

}
