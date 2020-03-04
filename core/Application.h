#pragma once

#ifndef VTX_APPLICATION_H
#define VTX_APPLICATION_H

#include <SFML/Graphics.hpp>

#include <string>

#include "../assets/AssetHolder.h"
#include "../states/State.h"

namespace vtx
{

	class Application
	{

	public:
		Application(const std::string& title, 
					int width, 
					int height, 
					int fixedUpdateRate=30, 
					const std::string& assetFolder="res");

		int Run();
		void Stop() { running = false; }

		AssetHolder& GetAssetHolder() { return assetHolder; }

		void ChangeState(State* state);
		void PushState(State* state);
		void PopState();

		sf::RenderWindow& GetRenderWindow() { return window; }

		int GetWidth() const { return width; }
		int GetHeight() const { return height; }

		bool IsRunning() const { return running; }

	protected:
		virtual void init() = 0;
		virtual void cleanup() = 0;

		void initWindow();

	protected:
		sf::RenderWindow window;

		std::vector<State*> states;

		AssetHolder assetHolder;

		std::string title;
		int width, height;
		float fixedUpdateRate;

		bool running;

	};

}

#endif
