#pragma once
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <math.h>
#include "GL/glut.h"

using namespace std;

// Stage 3���� ���� �������� �����ϰ� �׷��ش�.
// Q bert�� ���� ��ġ�� �׷��ش�.
// ���� ������ Qbert ���� �Լ��� ���� �����Ѵ�.

#define MAX_ROUND 5

class Point3 { //����Ŭ����
public:
	float x, y, z;//��ǥ
	void set(float dx, float dy, float dz) { x = dx; y = dy; z = dz; }//������ǥ����޼ҵ�
	//void set(Point3& p) { x = p.x; y = p.y; z = p.z; }//������ǥ����޼ҵ�2 �ٸ����� ����
	void set(Point3 p) { x = p.x; y = p.y; z = p.z; }//������ǥ����޼ҵ�2 �ٸ����� ����
	Point3(float xx, float yy, float zz) { x = xx; y = yy; z = zz; }//������: �����ʱ�ȭ
	Point3() { x = y = z = 0; }//������: �ʱ�ȭ������ ����
	friend bool operator==(const Point3& p1, const Point3& p2)
	{
		return (p1.x == p2.x && p1.y == p2.y && p1.z == p2.z);
	};
	friend bool operator!=(const Point3& p1, const Point3& p2)
	{
		return !(p1 == p2);
	};
};
class Vector3 {
public:
	float x, y, z;//���ͼ���
	void set(float dx, float dy, float dz) { x = dx; y = dy; z = dz; }//���ͻ����޼ҵ�
	//void set(Vector3& v){ x = v.x; y = v.y; z = v.z;}//���ͻ����޼ҵ�
	void set(Vector3 v) { x = v.x; y = v.y; z = v.z; }//���ͻ����޼ҵ�, ���� ��ȯ ���� �ذ�
	void flip() { x = -x; y = -y; z = -z; } //�ݴ���⺤��
	void setDiff(Point3& a, Point3& b)//�κ�������
	{
		x = a.x - b.x; y = a.y - b.y; z = a.z - b.z;
	}
	void normalize();//�������ͷ�
	Vector3(float xx, float yy, float zz) { x = xx; y = yy; z = zz; } //������
	//Vector3(Vector3& v){x = v.x; y = v.y; z = v.z;}
	Vector3() { x = y = z = 0.0; }
	Vector3 cross(Vector3 b);//����
	float dot(Vector3 b);//����
	friend bool operator==(const Vector3& v1, const Vector3& v2)
	{
		return (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z);
	};
	friend bool operator!=(const Vector3& v1, const Vector3& v2)
	{
		return !(v1 == v2);
	};
};

typedef struct tile 
{
	Vector3 color;
	bool step = false;
	Point3 tilePos;
} TILE;

class Map
{
private:
	// saving for diferrent 3 tile colors
	Vector3 tileColor[4];
	TILE tiles[28];
public:
	GLint level, round, score;
	Map();
	~Map();
	// get random color
	void getRColor();
	// drawing POLYGON
	void drawUpside(Vector3 v);
	void drawSide(Vector3 v, Vector3 tileColor);
	void drawTarget();
	void draw();
	// check Up || Down
	bool checkUD(Point3 p);
	// check Out
	bool checkOut(Point3 p);
	// check Finish round
	bool checkFinish();
	// change tile color
	void changeTile(Point3 p);
	// GameOver Restart
	void restart();
};