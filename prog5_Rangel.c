//Luis Rangel(luisrngl5@gmail.com or LuisRangel@my.unt.edu)
//Date:4/7/2016
//Class:UNT CSCE 4230
//Purpose:This program draws a model of the Bivariate function
#ifdef __APPLE__//Portable!
#include<GLUT/glut.h>
#else
#include<GL/glut.h>
#endif

#include<stdlib.h>
#include<math.h>//For maths operations

#define K 255//High number FOR MAXIMUM SHARPNESS
#define NV (K + 1)*(K + 1)
#define NT 2*K*K


//These are the global variables needed for the program
static int xrot = 0, yrot = 0;//These are the angles for the camera controls 
static GLfloat ver[NV][3];//This array will hold the vertex list
static GLint tri[NT][3];//This will hold the triangle list
static GLfloat norm[NV][3];//This will hold the normal vectors
static float zoom = 1.0;//This controls the zoom level
static GLfloat nr[3];//Used to hold normal calculations

void MenuDoer(int option) {//Handles the menu
	switch (option) {
	case 1://Increasing x rotation
		xrot = (xrot + 5) % 360;
		glutPostRedisplay();
		break;
	case 2://Decreasing x rotation
		xrot = (xrot - 5) % 360;
		glutPostRedisplay();
		break;
	case 3://Increasing y rotation
		yrot = (yrot + 5) % 360;
		glutPostRedisplay();
		break;
	case 4://Decreasing y rotation
		yrot = (yrot - 5) % 360;
		glutPostRedisplay();
		break;
	case 5://Increasing zoom
		zoom = zoom + 0.05;
		glutPostRedisplay();
		break;
	case 6://Decreasing zoom
		zoom = zoom - 0.05;
		glutPostRedisplay();
		break;
	case 7:
		exit(0);
		break;
	default:
		break;
	}
}

void MenuHandle() {
	glutCreateMenu(MenuDoer);
	//Adding the entries
	glutAddMenuEntry("'x'-Rotate Right", 1);
	glutAddMenuEntry("'X'-Rotate Left", 2);
	glutAddMenuEntry("'y'-Rotate Down", 3);
	glutAddMenuEntry("'Y'-Rotate Up", 4);
	glutAddMenuEntry("'z'-Zoom In", 5);
	glutAddMenuEntry("'Z'-Zoom Out", 6);
	glutAddMenuEntry("'<esc>'-Quit", 7);
	glutAttachMenu(GLUT_RIGHT_BUTTON);//Responds to right button
	glutPostRedisplay();
}

void init_lights()//Sets up the lights
{
	GLfloat ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat position[] = { 0.5, 0.5, 0.0, 1.0 };
	GLfloat mat_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat mat_shininess[] = { 50.0 };

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);//Making the model red
	glShadeModel(GL_SMOOTH);//Making the model smooth



	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);
	glColor3f(1.0, 0.0, 0.0);//Making the model blue
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
}

float Bivariate(float x, float y) {//This function will return z values for the model
	float result;
	result = .5 * exp(-.04 * sqrt((((80 * x) - 40) * ((80 * x) - 40)) + (((90 * y) - 45) * ((90 * y) - 45)))) * cos(0.15 * sqrt((((80 * x) - 40) * ((80 * x) - 40)) + (((90 * y) - 45) * ((90 * y) - 45))));
	return result;
}

void filling_all() {//This will fill the arrays with things
	GLint i, j, squares, tric, indv, indt;
	GLfloat xi, yi, step, squib;//These are the increments to pass into Bivariate function
	//The Vertex Array
	squib = K + 1;//The Program was not playing nice with the division
	step = 1 / squib;//To know how much to increment the sides
	i = 0;//Set up the counter
	xi = 0.0;
	yi = 0.0;
	indv = 0;
	for (j = 0; j <= K; j++) {
		GLfloat y = j * step;
		GLint i;
		for (i = 0; i <= K; i++) {
			GLfloat x = i * step;
			ver[indv][0] = x;//X cordinate
			ver[indv][1] = y;//Y cordinate
			ver[indv][2] = Bivariate(x, y);//X and Y passed to Bivariate
			indv++;
		}
	}
	
	//The Triangle List
	indt = 0;
	indv = 0;//Saving varaibles
	for (j = 1; j <= K; j++) {
		for (i = 1; i <= K; i++) {
			indv = j * (K + 1) + i;
			tri[indt][0] = indv - K - 2;
			tri[indt][1] = indv - K - 1;
			tri[indt][2] = indv;

			tri[indt + 1][0] = indv - K - 2;
			tri[indt + 1][1] = indv;
			tri[indt + 1][2] = indv - 1;
			indt = indt + 2;
		}
	}
}

