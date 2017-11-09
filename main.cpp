#include <cstdio>
#include <cstdlib>
#include <vector>
#include <windows.h>
#include <GL\glut.h>
#include <cstring>
#include "button.h"
#include "Texture.h"
//�����ȫ������ϵ��˼�����������⣬��ô����Ҫע�����˷���˳��ʹ����е�˳�����෴�ġ����þֲ�����ϵ��˼���Ļ������еĲ�����������ڵ�ǰ���ϱ仯������ϵ����ˣ�����˷�����Ȼ���������ٴ����г��ֵ�˳��һ����
//glPushMatrix()��glPopMatrix()����������һ�α任�Ա��α任��Ӱ�죬ʹ�ñ��α任���ǻ�����������ϵ��ԭ��Ϊ�ο�����еġ���ˣ�ʵ��̫��ϵ��ֻ��Ҫ��̫���Ȼ�����Ĭ������������ϵԭ�㣩��Ȼ�󱣴浱ǰ��ͼ���������ǣ��ָ���ͼ������˼·������ȫ������ϵ��˼�롣
using std::vector;
using std::pair;

#define MAX_PATH_NAME 128
void init() {
	

}

GLfloat windowLeft, windowDown;
void reshape(int w, int h)//�Զ������´��ڵĴ�С�����أ�
{
	glViewport(0, 0, w, h);//�ڴ�������ʾ��������ʾ�������½�������ʾ����Ŀ����߶�
	glMatrixMode(GL_PROJECTION);//������Ҫ����ͶӰ���ò���
	glLoadIdentity();//���ñ任����

					 //ʹ������ͶӰ�۲����壬�۲췽ʽ��ƽ���޼��ռ�
	if (w <= h) {//����ʹ���ۿ�߱���Σ�ʼ�չ۲촰����ô���һ������
		glOrtho(-2, 2, -2.0*(GLfloat)h / (GLfloat)w, 2.0*(GLfloat)h / (GLfloat)w, 0, 20);
		windowLeft = -2;
		windowDown = -2.0*(GLfloat)h / (GLfloat)w;
		//����۲�ռ�ģ����ҡ��¡��ϡ�ǰ����
	}
	else {
		glOrtho(-2.0*(GLfloat)w / (GLfloat)h, 2.0*(GLfloat)w / (GLfloat)h, -2.0, 2.0, 0, 20);
		windowLeft = -2.0*(GLfloat)w / (GLfloat)h;
		windowDown = -2;
	}

	//Ҳ����ʹ��͸��ͶӰͶӰ�۲���
	//gluPerspective(90, w / h, 0.1, 6);//�����������Ҫ����
	//����۲�ռ�Ĵ�ֱ�Ƕȣ���߱ȣ�ǰ���棬�����

	glMatrixMode(GL_MODELVIEW);//�����������Ӿ����ò���
	glLoadIdentity();//���ñ任����
					 //ps.��������GL_TEXTUREʱ���Խ����������


}

GLfloat vertices[][3] = { { -1.0,-1.0,-1.0 },{ 1.0,-1.0,-1.0 },{ 1.0,1.0,-1.0 },{ -1.0,1.0,-1.0 },{ -1.0,-1.0,1.0 },
{ 1.0,-1.0,1.0 },{ 1.0,1.0,1.0 },{ -1.0,1.0,1.0 } };//�������λ��

GLfloat colors[][3] = { { 1.0,0.0,0.0 },{ 0.0,1.0,1.0 },{ 1.0,1.0,0.0 },{ 0.0,1.0,0.0 },{ 0.0,0.0,1.0 },
{ 1.0,0.0,1.0 },{ 0.0,1.0,1.0 },{ 1.0,1.0,1.0 } };//ÿ�������ɫ

void polygon(int a, int b, int c, int d, bool line)
{
	if (!line) {
		glBegin(GL_POLYGON);
		glColor3fv(colors[a]);
		glVertex3fv(vertices[a]);
		glColor3fv(colors[b]);
		glVertex3fv(vertices[b]);
		glColor3fv(colors[c]);
		glVertex3fv(vertices[c]);
		glColor3fv(colors[d]);
		glVertex3fv(vertices[d]);
		glEnd();
	}
	else {
		glBegin(GL_POLYGON);
		glVertex3fv(vertices[a]);
		glVertex3fv(vertices[b]);
		glVertex3fv(vertices[c]);
		glVertex3fv(vertices[d]);
		glEnd();
	}
}

void colorcube(bool line)
{//��������
	polygon(0, 3, 2, 1, line);
	polygon(2, 3, 7, 6, line);
	polygon(0, 4, 7, 3, line);
	polygon(1, 2, 6, 5, line);
	polygon(4, 5, 6, 7, line);
	polygon(0, 1, 5, 4, line);

}

void setLight() {
	GLfloat lmodel_ambient[] = { 1,1,1,1 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	GLfloat light_position[] = { 1,1,1,0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	GLfloat light[] = { 1,1,1,1 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, light);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, light);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, light);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50.0);
}

