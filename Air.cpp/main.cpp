#ifdef _WIN32
#include<windows.h>
#endif
#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<math.h>
#include<iostream>
#include <cstdlib>
#include <ctime>
#define GL_SILENCE_DEPRECATION
#define PI 3.1416f
#define XMAX 1200
#define YMAX 700
#define SPACESHIP_SPEED 3
#define TOP 0
#define RIGHT 1
#define BOTTOM 2
#define LEFT 3
#define RAINSIZE 500

using namespace std;

enum view {INTRO, MENU, INSTRUCTIONS, GAME, GAMEOVER};
view viewPage = INTRO; // initial value
GLint m_viewport[4];
bool first=true;
bool isDay=true;
bool isNight=false;
bool midNight=false;
bool isMorning=true;
bool isAfternoon=false;
bool inc=true;
bool dcrmnt=false;
bool mButtonPressed = false;
bool laser1 = false, laser2 = false;
bool gameOver = false;

bool keyStates[256] = {false};
bool direction[4] = {false};
bool laser1Dir[2] = {false};
bool laser2Dir[2] = {false};

int playerLife = 100;
int boss1Life = 100;

float xOne = 400, yOne = 0;
float xTwo = 400, yTwo = 0;
float mouseX, mouseY;

GLint i, j, k;
GLfloat sun_spin=0, sun_x=0, sun_y=0;
GLfloat ax=0,bx=0,cx=0,dx=0,str=500.0,mn=500.0;
GLfloat sr=0.0,sg=0.749,sb=1.0;
GLfloat spin = 0.0;

GLfloat position1 = 0.0f;
GLfloat speed1 = 5.0f;

const int laserPeriod = 2000;

