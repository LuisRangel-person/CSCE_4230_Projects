//Luis Rangel(luisrngl5@gmail.com or LuisRangel@my.unt.edu)
//Date:3/19/2016
//Class:UNT CSCE 4230
//Purpose:This program is a modification of Robot.c to give it hand, make shapes solid, add a dash of color, change the point of view, and add camera controls
#ifdef __APPLE__//Portable!
#include<GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

//These are the global variables needed for the program
static int shoulder = 0, elbow = 0, hand = 0;//These are the rotation angles for the segments
static int solidmode = 0;//This is the 'bool' that will toggle solid shapes
static int xrot = 0, yrot = 0;//These are the angles for the camera controls 
static int permode = 0;//This is a variable used to keep track of the persceptive modes
static float claw = 0.00;//Claw is to control the movement of the claws-For Fun

void MenuDoer(int option) {//Handles the menu
	switch (option) {
	case 1:
		shoulder = (shoulder + 5) % 360;
		glutPostRedisplay();
		break;
	case 2:
		shoulder = (shoulder - 5) % 360;
		glutPostRedisplay();
		break;
	case 3:
		elbow = (elbow + 5) % 360;
		glutPostRedisplay();
		break;
	case 4:
		elbow = (elbow - 5) % 360;
		glutPostRedisplay();
		break;
	case 5 ://Increase hand angle
		hand = (hand + 5) % 360;
		glutPostRedisplay();
		break;
	case 6://Decrease hand angle
		hand = (hand - 5) % 360;
		glutPostRedisplay();
		break;
	case 7://Toggling solidmode
		solidmode = 1;
		glutPostRedisplay();
		break;
	case 8://Toggling wiremode
		solidmode = 0;
		glutPostRedisplay();
		break;
	case 9://Increasing x rotation
		xrot = (xrot + 5) % 360;
		glutPostRedisplay();
		break;
	case 10://Decreasing x rotation
		xrot = (xrot - 5) % 360;
		glutPostRedisplay();
		break;
	case 11://Increasing y rotation
		yrot = (yrot + 5) % 360;
		glutPostRedisplay();
		break;
	case 12://Decreasing y rotation
		yrot = (yrot - 5) % 360;
		glutPostRedisplay();
		break;
	case 13://Frus toggle
		permode = 1;
		glutPostRedisplay();
		break;
	case 14://Ortho toggle
		permode = 0;
		glutPostRedisplay();
		break;
	case 16://Claw Open-For Fun
		if (claw < .5) {
			claw = claw + 0.1;
			glutPostRedisplay();
		}
		break;
	case 17://Claw Close-For Fun
		if (claw > 0.0) {
			claw = claw - 0.1;
			glutPostRedisplay();
		}
		break;
	case 15:
		exit(0);
		break;
	default:
		break;
	}
}
void MenuHandle() {
	glutCreateMenu(MenuDoer);
	//Adding the entries
	glutAddMenuEntry("'s'-Move Shoulder Up", 1);
	glutAddMenuEntry("'S'-Move Shoulder Down", 2);
	glutAddMenuEntry("'e'-Move Elbow Up", 3);
	glutAddMenuEntry("'E'-Move Elbow Down", 4);
	glutAddMenuEntry("'w'-Move Hand Up", 5);
	glutAddMenuEntry("'W'-Move Hand Down", 6);
	glutAddMenuEntry("'h'-Solidmode",7);
	glutAddMenuEntry("'H'-Wireframe Mode", 8);
	glutAddMenuEntry("'x'-Rotate Right", 9);
	glutAddMenuEntry("'X'-Rotate Left", 10);
	glutAddMenuEntry("'y'-Rotate Down", 11);
	glutAddMenuEntry("'Y'-Rotate Up", 12);
	glutAddMenuEntry("'f'-Frustum Toggle", 13);
	glutAddMenuEntry("'F'-Ortho Toggle", 14);
	glutAddMenuEntry("'z'-Claw Open", 16);
	glutAddMenuEntry("'Z'-Claw Close", 17);
	glutAddMenuEntry("'<esc>'-Exit", 15);
	glutAttachMenu(GLUT_RIGHT_BUTTON);//Responds to right button
	glutPostRedisplay();
}