enum Model { CUBE_SLOID, CUBE_LINE, CUBE_POINT, BALL, EARTH }model;
vector<pair<int, GLfloat>> rotateLog;
const GLfloat axis[3][3] = { {1.0,0.0,0.0},{0.0,1.0,0.0},{0.0,0.0,1.0} };
GLfloat bigger = 1.0;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�����ɫ����ά���棿
	glMatrixMode(GL_MODELVIEW);//�����������Ӿ����ò���
	glLoadIdentity();//���ñ任����
	gluLookAt(15, 0, 0, 0, 0, 0, 0, 0, 1);//�������xyz���۲���xyz������Ϸ����xyz
	setLight();//���ù���
	glPushMatrix();
	for (int i = rotateLog.size()-1; i >= 0; i--)
		glRotatef(rotateLog[i].second, axis[rotateLog[i].first][0], axis[rotateLog[i].first][1], axis[rotateLog[i].first][2]);
	//������ת

	glScalef(bigger, bigger, bigger);//���÷Ŵ�
	 
	switch (model) {
	case CUBE_SLOID://��������ɫģʽ
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		colorcube(false);
	case CUBE_LINE://���ñ���ɫģʽ
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glColor3f(0.5, 0.5, 0.5);
		colorcube(true);
	case CUBE_POINT://���õ���ɫģʽ
		glColor3f(1, 1, 1);
		glPointSize(10);
		glBegin(GL_POINTS);
		for (int i = 0; i < 8; i++)
			glVertex3f(vertices[i][0], vertices[i][1], vertices[i][2]);
		glEnd();
		break;
	case BALL://����Ϊ��۲����
		glColor3f(0.2, 0.2, 0.8);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glutSolidSphere(1, 50, 50);
		glColor3f(0.5, 0.5, 0.5);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glutSolidSphere(1, 50, 50);
		break;
	case EARTH://����Ϊ����۲�����
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glRotatef(90, 1, 0, 0);
		glRotatef(90, 0, 1, 0);
		char localPath[MAX_PATH_NAME];
		GetCurrentDirectoryA(MAX_PATH_NAME, localPath);
		strcat(localPath, "\\");
		strcat(localPath, "tu.jpg");
		GLuint texid;
		BuildTexture(localPath, texid);
		glBindTexture(GL_TEXTURE_2D, texid);
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		GLfloat planes[] = { 0.5,0,0,0.5 };
		GLfloat planet[] = { 0,0.5,0,0.5 };
		glTexGenfv(GL_S, GL_OBJECT_PLANE, planes);
		glTexGenfv(GL_T, GL_OBJECT_PLANE, planet);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glutSolidSphere(1, 50, 50);
		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		break;
	}
	glPopMatrix();
	glPushMatrix();
	glTranslatef(10, 0, 0);
	glRotatef(90, 1, 0, 0);
	glRotatef(90, 0, 1, 0);
	button hint(windowLeft, windowDown, 2.26, 0.7);
	hint.setTex(1);
	char localPath[MAX_PATH_NAME];
	GetCurrentDirectoryA(MAX_PATH_NAME, localPath);
	strcat(localPath, "\\");
	strcat(localPath, "set.bmp");
	hint.setTexImage(localPath);
	hint.show();
	glPopMatrix();
	glutSwapBuffers();//�û����棨ˢ�»��棬��Ϊʹ����˫���棩
}


void logRotate(int axis, int count) {
	if (rotateLog.size() == 0)
		rotateLog.push_back(pair<int, GLfloat>(axis, count));
	else if (rotateLog.back().first == axis) {
		rotateLog.back().second += count;
		if ((int)rotateLog.back().second % 360 == 0)
			rotateLog.pop_back();
	}
	else rotateLog.push_back(pair<int, GLfloat>(axis, count));
}

void keyboard(unsigned char key, int _x, int _y) {
	if (key == 'u' && model != EARTH)
		rotateLog.clear();
	if (key == 'i' && model != BALL)
		rotateLog.clear();
	if ((key == 'j' || key == 'k' || key == 'l') && (model == EARTH || model == BALL))
		rotateLog.clear();
	switch (key)
	{//��Ӧ�л�ģ���¼�
	case 'j':
		model = CUBE_SLOID;
		break;
	case 'k':
		model = CUBE_LINE;
		break;
	case 'l' :
		model = CUBE_POINT;
		break;
	case 'u':
		model = EARTH;
		break;
	case 'i' :
		model = BALL;
		break;
	}
	switch (key)
	{//��Ӧ��ת�¼�
	case 'q':
		logRotate(0, 1);
		break;
	case 'e':
		logRotate(0, -1);
		break;
	case 'w':
		logRotate(1, -1);
		break;
	case 's':
		logRotate(1, 1);
		break;
	case 'a':
		logRotate(2, -1);
		break;
	case 'd':
		logRotate(2, 1);
		break;
	}
	switch (key)
	{
	case 'r':
		bigger *= 1.01;
		break;
	case 'f':
		bigger /= 1.01;
		if (bigger == 0)
			bigger = 1;
		break;
	}
	glutPostRedisplay();//ˢ����ͼ
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);//��ʼ��GLUT�⣻
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//˫����ģʽ��RGBģʽ����άģʽ��
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1200, 1000);//���ô��ڴ�С
	glutCreateWindow("colorcube");//���ô�������
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//˫���դ��
	glEnable(GL_DEPTH_TEST);//������άģʽ��
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glLineWidth(3);//ʹ��3ά��դ��
	init();
	glutReshapeFunc(reshape);//���õ����ڴ�С�����ı�ʱ���õĺ���
	glutDisplayFunc(display);//����ˢ�º���
	glutKeyboardFunc(keyboard);//���ü�����Ӧ�¼�
	glutMainLoop();//�����Զ�ˢ��ѭ��
	return 0;
}