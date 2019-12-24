#pragma once
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <math.h>
#include "GL/glut.h"

using namespace std;

// Stage 3가지 색을 랜덤으로 설정하고 그려준다.
// Q bert를 시작 위치에 그려준다.
// 이후 조작은 Qbert 안의 함수를 통해 조작한다.

#define MAX_ROUND 5

class Point3 { //정점클래스
public:
	float x, y, z;//좌표
	void set(float dx, float dy, float dz) { x = dx; y = dy; z = dz; }//정점좌표변경메소드
	//void set(Point3& p) { x = p.x; y = p.y; z = p.z; }//정점좌표변경메소드2 다른정점 대입
	void set(Point3 p) { x = p.x; y = p.y; z = p.z; }//정점좌표변경메소드2 다른정점 대입
	Point3(float xx, float yy, float zz) { x = xx; y = yy; z = zz; }//생성자: 정점초기화
	Point3() { x = y = z = 0; }//생성자: 초기화없을시 원점
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
	float x, y, z;//벡터성분
	void set(float dx, float dy, float dz) { x = dx; y = dy; z = dz; }//벡터생성메소드
	//void set(Vector3& v){ x = v.x; y = v.y; z = v.z;}//벡터생성메소드
	void set(Vector3 v) { x = v.x; y = v.y; z = v.z; }//벡터생성메소드, 인자 변환 문제 해결
	void flip() { x = -x; y = -y; z = -z; } //반대방향벡터
	void setDiff(Point3& a, Point3& b)//두벡터의차
	{
		x = a.x - b.x; y = a.y - b.y; z = a.z - b.z;
	}
	void normalize();//단위벡터로
	Vector3(float xx, float yy, float zz) { x = xx; y = yy; z = zz; } //생성자
	//Vector3(Vector3& v){x = v.x; y = v.y; z = v.z;}
	Vector3() { x = y = z = 0.0; }
	Vector3 cross(Vector3 b);//외적
	float dot(Vector3 b);//내적
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