//Luis Rangel(luisrngl5@gmail.com or LuisRangel@my.unt.edu
//Date:2/3/2016
//Class:CSCE 4230
//Assignment:Programming Assigment 1:The Chaos Game
//We are to impliment the chaos game!
//This program refernces the hello.c from the UNT CSCE 4230 class page

#include<GL/glut.h>//Include file for freeglut
#include<stdlib.h>
#include<time.h>//For the RNG

//This is the global variable zone, these are the vertices needed for the program
float x1 = .10;//v1
float y1 = .30;//v1
float x2 = .50;//v2
float y2 = .90;//v2
float x3 = .90;//v3
float y3 = .30;//v3
float x0 = .5;//p0
float y0 = .6;//p0

void display() {//This is where the visual magic is supposed to happen
	glClear(GL_COLOR_BUFFER_BIT);//Have to clear the screen first
	//In order to add some personal charm, I am going to draw some very small triangles where the main points are
	/*glBegin(GL_TRIANGLES);
		//The Red Triangle
		glColor4f(1.0, 0.0, 0.0, 1);//Blue
		glVertex3f(x2, y2, 0);//R_Top
		glVertex3f(x2 - 0.03, y2 - 0.03, 0);//R_Left
		glVertex3f(x2 + 0.03, y2 - 0.03, 0);//R_Right
		//The Green Triangle
		glColor4f(0, 1, 0, 1);//Green
		glVertex3f(x1, y1, 0);//G_Left
		glVertex3f(x1 + .03, y1 + .03, 0);//G_Top
		glVertex3f(x1 + .06, y1, 0);//G_Right
		//The Blue Triangle
		glColor4f(0, 0, 1, 1);//Blue
		glVertex3f(x3, y3, 0);//B_Right
		glVertex3f(x3 - .03, y3 + .03, 0);//B_Top
		glVertex3f(x3 - .06, y3, 0);//B_Left
	glEnd();//Ending the top triangle sequence*/
	//I have commented out the Triangle sequence as the points ended up covering them anyway
	//As requested by the Professor I will now draw 60,001 points!
	//First I will draw p0 as a yellow point!
	glBegin(GL_POINTS);
	glColor4f(1, 1, 0, 1);//Yellow
		glVertex2f(x0, y0);
	glEnd();
	int n = 60000;
	int choice;
	float x, y, Px, Py;//These will be used to calculate the endpoint
	Px = x0;
	Py = y0;
	srand(time(NULL));//Seeding the RNG
	for (int i = 0; i < n; i++) {//Executes the loop 60000 times, also i < n is equal to i <= n -1
		choice = (rand() % 3) + 1;//Returns a number between 1-3
		if (choice == 1) {//The RNG chooses RED
			//Calculating Midpoint
			x = (Px + x2) / 2;
			y = (Py + y2) / 2;
			//Making a point
			glBegin(GL_POINTS);
				glColor4f(1, 0, 0, 1);//Makes the point Red
				glVertex2f(x, y);
			glEnd();
			Px = x;
			Py = y;
		}
		if (choice == 2) {//The RNG chooses GREEN
			//Calculating Midpoint
			x = (Px + x1) / 2;
			y = (Py + y1) / 2;
			//Making a point
			glBegin(GL_POINTS);
				glColor4f(0, 1, 0, 1);//Makes the point Green
				glVertex2f(x, y);
			glEnd();
			Px = x;
			Py = y;
		}
		if (choice == 3) {//The RNG chooses BLUE
			//Calculating Midpoint
			x = (Px + x3) / 2;
			y = (Py + y3) / 2;
			//Making a point
			glBegin(GL_POINTS);
				glColor4f(0, 0, 1, 1);//Makes the point Blue
				glVertex2f(x, y);
			glEnd();
			Px = x;
			Py = y;
		}
	}

	glFlush();//This executes the visual commands
}

void keyboarding(unsigned char key, int x, int y) {//This will enable the escape button!
	switch (key) {
		case 27://The escape button
			exit(0);
			break;
		default:
			break;
	}
}

void init(void)//Initialzing a bunch of things
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv)//The good old familiar main loop
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(250, 250);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("The Chaos Game");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboarding);
	glutMainLoop();
	return 0;   /* ANSI C requires main to return int. */
}