#pragma once
#include <string>

class Cube {
public:
	int id; //�������� ������������� �����
	std::string stringId; //��������� ������������� �����
	bool usePhysics; //������������ �� ������ � ���� �����
	float quicksand; //�������� ���������
	float emmision; //�������� ������������ �����
	float transparent; //���������� ������������
	int topTexture; //������� �������� �����
	int bottomTexture; //������ �������� �����
	int northTexture; //�������� �������� �����            n
	int southTexture; //����� �������� �����             w B e
	int westTexture; //�������� �������� �����             s
	int eastTexture; //��������� �������� �����
};