void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
   glPushMatrix();
   //The Camera
   glRotatef((GLfloat)xrot, 0.0, 1.0, 0.0);//Rotation in x direction
   glRotatef((GLfloat)yrot, 0.0, 0.0, 1.0);//Rotation in y direction
   //The Upper Arm
   glTranslatef (-1.0, 0.0, 0.0);
   glRotatef ((GLfloat) shoulder, 0.0, 0.0, 1.0);
   glTranslatef (1.0, 0.0, 0.0);
   glPushMatrix();
   glScalef (5.0, 1.0, 1.0);
   glColor3d(0.0, 0.0, 1.0);//Making the forearm blue
   if (solidmode == 0) {//If solidmode is false
	   glutWireCube(1.0);//Wireframe
   }
   else {//If solidmode is true
	   glutSolidCube(1.0);//Solid
   }
   glPopMatrix();
   //The Forearm
   glTranslatef (2.5, 0.0, 0.0);//I thinkered with the x cordinate till things were aligned
   glRotatef ((GLfloat) elbow, 0.0, 0.0, 1.0);
   glTranslatef (2.0, 0.0, 0.0);//Had to tinker with this x cordinate as well to make sure the rotation looked right
   glPushMatrix();
   glScalef (4.0, 1.0, 1.0);
   glColor3d(0.0, 1.0, 0.0);//Making the forearm blue
   if (solidmode == 0) {//If solidmode is false
	   glutWireCube(1.0);//Wireframe shape
   }
   else {//If solidmode is true
	   glutSolidCube(1.0);//Solid shape
   }
   glPopMatrix();
   //The Hand
   glTranslatef(2.0, 0.0, 0.0);//I thinkered with the x cordinate till things were aligned
   glRotatef((GLfloat)hand, 0.0, 0.0, 1.0);
   glTranslatef(1.0, 0.0, 0.0);//Had to tinker with this x cordinate as well to make sure the rotation looked right
   glPushMatrix();
   glScalef(2.0, 1.0, 0.5);
   //glRotatef(-45.0, 0.0, 0.0, 1.0);//Seperating fingers
   glColor3d(1.0, 0.0, 0.0);//Making the hand red
   if (solidmode == 0) {//If solidmode is false
	   glutWireCube(1.0);//Wireframe shape
	   glTranslatef(1.0, -0.75, 0.0);
	   glScalef(1.0, 0.5, 0.25);
	   glTranslatef(0.0, 0.75, 0.0);//Seperate fingers
	   glutWireCube(1.0);
	   glTranslatef(0.0, 1.5 - claw, 0.0);//Moving the claw
	   glutWireCube(1.0);
   }
   else {//If solidmode is true
	   glutSolidCube(1.0);//Wireframe shape
	   glTranslatef(1.0, -0.75, 0.0);
	   glScalef(1.0, 0.5, 0.25);
	   glTranslatef(0.0, 0.75, 0.0);//Seperate fingers
	   glutSolidCube(1.0);
	   glTranslatef(0.0, 1.5 - claw, 0.0);//Moving the claw
	   glutSolidCube(1.0);
   }
   glPopMatrix();

   glPopMatrix();
   glutSwapBuffers();
}

void reshape (int w, int h)
{
	if (w < h) {//To keep it square
		glViewport(0, (h - w) / 2, w, w);
	}
	else {
		glViewport(0, (w - h) / 2, h, h);
	}

   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   if (permode == 0) {
	   glOrtho(-10, 10, -10, 10, -10, 20);//Making the ortho call
   }
   else {
	   glFrustum(-2, 2, -2, 2, 1, 20);//Making the frustum call
   }
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef (0.0, 0.0, -5.0);//This is where the camera controls go I bet
}

void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
      case 's':
         shoulder = (shoulder + 5) % 360;
         glutPostRedisplay();
         break;
      case 'S':
         shoulder = (shoulder - 5) % 360;
         glutPostRedisplay();
         break;
      case 'e':
         elbow = (elbow + 5) % 360;
         glutPostRedisplay();
         break;
      case 'E':
         elbow = (elbow - 5) % 360;
         glutPostRedisplay();
         break;
	  case 'w'://Increase hand angle
		  hand = (hand + 5) % 360;
		  glutPostRedisplay();
		  break;
	  case 'W'://Decrease hand angle
		  hand = (hand - 5) % 360;
		  glutPostRedisplay();
		  break;
	  case 'h'://Toggling solidmode
		solidmode = 1;
		glutPostRedisplay();
		  break;
	  case 'H'://Toggling wiremode
		solidmode = 0;
		glutPostRedisplay();
		  break;
	  case 'x'://Increasing x rotation
		  xrot = (xrot + 5) % 360;
		  glutPostRedisplay();
		  break;
	  case 'X'://Decreasing x rotation
		  xrot = (xrot - 5) % 360;
		  glutPostRedisplay();
		  break;
	  case 'y'://Increasing y rotation
		  yrot = (yrot + 5) % 360;
		  glutPostRedisplay();
		  break;
	  case 'Y'://Decreasing y rotation
		  yrot = (yrot - 5) % 360;
		  glutPostRedisplay();
		  break;
	  case 'p'://Frus toggle
		permode = 1;
		glutPostRedisplay();
		  break;
	  case 'P'://Ortho toggle
		  permode = 0;
		  glutPostRedisplay();
		  break;
	  case 'z'://Claw Open-For Fun
		  if (claw < .5) {
			  claw = claw + 0.1;
		  }
		  glutPostRedisplay();
		  break;
	  case 'Z'://Claw Close-For Fun
		  if (claw > 0) {
			  claw = claw - 0.1;
		  }
		  glutPostRedisplay();
		  break;
      case 27:
         exit(0);
         break;
      default:
         break;
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   MenuHandle();
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
