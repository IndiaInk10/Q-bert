#include "Map.h"

// 두 벡터의 외적
Vector3 Vector3::cross(Vector3 b)
{
	Vector3 c(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
	//메소드호출벡터와 파라미터벡터의 외적벡터를 반환하는 함수
	return c;
}
// 두 벡터의 내적
float Vector3::dot(Vector3 b)
{
	return x * b.x + y * b.y + z * b.z;
}
//해당벡터를 정규화하는 함수
void Vector3::normalize()
{
	double sizeSq = (double)x * x + (double)y * y + (double)z * z;// 크기를 구하고
	if (sizeSq < 0.0000001) {
		//cerr << "\nnormalize() sees vector (0,0,0)!";
		return;// does nothing to zero vectors;
	}
	float scaleFactor = 1.0f / (float)sqrt(sizeSq);// 크기로 나눠준다
	x *= scaleFactor; y *= scaleFactor; z *= scaleFactor;// 나눠준 비율을 기저에 적용하여 정규화
}

Map::Map(void)
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 4; i++)
	{
		tileColor[i].x = (rand() % 255 / 255.0f);
		tileColor[i].y = (rand() % 255 / 255.0f);
		tileColor[i].z = (rand() % 255 / 255.0f);
	}
	for (int j = 0; j < 28; j++)
	{
		tiles[j].color.set(tileColor[0]);
	}

	level = 1;
	round = 1;
	score = 0;
}
Map::~Map(void){}
void Map::getRColor()
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 4; i++)
	{
		tileColor[i].x = (rand() % 255 / 255.0f);
		tileColor[i].y = (rand() % 255 / 255.0f);
		tileColor[i].z = (rand() % 255 / 255.0f);
	}
}
// drawing POLYGON
void Map::drawUpside(Vector3 v)
{
	glBegin(GL_POLYGON);
		glVertex3f(v.x, v.y, v.z);
		glVertex3f(v.x, v.y, v.z - 5.0f);
		glVertex3f(v.x - 5.0f, v.y, v.z - 5.0f);
		glVertex3f(v.x - 5.0f, v.y, v.z);
	glEnd();
}
void Map::drawSide(Vector3 v, Vector3 tileColor)
{
	if (round % 2 != 0)
	{
		glColor3f((tileColor.x + 0.3f) / 1.0f, (tileColor.y + 0.3f) / 1.0f, (tileColor.z + 0.3f) / 1.0f);
		glBegin(GL_POLYGON);
			glVertex3f(v.x, v.y, v.z);
			glVertex3f(v.x - 5.0f, v.y, v.z);
			glVertex3f(v.x - 5.0f, v.y - 5.0f, v.z);
			glVertex3f(v.x, v.y - 5.0f, v.z);
		glEnd();
		glColor3f(tileColor.x, tileColor.y, tileColor.z);
		glBegin(GL_POLYGON);
			glVertex3f(v.x, v.y, v.z);
			glVertex3f(v.x, v.y - 5.0f, v.z);
			glVertex3f(v.x, v.y - 5.0f, v.z - 5.0f);
			glVertex3f(v.x, v.y, v.z - 5.0f);
		glEnd();
	}
	else
	{
		glColor3f(tileColor.x, tileColor.y, tileColor.z);
		glBegin(GL_POLYGON);
			glVertex3f(v.x, v.y, v.z);
			glVertex3f(v.x - 5.0f, v.y, v.z);
			glVertex3f(v.x - 5.0f, v.y - 5.0f, v.z);
			glVertex3f(v.x, v.y - 5.0f, v.z);
		glEnd();
		glColor3f((tileColor.x + 0.3f) / 1.0f, (tileColor.y + 0.3f) / 1.0f, (tileColor.z + 0.3f) / 1.0f);
		glBegin(GL_POLYGON);
			glVertex3f(v.x, v.y, v.z);
			glVertex3f(v.x, v.y - 5.0f, v.z);
			glVertex3f(v.x, v.y - 5.0f, v.z - 5.0f);
			glVertex3f(v.x, v.y, v.z - 5.0f);
		glEnd();
	}
}
void Map::drawTarget()
{
	Vector3 v;
	v.set(7.5f, 42.5f, 30.0f);
	if (level == 1)
	{
		glColor3f(tileColor[1].x, tileColor[1].y, tileColor[1].z);
		glBegin(GL_POLYGON);
			glVertex3f(v.x, v.y, v.z);
			glVertex3f(v.x, v.y, v.z - 2.5f);
			glVertex3f(v.x - 2.5f, v.y, v.z - 2.5f);
			glVertex3f(v.x - 2.5f, v.y, v.z);
		glEnd();
	}
	else
	{
		glColor3f(tileColor[2].x, tileColor[2].y, tileColor[2].z);
		glBegin(GL_POLYGON);
			glVertex3f(v.x, v.y, v.z);
			glVertex3f(v.x, v.y, v.z - 2.5f);
			glVertex3f(v.x - 2.5f, v.y, v.z - 2.5f);
			glVertex3f(v.x - 2.5f, v.y, v.z);
		glEnd();
	}
}
void Map::draw()
{
	int k = 7, tCount = 0;
	// tile draw Start Position
	Vector3 tileSPos(5.0f, 5.0f, 35.0f);

	for (int i = 0; i < 7; i++)
	{
		if (i != 0)
		{
			k -= 1;
			tileSPos.set(tileSPos.x + 5.0f, tileSPos.y, tileSPos.z - 5.0f);
		}
		// tile draw Position
		Vector3 tileDPos;
		tileDPos.set(tileSPos);

		for (int j = 0; j < k; j++)
		{
			// upside tile
			tiles[tCount].tilePos.set(tileDPos.x - 2.5f, tileDPos.y - 2.5f, tileDPos.z - 2.5f);
			/*cout << "tile[" << tCount << "]: " << tiles[tCount].tilePos.x << " " <<
				tiles[tCount].tilePos.y << " " << tiles[tCount].tilePos.z << endl;*/
			glColor3f(tiles[tCount].color.x, tiles[tCount].color.y, tiles[tCount].color.z);
			tCount += 1;
			drawUpside(tileDPos);
			// side tile
			drawSide(tileDPos, tileColor[3]);

			tileDPos.y += 5.0f;
			tileDPos.z -= 5.0f;
		}
	}
}
bool Map::checkUD(Point3 p)
{
	bool found = false;

	for (int i = 0; i < 28; i++)
	{
		if (tiles[i].tilePos == p)
		{
			// Up
			found = true;
			return found;
		}
		else
			continue;
	}

	// Down
	return found;
}
bool Map::checkOut(Point3 p)
{
	if (p.x < 0.0f || p.x > 35.0f || p.y < 5.0f || p.z < 0.0f || p.z > 35.0f)
	{
		return true;
	}
	else
		return false;
}

