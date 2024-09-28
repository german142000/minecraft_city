#pragma once
#include <string>
#include <vector>

#include "Cube.h"

using namespace std;

#define RESOURCE_PACKS_PATH "/resources"
#define RESOURCE_PACKS_CONF_FILE "/resources/packs.json"

/*------------------------------------------------------------
* Устройство пакета
* 
* textures/blocks - папка с текстурами для блоков
* textures/maps/blocks.json - файл с сопоставлениями идентификаторов и текстур блоков (массив, индексы которого соответствуют идентификатору текстуры, а значения - названию файла текстуры)
* blocks - папка для файлов, описывающих блоки
* lang - папка для языковых файлов
* pack.json - файл конфигурации пакета
* 
* Каждый файл пакета - это небольшой json объект со своими ключами
* 
* 
* Устройство файла pack.json
* 
* Файл pack.json хранит в себе json объект со следующими ключами:
* 
* uuid - уникальный идентификатор пакета
* version - версия пакета
* id - текстовый идентификатор пакета
* name - имя пакета
* desc - описание пакета
* min_engine - минимальная версия игры, в которой может использоваться пакет
* max_engine - максимальная версия игры, в которой может использоваться пакет
* use_blocks - добавляет ли пакет блоки
* use_entities - добавляет ли пакет сущности
* use_items - добавляет ли пакет инструменты
* 
* 
* Устройство файла textures/maps/blocks.json
* 
* block.json - массив путей к текстурам
* 
* Допустим у нас есть три текстуры - block1.png, block2.png, block3.png.
* 
* Если наш файл имеет вид:
* 
* [
*	'block3.png',
*	'block2.png',
*	'block1.png'
* ]
* 
* Это означает что у текстуры с именем block1.png идентификатор равен нулю и тд.
* 
* Файл описания блока - это json объект со следующими ключами:
* 
* id - текстовый идентификатор блока
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
	void loadCubes(int* texturesMatching); //texturesMatching - Параметр, который сопоставляет текстуры из пакета, с текстурами, загруженными в глобальный массив. 
	//Данная функция должна быть вызвана из блока, в котором происходила загрузка текстур

};