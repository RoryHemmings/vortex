#pragma once

#ifndef VTX_APPLICATION_H
#define VTX_APPLICATION_H

#include <SFML/Graphics.hpp>

#include <string>

#include "../assets/AssetHolder.h"
#include "../states/State.h"
#include "../states/States.h"

#include "../io/InputManager.h"

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

		// Prevents Memory Leaks
		virtual ~Application() { }

		int Run();
		void Stop() { running = false; }

		AssetHolder& GetAssetHolder() { return assetHolder; }

		sf::RenderWindow& GetRenderWindow() { return window; }

		int GetWidth() const { return width; }
		int GetHeight() const { return height; }

		bool IsRunning() const { return running; }

		// Time between ticks
		float GetFixedDelta() const { return fixedUpdateRate; }

	protected:
		virtual void init() = 0;
		virtual void cleanup() = 0;

		void initWindow();

	protected:
		sf::RenderWindow window;

		AssetHolder assetHolder;

		std::string title;
		int width, height;
		float fixedUpdateRate;

		bool running;

	};

}

#endif
