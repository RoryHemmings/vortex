#include "GameState.h"

#include "../../util/Math.h"

#define randY floor(vtx::GenRandomFloat(-15, -8))

void GameState::SetBlockCombos()
{
	blockCombos.push_back({});

	blockCombos[0].push_back({ 0.0f, -14.135f, 0.3f, b2_staticBody, &buildings[0] });
	blockCombos[0].push_back({ 10.0f, -9.67f, 0.3f, b2_staticBody, &buildings[1] });
	blockCombos[0].push_back({ 20.0f, -5.53f, 0.3f, b2_staticBody, &buildings[2] });

	blockCombos.push_back({});

	blockCombos[1].push_back({ 0.0f, randY, 1.0f, b2_staticBody, &short_beam });
	blockCombos[1].push_back({ 10.0f, -14.135f, 0.3f, b2_staticBody, &buildings[0] });
	blockCombos[1].push_back({ 20.0f, randY, 1.0f, b2_staticBody, &long_beam });

	blockCombos.push_back({});

	blockCombos[2].push_back({ 0.0f, -14.135f, 0.3f, b2_staticBody, &buildings[4] });
	blockCombos[2].push_back({ 10.0f, -5.53f, 0.3f, b2_staticBody, &buildings[2] });
	blockCombos[2].push_back({ 20.0f, -14.135f, 0.3f, b2_staticBody, &buildings[3] });
	blockCombos.push_back({});

	blockCombos[3].push_back({ 0.0f, randY, 1.0f, b2_staticBody, &short_beam });
	blockCombos[3].push_back({ 10.0f, randY, 1.0f, b2_staticBody, &short_beam});
	blockCombos[3].push_back({ 20.0f, randY, 1.0f, b2_staticBody, &long_beam });

	blockCombos.push_back({});

	blockCombos[4].push_back({ 0.0f, randY, 1.0f, b2_staticBody, &long_beam });
	blockCombos[4].push_back({ 10.0f, -14.135f, 0.3f, b2_staticBody, &buildings[4] });
	blockCombos[4].push_back({ 20.0f, -14.135f, 0.3f, b2_staticBody, &buildings[3] });
}