void init_norm() {//Initialize normals to 0
	int i;
	for (i = 0; i <= NV - 1; i++) {
		norm[i][0] = 0;
		norm[i][1] = 0;
		norm[i][2] = 0;
	}
}

void fill_normal(){//Figured it might be dicey to include filling the normal with the other function
	GLint it, i1, i2, i3;//Iterators needed for the normal calculations
	float len;//Length
	for (it = 0; it <= NT - 1; it++) {
		i1 = tri[it][0];//1st point
		i2 = tri[it][1];//2nd point
		i3 = tri[it][2];//3rd point
		//Cross product
		nr[0] = (ver[i2][1] - ver[i1][1]) * (ver[i3][2] - ver[i1][2]) - (ver[i2][2] - ver[i1][2]) * (ver[i3][1] - ver[i1][1]);
		nr[1] = (ver[i2][2] - ver[i1][2]) * (ver[i3][0] - ver[i1][0]) - (ver[i2][0] - ver[i1][0]) * (ver[i3][2] - ver[i1][2]);
		nr[2] = (ver[i2][0] - ver[i1][0]) * (ver[i3][1] - ver[i1][1]) - (ver[i2][1] - ver[i1][1]) * (ver[i3][0] - ver[i1][0]);
		//Calculating lengths
		len = sqrt(nr[0] * nr[0] + nr[1] * nr[1] + nr[2] * nr[2]);
		if (len != 0) {
			nr[0] = nr[0] / len;
			nr[1] = nr[1] / len;
			nr[2] = nr[2] / len;
		}
		//Filling Normal Array
		norm[i1][0] += nr[0];
		norm[i1][1] += nr[1];
		norm[i1][2] += nr[2];
		norm[i2][0] += nr[0];
		norm[i2][1] += nr[1];
		norm[i2][2] += nr[2];
		norm[i3][0] += nr[0];
		norm[i3][1] += nr[1];
		norm[i3][2] += nr[2];
	}
}

void normalize(GLfloat a[]) {//Calculates length and stores in the a array
	GLint i, n;
	GLfloat len = 0;//Length
	n = 3;
	for (i = 0; i < n; i++) {
		len += a[i] * a[i];
	}
	len = sqrt(len);
	for (i = 0; i < n; i++) {
		a[i] = a[i] / len;
	}
}

void ver_norm() {//Normalizes the vertex normals
	GLint indv;
	for (indv = 0; indv <= NV - 1; indv++)
	{
		normalize(norm[indv]); //Calls the normalize function
	}
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
	glOrtho(-1 * zoom, 1 * zoom, -1 * zoom, 1 * zoom, -1, 20);//Making the ortho call
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef (0.0, 0.0, -5.0);//This is where the camera controls go I bet
}

void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
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
   case 'z'://Increasing zoom
	   zoom = zoom + 0.05;
	   glutPostRedisplay();
	   break;
   case 'Z'://Decreasing zoom
	   zoom = zoom - 0.05;
	   glutPostRedisplay();
	   break;
   case 27:
	   exit(0);
	   break;
      default:
         break;
   }
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);//Enable smooth shading
	init_lights();//HIT THE LIGHTS!
	filling_all();//This fills in the vertex arrray and the triangle list
	init_norm();//Sets up the normal vector
	fill_normal();//Fills up the normal vector
	ver_norm();//Handles the vertor normal
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, ver);//Feeds in vertex array
	glNormalPointer(GL_FLOAT, 0, norm);//Feeds in normal array
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	//The Camera
	glRotatef((GLfloat)xrot, 0.0, 1.0, 0.0);//Rotation in x direction
	glRotatef((GLfloat)yrot, 0.0, 0.0, 1.0);//Rotation in y direction
	glScalef(zoom, zoom, zoom);//Zooming in and out
	glTranslatef(-0.5, -0.5, 0.0);//Moving to origin

	//The Object
	glDrawElements(GL_TRIANGLES, NT*3 , GL_UNSIGNED_INT, tri);//Dtawing the mesh
	glPopMatrix();
	glutSwapBuffers();
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