bool Map::checkFinish()
{
	if (level == 1)
	{
		for (int i = 0; i < 28; i++)
		{
			if (tiles[i].color == tileColor[1])
			{
				continue;
			}
			else
				return false;
		}

		return true;
	}
	else
	{
		for (int i = 0; i < 28; i++)
		{
			if (tiles[i].color == tileColor[2])
			{
				continue;
			}
			else
				return false;
		}

		return true;
	}
}

// change tile color
void Map::changeTile(Point3 p)
{
	p.y -= 5.0f;
	if (level == 1)
	{
		for (int i = 0; i < 28; i++)
		{
			if (tiles[i].tilePos == p)
			{
				if (tiles[i].color != tileColor[1])
				{
					tiles[i].color.set(tileColor[1]);
					score += 25;
					break;
				}
				else
					break;
			}
			else
				continue;
		}
	}
	else
	{
		for (int i = 0; i < 28; i++)
		{
			if (tiles[i].tilePos == p)
			{
				if (tiles[i].color != tileColor[2])
				{
					if (tiles[i].color != tileColor[1])
					{
						tiles[i].color.set(tileColor[1]);
						score += 25;
						break;
					}
					else
					{
						tiles[i].color.set(tileColor[2]);
						score += 25;
						break;
					}
				}
				else
					break;
			}
			else
				continue;
		}
	}
}
void Map::restart()
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 4; i++)
	{
		tileColor[i].x = (rand() % 255 / 255.0f);
		tileColor[i].y = (rand() % 255 / 255.0f);
		tileColor[i].z = (rand() % 255 / 255.0f);
	}
	for (int j = 0; j < 28; j++)
	{
		tiles[j].color.set(tileColor[0]);
	}

	level = 1;
	round = 1;
	score = 0;
}