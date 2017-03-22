//Luis Rangel(luisrngl5@gmail.com or LuisRangel@my.unt.edu)
//Date:3/1/2016
//Class:CSCE 4230
//Description:This program is view into really primative space
#ifdef __APPLE__//Portable!
#include<GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <math.h>//For the hexagon coordinates

static GLfloat spin = 0.00;//This controls the speed of the animation
static GLfloat Mspeed = 0.00;//This controls the speed of translating things
static GLfloat Lighting = 1.00;//This controls the 'lighting' of the scene
static GLfloat s_factor = 0.00;//The spinning factor defined by user, 0.01 by default, the higher the absolute value of the number, the faster it spins!
static GLfloat l = 8.0;//The distance of the spaceship from the center
static GLfloat r = 1.0;//Radius of space ship
static int M_menu;//This handles the menu
static int val = 0;
static int win;
static int playing = 0;//This keeps track which speed the animation is being played at

void keyboard(unsigned char key, int x, int y);

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT);
   glPushMatrix();
   //Setting up the speeed
   Mspeed = Mspeed + (s_factor * 2);//This makes sure the moon actually moves
   if (Mspeed > 500) {//Reset the moon once it leaves frame
	   Mspeed = 0;
   }
   if (Mspeed < -30) {
	   Mspeed = 500;
   }
   //Drawing the Rainbow Star
   glRotatef(spin, 0.0, 0.0, 1.0);
   glColor3f(1.0, 1.0, 1.0);//The Center is White
   glBegin(GL_POLYGON);//Octagon
   glVertex3f(-0.5, 1.0, 0.0);//Top Left
   glVertex3f(0.5, 1.0, 0.0);//Top Right
   glVertex3f(1.0, 0.5, 0.0);//Right Top
   glVertex3f(1.0, -0.5, 0.0);//Right Bottom
   glVertex3f(0.5, -1.0, 0.0);//Bottom Right
   glVertex3f(-0.5, - 1.0, 0.0);//Bottom Left
   glVertex3f(-1.0, -0.5, 0.0);//Left Bottom
   glVertex3f(-1.0, 0.5, 0.0);//Left Top
   glEnd();
   glColor3f(1.0, 0.0, 0.0);//North Petal will be Red
   glBegin(GL_POLYGON);
   glVertex3f(0.0, 1.0, 0.0);//Bottom Vertex
   glVertex3f(-0.5, 2.5, 0.0);//Left Vertex
   glVertex3f(0.0, 6.0 , 0.0);//Top
   glVertex3f(0.5, 2.5, 0.0);//Right
   glEnd();
   glColor3f(1.0, 0.65, 0.0);//The Northeast Petal will be Orange
   glBegin(GL_POLYGON);
   glVertex3d((sqrt(2) / 2), (sqrt(2) / 2), 0.0);//Bottom
   glVertex3d(((sqrt(2) / 2) + 0.75), ((sqrt(2) / 2) + 0.25), 0.0);//Right
   glVertex3d(3.0, 3.0, 0.0);//Top
   glVertex3d(((sqrt(2) / 2) + 0.25), ((sqrt(2) / 2) + 0.75), 0.0);//Left
   glEnd();
   glColor3f(1.0, 1.0, 0.0);//East Petal will be yellow
   glBegin(GL_POLYGON);
   glVertex3f(1.0, 0.0, 0.0);//Left
   glVertex3f(2.5, 0.5, 0.0);//Top
   glVertex3f(6.0, 0.0, 0.0);//Right
   glVertex3f(2.5, -0.5, 0.0);
   glEnd();
   glColor3f(0.65, 1.0, 0.0);//The Southeast Petal will be Lime
   glBegin(GL_POLYGON);
   glVertex3d((sqrt(2) / 2), -(sqrt(2) / 2), 0.0);//Bottom
   glVertex3d(((sqrt(2) / 2) + 0.75), -((sqrt(2) / 2) + 0.25), 0.0);//Right
   glVertex3d(3.0, -3.0, 0.0);//Top
   glVertex3d(((sqrt(2) / 2) + 0.25), -((sqrt(2) / 2) + 0.75), 0.0);//Left
   glEnd();
   glColor3f(0.0, 1.0, 0.0);//South Petal will be green
   glBegin(GL_POLYGON);
   glVertex3f(0.0, -1.0, 0.0);//Top
   glVertex3f(0.5, -2.5, 0.0);//Right
   glVertex3f(0.0, -6.0, 0.0);//Bottom
   glVertex3f(-0.5, -2.5, 0.0);//Left
   glEnd();
   glColor3f(0.0, 1.0, 0.6);//The Southwest Petal will be Cyan
   glBegin(GL_POLYGON);
   glVertex3d(-(sqrt(2) / 2), -(sqrt(2) / 2), 0.0);//Bottom
   glVertex3d(-((sqrt(2) / 2) + 0.75), -((sqrt(2) / 2) + 0.25), 0.0);//Right
   glVertex3d(-3.0, -3.0, 0.0);//Top
   glVertex3d(-((sqrt(2) / 2) + 0.25), -((sqrt(2) / 2) + 0.75), 0.0);//Left
   glEnd();
   glColor3f(0.0, 0.0, 1.0);//West Petal will be blue
   glBegin(GL_POLYGON);
   glVertex3f(-1.0, 0.0, 0.0);//Right
   glVertex3f(-2.5, 0.5, 0.0);//Top
   glVertex3f(-6.0, 0.0, 0.0);//Left
   glVertex3f(-2.5, -0.5, 0.0);//Bottom
   glEnd();
   glColor3f(0.73, 0.0, 1.0);//The Northwest Petal will be Purple
   glBegin(GL_POLYGON);
   glVertex3d(-(sqrt(2) / 2), (sqrt(2) / 2), 0.0);//Bottom
   glVertex3d(-((sqrt(2) / 2) + 0.75), ((sqrt(2) / 2) + 0.25), 0.0);//Right
   glVertex3d(-3.0, 3.0, 0.0);//Top
   glVertex3d(-((sqrt(2) / 2) + 0.25), ((sqrt(2) / 2) + 0.75), 0.0);//Left
   glEnd();
   glRotatef(-spin, 0.0, 0.0, 1.0);//Cancels spin
   //This will represent a moon passing in front of the rainbow star
   glTranslatef(Mspeed * .05, 0.0, 0.0);//This Moves the moon
   glColor3f(0.2, 0.2, 0.2);//The Moon is Dark Gray
   glBegin(GL_POLYGON);//Octagon
   glVertex3f(-10.5 , 1.0, 0.0);//Top Left
   glVertex3f(-9.5, 1.0, 0.0);//Top Right
   glVertex3f(-9.0, 0.5, 0.0);//Right Top
   glVertex3f(-9.0, -0.5, 0.0);//Right Bottom
   glVertex3f(-9.5, -1.0, 0.0);//Bottom Right
   glVertex3f(-10.5, -1.0, 0.0);//Bottom Left
   glVertex3f(-11.0, -0.5, 0.0);//Left Bottom
   glVertex3f(-11.0, 0.5, 0.0);//Left Top
   glEnd();
   glTranslatef(-Mspeed * .05, 0.0, 0.0);//This stops other things from moving
