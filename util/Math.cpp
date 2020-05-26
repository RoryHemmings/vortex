#include "Math.h"

#include <random>

namespace vtx
{
	float GenRandomFloat(float lowerBound, float upperBound)
	{
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<double> dist(lowerBound, upperBound);

		return dist(mt);
	}
}
