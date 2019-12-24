#include "Qbert.h"

Qbert::Qbert(void) 
{
	qPos.set(2.5f, 37.5f, 2.5f);
	prePos.set(qPos);
	life = 3;
	qViewAngle = 0.0f;
}
Qbert::~Qbert(void){}
void Qbert::setQPos(float x, float y, float z)
{
	qPos.x = x;
	qPos.y = y;
	qPos.z = z;
}
void Qbert::setQPos(Point3 p)
{
	qPos.set(p);
}
Point3 Qbert::getQPos()
{
	return qPos;
}
void Qbert::draw()
{
	// Orange
	glColor3f(1.0f, 0.4f, 0.0f);

	glTranslatef(qPos.x, qPos.y, qPos.z);
	glutSolidSphere(2.0, 15, 15);
}
// check Up || Down and Move
void Qbert::move(Point3 QPOS, bool UD)
{
	// Down
	if (UD == false)
	{
		qPos.set(QPOS);
		qPos.y -= 5.0f;
		//cout << "x: " << qPos.x << "y: " << qPos.y << "z: " << qPos.z << endl;
	}
	// Up: UD == true
	else
	{
		qPos.set(QPOS);
		qPos.y += 5.0f;
		//cout << "x: " << qPos.x << "y: " << qPos.y << "z: " << qPos.z << endl;
	}
}
void Qbert::restart()
{
	qPos.set(2.5f, 37.5f, 2.5f);
	prePos.set(qPos);
	life = 3;
}