//This will represent an asteroid field
   glTranslatef(Mspeed * .05, -Mspeed * .03, 0.0);//Moves the star
   glColor3f(0.41, 0.17, 0.0);//The asteroids will be brown
   glBegin(GL_POLYGON);
   glVertex3f(-11.0, 11.0, 0.0);//North
   glVertex3f(-11.5, 10.0, 0.0);//Northeast
   glVertex3f(-10, 9.0, 0.0);//East
   glVertex3f(-11.5, 9.0, 0.0);//Southeast
   glVertex3f(-12.0, 8.0, 0.0);//South
   glVertex3f(-13.5, 9.0, 0.0);//Southwest
   glVertex3f(-14, 10.0, 0.0);//West
   glVertex3f(-13.5, 11.0, 0.0);//Northwest
   glEnd();
   glBegin(GL_POLYGON);
   glVertex3f(-15.0, 6.0, 0.0);//North
   glVertex3f(-15.5, 5.0, 0.0);//Northeast
   glVertex3f(-14, 4.0, 0.0);//East
   glVertex3f(-15.5, 4.0, 0.0);//Southeast
   glVertex3f(-16.0, 3.0, 0.0);//South
   glVertex3f(-17.5, 4.0, 0.0);//Southwest
   glVertex3f(-18, 5.0, 0.0);//West
   glVertex3f(-17.5, 6.0, 0.0);//Northwest
   glEnd();
   glBegin(GL_POLYGON);
   glVertex3f(-11.0, 1.0, 0.0);//North
   glVertex3f(-11.5, 0.0, 0.0);//Northeast
   glVertex3f(-10, -1.0, 0.0);//East
   glVertex3f(-11.5, -1.0, 0.0);//Southeast
   glVertex3f(-12.0, -2.0, 0.0);//South
   glVertex3f(-13.5, -1.0, 0.0);//Southwest
   glVertex3f(-14, 0.0, 0.0);//West
   glVertex3f(-13.5, 1.0, 0.0);//Northwest
   glEnd();
   glTranslatef(-Mspeed * .05, Mspeed * .03, 0.0);//Cancels movement
   //This will represent the space ship!
   glRotatef(-spin * 2, 0.0, 0.0, 1.0);//Starts spin
   glColor3f(0.5, 0.5, 0.5);//The space ship will be gray!!
   glBegin(GL_POLYGON);//This is a space ship!
   glVertex3f(0.5 * r, -l + ((sqrt(3.0) / 2) * r), 0.0);//A-Top Right Vertex
   glVertex3f(-0.5 * r, -l +((sqrt(3.0) / 2) * r), 0.0);//B-Top Left Vertex
   glVertex3f(-r, -l, 0.0);//C-Middle Left
   glVertex3f(-0.5 * r, -l - ((sqrt(3.0) / 2) * r), 0.0);//D-Bottom Left
   glVertex3f(0.5 * r, -l - ((sqrt(3.0) / 2) * r), 0.0);//E-Bottom Right
   glVertex3f(r, -l, 0.0);//F-Middle Right, have to go around to get the hexagon drawn right
   glEnd();
   glColor3f(0.0, 0.0, 1.0);//This is the windshield of the ship
   glBegin(GL_POLYGON);
   glVertex3f(-0.3 * r, -l + .1, 0.0);//Top Left
   glVertex3f(0.0, -l + .25, 0.0);//Middle Top
   glVertex3f(0.3 * r, -l + .1, 0.0);//Top Right
   glVertex3f(0.3 * r, -l + .05, 0.0);//Bottom Right
   glVertex3f(0.0, -l + .025, 0.0);//Middle Bottom
   glVertex3f(-0.3 * r, -l + .05, 0.0);//Bottom Left
   glEnd();
   glRotatef(spin * 2, 0.0, 0.0, 1.0);//Cancels spin
   //This represents the second spaceship
   glRotatef(spin * 2, 0.0, 0.0, 1.0);//Rotates the space ship
   glColor3f(1.0, 0.0, 0.0);//The space ship body is red
   glBegin(GL_POLYGON);
   glVertex3f(7.0, 8.0, 0.0);//Front Tip
   glVertex3f(9.0, 7.0, 0.0);//Top Wing
   glVertex3f(8.5, 8.0, 0.0);//Middle
   glVertex3f(9.0, 9.0, 0.0);//Bottom Wing
   glEnd();
   glColor3f(0.0, 0.0, 1.0);//Windshield is blue
   glBegin(GL_TRIANGLES);//Ship Windshield
   glVertex3f(7.2, 8.0, 0.0);//Tip
   glVertex3f(7.4, 7.8, 0.0);//Bottom
   glVertex3f(7.4, 8.2, 0.0);//Top
   glEnd();
   glRotatef(-spin * 2, 0.0, 0.0, 1.0);//Cancel spin
   //Drawing the speed symbol
   if (playing == 1) {
	   glColor3f(0.0, 1.0, 0.0);//The play symbol will be green
	   glBegin(GL_TRIANGLES);
	   glVertex3f(6.5, -8.5, 0.0);//Left Top
	   glVertex3f(6.5, -9.5, 0.0);//Left Bottom
	   glVertex3f(7.5, -9, 0.0);//Right
	   glEnd();
   }
   if (playing == -1) {
	   glColor3f(1.0, 0.0, 0.0);//The reverse symbol will be red
	   glBegin(GL_TRIANGLES);
	   glVertex3f(7.5, -8.5, 0.0);//Left Top
	   glVertex3f(7.5, -9.5, 0.0);//Left Bottom
	   glVertex3f(6.5, -9, 0.0);//Right
	   glEnd();
   }
   if (playing == 0) {
	   glColor3f(1.0, 1.0, 1.0);//The Pause symbol will be white
	   glBegin(GL_POLYGON);//First Dash
	   glVertex3f(6.5, -8.5, 0.0);//Left Top
	   glVertex3f(6.5, -9.5, 0.0);//Left Bottom
	   glVertex3f(6.825, -9.5, 0.0);//Right Bottom
	   glVertex3f(6.825, -8.5, 0.0);//Right Top
	   glEnd();
	   glBegin(GL_POLYGON);//Second Dash
	   glVertex3f(7.125, -8.5, 0.0);//Left Top
	   glVertex3f(7.125, -9.5, 0.0);//Left Bottom
	   glVertex3f(7.5, -9.5, 0.0);//Right Bottom
	   glVertex3f(7.5, -8.5, 0.0);//Right Top
	   glEnd();
   }
   if (playing == 2) {
	   glColor3f(1.0, 1.0, 0.0);//The Fast Foward Symbol will be yellow
	   glBegin(GL_TRIANGLES);//First one
	   glVertex3f(6.5, -8.5, 0.0);//Left Top
	   glVertex3f(6.5, -9.5, 0.0);//Left Bottom
	   glVertex3f(7, -9, 0.0);//Right
	   glEnd();
	   glBegin(GL_TRIANGLES);//Second one
	   glVertex3f(7, -8.5, 0.0);//Left Top
	   glVertex3f(7, -9.5, 0.0);//Left Bottom
	   glVertex3f(7.5, -9, 0.0);//Right
	   glEnd();
   }
   
   glPopMatrix();

   glutSwapBuffers();
}

