#include "Runtime.h"

Runtime::Runtime()
{
	for (unsigned int x = 0; x < WORLD_WIDTH; x++) {
		for (unsigned int y = 0; y < WORLD_HEIGHT; y++) {
			if (random(0, 10) >= 8) {
				grid[x][y] = 1;
				bots.push_back(Bot{ x, y });
			}
			else {
				grid[x][y] = 0;
			}
		}
	}
}

Runtime::~Runtime()
{
}

void Runtime::step()
{
	map<std::string, bool> changes;
	map<std::string, Dead> deads;
	std::vector<Bot> newBots;

	for (const auto& bot : bots) {
		if (isNeedDelete(bot.x, bot.y, deads)) {
			std::string key = genKey(bot.x, bot.y);
			changes[key] = 0;
		} else {
			newBots.push_back(Bot{bot.x, bot.y});
		}
	}

	bots.resize(0);
	bots.clear();

	if (deads.size() > 0) {
		map <std::string, Dead> ::iterator it = deads.begin();

		for (; it != deads.end(); it++) {
			Dead* dead = &it->second;
			if (outOfGrid(dead->x, dead->y)) {
				continue;
			}

			if (isNeedCreate(dead->x, dead->y)) {
				std::string key = genKey(dead->x, dead->y);
				changes[key] = 1;
				newBots.push_back(Bot{ dead->x, dead->y });
			}
		}
	}
	
	bots = newBots;

	map <std::string, bool> ::iterator it = changes.begin();

	for (; it != changes.end(); it++) {
		std::string key = it->first;
		std::string delimiter = "_";
		size_t pos = 0;
		pos = key.find("_");
		int x = stoi(key.substr(0, pos)); // x
		key.erase(0, pos + delimiter.length());
		int y = stoi(key); // y

		grid[x][y] = it->second;
	}

	deads.clear();
}

bool Runtime::isNeedDelete(unsigned int x, unsigned int y, map<std::string, Dead> &empty)
{
	// left top
	int sx, sy;
	int liveCount = 0;

	sy = y - 1; sx = x - 1;
	if (!outOfGrid(sx, sy)) {
		if (isLive(sx, sy)) {
			liveCount++;
		}
		else {
			pushToMap(sx, sy, empty);
		}
	}

	// top
	sy = y - 1; sx = x;
	if (!outOfGrid(sx, sy)) {
		if (isLive(sx, sy)) {
			liveCount++;
		}
		else {
			pushToMap(sx, sy, empty);
		}
	}

	// top right
	sy = y - 1; sx = x + 1;
	if (!outOfGrid(sx, sy)) {
		if (isLive(sx, sy)) {
			liveCount++;
		}
		else {
			pushToMap(sx, sy, empty);
		}
	}

	// left
	sy = y; sx = x - 1;
	if (!outOfGrid(sx, sy)) {
		if (isLive(sx, sy)) {
			liveCount++;
		}
		else {
			pushToMap(sx, sy, empty);
		}
	}

	// right
	sy = y; sx = x + 1;
	if (!outOfGrid(sx, sy)) {
		if (isLive(sx, sy)) {
			liveCount++;
		}
		else {
			pushToMap(sx, sy, empty);
		}
	}

	// left bottom
	sy = y + 1; sx = x - 1;
	if (!outOfGrid(sx, sy)) {
		if (isLive(sx, sy)) {
			liveCount++;
		}
		else {
			pushToMap(sx, sy, empty);
		}
	}

	// bottom
	sy = y + 1; sx = x;
	if (!outOfGrid(sx, sy)) {
		if (isLive(sx, sy)) {
			liveCount++;
		}
		else {
			pushToMap(sx, sy, empty);
		}
	}

	// bottom right
	sy = y + 1; sx = x + 1;
	if (!outOfGrid(sx, sy)) {
		if (isLive(sx, sy)) {
			liveCount++;
		} else {
			pushToMap(sx, sy, empty);
		}
	}

	if (liveCount < 2 || liveCount > 3) {
		return true;
	}

	return false;
}

bool Runtime::isLive(int x, int y)
{
	if (outOfGrid(x, y)) {
		return false;
	}
	return grid[x][y] == 1;
}

bool Runtime::isNeedCreate(unsigned int x, unsigned int y)
{
	int sx, sy;
	int count = 0;

	sy = y - 1; sx = x - 1;
	if (isLive(sx, sy)) count++;

	sy = y - 1; sx = x;
	if (isLive(sx, sy)) count++;

	sy = y - 1; sx = x + 1;
	if (isLive(sx, sy)) count++;

	sy = y; sx = x - 1;
	if (isLive(sx, sy)) count++;

	sy = y; sx = x + 1;
	if (isLive(sx, sy)) count++;

	sy = y + 1; sx = x - 1;
	if (isLive(sx, sy)) count++;

	sy = y + 1; sx = x;
	if (isLive(sx, sy)) count++;

	sy = y + 1; sx = x + 1;
	if (isLive(sx, sy)) count++;

	return count == 3;
}

bool Runtime::outOfGrid(int x, int y)
{
	return x >= WORLD_WIDTH || x < 0 || y >= WORLD_HEIGHT || y < 0;
}

void Runtime::pushToMap(unsigned int x, unsigned int y, map<std::string, Dead>& empty)
{
	std::string key = genKey(x, y);
	if (empty.count(key) == 0) {
		empty[key] = Dead{ x, y };
	}
}

std::string Runtime::genKey(unsigned int x, unsigned int y)
{
	return to_string(x) + "_" + to_string(y);
}