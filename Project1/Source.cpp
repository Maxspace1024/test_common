#include<Windows.h>
#include<GL/glew.h>
#include<GL/freeglut.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#define _USE_MATH_DEFINES
#include"basicFunc.h"
#include"classDef.h"
#include"Imagx.h"

extern Player p1=Player();
extern Timer myTimer(30); //�C���ɪ�(��)
extern ProgressBar myProgressBar(100); //���|����

//�Ϥ�����
extern Imagx helpMenu;

//�C���}�l�e��
void drawStart() {
	//�i�H��K�ĭq�~�檺�e���A�ϥΪť���i�}�l�C��
	drawPlayer();

	//helpMenu
	glPushMatrix();
	{
		glTranslatef(0,4,2);
		glRotatef(-10,1,0,0);
		helpMenu.drawImg();
	}
	glPopMatrix();
}

//�C���B��e��
void drawGame() {
	
	//�a�O(�e,��)
	drawGround(6, 600);

	//�ؿv
	drawBuildings();

	//��ê��
	drawObstacles();

	//player
	drawPlayer();

	//�W�誺�i�ױ�
	drawProgressBar();

	//glTranslated(3, 2, 0);
	//glutSolidSphere(1, 100, 100);
}

//�C�������e��
void drawEnd() {
	//�i�H��K�Ħ���~�檺�e��
	drawProgressBar();
}

//�ɶ���F
void drawTimeUp() {
	//�i�H��K�ĦY����~��A��P�P���e��
	drawObstacles();
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	p1.lookAt();
	//====================================

	switch (p1.status)
	{
	case START:
		drawStart();
		break;

	case GAME:
		drawGame();
		break;

	case END:
		drawEnd();
		break;

	case TIMEUP:
		drawTimeUp();
		break;

	default:
		break;
	}
	drawTimer();
	//====================================

	glutSwapBuffers();
}



int main(int argc,char **argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH |GLUT_MULTISAMPLE);
	glutInitWindowPosition(500,200);
	glutInitWindowSize(700,700);
	glutCreateWindow("TITLE");

	init();

	GLenum err = glewInit();
	if( err != GLEW_OK){
		printf("GLEW_ERROR\n");
	}

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutTimerFunc(1000,timer,0);
	glutMainLoop();
	return 0;
}
