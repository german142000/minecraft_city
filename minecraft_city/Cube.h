#pragma once
#include <string>

class Cube {
public:
	int id; //Числовой идентификатор блока
	std::string stringId; //Текстовый идентификатор блока
	bool usePhysics; //Использовать ли физику в этом блоке
	float quicksand; //Величина зыбучести
	float emmision; //Величина испускаемого света
	float transparent; //Коэффицент прозрачности
	int topTexture; //Верхняя текстура блока
	int bottomTexture; //Нижняя текстура блока
	int northTexture; //Северная текстура блока            n
	int southTexture; //Южная текстура блока             w B e
	int westTexture; //Западная текстура блока             s
	int eastTexture; //Восточная текстура блока
};