void spinDisplay(void)//This is used to make sure full rotations are made
{
   spin = spin + s_factor;
	if (spin > 360.0)
      spin = spin - 360.0;
   glutPostRedisplay();
}

void MenuDoer(int option) {
	switch (option) {
	case 1://Plays Normal speed
		s_factor = .01;
		playing = 1;
		break;
	case 2://Rewind
		s_factor = - .01;
		playing = -1;
		break;
	case 5://2x Speed
		s_factor = .02;
		playing = 2;
		break;
	case 6://4x Speed
		s_factor = .04;
		playing = 2;
		break;
	case 3://The space bar, pause
		s_factor = 0;
		playing = 0;
		break;
	case 4://Escape button in case things get too crazy
		exit(0);
		break;
	default:
		break;
	}
}

void MenuHandle() {
	glutCreateMenu(MenuDoer);
	//Adding the entries
	glutAddMenuEntry("'+'Play Normal Speed", 1);
	glutAddMenuEntry("'-'Rewind", 2);
	glutAddMenuEntry("<space>-Pause", 3);
	glutAddMenuEntry("Z-Play 2x Speed", 5);
	glutAddMenuEntry("X-Play 4x Speed", 6);
	glutAddMenuEntry("<esc>-Quit", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);//Responds to right button
	glutPostRedisplay();
}

