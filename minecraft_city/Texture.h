#pragma once
#include <string>

struct Size {
	int width;
	int height;
};

class Texture {
public:
	char* raw;
	int width;
	int height;

	Texture(std::string path);
	char* getTexture();
	Size getTextureSize();

};