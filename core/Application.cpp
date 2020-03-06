#include "Application.h"

#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>

namespace vtx
{
	Application::Application(const std::string& title, int width, int height, int fixedUpdateRate, const std::string& assetFolder)
		: title(title), width(width), height(height), running(false), fixedUpdateRate(1.0f / fixedUpdateRate), assetHolder(assetFolder)
	{
	}

	int Application::Run()
	{
		running = true;

		init();

		sf::Clock anUpdateClock;
		sf::Clock anFrameClock;

		anUpdateClock.restart();

		sf::Int32 anUpdateNext = anUpdateClock.getElapsedTime().asMilliseconds();

		while (window.isOpen() && running) {
			if (!states.empty()) {
				State* currentState = states.back();    // Top of the stack

				// Count the number of sequential UpdateFixed loop calls
				sf::Uint32 anUpdates = 0;

				// Make note of the current update time
				sf::Int32 anUpdateTime = anUpdateClock.getElapsedTime().asMilliseconds();

				// Process our UpdateFixed portion of the game loop
				while ((anUpdateTime - anUpdateNext) >= fixedUpdateRate && anUpdates++ < (1 / fixedUpdateRate)) {
					// Check if window is trying to be closed
					sf::Event event;
					while (window.pollEvent(event)) {
						if (event.type == sf::Event::Closed)
							window.close();
					}

					// Let the current active state perform fixed updates next
					currentState->FixedUpdate(this);

					// Compute the next appropriate UpdateFixed time
					anUpdateNext += fixedUpdateRate;
				}

				currentState->VariableUpdate(this, anFrameClock.restart().asSeconds());

				// Clear and draw the screen
				window.clear(sf::Color::Black);
				currentState->Draw(this);
				window.display();
			}
		}

		cleanup();

		return 0;
	}

	void Application::ChangeState(State* state)
	{
		if (!states.empty()) {
			states.back()->Cleanup();
			states.pop_back();
		}

		states.push_back(state);
		states.back()->Init(this);
	}

	void Application::PushState(State* state)
	{
		if (!states.empty())
			states.back()->Pause();

		states.push_back(state);
		states.back()->Init(this);
	}

	void Application::PopState()
	{
		if (!states.empty()) {
			states.back()->Cleanup();
			states.pop_back();
		}

		if (!states.empty())
			states.back()->Resume();
	}

	void Application::initWindow()
	{
		window.create(sf::VideoMode(width, height), title);
	}
}