void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
}

void reshape(int w, int h)
{
	if (w < h) {
		glViewport(0, (h-w)/2, w, w);
	}
	else {
		glViewport(0, (w-h)/2, h, h);
	}
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-l * 1.3, l * 1.3, -l * 1.3, l * 1.3, -10.0, 10.0);//Changed the values from 50 to 13,10 for a better view
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void mouse(int button, int state, int x, int y) 
{
   switch (button) {
      case GLUT_LEFT_BUTTON:
         if (state == GLUT_DOWN)
            glutIdleFunc(spinDisplay);
         break;
      case GLUT_MIDDLE_BUTTON:
      case GLUT_RIGHT_BUTTON:
         if (state == GLUT_DOWN)
            glutIdleFunc(NULL);
         break;
      default:
         break;
   }
}

//This will handle all the keyboard input
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 1:
	case '+'://Playing
		s_factor = .01;
		playing = 1;
		break;
	case 2:
	case '-'://Rewind
		s_factor = -.01;
		playing = -1;
		break;
	case 5:
	case 'z'://2x Speed
		s_factor = .02;
		playing = 2;
		break;
	case 6:
	case 'x'://4x Speed
		s_factor = .04;
		playing = 2;
		break;
	case 3:
	case 32://The space bar, pauses
		s_factor = 0;
		playing = 0;
		break;
	case 4:
	case 27://Escape button in case things get too crazy
		exit(0);
		break;
	default:
		break;
	}
}
   
/* 
 *  Request double buffer display mode.
 *  Register mouse input callback functions
 */
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (0, 0);
   glutCreateWindow (argv[0]);
   MenuHandle();
   init ();
   glutIdleFunc(spinDisplay);//Bypasses the mouseclick
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape); 
   glutMouseFunc(mouse);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;   /* ANSI C requires main to return int. */
}
