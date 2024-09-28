#pragma once
#include <string>
#include <vector>

#include "Cube.h"

using namespace std;

#define RESOURCE_PACKS_PATH "/resources"
#define RESOURCE_PACKS_CONF_FILE "/resources/packs.json"

/*------------------------------------------------------------
* ���������� ������
* 
* textures/blocks - ����� � ���������� ��� ������
* textures/maps/blocks.json - ���� � ��������������� ��������������� � ������� ������ (������, ������� �������� ������������� �������������� ��������, � �������� - �������� ����� ��������)
* blocks - ����� ��� ������, ����������� �����
* lang - ����� ��� �������� ������
* pack.json - ���� ������������ ������
* 
* ������ ���� ������ - ��� ��������� json ������ �� ������ �������
* 
* 
* ���������� ����� pack.json
* 
* ���� pack.json ������ � ���� json ������ �� ���������� �������:
* 
* uuid - ���������� ������������� ������
* version - ������ ������
* id - ��������� ������������� ������
* name - ��� ������
* desc - �������� ������
* min_engine - ����������� ������ ����, � ������� ����� �������������� �����
* max_engine - ������������ ������ ����, � ������� ����� �������������� �����
* use_blocks - ��������� �� ����� �����
* use_entities - ��������� �� ����� ��������
* use_items - ��������� �� ����� �����������
* 
* 
* ���������� ����� textures/maps/blocks.json
* 
* block.json - ������ ����� � ���������
* 
* �������� � ��� ���� ��� �������� - block1.png, block2.png, block3.png.
* 
* ���� ��� ���� ����� ���:
* 
* [
*	'block3.png',
*	'block2.png',
*	'block1.png'
* ]
* 
* ��� �������� ��� � �������� � ������ block1.png ������������� ����� ���� � ��.
* 
* ���� �������� ����� - ��� json ������ �� ���������� �������:
* 
* id - ��������� ������������� �����
* 
* 
*/

struct TexturesInfo {
	vector<string> paths;
	int offset;
	int count;
};

class ResourcePack {
public:
	int name;
	string uuid;

	vector<Cube> cubes;

	int texturesStartOffset = 0;
	int numOfTextures;

	vector<string> texturesMap;
	vector<string> soundsMap;

	ResourcePack(string packConfig);
	TexturesInfo getTexturesInfo();
	void loadCubes(int* texturesMatching); //texturesMatching - ��������, ������� ������������ �������� �� ������, � ����������, ������������ � ���������� ������. 
	//������ ������� ������ ���� ������� �� �����, � ������� ����������� �������� �������

};