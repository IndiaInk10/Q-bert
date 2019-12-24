#pragma once
#include "Map.h"

class Qbert 
{
private:
	// Qbert's Position
	Point3 qPos;
	// Qbert's Viewing Point
	GLfloat qViewAngle;
public:
	Point3 prePos;
	GLint life;
	Qbert();
	~Qbert();
	void setQPos(float x, float y, float z);
	void setQPos(Point3 p);
	Point3 getQPos();
	void draw();
	// check Up || Down and Move
	void move(Point3 QPOS, bool UD);
	// GameOver Restart
	void restart();
};