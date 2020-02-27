#include "State.h"

#include "../core/Application.h"

namespace vtx
{

	void State::ChangeState(Application* app, State* state)
	{
		app->ChangeState(state);
	}

}
