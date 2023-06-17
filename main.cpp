
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
#include <cstdio>
#include <windows.h>

#define FORWARD 1

#define BACKWARD 2

int WIDTH = 1000, HEIGHT = 750;
int OBJECT_HEIGHT = HEIGHT / 15;

int CLOUD_POSITION = WIDTH, SUN_X_POSITION = 0, SUN_Y_POSITION = 0, day = 1;
int BUS_POSITION = WIDTH, human_x = 150, human_y = 300;

double angle = 0.0;

void reshape( int width,int height)
{
    glClearColor(1.0, 1.0 ,1.0, 1.0);
    glViewport(0,0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(0.0,width,0.0,height);


    if (width < 1000 || height < 750)
    {
        glutReshapeWindow(1000, 750);
    }

    glMatrixMode(GL_MODELVIEW);

}


void drawRays(float r, double x_center, double y_center, int degree, int line_width)
{
    int deg = 0;
    double theta, x0 = x_center, y0 = y_center, x1 = 0, y1 = 0;

    glLineWidth(line_width);
    glColor3ub(255, 228, 132);
    glBegin(GL_LINES);

    while(deg <= 360)
    {
        theta = (deg* M_PI)/180;
        x0 = x_center + (r+10) * cos(theta);
        y0 = y_center + (r+10) * sin(theta);

        x1 = x_center + (r+20) * cos(theta);
        y1 = y_center + (r+20) * sin(theta);



        glVertex2d(x0, y0);
        glVertex2d(x1, y1);
        deg+=degree;
    }
    glEnd();
}

void makeCircle(int r, double x_center, double y_center, bool isFill)
{
    int deg = 0;
    double theta, x = x_center, y = y_center;

    if(isFill)
    {
        glBegin(GL_TRIANGLE_FAN);
    }
    else
    {
        glBegin(GL_POINTS);
    }
    glPointSize(3);

    glVertex2d(x, y);
    while(deg <= 360)
    {
        theta = (deg* M_PI)/180;
        x = x_center + r * cos(theta);
        y = y_center + r * sin(theta);



        glVertex2d(x, y);
        deg+=1;
    }
    glEnd();
}


void makeSun(int r, double x_center, double y_center)
{
    if (day == 1)
    {
        glColor3ub(255, 228, 132);
        drawRays(r, x_center, y_center, 20, 1);
    }
    else if(day == 0)
    {
        glColor3ub(240, 240, 240);
    }
    makeCircle(r, x_center, y_center, 1);

}

void makeCloud(int radius, int x, int y)
{
    int r = radius;

    if (day == 1)
    {
        glColor3ub(227, 224, 236);
    }
    else if (day == 0)
    {
        glColor3ub(20, 20, 20);
    }

    makeCircle(r, x, y, 1);
    makeCircle(r, x + 20, y+10, 1);
    makeCircle(r, x + 20 , y-10, 1);
    makeCircle(r, x + 40 , y + 10, 1);
    makeCircle(r, x + 40 , y - 10, 1);
    makeCircle(r, x + 60 , y, 1);

}
void makeBus(int x, int y)
{
    glColor3ub(50, 100, 155);
    glRecti(450, 230, 700, 370);

    glColor3ub(150, 100, 155);
    glBegin(GL_QUADS);
    glVertex2i(460, 220);
    glVertex2i(690, 220);
    glVertex2i(700, 230);
    glVertex2i(450, 230);
    glEnd();

    //window

    glColor3ub(244, 244, 169);
    glRecti(480, 300, 530, 350);

    glPushMatrix();
    glTranslatef(70, 0, 0);
    glRecti(480, 300, 530, 350);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(140, 0, 0);
    glRecti(480, 300, 530, 350);
    glPopMatrix();

    //Font glass

    glColor3ub(45, 244, 23);
    glBegin(GL_QUADS);
    glVertex2i(450, 290);
    glVertex2i(460, 300);
    glVertex2i(460, 360);
    glVertex2i(450, 360);
    glVertex2i(450, 290);
    glEnd();

    glLineWidth(3);
    glBegin(GL_LINE_STRIP);
    glVertex2i(450, 360);
    glVertex2i(440, 360);
    glVertex2i(440, 350);
    glEnd();

    /// Wheel

    glColor3ub(0, 0, 0);
    //Front Wheel
    makeCircle(20, 510, 220, 1);

    glPushMatrix();
    glTranslated(510, 220, 0);
    glRotated(angle, 0, 0, 1);
    glTranslated(-510, -220, 0);
    drawRays(1, 510, 220, 45, 3);
    glPopMatrix();

    makeCircle(8, 510, 220, 1);
    //Back Wheel
    glColor3ub(0, 0, 0);
    makeCircle(20, 640, 220, 1);

    glPushMatrix();
    glTranslated(640, 220, 0);
    glRotated(angle, 0, 0, 1);
    glTranslated(-640, -220, 0);
    drawRays(1, 640, 220, 45, 3);
    glPopMatrix();

    makeCircle(8, 640, 220, 1);


}

void makeHouse(int x , int y)
{
    // House front part
    glColor3ub(212, 40, 48);
    glRecti(780, 300, 950, 400);

    // House side part
    glColor3ub(102, 18, 21);
    glBegin(GL_QUADS);
    glVertex2i(780, 300);
    glVertex2i(780, 400);
    glVertex2i(730, 400);
    glVertex2i(730, 320);
    glEnd();

    // Roof top small part
    glColor3ub(68, 68, 68);
    glBegin(GL_TRIANGLES);
    glVertex2i(710, 400);
    glVertex2i(780, 400);
    glVertex2i(740, 450);
    glEnd();

    // Roof top big part
    glColor3ub(124, 124, 124);
    glBegin(GL_QUADS);
    glVertex2i(780, 400);
    glVertex2i(980, 400);
    glVertex2i(950, 450);
    glVertex2i(740, 450);
    glEnd();

    // Window
    glColor3ub(128, 128, 255);
    glRecti(810, 330, 850, 370);

    //Door
    glColor3ub(252, 190, 111);
    glRecti(880, 300, 920, 370);

    //shadow
    glColor4ub(0, 0, 0, 224);
    glBegin(GL_TRIANGLES);
    glVertex2i(730, 320);
    glVertex2i(730, 300);
    glVertex2i(780, 300);
    glEnd();

}


void tree()
{
    // Tree body part
    glColor4ub(166, 123, 81,255);
    glRecti(350, 300, 370, 400);
    //Tree leaf
    glColor3ub(12,174, 31);
    makeCircle(20, 315, 390, 1);
    makeCircle(20, 330, 390, 1);
    makeCircle(20, 345, 390, 1);
    makeCircle(20, 360, 390, 1);
    makeCircle(20, 375, 390, 1);
    makeCircle(20, 390, 390, 1);
    makeCircle(20, 405, 390, 1);

    makeCircle(20, 330, 405, 1);
    makeCircle(20, 345, 405, 1);
    makeCircle(20, 360, 405, 1);
    makeCircle(20, 375, 405, 1);
    makeCircle(20, 390, 405, 1);

    makeCircle(20, 345, 420, 1);
    makeCircle(20, 360, 420, 1);
    makeCircle(20, 375, 420, 1);

    makeCircle(20, 360, 435, 1);

}
void star()
{
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(770,520);
    glVertex2f(784,520);
    glVertex2f(777,534);
    glVertex2f(770,529);
    glVertex2f(784,529);
    glVertex2f(777,515);
    glEnd();
}
void skyView(int x, int y)
{
    if (day == 1)
    {
        glColor3ub(135, 206, 235);
    }
    else if(day == 0)
    {

        glColor3ub(10, 10, 10);

    }
    glRecti(0, 0, x, y);

    // star
    if (day == 0)
    {
        int star_pos_x = 0, star_pos_y = 0;
        for (int i = 1; i<=5; i++)
        {
            glPushMatrix();
            glTranslated(star_pos_x, star_pos_y, 0);
            star();
            glTranslated(star_pos_x, star_pos_y, 0);
            glPopMatrix();
            star_pos_x -= 150;
            star_pos_y +=30;

        }
    }
    glPushMatrix();
    glTranslated(CLOUD_POSITION, 0, 0);
    makeCloud(15, 200, 400);
    makeCloud(20, 400, 500);
    makeCloud(20, 600, 550);
    makeCloud(30 ,800, 600);
    makeCloud(30, 950, 600);
    glPopMatrix();



    glPushMatrix();
    glTranslated(SUN_X_POSITION, SUN_Y_POSITION, 0);
    makeSun(40, 150, 300);
    glPopMatrix();

}
void river(int x, int y)
{
    glRecti(0, 0, x, y);
}

void passengerSet()
{
    glColor3ub(0, 0, 244);
    glRecti(100, 270, 250, 350);


    glColor4ub(34, 56, 127, 220);
    glRecti(90, 370, 150, 400);
    glRecti(200, 370, 270, 400);

    // vertical line
    glColor3ub(50, 0, 255);
    glLineWidth(5);
    glBegin(GL_LINES);

    glVertex2i(100, 250);
    glVertex2i(100, 370);
    glVertex2i(250, 250);
    glVertex2i(250, 370);

    // uper part line
    glColor3ub(156, 35, 189);
    glVertex2i(80, 370);
    glVertex2i(280, 370);
    glVertex2i(80, 400);
    glVertex2i(280, 400);

    glEnd();

}
void makeHuman(int x, int y)
{
    glColor3ub(255, 255, 148);
    makeCircle(10, x, y, 1);
    glBegin(GL_LINES);
    glVertex2i(x, y);
    glVertex2i(x, y-15);
    glEnd();
    glRecti(x-10, y-15, x+10, y-30);


    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2i(x-5, y-30);
    glVertex2i(x-5, y-50);
    glVertex2i(x+5, y-30);
    glVertex2i(x+5, y-50);
    glEnd();
}
void mountain()
{
    int r=200, x = 500, y = 250;

    glColor3ub(71, 169, 146);
    makeCircle(r-75, x - 400, y, 1);
    glColor3ub(92, 137, 132);
    makeCircle(r-50, x - 300, y, 1);
    glColor3ub(71, 169, 146);
    makeCircle(r-25, x - 200, y, 1);

    glColor3ub(92, 137, 132);
    makeCircle(r, x, y, 1);

    glColor3ub(71, 169, 146);
    makeCircle(r+25, x + 200, y, 1);
    glColor3ub(92, 137, 132);
    makeCircle(r+50, x + 300, y, 1);
    glColor3ub(71, 169, 146);
    makeCircle(r+75, x + 400, y, 1);
}
void mountainView(int x, int y)
{
    mountain();
//    glRecti(0, 0, x, y);
    makeHouse(x, y);
    tree();
    glPushMatrix();
    glTranslatef(200, 0, 0);
    tree();
    glPopMatrix();

}


void roadLight()
{
    glColor3ub(40, 40, 40);
    glRecti(150, 100, 160, 400);
    glRecti(130, 400, 180, 410);

    if(day == 0)
    {
        glColor3ub(231,180,22);
    }
    glRecti(130, 410, 140, 390);
    glRecti(170, 410, 180, 390);
}

// Road Construction

void roadLine(int w, int h)
{

    int line_width = 0;
    glLineWidth(5);
    glBegin(GL_LINES);

    glColor3ub(255, 255, 255);
    glVertex2i(line_width, h/2);

    // draw road single line with gap 50 points
    while(line_width<=WIDTH)
    {
        line_width +=50;
        glVertex2i(line_width, h/2);
    }
    glEnd();

    // draw a full of the upper part of the road
    glBegin(GL_LINES);
    glVertex2i(0, h - 50);
    glVertex2i(WIDTH,  h - 50);

    glEnd();


}
void roadView(int x, int y)
{
    glRecti(0, 0, x, y);
    roadLine(x, y);
    passengerSet();
    makeHuman(human_x, human_y);
    makeHuman(human_x+25, human_y);
    makeHuman(human_x+50, human_y);

    glPushMatrix();
    glTranslated(BUS_POSITION, 0, 0);
    makeBus(x, y);
    glPopMatrix();

    // Road Light
    int light_pos = 0;
    for (int i = 1; i<=3; i++)
    {
        glPushMatrix();
        glTranslated(light_pos, 0, 0);
        roadLight();
        glTranslated(-light_pos, 0, 0);
        light_pos += 300;
        glPopMatrix();
    }

}

int state = FORWARD;
void timer(int value)
{
    switch(state)
    {
        case FORWARD:
            SUN_X_POSITION -= 1;
            SUN_Y_POSITION += 5;
//        printf("%d \t %d\n",SUN_X_POSITION, SUN_Y_POSITION);
            if(SUN_Y_POSITION >= 300)
            {
                SUN_X_POSITION = -60;
                SUN_Y_POSITION = 300;

            }
            if(CLOUD_POSITION <= WIDTH)
            {

                if(CLOUD_POSITION > -350)
                {
                    CLOUD_POSITION -=2;

                }
                else
                {
                    state = BACKWARD;
                }

            }

            if (BUS_POSITION <= WIDTH)
            {
                BUS_POSITION -=5;
                angle += 20;
                printf("%d\n", BUS_POSITION);

                if (BUS_POSITION < -900)
                {
                    BUS_POSITION = WIDTH;
                    human_x = 150;
                    human_y = 300;
                }
                if (BUS_POSITION == -415)
                {
                    human_x = -50;
                    human_y = -50;
                    Sleep(1000);

                }
                printf("%d\n", BUS_POSITION);
            }

            glutPostRedisplay();
            glutTimerFunc(1000/30, timer, 0);
            break;
        case BACKWARD:
            if(CLOUD_POSITION < 150)
            {
                CLOUD_POSITION +=2;
            }

            else state = FORWARD;
            glutPostRedisplay();
            glutTimerFunc(1000/30, timer, 0);
            break;
        default:

            break;
    }
}

void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 'N':
        case 'n':
            day = 0;
            glutPostRedisplay();
            break;

        case 'D':
        case 'd':
            day = 1;
            glutPostRedisplay();
            break;

        default:
            //nothing
            break;
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();


    // This is used for transparant color
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//    glColor3ub(38, 156, 230);
    glColor3ub(0, 0, 0);
    skyView(WIDTH, OBJECT_HEIGHT * 15);

//    glColor3ub(38, 156, 23);
    mountainView(WIDTH, OBJECT_HEIGHT * 11);

    glColor3ub(194, 195, 199);
    roadView(WIDTH, OBJECT_HEIGHT * 6);

    glColor3ub(127, 205, 255);
    river(WIDTH, OBJECT_HEIGHT * 2);



    glutSwapBuffers();
}
int main(int argc, char** argv)
{


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);



    glutInitWindowPosition(0, 0);
    glutInitWindowSize(WIDTH, HEIGHT);

    glutCreateWindow("Smart Bus Station");
    glutDisplayFunc(display);
    glutTimerFunc(1000, timer, 0);

    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);

//    init();
    glutMainLoop();
}

