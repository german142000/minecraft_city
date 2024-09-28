#pragma once
#include <string>
#include <vector>

#include "ResourcePack.h"

using namespace std;

#define WORLDS_PATH "/worlds"
#define WORLDS_CONF_PATH "/worlds/config.json"

class WorldLoader {
public:
	WorldLoader(std::string worldConfigPath);
	vector<ResourcePack> getResourcePacks();
	
};