void initBG()
{
	glClearColor(.40, .110, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 0, 0, 0);
}
void checkLaserContact(int x, int y, bool dir[], int xp, int yp, bool palyer1);
void circleBG(GLdouble rad)
{
    GLint points = 50;
    GLdouble delTheta = (2.0 * PI) / (GLdouble)points;
    GLdouble theta = 0.0;

    glBegin(GL_POLYGON);
    {
        for( i = 0; i <=50; i++, theta += delTheta )
        {
            glVertex2f(rad * cos(theta),rad * sin(theta));
        }
    }
    glEnd();
}
/// *** Sun_Model **///
void Sun_Model(){
    glPushMatrix();
    glTranslatef(500,0,0);
    circleBG(30);
    glPopMatrix();

}
void Moving_Sun_Model(){
    glPushMatrix();
    glRotatef(-sun_spin, 0,0,-.009);
    Sun_Model();
    glPopMatrix();

}
///*** Cloud_Model***///
void cloud_model_one(){

    glColor3f(1.25, 0.924, 0.930);

    ///Top_Left

    glPushMatrix();
    glTranslatef(320,210,0);
    circleBG(15);
    glPopMatrix();

    ///Top

    glPushMatrix();
    glTranslatef(340, 225, 0);
    circleBG(16);
    glPopMatrix();

    ///Right

    glPushMatrix();
    glTranslatef(360,210,0);
    circleBG(16);
    glPopMatrix();


    ///middle_Fill
    glPushMatrix();
    glTranslatef(355,210,0);
    circleBG(16);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(350,210,0);
    circleBG(16);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(345,204,0);
    circleBG(10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(340,204,0);
    circleBG(10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(335,204,0);
    circleBG(10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(330,204,0);
    circleBG(10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(325,204,0);
    circleBG(10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(320,204,0);
    circleBG(10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(315,204,0);
    circleBG(10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(310,204,0);
    circleBG(10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(305,204,0);
    circleBG(10);
    glPopMatrix();

    ///****Fill End****

}

void cloud_model_Two(){
    glColor3f(1.25, 0.924, 0.930);

    ///Left_Part
    glPushMatrix();
    glTranslatef(305,205,0);
    circleBG(10);
    glPopMatrix();

    ///Top

    glPushMatrix();
    glTranslatef(320,210,0);
    circleBG(15);
    glPopMatrix();

    ///Right_Part
    glPushMatrix();
    glTranslatef(334,207,0);
    circleBG(10);
    glPopMatrix();

    ///Bottom_Part
    glPushMatrix();
    glTranslatef(320,207,0);
    circleBG(10);
    glPopMatrix();



}

void cloud_model_Three(){
    glColor3f(1.25, 0.924, 0.930);

    ///Left_Part
    glPushMatrix();
    glTranslatef(300,200,0);
    circleBG(15);
    glPopMatrix();

    ///Top_Left

    glPushMatrix();
    glTranslatef(320,210,0);
    circleBG(15);
    glPopMatrix();

    ///Top
    glPushMatrix();
    glTranslatef(340,220,0);
    circleBG(16);
    glPopMatrix();

    ///Top_Right
    glPushMatrix();
    glTranslatef(360,210,0);
    circleBG(15);
    glPopMatrix();

    ///Right_Part
    glPushMatrix();
    glTranslatef(380,200,0);
    circleBG(15);
    glPopMatrix();

    ///Bottom_Right
    glPushMatrix();
    glTranslatef(360,190,0);
    circleBG(20);
    glPopMatrix();

    ///Bottom_Left
    glPushMatrix();
    glTranslatef(320,190,0);
    circleBG(20);
    glPopMatrix();

    ///Bottom
    glPushMatrix();
    glTranslatef(340,190,0);
    circleBG(20);
    glPopMatrix();




    ///****Fill End****

}
///*** Hill_Model***///
void hill_big(){

    ///Hill
	glBegin(GL_POLYGON);
    glColor3f(0.38, 0.41, 0.36);
	glVertex2i(70, 70);
	glVertex2i(200, 225);
	glVertex2i(330, 70);

	glEnd();

	///Hill_Snow
    glBegin(GL_POLYGON);
    glColor3f(1.25, 0.924, 0.930);

	glVertex2i(200, 225);
	glVertex2i(230, 190);
	glVertex2i(220, 180);
	glVertex2i(200, 190);
	glVertex2i(190, 180);
	glVertex2i(170, 190);

	glEnd();

}
void hill_small(){
    ///Hill_Small
	glBegin(GL_POLYGON);
    glColor3f(0.11, 0.23, 0.36);
	glVertex2i(250, 100);
	glVertex2i(310, 175);
	glVertex2i(370, 100);

	glEnd();

    ///Hill_Small_Snow
	glBegin(GL_POLYGON);
    glColor3f(1.25, 0.924, 0.930);
    glVertex2i(290, 150);
	glVertex2i(310, 175);
	glVertex2i(330, 150);
	glVertex2i(325, 140);
	glVertex2i(310, 150);
	glVertex2i(300, 140);


	glEnd();
}
///*** Tilla_Model ***///
void Tilla_One_Model(){
    ///Tilla
	glBegin(GL_POLYGON);
	glColor3f(0.1, 1.293, 0.0);
	glVertex2i(125, 70);
	glVertex2i(150, 80);
	glVertex2i(160, 90);
	glVertex2i(170, 90);
	glVertex2i(180, 100);
	glVertex2i(190, 105);
	glVertex2i(200, 108);
	glVertex2i(300, 110);
	glVertex2i(300, 70);

	glEnd();

}

void Tilla_Two_Model(){

	glColor3f(0.1, 1.293, 0.0);
    /// Left_Part
    glPushMatrix();
    glTranslatef(430,90,0);
    circleBG(30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(420,87,0);
    circleBG(30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(410,80,0);
    circleBG(30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(400,80,0);
    circleBG(30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(390,70,0);
    circleBG(30);
    glPopMatrix();

    ///Right_Part
    glPushMatrix();
    glTranslatef(445,80,0);
    circleBG(30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(455,75,0);
    circleBG(30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(465,70,0);
    circleBG(30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(470,65,0);
    circleBG(30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(480,60,0);
    circleBG(30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(485,55,0);
    circleBG(20);
    glPopMatrix();



}
///*** House_Model ***///
void house(){
    ///House_Roof
	glBegin(GL_POLYGON);
    glColor3f(.990, 0.0, 0.0);
	glVertex2i(285, 105);
	glVertex2i(285, 130);
	glVertex2i(380, 115);
	glVertex2i(380, 105);

	glEnd();

    ///House_Roof_Shadow
	glBegin(GL_POLYGON);
    glColor3f(.890, 0.0, 0.0);
	glVertex2i(285, 105);
	glVertex2i(285, 120);
	glVertex2i(380, 105);
	glVertex2i(380, 105);

	glEnd();

    ///House_Fence
	glBegin(GL_POLYGON);
    glColor3f(.555, 1.0, 1.0);
	glVertex2i(290, 70);
	glVertex2i(290, 104);
	glVertex2i(375, 104);
	glVertex2i(375, 70);

	glEnd();

    ///House_Fence_Shadow
	glBegin(GL_POLYGON);
    glColor3f(.555, 0.924, 0.930);
	glVertex2i(310, 70);
	glVertex2i(350, 104);
	glVertex2i(375, 104);
	glVertex2i(375, 70);

	glEnd();

    ///House_Door
	glBegin(GL_POLYGON);
    glColor3f(0.38, 0.41, 0.36);
	glVertex2i(330, 70);
	glVertex2i(330, 100);
	glVertex2i(350, 100);
	glVertex2i(350, 70);

	glEnd();

    ///House_Window1
	glBegin(GL_POLYGON);
    glColor3f(0.38, 0.21, 0.26);
	glVertex2i(295, 75);
	glVertex2i(295, 90);
	glVertex2i(310, 90);
	glVertex2i(310, 75);

	glEnd();

    ///House_Window2
	glBegin(GL_POLYGON);
    glColor3f(0.38, 0.21, 0.26);
	glVertex2i(312, 75);
	glVertex2i(312, 90);
	glVertex2i(327, 90);
	glVertex2i(327, 75);

	glEnd();

    ///House_Window3
	glBegin(GL_POLYGON);
    glColor3f(0.38, 0.21, 0.26);
	glVertex2i(355, 75);
	glVertex2i(355, 90);
	glVertex2i(370, 90);
	glVertex2i(370, 75);

	glEnd();

    ///House_Small_Roof
	glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
	glVertex2i(250, 90);
	glVertex2i(257, 104);
	glVertex2i(290, 104);
	glVertex2i(290, 90);

	glEnd();

    ///House_Small_Fence
	glBegin(GL_POLYGON);
    glColor3f(.555, .724, .930);
	glVertex2i(255, 70);
	glVertex2i(255, 90);
	glVertex2i(290, 90);
	glVertex2i(290, 70);

	glEnd();

    ///House_Small_Door
	glBegin(GL_POLYGON);
    glColor3f(0.11, 0.23, 0.36);
	glVertex2i(260, 70);
	glVertex2i(260, 80);
	glVertex2i(285, 80);
	glVertex2i(285, 70);

	glEnd();


}
///*** Field_Model ***///
void field(){
    ///Field
	glBegin(GL_POLYGON);
    glColor3f(0.533, 1.293, 0.0);
	glVertex2i(0, 50);
	glVertex2i(0, 70);
	glVertex2i(1000, 70);
	glVertex2i(1000, 50);

	glEnd();


    ///Field_Shadow
	glBegin(GL_POLYGON);
	glColor3f(0.1, 1.293, 0.0);
	glVertex2i(0, 0);
	glVertex2i(0, 50);
	glVertex2i(1000, 50);
	glVertex2i(1000, 0);

	glEnd();


}
///*** Tree_Model ***///
void Tree_Model_One(){


    glPushMatrix();
    glTranslatef(110,110,0);
    circleBG(15);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(110,100,0);
    circleBG(15);
    glPopMatrix();

    glBegin(GL_POLYGON);
    glColor3f(0.38, 0.21, 0.26);
	glVertex2f(109, 70);
	glVertex2f(109, 90);
	glVertex2f(111, 90);
	glVertex2f(111, 70);

    glEnd();

}
void Tree_Model_Two(){

    glPushMatrix();
    glTranslatef(130,130,0);
    circleBG(5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(125,126,0);
    circleBG(5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(135,126,0);
    circleBG(5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(130,125,0);
    circleBG(5);
    glPopMatrix();

    glBegin(GL_POLYGON);
    glColor3f(0.38, 0.21, 0.26);
	glVertex2f(129, 110);
	glVertex2f(129, 124);
	glVertex2f(131, 124);
	glVertex2f(131, 110);

    glEnd();
}

void Tree_Model_Three(){


    glBegin(GL_POLYGON);

	glVertex2f(125, 123);
	glVertex2f(133, 145);
	glVertex2f(141, 123);

	glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.38, 0.21, 0.26);
	glVertex2f(132, 110);
	glVertex2f(132, 124);
	glVertex2f(134, 124);
	glVertex2f(134, 110);

    glEnd();
}

/// *** Windmill_Stand_Model ***///
void Windmill_Stand_Model(){

    glColor3f(0.38, 0.41, 0.36);
    glBegin(GL_POLYGON);
    glVertex2i(375, 100);
    glVertex2i(380, 240);
    glVertex2i(384, 240);
    glVertex2i(390, 100);
    glEnd();
}

///*** Windmill_Blades_Model ***///

void Windmill_Blade(){

    ///Blade_One
    glPushMatrix();
    glRotatef(spin,0,0,90);
    glBegin(GL_POLYGON);
    glVertex2i(-5, 0);
    glVertex2i(-85, -36);
    glVertex2i(-83, -37);
    glVertex2i(-3, -8);
    glEnd();
    glPopMatrix();

    ///Blade_Two
    glPushMatrix();
    glRotatef(spin,0,0,90);
    glBegin(GL_POLYGON);
    glVertex2i(0, 5);
    glVertex2i(45, 70);
    glVertex2i(50, 73);
    glVertex2i(5, 0);
    glEnd();
    glPopMatrix();

    ///Blade_Three
    glPushMatrix();
    glRotatef(spin,0,0,90);
    glBegin(GL_POLYGON);
    glVertex2i(68, -78);
    glVertex2i(0,0);
    glVertex2i(5, 5);
    glVertex2i(70, -77);
    glEnd();
    glPopMatrix();

}
///*** Windmill_Final_Model ***///
void Windmill(){



        ///Windmill_Stand
    glColor3f(0.38, 0.41, 0.36);
    glPushMatrix();
    Windmill_Stand_Model();
    glPopMatrix();

    ///Windmill_Motor
    glColor3f(0.11, 0.23, 0.36);
    glPushMatrix();
    glTranslatef(380,250,0);
    circleBG(10);
    glPopMatrix();

    ///Windmill_Rotary_Blades
    glColor3f(0.11, 0.23, 0.36);
    glPushMatrix();
    glTranslatef(380,251,0);
    Windmill_Blade();
    glPopMatrix();
}

void Sun(){
    glColor3f(1, 1, 0);
    glPushMatrix();
    Moving_Sun_Model();
    glPopMatrix();
}
///*** Cloud_One_Model_One ***///
void cloud_one(){
    glPushMatrix();
    glTranslatef(cx,-40,0);
    cloud_model_one();
    glPopMatrix();

}

///*** Cloud_Two_Model_one ***///

void cloud_two(){
    glPushMatrix();
    glTranslatef(bx+100,150,0);
    cloud_model_one();
    glPopMatrix();

}

///*** Cloud_Three_Model_Two ***///

void cloud_three(){
    glPushMatrix();
    glTranslatef(ax-80,80,0);
    cloud_model_Two();
    glPopMatrix();

}
///*** Cloud_Four_Model_Two ***///

void cloud_four(){
    glPushMatrix();
    glTranslatef(dx+300,125,0);
    cloud_model_Two();
    glPopMatrix();

}
///*** Cloud_Five_Model_Three ***///
void cloud_five(){

    glPushMatrix();
    glTranslatef(ax+-300,170,0);
    cloud_model_Three();
    glPopMatrix();
}
///*** Cloud_Six_Model_Three ***///
void cloud_six(){

    glPushMatrix();
    glTranslatef(cx+-500,20,0);
    cloud_model_Three();
    glPopMatrix();
}

///*** House_One ***///
void house_one(){
    glPushMatrix();
    glTranslatef(0,0,0);
    house();
    glPopMatrix();
}
///*** House_Two ***///
void house_two(){
    glPushMatrix();
    glTranslatef(450,0,0);
    house();
    glPopMatrix();
}
///*** House_Two ***///
void house_three(){
    glPushMatrix();
    glTranslatef(320, 37,0);
    house();
    glPopMatrix();
}
///*** Hill_big_One ***///
void Hill_Big_One(){
    glPushMatrix();
    glTranslatef(0,0,0);
    hill_big();
    glPopMatrix();
}
///*** Hill_big_Two ***///
void Hill_Big_Two(){
    glPushMatrix();
    glTranslatef(550,-20,0);
    hill_big();
    glPopMatrix();
}
///*** Hill_Small_One ***///
void Hill_Small_One(){
    glPushMatrix();
    glTranslatef(0,0,0);
    hill_small();
    glPopMatrix();

}
/// *** Tilla_One_Model_One ***///

void Tilla_One(){

    glPushMatrix();
    glTranslatef(0,0,0);
    Tilla_One_Model();
    glPopMatrix();

}
/// *** Tilla_Two_Model_Two ***///
void Tilla_Two(){

    glPushMatrix();
    glTranslatef(0,0,0);
    Tilla_Two_Model();
    glPopMatrix();


}
/// *** Tilla_Three_Model_Two ***///
void Tilla_Three(){

    glPushMatrix();
    glTranslatef(400,0,0);
    Tilla_Two_Model();
    glPopMatrix();


}
/// *** Tilla_Four_Model_One ***///
void Tilla_Four(){

    glColor3f(0.833, 1., 0.0);
    glPushMatrix();
    glTranslatef(380,0,0);
    Tilla_One_Model();
    glPopMatrix();


}
///*** Tree_1 ***///
void Tree_One(){
    glColor3f(0.533, 1.293, 0.0);
    glPushMatrix();
    glTranslatef(0,0,0);
    Tree_Model_One();
    glPopMatrix();
}

///*** Tree_2 ***///
void Tree_Two(){
    glColor3f(0.533, 1.293, 0.0);
    glPushMatrix();
    glTranslatef(540,0,0);
    Tree_Model_One();
    glPopMatrix();
}

///*** Tree_3 ***///
void Tree_Three(){
    glColor3f(0.533, 1.293, 0.0);
    glPushMatrix();
    glTranslatef(750,0,0);
    Tree_Model_One();
    glPopMatrix();
}
///*** Tree_4 ***///
void Tree_Four(){
    glColor3f(0.533, 1.293, 0.0);
    glPushMatrix();
    glTranslatef(292,40,0);
    Tree_Model_One();
    glPopMatrix();
}

///*** Tree_5 ***///
void Tree_Five(){
    glColor3f(0.533, 1.293, 0.0);
    glPushMatrix();
    glTranslatef(30,-20,0);
    Tree_Model_Two();
    glPopMatrix();
}

///*** Tree_6 ***///
void Tree_Six(){
    glColor3f(0.533, 1.293, 0.0);
    glPushMatrix();
    glTranslatef(50,-10,0);
    Tree_Model_Two();
    glPopMatrix();
}
///*** Tree_7 ***///
void Tree_Seven(){
    glColor3f(0.533, 1.293, 0.0);
    glPushMatrix();
    glTranslatef(322,0,0);
    Tree_Model_Two();
    glPopMatrix();
}

///*** Tree_8 ***///
void Tree_Eight(){
    glColor3f(0.533, 1.293, 0.0);
    glPushMatrix();
    glTranslatef(350,-15,0);
    Tree_Model_Two();
    glPopMatrix();
}

///*** Tree_9 ***///
void Tree_Nine(){
    glColor3f(0.533, 1.293, 0.0);
    glPushMatrix();
    glTranslatef(760,-25,0);
    Tree_Model_Two();
    glPopMatrix();
}

///*** Tree_10 ***///
void Tree_Ten(){
    glColor3f(0.533, 1.293, 0.0);
    glPushMatrix();
    glTranslatef(90,-2,0);
    Tree_Model_Three();
    glPopMatrix();
}

///*** Tree_11 ***///
void Tree_Eleven(){
    glColor3f(0.533, 1.293, 0.0);
    glPushMatrix();
    glTranslatef(125,0,0);
    Tree_Model_Three();
    glPopMatrix();
}

///*** Tree_12 ***///
void Tree_Twelve(){
    glColor3f(0.533, 1.293, 0.0);
    glPushMatrix();
    glTranslatef(408,-22,0);
    Tree_Model_Three();
    glPopMatrix();
}

/// *** Windmill ***///
void Windmill_One(){
    glColor3f(0.11, 0.23, 0.36);
    glPushMatrix();
    glTranslatef(0,-10,0);
    Windmill();
    glPopMatrix();

}

void Windmill_Two(){
    glColor3f(0.11, 0.23, 0.36);
    glPushMatrix();
    glTranslatef(508,-70,0);
    Windmill();
    glPopMatrix();

}
void Windmill_Three(){
    glColor3f(0.11, 0.23, 0.36);
    glPushMatrix();
    glTranslatef(108,-90,0);
    Windmill();
    glPopMatrix();

}
void sun_move(){

    sun_spin = sun_spin + 0.0008;

}
void move_right(){

    sun_move();

    spin = spin +.1;
    ax = ax + .05;
    bx = bx + .08;
    cx = cx + .10;
    dx = dx + .15;

    if(cx>1000){
        cx = -300;
    }
    if(bx>1000){
            bx= -400;

    }
    if(cx>1000){
            cx= -400;

    }
    if(dx>1000){
            dx= -500;

    }


    glutPostRedisplay();
}


void screenBG(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);

    ///*** Object_Layer ***///
    Sun();
    move_right();

    Windmill_Three();

    Hill_Big_One();
    Tilla_Four();

    house_three();

    Hill_Big_Two();
    Hill_Small_One();

    cloud_three();
    cloud_four();

    Windmill_One();
    Windmill_Two();


    Tilla_One();
    Tilla_Two();
    Tilla_Three();


    house_one();
    cloud_one();
    house_two();


    Tree_One();
    Tree_Two();
    Tree_Three();
    Tree_Four();
    Tree_Five();
    Tree_Six();
    Tree_Seven();
    Tree_Eight();
    Tree_Nine();
    Tree_Ten();
    Tree_Eleven();
    Tree_Twelve();



    cloud_two();
    cloud_five();
    cloud_six();
    field();

	glFlush();
}

void displayRasterText(float x ,float y ,float z ,char *stringToDisplay)
{
	glRasterPos3f(x, y, z);
	for(char* c = stringToDisplay; *c != '\0'; c++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24 , *c);
	}
}

void init()
{
	glClearColor(0.0,0.0,0.0,0);
	glColor3f(1.0,0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

    gluOrtho2D(-1200,1200,-700,700);                   //<-----CHANGE THIS TO GET EXTRA SPACE
//  gluOrtho2D(-200,200,-200,200);
	glMatrixMode(GL_MODELVIEW);
}

void introScreen()
{
	glClearColor(0.27, 0.77, 0.17, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	/*glColor3f(0.62, 0.28, 0.10);						//once we submitted the project
	displayRasterText(-400, 250, 0.0,"AIR STRIKE!!!");
	glColor3f(0.10, 0.28, 0.62);
	displayRasterText(-400, 300, 0.0,"---THE REAL SHOOTERS---");	//once we submitted the project
	*/
	glColor3f(0.30, 0.20, 0.50);
	displayRasterText(-400, 575, 0.0,"American International University");
	displayRasterText(-300, 500, 0.0,"-Bangladesh(AIUB)");
	glColor3f(0.0, 0.0, 1.0);
	displayRasterText(-600, 400, 0.0,"FACULTY OF SCIENCE AND TECHNOLOGY");
	displayRasterText(-40, 320, 0.0,"Spring 22-23");
	displayRasterText(-312, 220, 0.0,"Project Name: Air Strike!!!");
	displayRasterText(-230, 120, 0.0,"Project Proposed by:");
	displayRasterText(-800, 00, 0.0,"Name:");
	displayRasterText(-100, 00, 0.0,"ID:");
	displayRasterText(350, 00, 0.0,"Supervised By:");
	glColor3f(0.0, 0.0, 0.0);
	displayRasterText(-1000, -100, 0.0,"1. MD SAHADUL HAQUE ");
	displayRasterText(-1000, -150, 0.0,"2. KOWSHIK HALDER");
	displayRasterText(-1000, -200, 0.0,"3. JWEL MIAH");
	displayRasterText(-1000, -250, 0.0,"4. MAHASHETAB HASSAN");
	displayRasterText(-1000, -300, 0.0,"5. TIRTHO KUMAR DAS");
	displayRasterText(-1000, -350, 0.0,"6. AMATUL WAHID PROTTASHA");
	glColor3f(0.0, 0.0, 0.0);
	displayRasterText(-200, -100, 0.0,"21-45417-3");
	displayRasterText(-200, -150, 0.0,"21-45408-3");
	displayRasterText(-200, -200, 0.0,"20-43243-1");
	displayRasterText(-200, -250, 0.0,"20-44361-3");
	displayRasterText(-200, -300, 0.0,"20-41894-1");
	displayRasterText(-200, -350, 0.0,"20-42071-1");
	displayRasterText(300, -100, 0.0,"MAHFUJUR RAHMAN");
	displayRasterText(300, -150, 0.0,"Lecturer, Computer Science");
	glColor3f(1.0, 0.0, 1.0);
	displayRasterText(-250, -400, 0.0,"Computer Graphics[D]");
    glColor3f(1.0, 1.0, 0.0);
	displayRasterText(-150, -550, 0.0,"Press ENTER to PLAY!");
	glFlush();
	glutSwapBuffers();
}

void startScreenDisplay()
{
	glLineWidth(10);
	//SetDisplayMode(MENU_SCREEN);

	glColor3f(1,0,0);
	glBegin(GL_LINE_LOOP);               //Border
    glVertex2f(-750 ,-500);
    glVertex2f(-750 ,550);
    glVertex2f(750 ,550);
    glVertex2f(750 ,-500);
	glEnd();

	glLineWidth(1);

	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);				//START GAME PLOYGON
    glVertex2f(-200 ,300);
    glVertex2f(-200 ,400);
    glVertex2f(200 ,400);
    glVertex2f(200 ,300);
	glEnd();

	glBegin(GL_POLYGON);				//INSTRUCTIONS POLYGON
    glVertex2f(-200, 50);
    glVertex2f(-200 ,150);
    glVertex2f(200 ,150);
    glVertex2f(200 ,50);
	glEnd();

	glBegin(GL_POLYGON);				//QUIT POLYGON
    glVertex2f(-200 ,-200);
    glVertex2f(-200 ,-100);
    glVertex2f(200, -100);
    glVertex2f(200, -200);
	glEnd();

	if(mouseX>=-100 && mouseX<=100 && mouseY>=150 && mouseY<=200)
    {
		glColor3f(0 ,0 ,1) ;
		if(mButtonPressed)
        {
			playerLife = boss1Life = 1000;
			viewPage = GAME;
			mButtonPressed = false;
		}
	}
    else
		glColor3f(0 , 0, 0);

	displayRasterText(-100 ,340 ,0.4 ,"Start Game");

	if(mouseX>=-100 && mouseX<=100 && mouseY>=30 && mouseY<=80)
    {
		glColor3f(0 ,0 ,1);
		if(mButtonPressed)
        {
			viewPage = INSTRUCTIONS;
			printf("button pressed bitch\n");
			mButtonPressed = false;
		}
	} else
		glColor3f(0 , 0, 0);
	displayRasterText(-120 ,80 ,0.4 ,"Instructions");

	if(mouseX>=-100 && mouseX<=100 && mouseY>=-90 && mouseY<=-40)
    {
		glColor3f(0 ,0 ,1);
		if(mButtonPressed)
		{
			mButtonPressed = false;
			exit(0);
		}
	}
	else
		glColor3f(0 , 0, 0);
	displayRasterText(-100 ,-170 ,0.4 ,"    Quit");
	glutPostRedisplay();
}

void backButton()
{
	if(mouseX <= -450 && mouseX >= -500 && mouseY >= -275 && mouseY <= -250)
    {
			glColor3f(0, 0, 1);
			if(mButtonPressed)
            {
				viewPage = MENU;
				mButtonPressed = false;
				//instructionsGame = false;
				glutPostRedisplay();
			}
	}
	else glColor3f(1, 0, 0);
	displayRasterText(-1000 ,-550 ,0, "Back");
}

void instructionsScreenDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//SetDisplayMode(MENU_SCREEN);
	//colorBackground();
	glColor3f(1, 0, 0);
	displayRasterText(-300 ,550 ,0.4 ,"INSTRUCTIONS");
    glColor3f(1, 0, 0);
	displayRasterText(-1000 ,400 ,0.4 ,"CONTROLS: ");

	glColor3f(1, 1, 1);
	displayRasterText(-600 ,400 ,0.4 ,"Key 'w' to move up.");
	displayRasterText(-600 ,300 ,0.4 ,"Key 's' to move down.");
	displayRasterText(-600 ,200 ,0.4 ,"Key 'd' to move right.");
	displayRasterText(-600 ,100 ,0.4 ,"Key 'a' to move left.");

	displayRasterText(-600 ,0 ,0.4 ,"Key 'SPACE' to shoot.");
	//displayRasterText(-1100 ,-100 ,0.4 ,"The packet can be placed only when 's' is pressed before.");
	displayRasterText(-1000, -300,0.4,"The Objective is to kill THE BOSS.");
	displayRasterText(-1000 ,-370 ,0.4 ,"Each time a player gets shot, LIFE decreases by 5 points.");
	backButton();
	//if(previousScreen)
	//	nextScreen = false ,previousScreen = false; //as set by backButton()
}

void DrawLaser(int x, int y, bool dir[])
{
	//glPushMatrix();
	int xend = -XMAX, yend = y;
	if(dir[0])
		yend = YMAX;
	else if(dir[1])
		yend = -YMAX;
	glLineWidth(5);
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
		glVertex2f(x, y);
		glVertex2f(xend, yend);
	glEnd();
	//glPopMatrix();
}
void drawBullet(int x, int y, bool isPlayer1)
{
    glPushMatrix();
    glTranslated(x,y,0);

    glColor3f(0.0,0.0,0.0);
    glBegin(GL_POLYGON);//upper triangle construction plane
    glVertex2f(135.0,55.0);
    glVertex2f(150.0,50.0);
    glVertex2f(155.0,45.0);
    glVertex2f(160.0,40.0);
    glVertex2f(135.0,40.0);
    glEnd();
    glPopMatrix();

}

 void asLine(GLfloat px1,GLfloat py1,GLfloat px2,GLfloat py2,GLfloat Rcolor,GLfloat Gcolor,GLfloat Bcolor)
 {
    glLineWidth(4);
	glBegin(GL_LINES);              // Each set of 4 vertices form a quad
	glColor3f(Rcolor, Gcolor, Bcolor); // Red
	glVertex2f(px1,py1);    // x, y
	glVertex2f(px2, py2);    // x, y

	glEnd();
 }

GLfloat Round(GLfloat num)
{
    GLfloat rounded_num = round((num/255) * 100000) / 100000.0;
    return rounded_num;
}

void circle(GLfloat cx,GLfloat cy,GLfloat rx,GLfloat ry,GLfloat Rcolor,GLfloat Gcolor,GLfloat Bcolor)//cy,cx center.rx,ry radius of x and y.for circle both rx,xy same value.
{
    int triangleAmount = 100;
	GLfloat twicePi = 2.0f * PI;

	glColor3f(Round(Rcolor),Round(Gcolor),Round(Bcolor));//for color
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(cx, cy); // center of circle
		for(int i = 0; i <= triangleAmount;i++)
        {
			glVertex2f( cx + (rx * cos(i *  twicePi / triangleAmount)),
                        cy + (ry * sin(i * twicePi / triangleAmount)) );
		}
	glEnd();
}


void rocket()
{
	asLine(30,-30,0,0,1,1,1);
	asLine(30,30,0,0,1,1,1);

	circle(30,-30,-22.5,-15,52,180, 235);
	circle(42,-30,-15,-30,255, 100, 0);

	circle(30,30,-22.5,-15,52,180, 235);
	circle(42,30,-15,-30,255, 100, 0);



	asLine(-75,0,-90,0,1,1,1);
	circle(-90,0,-3,-3,0,0,0);
	circle(-30,0,-45,-15,245, 42, 69);
	circle(-37.5,0,-37.5,-22.5,245, 42, 69);
	asLine(22.5,0,0.0,0,0,0,0);
	circle(-52.5,0,-9,-9,247, 245, 245);
	circle(-52.5,0,-7.5,-7.5,149, 201, 252);

	circle(-30,0,-6,-6,247, 245, 245);
	circle(-30,0,-4.5,-4.5,149, 201, 252);
}

void createPlane(int x, int y, bool isPlayer1)
{
    glPushMatrix();
    glTranslated(x,y,0);

    rocket();

    glPopMatrix();
}

void boss1()
{
    circle(0,0,50,65, 64, 86, 48);
	circle(0,-30,30,-2, 255, 255, 255);  //x,y,x-radius,y-radius,color,gl color,gl color
	circle(30,25,8,8,255, 0, 0 ); //eye circle right red
	circle(27,25,4,4,0, 0, 0 ); //eye circle black

	circle(-20,25,8,8,255, 0, 0 ); //eye circle left red
	circle(-23,25,4,4,0, 0, 0 ); //eye circle black


	asLine(110,0,120,0,255,0,0);
	circle(-5,0,6,6,0, 0, 0 ); //nose circle black
}
int flag=1;
void update1(int value)
{
    if(flag==1){
        if(position1<-200.0){
            flag=2;
        }
        position1-=speed1;
    }
    else if(flag==2){
        if(position1>200.0){
            flag=1;
        }
        position1+=speed1;
    };
    glutPostRedisplay();
    glutTimerFunc(100,update1,0);
}
void createBoss1(int x, int y, bool isPlayer)
{
    // Seed the random number generator with the current time
    //srand(time(nullptr));

    // Generate a random number between 1 and 100
    int randomNumber = rand() % 201 - 100;
    int flag=1;
    x=550;
    y=position1;
    // Output the random number to the console
    std::cout << "Random number: " << randomNumber << std::endl;
    glPushMatrix();
    glTranslated(x,y,0);
    // Get the current elapsed time
    int currentTime = glutGet(GLUT_ELAPSED_TIME);

    // Check if it's time to show the laser
    if (laser1 && currentTime % laserPeriod < laserPeriod / 2) {
    DrawLaser(xOne, yOne, laser1Dir);
    checkLaserContact(xOne, yOne, laser1Dir, -xTwo, yTwo, true);
    }

    boss1();

    glPopMatrix();

}

void DisplayHealthBar1()
{
	char temp1[40];
	glColor3f(1 ,1 ,1);
	sprintf(temp1," Player LIFE = %d",playerLife);
	displayRasterText(-1100 ,600 ,0.4 ,temp1);
	glColor3f(1 ,0 ,0);
}

void DisplayHealthBar2()
{
	char temp2[40];
	glColor3f(1 ,1 ,1);
	sprintf(temp2," Boss LIFE = %d",boss1Life);
	displayRasterText(800 ,600 ,0.4 ,temp2);
	glColor3f(1 ,0 ,0);
}

void checkLaserContact(int x, int y, bool dir[], int xp, int yp, bool player1)
{
	int xend = -XMAX, yend = y;
	xp += 8; yp += 8; // moving circle slightly up to fix laser issue
	if(dir[0])
		yend = YMAX;
	else if(dir[1])
		yend = -YMAX;

	// Here we find out if the laser(line) intersects with spaceship(circle)
	// by solving the equations for the same and finding the discriminant of the
	// quadratic equation obtained
	float m = (float)(yend - y) / (float)(xend - x);
	float k = y - m * x ;
	int r = 50; // approx radius of the spaceship

	//calculating value of b, a, and c needed to find discriminant
	float b = 2 * xp - 2 * m * (k - yp);
	float a = 1 + m * m;
	float c = xp * xp + (k - yp) * (k - yp) - r * r;

	float d = (b * b - 4 * a * c); // discriminant for the equation
	printf("\nDisc: %f x: %d, y: %d, xp: %d, yp: %d", d, x, y, xp, yp);
	if(d >= 0)
    {
		if(player1)
			playerLife -= .05;
		else
			boss1Life -= .05;

		printf("%d %d\n", playerLife, boss1Life);
	}
}

void createBG1(int x, int y, bool isPlayer)
{
    glPushMatrix();
    initBG();
    glTranslated(x,0,0);
    screenBG();

    glPopMatrix();
}

void gameScreenDisplay()
{
    //createBG1(1,0,1);
	DisplayHealthBar1();
	DisplayHealthBar2();
	glScalef(2, 2 ,0);

	if(playerLife > 0)
    {
		createBoss1(xOne, yOne, true);

	}
	else
    {
		viewPage = GAMEOVER;
	}

	if(boss1Life > 0)
    {
		glPushMatrix();
		glScalef(-1, 1, 1);
		createPlane(xTwo, yTwo, false);
		if(laser2)
		{
			DrawLaser(xTwo, yTwo, laser2Dir);
			checkLaserContact(xTwo, yTwo, laser2Dir, -xOne, yOne, false);
		}
		glPopMatrix();
	}
	else
    {
		viewPage = GAMEOVER;
	}

	if(viewPage == GAMEOVER)
    {
		xOne = xTwo = 400;
		yOne = yTwo = 0;
	}
}

void displayGameOverMessage()
{
	glColor3f(1, 1, 0);
	char* message;
	if(playerLife > 0)
		message = "You won the game...";
	else
		message = "Game Over!";

	displayRasterText(-350 ,600 ,0.4 , message);
}

void keyOperations()
{
	if(keyStates[13] == true && viewPage == INTRO)
    {
		viewPage = MENU;
		printf("view value changed to %d", viewPage);
		printf("enter key pressed\n");
	}
	if(viewPage == GAME)
	{
		laser1Dir[0] = laser1Dir[1] = false;
		laser2Dir[0] = laser2Dir[1] = false;
		if(keyStates[' '] == true) laser2 = true;
		if(keyStates[' '] == false) laser2 = false;
        if(keyStates['d'] == true) xTwo-=SPACESHIP_SPEED;
        if(keyStates['a'] == true) xTwo+=SPACESHIP_SPEED;
        if(keyStates['w'] == true) yTwo+=SPACESHIP_SPEED;
        if(keyStates['s'] == true) yTwo-=SPACESHIP_SPEED;

		laser1 = true;
	}
}

void display()
{
	//glClearColor(, 0 , 0, 1);
	keyOperations();
	glClear(GL_COLOR_BUFFER_BIT);

	switch (viewPage)
	{
		case INTRO:
			introScreen();
			break;
		case MENU:
			startScreenDisplay();
			break;
		case INSTRUCTIONS:
			instructionsScreenDisplay();
			break;
		case GAME:
			gameScreenDisplay();
			//reset scaling values
			glScalef(1/2 ,1/2 ,0);
			break;
		case GAMEOVER:
			displayGameOverMessage();
			startScreenDisplay();
			break;
	}

	glFlush();
	glLoadIdentity();
	glutSwapBuffers();
}

// void reshape(GLint w, GLint h)
// {
// 	glViewport(0, 0, w, h);
// 	glMatrixMode(GL_PROJECTION);
// 	glLoadIdentity();
// 	if(h>w)
// 	{
// 		gluOrtho2D(0, 500, ((float)h/(float)w)*(0), ((float)h/(float)w)*500);
// 	}
// 	else
// 	{
// 		gluOrtho2D(((float)w/(float)h)*(0), ((float)w/(float)h)*(500), 0, 500);
// 	}
// 	glMatrixMode(GL_MODELVIEW);
// 	glutPostRedisplay();
// }

void passiveMotionFunc(int x,int y)
{

	//when mouse not clicked
	mouseX = float(x)/(m_viewport[2]/1200.0)-600.0;  //converting screen resolution to ortho 2d spec
	mouseY = -(float(y)/(m_viewport[3]/700.0)-350.0);

	//Do calculations to find value of LaserAngle
	//somethingMovedRecalculateLaserAngle();
	glutPostRedisplay();
}

void mouseClick(int buttonPressed ,int state ,int x, int y)
{

	if(buttonPressed == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		mButtonPressed = true;
	else
		mButtonPressed = false;
	glutPostRedisplay();
}

void keyPressed(unsigned char key, int x, int y)
{
	keyStates[key] = true;
	glutPostRedisplay();
}

void refresh()
{
	glutPostRedisplay();
}

void keyReleased(unsigned char key, int x, int y)
{
	keyStates[key] = false;
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1200, 700);
    glutCreateWindow("Space Shooter");
    init();
    //glutReshapeFunc(reshape);
	glutIdleFunc(refresh);
    glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyReleased);
	glutMouseFunc(mouseClick);
	glutPassiveMotionFunc(passiveMotionFunc);
	glGetIntegerv(GL_VIEWPORT ,m_viewport);
    glutDisplayFunc(display);
    glutTimerFunc(100, update1, 0);

    glutMainLoop();
}
