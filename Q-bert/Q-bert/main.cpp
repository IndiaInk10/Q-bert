#define _CRT_SECURE_NO_WARNINGS

#include "Menu.h"
#include <iostream>

GLint width, height; // 창 크기에 따른 뷰포트 사이즈 및 뷰포트 분할 하기 위한 변수

//Menu* menu;
Map* map;
Qbert qbert;

void drawText(const char* text, int length, int x, int y);
void MyReshap(int NewWidth, int NewHeight);
void MyWorld();
void Idle();
void MyKeyboard(unsigned char key, int x, int y);

int main(int argc, char** argv)
{
	// 시작메뉴를 그리고,
	// 조작법 설명 메뉴를 띄우고,
	// 스테이지를 보여준다. 스테이지는 계속 나옴.
	// 조작은 키보드 동시입력은 안되도록 설정 KeyboardFunc을 사용
	width = 600; height = 600;

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(500, 110);
	glutCreateWindow("Q*bert");

	cout << "Game Start" << endl;

	glClearColor(0.0, 0.0, 0.0, 1.0);

	glutReshapeFunc(MyReshap);
	glutDisplayFunc(MyWorld);
	glutIdleFunc(Idle);
	glutKeyboardFunc(MyKeyboard);

	map = new Map();

	glutMainLoop();
	return 0;
}

void drawText(const char* text, int length, int x, int y)
{
	glMatrixMode(GL_PROJECTION);
	double* matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glOrtho(0, 600, 0, 600, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
		glLoadIdentity();
		glRasterPos2i(x, y);
		for (int i = 0; i < length; i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
		}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
}

void MyReshap(int NewWidth, int NewHeight) 
{
	if (NewHeight == 0)
		NewHeight = 1;

	width = NewWidth;
	height = NewHeight;
}
void MyWorld()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
		glLoadIdentity();
		gluPerspective(45.0, 1.0, 1.0, 100.0);
		//glOrtho(-30.0, 30.0, -30.0, 30.0, 1.0, 100.0);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			gluLookAt(60.0, 80.0, 60.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
			map->draw();
			map->drawTarget();
			qbert.draw();
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	string text[5];
	char data[4][6];
	text[0] = "PLAYER1";
	text[1] = "LEVEL:";
	text[2] = "ROUND:";
	text[3] = "LIFE:";
	text[4] = "=>     <=";
	_itoa(map->score, &data[0][0], 10);
	_itoa(map->level, &data[1][0], 10);
	_itoa(map->round, &data[2][0], 10);
	_itoa(qbert.life, &data[3][0], 10);
	glColor3f(1.0f, 0.0f, 1.0f);
	drawText(text[0].data(), text[0].size(), 100, 500);
	glColor3f(1.0f, 0.4f, 0.0f);
	drawText(text[3].data(), text[3].size(), 100, 470);
	drawText(text[4].data(), text[4].size(), 95, 440);
	glColor3f(0.0f, 1.0f, 0.0f);
	drawText(text[1].data(), text[1].size(), 440, 485);
	glColor3f(1.0f, 0.0f, 1.0f);
	drawText(text[2].data(), text[2].size(), 440, 470);
	glColor3f(1.0f, 0.4f, 0.0f);
	drawText(&data[0][0], 6, 100, 485);
	drawText(&data[3][0], 6, 150, 470);
	drawText(&data[1][0], 6, 500, 485);
	drawText(&data[2][0], 6, 500, 470);

	glutSwapBuffers();
}

void Idle()
{
	if (map->checkFinish())
	{
		map->getRColor();
		qbert.setQPos(2.5f, 37.5f, 2.5f);
		// Bonus Score
		map->score += 1000;
		map->round += 1;
	}
	if (map->round == MAX_ROUND)
	{
		map->level += 1;
		map->round = 0;
	}
	if (map->checkOut(qbert.getQPos()))
	{
		cout << "You fell, You lost your LIFE" << endl;
		qbert.life -= 1;
		qbert.setQPos(qbert.prePos);
	}
	if (qbert.life == 0)
	{
		cout << "Game Over Restart" << endl;
		map->restart();
		qbert.restart();
	}

	glutPostRedisplay();
}

void MyKeyboard(unsigned char key, int x, int y)
{
	Point3 check;
	qbert.prePos.set(qbert.getQPos());
	check.set(qbert.getQPos());
	switch (key)
	{
		// RIGHT && UP
	case 'W':
	case 'w':
	{
		check.set(check.x, check.y, check.z - 5.0f);
		qbert.move(check, map->checkUD(check));
		map->changeTile(qbert.getQPos());
		glutPostRedisplay();
		break;
	}
	// LEFT && UP
	case 'A':
	case 'a':
	{
		check.set(check.x - 5.0f, check.y, check.z);
		qbert.move(check, map->checkUD(check));
		map->changeTile(qbert.getQPos());
		glutPostRedisplay();
		break;
	}
	// LEFT && DOWN
	case 'S':
	case 's':
	{
		check.set(check.x, check.y, check.z + 5.0f);
		qbert.move(check, map->checkUD(check));
		map->changeTile(qbert.getQPos());
		glutPostRedisplay();
		break;
	}
	// RIGHT && DOWN
	case 'D':
	case 'd':
	{
		check.set(check.x + 5.0f, check.y, check.z);
		qbert.move(check, map->checkUD(check));
		map->changeTile(qbert.getQPos());
		glutPostRedisplay();
		break;
	}
	}
}