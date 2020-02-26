#pragma once

#ifndef VTX_APPLICATION_H
#define VTX_APPLICATION_H

#include "SFML/Window/Window.hpp"

#include <string>

#include "../states/StateManager.h"

namespace vtx
{

	class Application
	{

	public:
		Application(const std::string& title, int width, int height, int fixedUpdateRate=30);

		int Run();
		void Stop() { running = false; }

		//AssetManager getAssetManager();

		void ChangeState(State* state);
		void PushState(State* state);
		void PopState();

		int GetWidth() const { return width; }
		int GetHeight() const { return height; }

		bool IsRunning() const { return running; }

	protected:
		virtual void init() = 0;
		virtual void cleanup() = 0;

		void initWindow();

	protected:
		sf::Window window;

		std::vector<State*> states;

		std::string title;
		int width, height;
		float fixedUpdateRate;

		bool running;

	};

}

#endif
