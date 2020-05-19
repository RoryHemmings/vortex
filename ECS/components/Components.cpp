#include "Components.h"

namespace vtx
{
	namespace components 
	{
		void Renderer::SetAnimation(const std::string& name, float fps)
		{
			if (name == currentAnimation) return;
			if (animations.count(name) < 1)
				throw "Animation: [" + name + "] is invalid";

			currentAnimation = name;

			frameIndex = 0;
			millisecondsSinceLastFrame = 0;

			if (fps == 0.0f)
				millisecondsPerFrame = -1.0f;
			else
				millisecondsPerFrame = (1 / fps) * 1000;
		}

		void Renderer::AddAnimation(const std::string& name, const std::vector<sf::Texture*>& frames)
		{
			if (animations.count(name) > 0) return;

			animations[name] = frames;
		}
	}
}
