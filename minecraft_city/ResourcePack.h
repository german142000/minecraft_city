#pragma once
#include <map>
#include <string>

#define RESOURCE_PACKS_PATH "/resources"
#define RESOURCE_PACKS_CONF_FILE "/resources/packs.json"

class ResourcePack {
public:
	int id;
	int name;
	std::map<int, std::string> texturesMap;
	std::map<int, std::string> soundsMap;

	ResourcePack(std::string packConfig);
};