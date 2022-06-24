#include <GL/glut.h>
#include <math.h>
#include <iostream>
using namespace std;

#define FPS 120
#define TO_RADIANS 3.14/180.0

//  Anggota Kelompok X
//  Nama (NIM)
//  Nama (NIM)
//  Nama (NIM)
//  Nama (NIM)
//  Nama (NIM)

const int width = 1280;
const int height = 720;
int i;
float sudut;
double x_geser, y_geser, z_geser;

float pitch = 0.0, yaw = 0.0;
float camX = 0.0, camZ = 0.0, terbang = 25.0;

void display();
void reshape(int w, int h);
void timer(int);
void passive_motion(int, int);
void camera();
void keyboard(unsigned char key, int x, int y);
void keyboard_up(unsigned char key, int x, int y);

struct Motion {
    bool Forward, Backward, Left, Right, Naik, Turun;
};
Motion motion = { false,false,false,false,false,false };

void init() {
    glClearColor(0.529, 0.807, 0.921, 0.0);
    glutSetCursor(GLUT_CURSOR_NONE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc(GL_LEQUAL);
    glutWarpPointer(width / 2, height / 2);
}

void ground() {
    glBegin(GL_QUADS);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1000.0, 0, -1000.0);

    glColor3f(0.6f, 0.6f, 0.6f);
    glVertex3f(1000.0, 0, -1000.0);

    glColor3f(0.6f, 0.6f, 0.6f);
    glVertex3f(1000.0, 0, 1000.0);

    glColor3f(0.3f, 0.3f, 0.3f);
    glVertex3f(-1000.0, 0, 1000.0);
    glEnd();
}

void lantai1() {
    glBegin(GL_POLYGON); //atas
    glColor3f(0.36, 0.36, 0.36);
    glVertex3f(-200, 0.5, -200); //1
    glVertex3f(200, 0.5, -200); //2
    glVertex3f(200, 0.5, 200); //3
    glVertex3f(-200, 0.5, 200); //4
    glEnd();

    glBegin(GL_POLYGON); //bawah
    glColor3f(0.36, 0.36, 0.36);
    glVertex3f(-200, 25, 200); //5
    glVertex3f(200, 25, 200); //6
    glVertex3f(200, 25, -200); //7
    glVertex3f(-200, 25, -200); //8
    glEnd();

    glBegin(GL_POLYGON); //sisi1
    glColor3f(0.36, 0.36, 0.36);
    glVertex3f(-200, 25, 200); //5
    glVertex3f(-200, 0.5, 200); //4
    glVertex3f(200, 0.5, 200); //3
    glVertex3f(200, 25, 200); //6
    glEnd();

    glBegin(GL_POLYGON); //sisi2
    glColor3f(0.36, 0.36, 0.36);
    glVertex3f(-200, 25, -200); //8
    glVertex3f(-200, 0.5, -200); //1
    glVertex3f(-200, 0.5, 200); //4
    glVertex3f(-200, 25, 200); //5
    glEnd();

    glBegin(GL_POLYGON); //sisi3
    glColor3f(0.36, 0.36, 0.36);
    glVertex3f(-200, 25, -200); //8
    glVertex3f(-200, 0.5, -200); //1
    glVertex3f(200, 0.5, -200); //2
    glVertex3f(200, 25, -200); //7
    glEnd();

    glBegin(GL_POLYGON); //sisi4
    glColor3f(0.36, 0.36, 0.36);
    glVertex3f(200, 25, -200); //7
    glVertex3f(200, 0.5, -200); //2
    glVertex3f(200, 0.5, 200); //3
    glVertex3f(200, 25, 200); //6
    glEnd();

    glBegin(GL_POLYGON); //bawah
    glColor3f(0.46, 0.46, 0.46);
    glVertex3f(-190, 25.1, 190); //5
    glVertex3f(190, 25.1, 190); //6
    glVertex3f(190, 25.1, -190); //7
    glVertex3f(-190, 25.1, -190); //8
    glEnd();
}

void bangun_lantai1() {
    //(-87.5,  150, -87.5,)
    //glColor3ub(237, 91, 23);

    glBegin(GL_POLYGON); //atas
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-87.5, 150, -87.5); //1
    glVertex3f(87.5, 150, -87.5); //2
    glVertex3f(87.5, 150, 87.5); //3
    glVertex3f(-87.5, 150, 87.5); //4
    glEnd();

    glBegin(GL_POLYGON); //sisi1
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-87.5, 25, 87.5); //5
    glVertex3f(-87.5, 150, 87.5); //4
    glVertex3f(87.5, 150, 87.5); //3
    glVertex3f(87.5, 25, 87.5); //6
    glEnd();

    glBegin(GL_POLYGON); //sisi2
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-87.5, 25, -87.5); //8
    glVertex3f(-87.5, 150, -87.5); //1
    glVertex3f(-87.5, 150, 87.5); //4
    glVertex3f(-87.5, 25, 87.5); //5
    glEnd();

    glBegin(GL_POLYGON); //sisi3
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-87.5, 25, -87.5); //8
    glVertex3f(-87.5, 150, -87.5); //1
    glVertex3f(87.5, 150, -87.5); //2
    glVertex3f(87.5, 25, -87.5); //7
    glEnd();

    glBegin(GL_POLYGON); //sisi4
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(87.5, 25, -87.5); //7
    glVertex3f(87.5, 150, -87.5); //2
    glVertex3f(87.5, 150, 87.5); //3
    glVertex3f(87.5, 25, 87.5); //6
    glEnd();

    //(-130, 170,-130)
    glBegin(GL_POLYGON); //sisi4
    glColor3ub(238, 124, 32);
    glVertex3f(-130, 170, -130); //1
    glVertex3f(130, 170, -130); //2
    glVertex3f(130, 170, 130); //3
    glVertex3f(-130, 170, 130); //4
    glEnd();

    glBegin(GL_POLYGON); //sisi1
    glColor3ub(238, 124, 32);
    glVertex3f(-87.5, 150, 87.5); //5
    glVertex3f(-130, 170, 130); //4
    glVertex3f(130, 170, 130); //3
    glVertex3f(87.5, 150, 87.5); //6
    glEnd();

    glBegin(GL_POLYGON); //sisi2
    glColor3ub(238, 124, 32);
    glVertex3f(-87.5, 150, -87.5); //8
    glVertex3f(-130, 170, -130); //1
    glVertex3f(-130, 170, 130); //4
    glVertex3f(-87.5, 150, 87.5); //5
    glEnd();

    glBegin(GL_POLYGON); //sisi3
    glColor3ub(238, 124, 32);
    glVertex3f(-87.5, 150, -87.5); //8
    glVertex3f(-130, 170, -130); //1
    glVertex3f(130, 170, -130); //2
    glVertex3f(87.5, 150, -87.5); //7
    glEnd();

    glBegin(GL_POLYGON); //sisi4
    glColor3ub(238, 124, 32);
    glVertex3f(87.5, 150, -87.5); //7
    glVertex3f(130, 170, -130); //2
    glVertex3f(130, 170, 130); //3
    glVertex3f(87.5, 150, 87.5); //6
    glEnd();
}

void lantai2() {
    //glColor3ub(237, 91, 23);
    glBegin(GL_POLYGON); //atas
    glColor3ub(237, 91, 23);
    glVertex3f(-130, 180, -130); //1
    glVertex3f(130, 180, -130); //2
    glVertex3f(130, 180, 130); //3
    glVertex3f(-130, 180, 130); //4
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3f(0.26, 0.26, 0.26);
    glVertex3f(-120, 180.1, -120); //1
    glVertex3f(120, 180.1, -120); //2
    glVertex3f(120, 180.1, 120); //3
    glVertex3f(-120, 180.1, 120); //4
    glEnd();

    glBegin(GL_POLYGON); //sisi4
    glColor3ub(237, 91, 23);
    glVertex3f(-130, 170, -130); //8
    glVertex3f(130, 170, -130); //7
    glVertex3f(130, 170, 130); //6
    glVertex3f(-130, 170, 130); //5
    glEnd();

    glBegin(GL_POLYGON); //sisi1
    glColor3ub(237, 91, 23);
    glVertex3f(-130, 170, 130); //5
    glVertex3f(-130, 180, 130); //4
    glVertex3f(130, 180, 130); //3
    glVertex3f(130, 170, 130); //6
    glEnd();

    glBegin(GL_POLYGON); //sisi2
    glColor3ub(237, 91, 23);
    glVertex3f(-130, 170, -130); //8
    glVertex3f(-130, 180, -130); //1
    glVertex3f(-130, 180, 130); //4
    glVertex3f(-130, 170, 130); //5
    glEnd();

    glBegin(GL_POLYGON); //sisi3
    glColor3ub(237, 91, 23);
    glVertex3f(-130, 170, -130); //8
    glVertex3f(-130, 180, -130); //1
    glVertex3f(130, 180, -130); //2
    glVertex3f(130, 170, -130); //7
    glEnd();

    glBegin(GL_POLYGON); //sisi4
    glColor3ub(237, 91, 23);
    glVertex3f(130, 170, -130); //7
    glVertex3f(130, 180, -130); //2
    glVertex3f(130, 180, 130); //3
    glVertex3f(130, 170, 130); //6
    glEnd();
}

void bangun_lantai2() {
    //(-77.5,300,-77.5 )
    glBegin(GL_POLYGON); //atas
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-77.5, 300, -77.5); //1
    glVertex3f(77.5, 300, -77.5); //2
    glVertex3f(77.5, 300, 77.5); //3
    glVertex3f(-77.5, 300, 77.5); //4
    glEnd();

    glBegin(GL_POLYGON); //sisi1
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-77.5, 180, -77.5); //8
    glVertex3f(-77.5, 300, -77.5); //1
    glVertex3f(-77.5, 300, 77.5); //4
    glVertex3f(-77.5, 180, 77.5); //5
    glEnd();

    //pintu2_1
    glBegin(GL_POLYGON); //sisi1
    glColor3ub(237, 91, 23);
    glVertex3f(-77.6, 180, -22.5); //8
    glVertex3f(-77.6, 245, -22.5); //1
    glVertex3f(-77.6, 245, 22.5); //4
    glVertex3f(-77.6, 180, 22.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-77.7, 180, -17.5); //8
    glVertex3f(-77.7, 240, -17.5); //1
    glVertex3f(-77.7, 240, 17.5); //4
    glVertex3f(-77.7, 180, 17.5); //5
    glEnd();

    //pintu2_2
    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(155.5, 0, 0);
    //glRotatef(-90, 18, 0, 0);
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-77.7, 180, -22.5); //8
    glVertex3f(-77.7, 245, -22.5); //1
    glVertex3f(-77.7, 245, 22.5); //4
    glVertex3f(-77.7, 180, 22.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-77.6, 180, -17.5); //8
    glVertex3f(-77.6, 240, -17.5); //1
    glVertex3f(-77.6, 240, 17.5); //4
    glVertex3f(-77.6, 180, 17.5); //5
    glEnd();
    glPopMatrix();

    //pintu2_3
    glColor3ub(237, 91, 23);
    glPushMatrix();
    //glTranslatef(155.5, 0, 0);
    glRotatef(90, 0, 10, 0);
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-77.6, 180, -22.5); //8
    glVertex3f(-77.6, 245, -22.5); //1
    glVertex3f(-77.6, 245, 22.5); //4
    glVertex3f(-77.6, 180, 22.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-77.7, 180, -17.5); //8
    glVertex3f(-77.7, 240, -17.5); //1
    glVertex3f(-77.7, 240, 17.5); //4
    glVertex3f(-77.7, 180, 17.5); //5
    glEnd();
    glPopMatrix();

    //pintu2_3
    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(0, 0, -155.5);
    glRotatef(90, 0, 10, 0);
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-77.7, 180, -22.5); //8
    glVertex3f(-77.7, 245, -22.5); //1
    glVertex3f(-77.7, 245, 22.5); //4
    glVertex3f(-77.7, 180, 22.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-77.6, 180, -17.5); //8
    glVertex3f(-77.6, 240, -17.5); //1
    glVertex3f(-77.6, 240, 17.5); //4
    glVertex3f(-77.6, 180, 17.5); //5
    glEnd();
    glPopMatrix();

    //pintu2_3
    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(0, -155, -165.5);
    glRotatef(90, 0, 10, 0);
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-77.7, 180, -22.5); //8
    glVertex3f(-77.7, 245, -22.5); //1
    glVertex3f(-77.7, 245, 22.5); //4
    glVertex3f(-77.7, 180, 22.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-77.6, 180, -17.5); //8
    glVertex3f(-77.6, 240, -17.5); //1
    glVertex3f(-77.6, 240, 17.5); //4
    glVertex3f(-77.6, 180, 17.5); //5
    glEnd();
    glPopMatrix();

    glBegin(GL_POLYGON); //sisi2
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-77.5, 180, -77.5); //8
    glVertex3f(-77.5, 300, -77.5); //1
    glVertex3f(77.5, 300, -77.5); //2
    glVertex3f(77.5, 180, -77.5); //7
    glEnd();

    glBegin(GL_POLYGON); //sisi3
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(77.5, 180, -77.5); //7
    glVertex3f(77.5, 300, -77.5); //2
    glVertex3f(77.5, 300, 77.5); //3
    glVertex3f(77.5, 180, 77.5); //6
    glEnd();

    glBegin(GL_POLYGON); //sisi4
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-77.5, 180, 77.5); //5
    glVertex3f(-77.5, 300, 77.5); //4
    glVertex3f(77.5, 300, 77.5); //3
    glVertex3f(77.5, 180, 77.5); //6
    glEnd();
}

void lantai3() {

    glBegin(GL_POLYGON); //atas
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-57.5, 420, -57.5); //1
    glVertex3f(57.5, 420, -57.5); //2
    glVertex3f(57.5, 420, 57.5); //3
    glVertex3f(-57.5, 420, 57.5); //4

    glEnd();
    glBegin(GL_POLYGON); //atas
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-57.5, 350, -57.5); //8
    glVertex3f(57.5, 350, -57.5); //7
    glVertex3f(57.5, 350, 57.5); //6
    glVertex3f(-57.5, 350, 57.5); //5
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-57.5, 350, -57.5); //8
    glVertex3f(-57.5, 420, -57.5); //1
    glVertex3f(-57.5, 420, 57.5); //4
    glVertex3f(-57.5, 350, 57.5); //5
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-57.5, 350, -57.5); //8
    glVertex3f(-57.5, 420, -57.5); //1
    glVertex3f(57.5, 420, -57.5); //2
    glVertex3f(57.5, 350, -57.5); //7
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(57.5, 350, -57.5); //7
    glVertex3f(57.5, 420, -57.5); //2
    glVertex3f(57.5, 420, 57.5); //3
    glVertex3f(57.5, 350, 57.5); //6
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-57.5, 350, 57.5); //5
    glVertex3f(-57.5, 420, 57.5); //4
    glVertex3f(57.5, 420, 57.5); //3
    glVertex3f(57.5, 350, 57.5); //6
    glEnd();

    glBegin(GL_POLYGON); //atasa
    glColor3ub(237, 91, 23);
    glVertex3f(-87.5, 350, -87.5); //1
    glVertex3f(87.5, 350, -87.5); //2
    glVertex3f(87.5, 350, 87.5); //3
    glVertex3f(-87.5, 350, 87.5); //4
    glEnd();
    glBegin(GL_POLYGON); //atas
    glColor3ub(237, 91, 23);
    glVertex3f(-87.5, 355, -87.5); //8
    glVertex3f(87.5, 355, -87.5); //7
    glVertex3f(87.5, 355, 87.5); //6
    glVertex3f(-87.5, 355, 87.5); //5
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(237, 91, 23);
    glVertex3f(-87.5, 355, -87.5); //8
    glVertex3f(-87.5, 350, -87.5); //1
    glVertex3f(-87.5, 350, 87.5); //4
    glVertex3f(-87.5, 355, 87.5); //5
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(237, 91, 23);
    glVertex3f(-87.5, 355, -87.5); //8
    glVertex3f(-87.5, 350, -87.5); //1
    glVertex3f(87.5, 350, -87.5); //2
    glVertex3f(87.5, 355, -87.5); //7
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(237, 91, 23);
    glVertex3f(87.5, 355, -87.5); //7
    glVertex3f(87.5, 350, -87.5); //2
    glVertex3f(87.5, 350, 87.5); //3
    glVertex3f(87.5, 355, 87.5); //6
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(237, 91, 23);
    glVertex3f(-87.5, 355, 87.5); //5
    glVertex3f(-87.5, 350, 87.5); //4
    glVertex3f(87.5, 350, 87.5); //3
    glVertex3f(87.5, 355, 87.5); //6
    glEnd();

    glBegin(GL_POLYGON); //bawah
    glColor3f(0.26, 0.26, 0.26);
    glVertex3f(-67.5, 355.1, -67.5); //8
    glVertex3f(67.5, 355.1, -67.5); //7
    glVertex3f(67.5, 355.1, 67.5); //6
    glVertex3f(-67.5, 355.1, 67.5); //5
    glEnd();
}

void atap2() {
    glBegin(GL_POLYGON); //atas
    glColor3ub(36, 36, 34);  //atap
    glVertex3f(-72.5, 420, -72.5); //1
    glVertex3f(72.5, 420, -72.5); //2
    glVertex3f(72.5, 420, 72.5); //3
    glVertex3f(-72.5, 420, 72.5); //4
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(36, 36, 34);  //atap
    glVertex3f(-90, 404, -90); //5
    glVertex3f(90, 404, -90); //6
    glVertex3f(90, 404, 90); //7
    glVertex3f(-90, 404, 90); //8
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(36, 36, 34);  //atap
    glVertex3f(-110, 395, -110); //9
    glVertex3f(110, 395, -110); //10
    glVertex3f(110, 395, 110); //11
    glVertex3f(-110, 395, 110); //12
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(36, 36, 34);  //atap
    glVertex3f(-90, 404, -90); //8
    glVertex3f(-72.5, 420, -72.5); //1
    glVertex3f(-72.5, 420, 72.5); //4
    glVertex3f(-90, 404, 90); //5
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(36, 36, 34);  //atap
    glVertex3f(-90, 404, -90); //8
    glVertex3f(-72.5, 420, -72.5); //1
    glVertex3f(72.5, 420, -72.5); //2
    glVertex3f(90, 404, -90); //7
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(36, 36, 34);  //atap
    glVertex3f(90, 404, -90); //7
    glVertex3f(72.5, 420, -72.5); //2
    glVertex3f(72.5, 420, 72.5); //3
    glVertex3f(90, 404, 90); //6
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(36, 36, 34);  //atap
    glVertex3f(-90, 404, 90); //5
    glVertex3f(-72.5, 420, 72.5); //4
    glVertex3f(72.5, 420, 72.5); //3
    glVertex3f(90, 404, 90); //6
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(36, 36, 34);  //atap
    glVertex3f(-110, 395, -110); //8
    glVertex3f(-90, 404, -90); //1
    glVertex3f(-90, 404, 90); //4
    glVertex3f(-110, 395, 110); //5
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(36, 36, 34);  //atap
    glVertex3f(-110, 395, -110); //8
    glVertex3f(-90, 404, -90); //1
    glVertex3f(90, 404, -90); //2
    glVertex3f(110, 395, -110); //7
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(36, 36, 34);  //atap
    glVertex3f(110, 395, -110); //7
    glVertex3f(90, 404, -90); //2
    glVertex3f(90, 404, 90); //3
    glVertex3f(110, 395, 110); //6
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(36, 36, 34);  //atap
    glVertex3f(-110, 395, 110); //5
    glVertex3f(-90, 404, 90); //4
    glVertex3f(90, 404, 90); //3
    glVertex3f(110, 395, 110); //6
    glEnd();
}

void bangun_lantai4() {
    //(-62.5, -62.5, 430)

    glBegin(GL_POLYGON); //atas
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-62.5, 530, -62.5); //1
    glVertex3f(62.5, 530, -62.5); //2
    glVertex3f(62.5, 530, 62.5); //3
    glVertex3f(-62.5, 530, 62.5); //4
    glEnd();

    glBegin(GL_POLYGON); //bawah
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-62.5, 430, -62.5); //8
    glVertex3f(62.5, 430, -62.5); //7
    glVertex3f(62.5, 430, 62.5); //6
    glVertex3f(-62.5, 430, 62.5); //5
    glEnd();

    glBegin(GL_POLYGON); //sisi1
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-62.5, 430, -62.5); //8
    glVertex3f(-62.5, 530, -62.5); //1
    glVertex3f(62.5, 530, -62.5); //2
    glVertex3f(62.5, 430, -62.5); //7
    glEnd();

    glBegin(GL_POLYGON); //sisi2
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(62.5, 430, -62.5); //7
    glVertex3f(62.5, 530, -62.5); //2
    glVertex3f(62.5, 530, 62.5); //3
    glVertex3f(62.5, 430, 62.5); //6
    glEnd();

    glBegin(GL_POLYGON); //sisi3
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-62.5, 430, 62.5); //5
    glVertex3f(-62.5, 530, 62.5); //4
    glVertex3f(62.5, 530, 62.5); //3
    glVertex3f(62.5, 430, 62.5); //6
    glEnd();

    glBegin(GL_POLYGON); //sisi4s
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-62.5, 430, -62.5); //8
    glVertex3f(-62.5, 530, -62.5); //1
    glVertex3f(-62.5, 530, 62.5); //4
    glVertex3f(-62.5, 430, 62.5); //5
    glEnd();
}

void floor3() {
    //(-100, -100, 420)
    glBegin(GL_POLYGON); //atas
    glColor3ub(237, 91, 23);
    glVertex3f(-100, 430, -100); //1
    glVertex3f(100, 430, -100); //2
    glVertex3f(100, 430, 100); //3
    glVertex3f(-100, 430, 100); //4
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(237, 91, 23);
    glVertex3f(-100, 420, -100); //8
    glVertex3f(100, 420, -100); //7
    glVertex3f(100, 420, 100); //6
    glVertex3f(-100, 420, 100); //5
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(237, 91, 23);
    glVertex3f(-100, 420, -100); //8
    glVertex3f(-100, 430, -100); //1
    glVertex3f(-100, 430, 100); //4
    glVertex3f(-100, 420, 100); //5
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(237, 91, 23);
    glVertex3f(-100, 420, -100); //8
    glVertex3f(-100, 430, -100); //1
    glVertex3f(100, 430, -100); //2
    glVertex3f(100, 420, -100); //7
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(237, 91, 23);
    glVertex3f(100, 420, -100); //7
    glVertex3f(100, 430, -100); //2
    glVertex3f(100, 430, 100); //3
    glVertex3f(100, 420, 100); //6
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(237, 91, 23);
    glVertex3f(-100, 420, 100); //5
    glVertex3f(-100, 430, 100); //4
    glVertex3f(100, 430, 100); //3
    glVertex3f(100, 420, 100); //6
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3f(0.26, 0.26, 0.26);
    glVertex3f(-90, 430.1, -90); //8
    glVertex3f(90, 430.1, -90); //7
    glVertex3f(90, 430.1, 90); //6
    glVertex3f(-90, 430.1, 90); //5
    glEnd();
}

void atas_bangun4() {
    //(-70, 530,, -70)
    glBegin(GL_POLYGON); //atas
    glColor3ub(238, 124, 32);
    glVertex3f(-70, 530, -70); //1
    glVertex3f(70, 530, -70); //2
    glVertex3f(70, 530, 70); //3
    glVertex3f(-70, 530, 70); //4
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(238, 124, 32);
    glVertex3f(-70, 540, -70); //8
    glVertex3f(70, 540, -70); //7
    glVertex3f(70, 540, 70); //6
    glVertex3f(-70, 540, 70); //5
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(238, 124, 32);
    glVertex3f(-70, 540, -70); //8
    glVertex3f(-70, 530, -70); //1
    glVertex3f(-70, 530, 70); //4
    glVertex3f(-70, 540, 70); //5
    glEnd();
    glBegin(GL_POLYGON); //atas
    glColor3ub(238, 124, 32);
    glVertex3f(-70, 540, -70); //8
    glVertex3f(-70, 530, -70); //1
    glVertex3f(70, 530, -70); //2
    glVertex3f(70, 540, -70); //7
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(238, 124, 32);
    glVertex3f(70, 540, -70); //7
    glVertex3f(70, 530, -70); //2
    glVertex3f(70, 530, 70); //3
    glVertex3f(70, 540, 70); //6
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(238, 124, 32);
    glVertex3f(-70, 540, 70); //5
    glVertex3f(-70, 530, 70); //4
    glVertex3f(70, 530, 70); //3
    glVertex3f(70, 540, 70); //6
    glEnd();

    //(-60, 550,-90)
    glBegin(GL_POLYGON); //atas
    glColor3ub(237, 91, 23);
    glVertex3f(-70, 540, -70); //8
    glVertex3f(70, 540, -70); //7
    glVertex3f(60, 550, -90); //4
    glVertex3f(-60, 550, -90); //3
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(237, 91, 23);
    glVertex3f(70, 540, -70); //8
    glVertex3f(70, 540, 70); //8
    glVertex3f(90, 550, 60); //7
    glVertex3f(90, 550, -60); //7
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(237, 91, 23);
    glVertex3f(70, 540, 70); //5
    glVertex3f(-70, 540, 70); //
    glVertex3f(-60, 550, 90); //3
    glVertex3f(60, 550, 90); //4
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(237, 91, 23);
    glVertex3f(-70, 540, 70); //7
    glVertex3f(-70, 540, -70); //7
    glVertex3f(-90, 550, -60); //7
    glVertex3f(-90, 550, 60); //7
    glEnd();

    /*glVertex3f(-70, 540, -70); //7
      glVertex3f(-60, 550, -90); //3
      glVertex3f(-90, 560, -90); //7
      glVertex3f(-90, 550, -60); //7*/

    glBegin(GL_POLYGON); //atas
    glColor3ub(237, 91, 23);
    glVertex3f(-70, 540, -70); //7
    glVertex3f(-60, 550, -90); //3
    glVertex3f(-90, 560, -90); //7
    glVertex3f(-90, 550, -60); //7
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(237, 91, 23);
    glVertex3f(70, 540, -70); //7
    glVertex3f(60, 550, -90); //3
    glVertex3f(90, 560, -90); //7
    glVertex3f(90, 550, -60); //7
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(237, 91, 23);
    glVertex3f(70, 540, 70); //7
    glVertex3f(60, 550, 90); //3
    glVertex3f(90, 560, 90); //7
    glVertex3f(90, 550, 60); //7
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(237, 91, 23);
    glVertex3f(-70, 540, 70); //7
    glVertex3f(-60, 550, 90); //3
    glVertex3f(-90, 560, 90); //7
    glVertex3f(-90, 550, 60); //7
    glEnd();
}

void atap1() {


    glBegin(GL_POLYGON); //bawah
    glColor3ub(36, 36, 34);  //atap
    glVertex3f(-77.5, 350, -77.5); //8
    glVertex3f(77.5, 350, -77.5); //7
    glVertex3f(77.5, 350, 77.5); //6
    glVertex3f(-77.5, 350, 77.5); //5
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(36, 36, 34);  //atap
    glVertex3f(-90, 330, -90); //1
    glVertex3f(90, 330, -90); //2
    glVertex3f(90, 330, 90); //3
    glVertex3f(-90, 330, 90); //4

    glEnd();

    glBegin(GL_POLYGON); //bawah
    glColor3ub(36, 36, 34);  //atap
    glVertex3f(-110, 310, -110); //8
    glVertex3f(110, 310, -110); //7
    glVertex3f(110, 310, 110); //6
    glVertex3f(-110, 310, 110); //5

    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(36, 36, 34);  //atap
    glVertex3f(-130, 300, -130); //1
    glVertex3f(130, 300, -130); //2
    glVertex3f(130, 300, 130); //3
    glVertex3f(-130, 300, 130); //4

    glEnd();


    glBegin(GL_POLYGON); //atas
    glColor3ub(36, 36, 34);  //atap
    glVertex3f(-90, 330, -90); //8
    glVertex3f(-77.5, 350, -77.5); //1
    glVertex3f(-77.5, 350, 77.5); //4
    glVertex3f(-90, 330, 90); //5
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(36, 36, 34);  //atap
    glVertex3f(-90, 330, -90); //8
    glVertex3f(-77.5, 350, -77.5); //1
    glVertex3f(77.5, 350, -77.5); //2
    glVertex3f(90, 330, -90); //7

    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(36, 36, 34);  //atap
    glVertex3f(90, 330, -90); //7
    glVertex3f(77.5, 350, -77.5); //2
    glVertex3f(77.5, 350, 77.5); //3
    glVertex3f(90, 330, 90); //6

    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(36, 36, 34);  //atap
    glVertex3f(-90, 330, 90); //5
    glVertex3f(-77.5, 350, 77.5); //4
    glVertex3f(77.5, 350, 77.5); //3
    glVertex3f(90, 330, 90); //6
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(36, 36, 34);  //atap
    glVertex3f(-110, 310, -110); //8
    glVertex3f(-90, 330, -90); //1
    glVertex3f(-90, 330, 90); //4
    glVertex3f(-110, 310, 110); //5

    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(36, 36, 34);  //atap
    glVertex3f(-110, 310, -110); //8
    glVertex3f(-90, 330, -90); //1
    glVertex3f(90, 330, -90); //2
    glVertex3f(110, 310, -110); //7
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(36, 36, 34);  //atap
    glVertex3f(110, 310, -110); //7
    glVertex3f(90, 330, -90); //2
    glVertex3f(90, 330, 90); //3
    glVertex3f(110, 310, 110); //6

    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(36, 36, 34);  //atap
    glVertex3f(-110, 310, 110); //5
    glVertex3f(-90, 330, 90); //4
    glVertex3f(90, 330, 90); //3
    glVertex3f(110, 310, 110); //6
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(36, 36, 34);  //atap
    glVertex3f(-130, 300, -130); //8
    glVertex3f(-110, 310, -110); //1
    glVertex3f(-110, 310, 110); //4
    glVertex3f(-130, 300, 130); //5
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(36, 36, 34);  //atap
    glVertex3f(-130, 300, -130); //8
    glVertex3f(-110, 310, -110); //1
    glVertex3f(110, 310, -110); //2
    glVertex3f(130, 300, -130); //7
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(36, 36, 34);  //atap
    glVertex3f(130, 300, -130); //7
    glVertex3f(110, 310, -110); //2
    glVertex3f(110, 310, 110); //3
    glVertex3f(130, 300, 130); //6
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(36, 36, 34);  //atap
    glVertex3f(-130, 300, 130); //5
    glVertex3f(-110, 310, 110); //4
    glVertex3f(110, 310, 110); //3
    glVertex3f(130, 300, 130); //6
    glEnd();
}

void pilar() {
    // Pilar 1 
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(30, 25, -200); //1
    glVertex3f(30, 25, -190); //2
    glVertex3f(40, 25, -190); //3
    glVertex3f(40, 25, -200); //4

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(30, 65, -200); //8
    glVertex3f(30, 65, -190); //7
    glVertex3f(40, 65, -190); //6
    glVertex3f(40, 65, -200); //5

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(30, 65, -200); //8
    glVertex3f(30, 25, -200); //1
    glVertex3f(40, 25, -200); //4
    glVertex3f(40, 65, -200); //5

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(30, 65, -200); //8
    glVertex3f(30, 25, -200); //1
    glVertex3f(30, 25, -190); //2
    glVertex3f(30, 65, -190); //7

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(30, 65, -190); //7
    glVertex3f(30, 25, -190); //2
    glVertex3f(40, 25, -190); //3
    glVertex3f(40, 65, -190); //6

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);

    glVertex3f(40, 65, -200); //5
    glVertex3f(40, 25, -200); //4
    glVertex3f(40, 25, -190); //3
    glVertex3f(40, 65, -190); //6

    glEnd();
    // end of pilar 1

    // pilar 2 
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-30, 25, -200); //1
    glVertex3f(-30, 25, -190); //2
    glVertex3f(-40, 25, -190); //3
    glVertex3f(-40, 25, -200); //4

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-30, 65, -200); //8
    glVertex3f(-30, 65, -190); //7
    glVertex3f(-40, 65, -190); //6
    glVertex3f(-40, 65, -200); //5

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-30, 65, -200); //8
    glVertex3f(-30, 25, -200); //1
    glVertex3f(-40, 25, -200); //4
    glVertex3f(-40, 65, -200); //5

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-30, 65, -200); //8
    glVertex3f(-30, 25, -200); //1
    glVertex3f(-30, 25, -190); //2
    glVertex3f(-30, 65, -190); //7

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-30, 65, -190); //7
    glVertex3f(-30, 25, -190); //2
    glVertex3f(-40, 25, -190); //3
    glVertex3f(-40, 65, -190); //6

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);

    glVertex3f(-40, 65, -200); //5
    glVertex3f(-40, 25, -200); //4
    glVertex3f(-40, 25, -190); //3
    glVertex3f(-40, 65, -190); //6

    glEnd();
    // end of pilar 2 

    // pilar 3 
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(190, 25, -200); //1
    glVertex3f(190, 25, -190); //2
    glVertex3f(200, 25, -190); //3
    glVertex3f(200, 25, -200); //4

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(190, 65, -200); //8
    glVertex3f(190, 65, -190); //7
    glVertex3f(200, 65, -190); //6
    glVertex3f(200, 65, -200); //5

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(190, 65, -200); //8
    glVertex3f(190, 25, -200); //1
    glVertex3f(200, 25, -200); //4
    glVertex3f(200, 65, -200); //5

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(190, 65, -200); //8
    glVertex3f(190, 25, -200); //1
    glVertex3f(190, 25, -190); //2
    glVertex3f(190, 65, -190); //7

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(190, 65, -190); //7
    glVertex3f(190, 25, -190); //2
    glVertex3f(200, 25, -190); //3
    glVertex3f(200, 65, -190); //6

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);

    glVertex3f(200, 65, -200); //5
    glVertex3f(200, 25, -200); //4
    glVertex3f(200, 25, -190); //3
    glVertex3f(200, 65, -190); //6

    glEnd();
    // end of pilar 3

    // pilar 4 
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-190, 25, -200); //1
    glVertex3f(-190, 25, -190); //2
    glVertex3f(-200, 25, -190); //3
    glVertex3f(-200, 25, -200); //4

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-190, 65, -200); //8
    glVertex3f(-190, 65, -190); //7
    glVertex3f(-200, 65, -190); //6
    glVertex3f(-200, 65, -200); //5

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-190, 65, -200); //8
    glVertex3f(-190, 25, -200); //1
    glVertex3f(-200, 25, -200); //4
    glVertex3f(-200, 65, -200); //5

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-190, 65, -200); //8
    glVertex3f(-190, 25, -200); //1
    glVertex3f(-190, 25, -190); //2
    glVertex3f(-190, 65, -190); //7

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-190, 65, -190); //7
    glVertex3f(-190, 25, -190); //2
    glVertex3f(-200, 25, -190); //3
    glVertex3f(-200, 65, -190); //6

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);

    glVertex3f(-200, 65, -200); //5
    glVertex3f(-200, 25, -200); //4
    glVertex3f(-200, 25, -190); //3
    glVertex3f(-200, 65, -190); //6

    glEnd();

    // end of pilar 4

    // pilar 5
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-190, 25, 200); //1
    glVertex3f(-190, 25, 190); //2
    glVertex3f(-200, 25, 190); //3
    glVertex3f(-200, 25, 200); //4

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-190, 65, 200); //8
    glVertex3f(-190, 65, 190); //7
    glVertex3f(-200, 65, 190); //6
    glVertex3f(-200, 65, 200); //5

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-190, 65, 200); //8
    glVertex3f(-190, 25, 200); //1
    glVertex3f(-200, 25, 200); //4
    glVertex3f(-200, 65, 200); //5

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-190, 65, 200); //8
    glVertex3f(-190, 25, 200); //1
    glVertex3f(-190, 25, 190); //2
    glVertex3f(-190, 65, 190); //7

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-190, 65, 190); //7
    glVertex3f(-190, 25, 190); //2
    glVertex3f(-200, 25, 190); //3
    glVertex3f(-200, 65, 190); //6

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);

    glVertex3f(-200, 65, 200); //5
    glVertex3f(-200, 25, 200); //4
    glVertex3f(-200, 25, 190); //3
    glVertex3f(-200, 65, 190); //6

    glEnd();
    // end of pilar 5

    // pilar 6
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(190, 25, 200); //1
    glVertex3f(190, 25, 190); //2
    glVertex3f(200, 25, 190); //3
    glVertex3f(200, 25, 200); //4

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(190, 65, 200); //8
    glVertex3f(190, 65, 190); //7
    glVertex3f(200, 65, 190); //6
    glVertex3f(200, 65, 200); //5

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(190, 65, 200); //8
    glVertex3f(190, 25, 200); //1
    glVertex3f(200, 25, 200); //4
    glVertex3f(200, 65, 200); //5

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(190, 65, 200); //8
    glVertex3f(190, 25, 200); //1
    glVertex3f(190, 25, 190); //2
    glVertex3f(190, 65, 190); //7

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(190, 65, 190); //7
    glVertex3f(190, 25, 190); //2
    glVertex3f(200, 25, 190); //3
    glVertex3f(200, 65, 190); //6

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);

    glVertex3f(200, 65, 200); //5
    glVertex3f(200, 25, 200); //4
    glVertex3f(200, 25, 190); //3
    glVertex3f(200, 65, 190); //6

    glEnd();
}

void kotak_atap() {
    //(12.5, 12.5, 630)
    glBegin(GL_POLYGON); //atas
    glColor3ub(121, 107, 38);
    glVertex3f(-12.5, 650, -12.5); //1
    glVertex3f(12.5, 650, -12.5); //2
    glVertex3f(12.5, 650, 12.5); //3
    glVertex3f(-12.5, 650, 12.5); //4
    glEnd();
    glBegin(GL_POLYGON); //atas
    glColor3ub(121, 107, 38);
    glVertex3f(-12.5, 630, -12.5); //8
    glVertex3f(12.5, 630, -12.5); //7
    glVertex3f(12.5, 630, 12.5); //6
    glVertex3f(-12.5, 630, 12.5); //5
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(121, 107, 38);
    glVertex3f(-12.5, 630, -12.5); //8
    glVertex3f(-12.5, 650, -12.5); //1
    glVertex3f(-12.5, 650, 12.5); //4
    glVertex3f(-12.5, 630, 12.5); //5
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(121, 107, 38);
    glVertex3f(-12.5, 630, -12.5); //8
    glVertex3f(-12.5, 650, -12.5); //1
    glVertex3f(12.5, 650, -12.5); //2
    glVertex3f(12.5, 630, -12.5); //7
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(121, 107, 38);
    glVertex3f(12.5, 630, -12.5); //7
    glVertex3f(12.5, 650, -12.5); //2
    glVertex3f(12.5, 650, 12.5); //3
    glVertex3f(12.5, 630, 12.5); //6
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(121, 107, 38);
    glVertex3f(-12.5, 630, 12.5); //5
    glVertex3f(-12.5, 650, 12.5); //4
    glVertex3f(12.5, 650, 12.5); //3
    glVertex3f(12.5, 630, 12.5); //6

    glEnd();

    //(7.5, -7.5, 650)
    //2.5, -2.5, 750
    //0, 0, 770
    glBegin(GL_POLYGON); //atas
    glColor3ub(121, 107, 38);
    glVertex3f(-7.5, 650, -7.5); //1
    glVertex3f(7.55, 650, -7.5); //2
    glVertex3f(7.5, 650, 7.5); //3
    glVertex3f(-7.5, 650, 7.5); //4
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(121, 107, 38);
    glVertex3f(-2.5, 750, -2.5); //8
    glVertex3f(2.5, 750, -2.5); //7
    glVertex3f(2.5, 750, 2.5); //6
    glVertex3f(-2.5, 750, 2.5); //5
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(121, 107, 38);
    glVertex3f(-2.5, 750, -2.5); //8
    glVertex3f(-7.5, 650, -7.5); //1
    glVertex3f(-7.5, 650, 7.5); //4
    glVertex3f(-2.5, 750, 2.5); //5
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(121, 107, 38);
    glVertex3f(-2.5, 750, -2.5); //8
    glVertex3f(-7.5, 650, -7.5); //1
    glVertex3f(7.55, 650, -7.5); //2
    glVertex3f(2.5, 750, -2.5); //7
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(121, 107, 38);
    glVertex3f(2.5, 750, -2.5); //7
    glVertex3f(7.55, 650, -7.5); //2
    glVertex3f(7.5, 650, 7.5); //3
    glVertex3f(2.5, 750, 2.5); //6
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(121, 107, 38);
    glVertex3f(-2.5, 750, 2.5); //5
    glVertex3f(-7.5, 650, 7.5); //4
    glVertex3f(7.5, 650, 7.5); //3
    glVertex3f(2.5, 750, 2.5); //6
    glEnd();

    //(10, 10, 750)
    glBegin(GL_POLYGON); //atas
    glColor3ub(121, 107, 38);
    glVertex3f(-10, 750, -10); //1
    glVertex3f(10, 750, -10); //2
    glVertex3f(10, 750, 10); //3
    glVertex3f(-10, 750, 10); //4
    glEnd();

    glPushMatrix();
    glTranslatef(0, 760, 0);
    glColor3ub(121, 107, 38);
    glutSolidSphere(10, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1000, 1500, 0);
    glColor3f(1, 1, 1);
    glutSolidSphere(100.0, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1000, 1500, 0);
    glColor4f(1, 1, 1,0.5);
    glutSolidSphere(120.0, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1000, 1500, 0);
    glColor4f(1, 1, 1, 0.25);
    glutSolidSphere(140.0, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1000, 1500, 0);
    glColor4f(1, 1, 1, 0.1);
    glutSolidSphere(160.0, 30, 30);
    glPopMatrix();
}

void atap_ujung() {
    //(51.25, -51.25, 575)
    //(90, -60, 550)
    //(90, 60, 550)
    //(51.25, 51.25, 575)
    //(60, 90, 550)

    glBegin(GL_POLYGON); //atas
    glColor3ub(36, 36, 34);  //atap
    glVertex3f(-51.25, 575, -51.25); //8
    glVertex3f(51.25, 575, -51.25); //8
    glVertex3f(60, 550, -90); //4
    glVertex3f(-60, 550, -90); //3
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(36, 36, 34);  //atap
    glVertex3f(51.25, 575, -51.25); //8
    glVertex3f(51.25, 575, 51.25); //8
    glVertex3f(90, 550, 60); //7
    glVertex3f(90, 550, -60); //7
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(36, 36, 34);  //atap
    glVertex3f(51.25, 575, 51.25); //8
    glVertex3f(-51.25, 575, 51.25); //8
    glVertex3f(-60, 550, 90); //3
    glVertex3f(60, 550, 90); //4
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(36, 36, 34);  //atap
    glVertex3f(-51.25, 575, 51.25); //8
    glVertex3f(-51.25, 575, -51.25); //8
    glVertex3f(-90, 550, -60); //7
    glVertex3f(-90, 550, 60); //7
    glEnd();

    //(51.25, 51.25, 575)
    //(-31.25, 590,31.25)

    glBegin(GL_POLYGON); //atas
    glColor3ub(36, 36, 34);  //atap
    glVertex3f(-31.25, 590, -31.25); //8
    glVertex3f(31.25, 590, -31.25); //8
    glVertex3f(51.25, 575, -51.25); //8
    glVertex3f(-51.25, 575, -51.25); //8
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(36, 36, 34);  //atap
    glVertex3f(31.25, 590, -31.25); //8
    glVertex3f(31.25, 590, 31.25); //8
    glVertex3f(51.25, 575, 51.25); //8
    glVertex3f(51.25, 575, -51.25); //8
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(36, 36, 34);  //atap
    glVertex3f(31.25, 590, 31.25); //8
    glVertex3f(-31.25, 590, 31.25); //8
    glVertex3f(-51.25, 575, 51.25); //8
    glVertex3f(51.25, 575, 51.25); //8
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(36, 36, 34);  //atap
    glVertex3f(-31.25, 590, 31.25); //8
    glVertex3f(-31.25, 590, -31.25); //8
    glVertex3f(-51.25, 575, -51.25); //8
    glVertex3f(-51.25, 575, 51.25); //8
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(36, 36, 34);  //atap
    glVertex3f(-21.25, 605, -21.25); //8
    glVertex3f(21.25, 605, -21.25); //8

    glVertex3f(31.25, 590, -31.25); //8
    glVertex3f(-31.25, 590, -31.25); //8
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(36, 36, 34);  //atap
    glVertex3f(31.25, 590, -31.25); //8
    glVertex3f(31.25, 590, 31.25); //8
    glVertex3f(21.25, 605, 21.25); //8
    glVertex3f(21.25, 605, -21.25); //8

    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(36, 36, 34);  //atap
    glVertex3f(31.25, 590, 31.25); //8
    glVertex3f(-31.25, 590, 31.25); //8
    glVertex3f(-21.25, 605, 21.25); //8
    glVertex3f(21.25, 605, 21.25); //8

    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(36, 36, 34);  //atap
    glVertex3f(-31.25, 590, 31.25); //8
    glVertex3f(-31.25, 590, -31.25); //8
    glVertex3f(-21.25, 605, -21.25); //8
    glVertex3f(-21.25, 605, 21.25); //8

    glEnd();


    //(-12.5, -12.5, 630)
    glBegin(GL_POLYGON); //atas
    glColor3ub(36, 36, 34);  //atap
    glVertex3f(-21.25, 605, -21.25); //8
    glVertex3f(21.25, 605, -21.25); //8

    glVertex3f(12.5, 630, -12.5); //8
    glVertex3f(-12.5, 630, -12.5); //8
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(36, 36, 34);  //atap
    glVertex3f(12.5, 630, -12.5); //8
    glVertex3f(12.5, 630, 12.5); //8
    glVertex3f(21.25, 605, 21.25); //8
    glVertex3f(21.25, 605, -21.25); //8

    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(36, 36, 34);  //atap
    glVertex3f(12.5, 630, 12.5); //8
    glVertex3f(-12.5, 630, 12.5); //8
    glVertex3f(-21.25, 605, 21.25); //8
    glVertex3f(21.25, 605, 21.25); //8

    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(36, 36, 34);  //atap
    glVertex3f(-12.5, 630, 12.5); //8
    glVertex3f(-12.5, 630, -12.5); //8
    glVertex3f(-21.25, 605, -21.25); //8
    glVertex3f(-21.25, 605, 21.25); //8

    glEnd();

    //(-51.25, -51.25, 575)
    //(-90, -90, 560)
    //(-90, -60, 550)
    //(-60, -90, 550)
    glBegin(GL_POLYGON); //atas
    glColor3ub(36, 36, 34);  //atap
    glVertex3f(-51.25, 575, -51.25); //8
    glVertex3f(-90, 550, -60); //8
    glVertex3f(-90, 560, -90); //8
    glVertex3f(-60, 550, -90); //8

    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(36, 36, 34);  //atap
    glVertex3f(51.25, 575, -51.25); //8
    glVertex3f(90, 550, -60); //8
    glVertex3f(90, 560, -90); //8
    glVertex3f(60, 550, -90); //8

    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(36, 36, 34);  //atap
    glVertex3f(51.25, 575, 51.25); //8
    glVertex3f(90, 550, 60); //8
    glVertex3f(90, 560, 90); //8
    glVertex3f(60, 550, 90); //8

    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3ub(36, 36, 34);  //atap
    glVertex3f(-51.25, 575, 51.25); //8
    glVertex3f(-90, 550, 60); //8
    glVertex3f(-90, 560, 90); //8
    glVertex3f(-60, 550, 90); //8

    glEnd();
}

void tangga() {
    //-30, -270, 0
    //glColor3ub(237, 91, 23);
    //Tiang tangga 1
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-30, 0, -270); //1
    glVertex3f(-30, 0, -260); //2
    glVertex3f(-40, 0, -260); //3
    glVertex3f(-40, 0, -270); //4

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-30, 40, -270); //8
    glVertex3f(-30, 40, -260); //7
    glVertex3f(-40, 40, -260); //6
    glVertex3f(-40, 40, -270); //5

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-30, 40, -270); //8
    glVertex3f(-30, 0, -270); //1
    glVertex3f(-40, 0, -270); //4
    glVertex3f(-40, 40, -270); //5

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-30, 40, -270); //8
    glVertex3f(-30, 0, -270); //1
    glVertex3f(-30, 0, -260); //2
    glVertex3f(-30, 40, -260); //7

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-30, 40, -260); //7
    glVertex3f(-30, 0, -260); //2
    glVertex3f(-40, 0, -260); //3
    glVertex3f(-40, 40, -260); //6

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-40, 40, -270); //5
    glVertex3f(-40, 0, -270); //4
    glVertex3f(-40, 0, -260); //3
    glVertex3f(-40, 40, -260); //6

    glEnd();

    //tiang tangga 2
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(30, 0, -270); //1
    glVertex3f(30, 0, -260); //2
    glVertex3f(40, 0, -260); //3
    glVertex3f(40, 0, -270); //4

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(30, 40, -270); //1
    glVertex3f(30, 40, -260); //2
    glVertex3f(40, 40, -260); //3
    glVertex3f(40, 40, -270); //4

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(30, 40, -270); //8
    glVertex3f(30, 0, -270); //1
    glVertex3f(40, 0, -270); //4
    glVertex3f(40, 40, -270); //5

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(30, 40, -270); //8
    glVertex3f(30, 0, -270); //1
    glVertex3f(30, 0, -260); //2
    glVertex3f(30, 40, -260); //7

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(30, 40, -260); //7
    glVertex3f(30, 0, -260); //2
    glVertex3f(40, 0, -260); //3
    glVertex3f(40, 40, -260); //6

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(40, 40, -270); //5
    glVertex3f(40, 0, -270); //4
    glVertex3f(40, 0, -260); //3
    glVertex3f(40, 40, -260); //6

    glEnd();

    //tiang sambung
    //32.5, -260, 37.5
    //-32.5, -200, 62.5
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(37.5, 32.5, -260); //1
    glVertex3f(32.5, 32.5, -260); //2
    glVertex3f(32.5, 37.5, -260); //4
    glVertex3f(37.5, 37.5, -260); //3
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(37.5, 57.5, -200); //8
    glVertex3f(32.5, 57.5, -200); //7
    glVertex3f(32.5, 62.5, -200); //6
    glVertex3f(37.5, 62.5, -200); //5
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(37.5, 57.5, -200); //8
    glVertex3f(37.5, 32.5, -260); //1
    glVertex3f(32.5, 37.5, -260); //4
    glVertex3f(37.5, 62.5, -200); //5

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(37.5, 57.5, -200); //8
    glVertex3f(37.5, 32.5, -260); //1
    glVertex3f(32.5, 32.5, -260); //2
    glVertex3f(32.5, 57.5, -200); //7

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(32.5, 57.5, -200); //7
    glVertex3f(32.5, 32.5, -260); //2
    glVertex3f(37.5, 37.5, -260); //3
    glVertex3f(32.5, 62.5, -200); //6

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(37.5, 62.5, -200); //5
    glVertex3f(32.5, 37.5, -260); //4
    glVertex3f(37.5, 37.5, -260); //3
    glVertex3f(32.5, 62.5, -200); //6

    glEnd();

    //tiang sambung 2
//32.5, -260, 37.5
//-32.5, -200, 62.5
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-37.5, 32.5, -260); //1
    glVertex3f(-32.5, 32.5, -260); //2
    glVertex3f(-32.5, 37.5, -260); //4
    glVertex3f(-37.5, 37.5, -260); //3
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-37.5, 57.5, -200); //8
    glVertex3f(-32.5, 57.5, -200); //7
    glVertex3f(-32.5, 62.5, -200); //6
    glVertex3f(-37.5, 62.5, -200); //5
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-37.5, 57.5, -200); //8
    glVertex3f(-37.5, 32.5, -260); //1
    glVertex3f(-32.5, 37.5, -260); //4
    glVertex3f(-37.5, 62.5, -200); //5

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-37.5, 57.5, -200); //8
    glVertex3f(-37.5, 32.5, -260); //1
    glVertex3f(-32.5, 32.5, -260); //2
    glVertex3f(-32.5, 57.5, -200); //7

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-32.5, 57.5, -200); //7
    glVertex3f(-32.5, 32.5, -260); //2
    glVertex3f(-37.5, 37.5, -260); //3
    glVertex3f(-32.5, 62.5, -200); //6

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-37.5, 62.5, -200); //5
    glVertex3f(-32.5, 37.5, -260); //4
    glVertex3f(-37.5, 37.5, -260); //3
    glVertex3f(-32.5, 62.5, -200); //6

    glEnd();

    //TANGGA 1
    //40, -260, 0
    glBegin(GL_POLYGON); //atas
    glColor3f(0.16, 0.16, 0.16);
    glVertex3f(-40, 0, -260); //1
    glVertex3f(40, 0, -260); //2
    glVertex3f(40, 0, -240); //3
    glVertex3f(-40, 0, -240); //4
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3f(0.16, 0.16, 0.16);
    glVertex3f(-40, 8.33, -260); //8
    glVertex3f(40, 8.33, -260); //7
    glVertex3f(40, 8.33, -240); //6
    glVertex3f(-40, 8.33, -240); //5
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3f(0.36, 0.36, 0.36);
    glVertex3f(-40, 8.33, -260); //8
    glVertex3f(-40, 0, -260); //1
    glVertex3f(-40, 0, -240); //4
    glVertex3f(-40, 8.33, -240); //5
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3f(0.36, 0.36, 0.36);
    glVertex3f(-40, 8.33, -260); //8
    glVertex3f(-40, 0, -260); //1
    glVertex3f(40, 0, -260); //2
    glVertex3f(40, 8.33, -260); //7
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3f(0.36, 0.36, 0.36);
    glVertex3f(40, 8.33, -260); //7
    glVertex3f(40, 0, -260); //2
    glVertex3f(40, 0, -240); //3
    glVertex3f(40, 8.33, -240); //6
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3f(0.36, 0.36, 0.36);
    glVertex3f(-40, 8.33, -240); //5
    glVertex3f(-40, 0, -240); //4
    glVertex3f(40, 0, -240); //3
    glVertex3f(40, 8.33, -240); //6
    glEnd();

    //TANGGA2
    //40, -240, 0
    //40, -220, 0
    glBegin(GL_POLYGON); //atas
    glColor3f(0.16, 0.16, 0.16);
    glVertex3f(-40, 0, -240); //1
    glVertex3f(40, 0, -240); //2
    glVertex3f(40, 0, -220); //3
    glVertex3f(-40, 0, -220); //4
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3f(0.16, 0.16, 0.16);
    glVertex3f(-40, 16.67, -240); //8
    glVertex3f(40, 16.67, -240); //7
    glVertex3f(40, 16.67, -220); //6
    glVertex3f(-40, 16.67, -220); //5
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3f(0.36, 0.36, 0.36);
    glVertex3f(-40, 16.67, -240); //8
    glVertex3f(-40, 0, -240); //1
    glVertex3f(-40, 0, -220); //4
    glVertex3f(-40, 16.67, -220); //5
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3f(0.36, 0.36, 0.36);
    glVertex3f(-40, 16.67, -240); //8
    glVertex3f(-40, 0, -240); //1
    glVertex3f(40, 0, -240); //2
    glVertex3f(40, 16.67, -240); //7
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3f(0.36, 0.36, 0.36);
    glVertex3f(40, 16.67, -240); //7
    glVertex3f(40, 0, -240); //2
    glVertex3f(40, 0, -220); //3
    glVertex3f(40, 16.67, -220); //6
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3f(0.36, 0.36, 0.36);
    glVertex3f(-40, 16.67, -220); //5
    glVertex3f(-40, 0, -220); //4
    glVertex3f(40, 0, -220); //3
    glVertex3f(40, 16.67, -220); //6
    glEnd();

    //TANGGA3
    //40, -220, 0
    //40, -200, 0

    glBegin(GL_POLYGON); //atas
    glColor3f(0.16, 0.16, 0.16);
    glVertex3f(-40, 0, -220); //1
    glVertex3f(40, 0, -220); //2
    glVertex3f(40, 0, -200); //3
    glVertex3f(-40, 0, -200); //4
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3f(0.16, 0.16, 0.16);
    glVertex3f(-40, 25, -220); //8
    glVertex3f(40, 25, -220); //7
    glVertex3f(40, 25, -200); //6
    glVertex3f(-40, 25, -200); //5
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3f(0.36, 0.36, 0.36);
    glVertex3f(-40, 25, -220); //8
    glVertex3f(-40, 0, -220); //1
    glVertex3f(-40, 0, -200); //4
    glVertex3f(-40, 25, -200); //5
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3f(0.36, 0.36, 0.36);
    glVertex3f(-40, 25, -220); //8
    glVertex3f(-40, 0, -220); //1
    glVertex3f(40, 0, -220); //2
    glVertex3f(40, 25, -220); //7
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3f(0.36, 0.36, 0.36);
    glVertex3f(40, 25, -220); //7
    glVertex3f(40, 0, -220); //2
    glVertex3f(40, 0, -200); //3
    glVertex3f(40, 25, -200); //6
    glEnd();

    glBegin(GL_POLYGON); //atas
    glColor3f(0.36, 0.36, 0.36);
    glVertex3f(-40, 0, -200); //4
    glVertex3f(-40, 25, -200); //5
    glVertex3f(40, 0, -200); //3
    glVertex3f(40, 25, -200); //6
    glEnd();
}

void pagar1() {
    //1
    //glColor3ub(237, 91, 23);
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-190., 57.5, -192.5); //1
    glVertex3f(-190, 62.5, -192.5); //2
    glVertex3f(-190, 62.5, -197.5); //3
    glVertex3f(-190, 57.5, -197.5); //4
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-40., 57.5, -192.5); //8
    glVertex3f(-40, 62.5, -192.5); //7
    glVertex3f(-40, 62.5, -197.5); //6
    glVertex3f(-40, 57.5, -197.5); //5
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-40., 57.5, -192.5); //8
    glVertex3f(-190., 57.5, -192.5); //1
    glVertex3f(-190, 57.5, -197.5); //4
    glVertex3f(-40, 57.5, -197.5); //5
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-40., 57.5, -192.5); //8
    glVertex3f(-190., 57.5, -192.5); //1
    glVertex3f(-190, 62.5, -192.5); //2
    glVertex3f(-40, 62.5, -192.5); //7
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-40, 62.5, -192.5); //7
    glVertex3f(-190, 62.5, -192.5); //2
    glVertex3f(-190, 62.5, -197.5); //3
    glVertex3f(-40, 62.5, -197.5); //6
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-40, 57.5, -197.5); //5
    glVertex3f(-190, 57.5, -197.5); //4
    glVertex3f(-190, 62.5, -197.5); //3
    glVertex3f(-40, 62.5, -197.5); //6
    glEnd();


    // end of 1 

    // 2 
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-192.5, 57.5, -190); //1
    glVertex3f(-192.5, 62.5, -190); //2
    glVertex3f(-197.5, 62.5, -190); //3
    glVertex3f(-197.5, 57.5, -190); //4
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-197.5, 57.5, 190); //5
    glVertex3f(-197.5, 62.5, 190); //6
    glVertex3f(-192.5, 62.5, 190); //7
    glVertex3f(-192.5, 57.5, 190); //8
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-192.5, 57.5, 190); //8
    glVertex3f(-192.5, 57.5, -190); //1
    glVertex3f(-192.5, 62.5, -190); //2
    glVertex3f(-192.5, 62.5, 190); //7
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-197.5, 57.5, 190); //5
    glVertex3f(-197.5, 62.5, 190); //6
    glVertex3f(-197.5, 62.5, -190); //3
    glVertex3f(-197.5, 57.5, -190); //4
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-192.5, 57.5, 190); //8
    glVertex3f(-192.5, 57.5, -190); //1
    glVertex3f(-197.5, 57.5, -190); //4
    glVertex3f(-197.5, 57.5, 190); //5
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-192.5, 62.5, -190); //2
    glVertex3f(-197.5, 62.5, -190); //3
    glVertex3f(-197.5, 62.5, 190); //6
    glVertex3f(-192.5, 62.5, 190); //7
    glEnd();

    // end of  2

    // 3 
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-190, 57.5, 192.5); //1
    glVertex3f(-190, 62.5, 192.5); //2
    glVertex3f(-190, 62.5, 197.5); //3
    glVertex3f(-190, 57.5, 197.5); //4
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(190, 57.5, 197.5); //8
    glVertex3f(190, 62.5, 197.5); //7
    glVertex3f(190, 62.5, 192.5); //6
    glVertex3f(190, 57.5, 192.5); //5
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-190, 57.5, 192.5); //1
    glVertex3f(-190, 62.5, 192.5); //2
    glVertex3f(190, 62.5, 192.5); //6
    glVertex3f(190, 57.5, 192.5); //5
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-190, 62.5, 197.5); //3
    glVertex3f(-190, 57.5, 197.5); //4
    glVertex3f(190, 57.5, 197.5); //8
    glVertex3f(190, 62.5, 197.5); //7
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-190, 62.5, 192.5); //2
    glVertex3f(-190, 62.5, 197.5); //3
    glVertex3f(190, 62.5, 197.5); //7
    glVertex3f(190, 62.5, 192.5); //6

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(190, 57.5, 197.5); //8
    glVertex3f(-190, 57.5, 192.5); //1
    glVertex3f(-190, 57.5, 197.5); //4
    glVertex3f(190, 57.5, 192.5); //5
    glEnd();


    // end of 3

    // 4 
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(192.5, 57.5, 190); //1
    glVertex3f(192.5, 62.5, 190); //2
    glVertex3f(197.5, 62.5, 190); //3
    glVertex3f(197.5, 57.5, 190); //4
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(197.5, 57.5, -190); //8
    glVertex3f(197.5, 62.5, -190); //7
    glVertex3f(192.5, 62.5, -190); //6
    glVertex3f(192.5, 57.5, -190); //5
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(192.5, 57.5, 190); //1
    glVertex3f(192.5, 62.5, 190); //2
    glVertex3f(192.5, 62.5, -190); //6
    glVertex3f(192.5, 57.5, -190); //5
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(197.5, 62.5, 190); //3
    glVertex3f(197.5, 57.5, 190); //4
    glVertex3f(197.5, 57.5, -190); //8
    glVertex3f(197.5, 62.5, -190); //7
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(192.5, 57.5, 190); //1
    glVertex3f(197.5, 57.5, 190); //4
    glVertex3f(192.5, 57.5, -190); //5
    glVertex3f(197.5, 57.5, -190); //8
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(192.5, 62.5, 190); //2
    glVertex3f(197.5, 62.5, 190); //3
    glVertex3f(197.5, 62.5, -190); //7
    glVertex3f(192.5, 62.5, -190); //6
    glEnd();
    //end of 4

    // 5
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(40, 57.5, -197.5); //1
    glVertex3f(40, 62.5, -197.5); //2
    glVertex3f(40, 62.5, -192.5); //3
    glVertex3f(40, 57.5, -192.5); //4
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(190, 57.5, -192.5); //8
    glVertex3f(190, 62.5, -192.5); //7
    glVertex3f(190, 62.5, -197.5); //6
    glVertex3f(190, 57.5, -197.5); //5
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(40, 57.5, -197.5); //1
    glVertex3f(40, 62.5, -197.5); //2
    glVertex3f(190, 62.5, -197.5); //6
    glVertex3f(190, 57.5, -197.5); //5
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(40, 62.5, -192.5); //3
    glVertex3f(40, 57.5, -192.5); //4
    glVertex3f(190, 57.5, -192.5); //8
    glVertex3f(190, 62.5, -192.5); //7
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(40, 62.5, -197.5); //2
    glVertex3f(40, 62.5, -192.5); //3
    glVertex3f(190, 62.5, -192.5); //7
    glVertex3f(190, 62.5, -197.5); //6
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(190, 57.5, -192.5); //8
    glVertex3f(40, 57.5, -197.5); //1
    glVertex3f(40, 57.5, -192.5); //4
    glVertex3f(190, 57.5, -197.5); //5
    glEnd();


}

void pagar_lantai2() {
    //glColor3ub(237, 91, 23);
    //Pilar 1

    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(-130, 180, -130); //1
    glVertex3f(-130, 180, -120); //2
    glVertex3f(-130, 220, -120); //3
    glVertex3f(-130, 220, -130); //4
    glEnd();

    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(-130, 180, -120); //1
    glVertex3f(-120, 180, -120); //2
    glVertex3f(-120, 220, -120); //3
    glVertex3f(-130, 220, -120); //4
    glEnd();

    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(-120, 180, -120); //1
    glVertex3f(-120, 180, -130); //2
    glVertex3f(-120, 220, -130); //3
    glVertex3f(-120, 220, -120); //4
    glEnd();

    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(-130, 220, -130); //1
    glVertex3f(-130, 220, -120); //2
    glVertex3f(-120, 220, -120); //3
    glVertex3f(-120, 220, -130); //4
    glEnd();

    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(-120, 180, -130); //1
    glVertex3f(-130, 180, -130); //2
    glVertex3f(-130, 180, -120); //3
    glVertex3f(-120, 180, -120); //4
    glEnd();


    //pilar 2

    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(130, 180, -130); //1
    glVertex3f(130, 220, -130); //2
    glVertex3f(130, 220, -120); //3
    glVertex3f(130, 180, -120); //4
    glEnd();

    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(130, 180, -120); //1
    glVertex3f(130, 220, -120); //2
    glVertex3f(120, 220, -120); //3
    glVertex3f(120, 180, -120); //4
    glEnd();

    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(120, 180, -120); //1
    glVertex3f(120, 220, -120); //2
    glVertex3f(120, 220, -130); //3
    glVertex3f(120, 180, -130); //4
    glEnd();

    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(120, 180, -130); //1
    glVertex3f(120, 220, -130); //2
    glVertex3f(130, 220, -130); //3
    glVertex3f(130, 180, -130); //4
    glEnd();

    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(130, 180, -120); //1
    glVertex3f(130, 180, -130); //2
    glVertex3f(120, 180, -130); //3
    glVertex3f(120, 180, -120); //4
    glEnd();

    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(130, 220, -120); //1
    glVertex3f(120, 220, -120); //2
    glVertex3f(120, 220, -130); //3
    glVertex3f(130, 220, -130); //4
    glEnd();

    //pilar3
    glPushMatrix();
    glTranslatef(0, 0, 250);
    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(130, 180, -130); //1
    glVertex3f(130, 220, -130); //2
    glVertex3f(130, 220, -120); //3
    glVertex3f(130, 180, -120); //4
    glEnd();

    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(130, 180, -120); //1
    glVertex3f(130, 220, -120); //2
    glVertex3f(120, 220, -120); //3
    glVertex3f(120, 180, -120); //4
    glEnd();

    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(120, 180, -120); //1
    glVertex3f(120, 220, -120); //2
    glVertex3f(120, 220, -130); //3
    glVertex3f(120, 180, -130); //4
    glEnd();

    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(120, 180, -130); //1
    glVertex3f(120, 220, -130); //2
    glVertex3f(130, 220, -130); //3
    glVertex3f(130, 180, -130); //4
    glEnd();

    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(130, 180, -120); //1
    glVertex3f(130, 180, -130); //2
    glVertex3f(120, 180, -130); //3
    glVertex3f(120, 180, -120); //4
    glEnd();

    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(130, 220, -120); //1
    glVertex3f(120, 220, -120); //2
    glVertex3f(120, 220, -130); //3
    glVertex3f(130, 220, -130); //4
    glEnd();
    glPopMatrix();

    //pilar 4

    glPushMatrix();
    glTranslatef(0, 0, 250);

    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(-130, 180, -130); //1
    glVertex3f(-130, 180, -120); //2
    glVertex3f(-130, 220, -120); //3
    glVertex3f(-130, 220, -130); //4
    glEnd();

    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(-130, 180, -120); //1
    glVertex3f(-120, 180, -120); //2
    glVertex3f(-120, 220, -120); //3
    glVertex3f(-130, 220, -120); //4
    glEnd();

    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(-120, 180, -120); //1
    glVertex3f(-120, 180, -130); //2
    glVertex3f(-120, 220, -130); //3
    glVertex3f(-120, 220, -120); //4
    glEnd();

    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(-130, 220, -130); //1
    glVertex3f(-130, 220, -120); //2
    glVertex3f(-120, 220, -120); //3
    glVertex3f(-120, 220, -130); //4
    glEnd();

    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(-120, 180, -130); //1
    glVertex3f(-130, 180, -130); //2
    glVertex3f(-130, 180, -120); //3
    glVertex3f(-120, 180, -120); //4
    glEnd();
    glPopMatrix();

    //garis 1
    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(-120, 212.5, -127.5); //1
    glVertex3f(-120, 217.5, -127.5); //2
    glVertex3f(-120, 217.5, -122.5); //3
    glVertex3f(-120, 212.5, -122.5); //4
    glEnd();

    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(120, 212.5, -122.5); //8
    glVertex3f(120, 217.5, -122.5); //7
    glVertex3f(120, 217.5, -127.5); //6
    glVertex3f(120, 212.5, -127.5); //5
    glEnd();

    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(-120, 212.5, -127.5); //1
    glVertex3f(-120, 212.5, -122.5); //4
    glVertex3f(120, 212.5, -122.5); //8
    glVertex3f(120, 212.5, -127.5); //5
    glEnd();

    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(-120, 217.5, -127.5); //2
    glVertex3f(-120, 217.5, -122.5); //3
    glVertex3f(120, 217.5, -122.5); //7
    glVertex3f(120, 217.5, -127.5); //6
    glEnd();

    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(120, 212.5, -122.5); //8
    glVertex3f(-120, 212.5, -127.5); //1
    glVertex3f(-120, 217.5, -127.5); //2
    glVertex3f(120, 217.5, -122.5); //7
    glEnd();

    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(-120, 217.5, -122.5); //3
    glVertex3f(-120, 212.5, -122.5); //4
    glVertex3f(120, 217.5, -127.5); //6
    glVertex3f(120, 212.5, -127.5); //5
    glEnd();

    //garis2
    glPushMatrix();
    glTranslatef(0, 0, 250);
    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(-120, 212.5, -127.5); //1
    glVertex3f(-120, 217.5, -127.5); //2
    glVertex3f(-120, 217.5, -122.5); //3
    glVertex3f(-120, 212.5, -122.5); //4
    glEnd();

    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(120, 212.5, -122.5); //8
    glVertex3f(120, 217.5, -122.5); //7
    glVertex3f(120, 217.5, -127.5); //6
    glVertex3f(120, 212.5, -127.5); //5
    glEnd();

    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(-120, 212.5, -127.5); //1
    glVertex3f(-120, 212.5, -122.5); //4
    glVertex3f(120, 212.5, -122.5); //8
    glVertex3f(120, 212.5, -127.5); //5
    glEnd();

    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(-120, 217.5, -127.5); //2
    glVertex3f(-120, 217.5, -122.5); //3
    glVertex3f(120, 217.5, -122.5); //7
    glVertex3f(120, 217.5, -127.5); //6
    glEnd();

    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(120, 212.5, -122.5); //8
    glVertex3f(-120, 212.5, -127.5); //1
    glVertex3f(-120, 217.5, -127.5); //2
    glVertex3f(120, 217.5, -122.5); //7
    glEnd();

    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(-120, 217.5, -122.5); //3
    glVertex3f(-120, 212.5, -122.5); //4
    glVertex3f(120, 217.5, -127.5); //6
    glVertex3f(120, 212.5, -127.5); //5
    glEnd();
    glPopMatrix();

    //garis 3
    glPushMatrix();
    glRotatef(90, 0, 100, 0);
    glTranslatef(0, 0, 250);
    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(-120, 212.5, -127.5); //1
    glVertex3f(-120, 217.5, -127.5); //2
    glVertex3f(-120, 217.5, -122.5); //3
    glVertex3f(-120, 212.5, -122.5); //4
    glEnd();

    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(120, 212.5, -122.5); //8
    glVertex3f(120, 217.5, -122.5); //7
    glVertex3f(120, 217.5, -127.5); //6
    glVertex3f(120, 212.5, -127.5); //5
    glEnd();

    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(-120, 212.5, -127.5); //1
    glVertex3f(-120, 212.5, -122.5); //4
    glVertex3f(120, 212.5, -122.5); //8
    glVertex3f(120, 212.5, -127.5); //5
    glEnd();

    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(-120, 217.5, -127.5); //2
    glVertex3f(-120, 217.5, -122.5); //3
    glVertex3f(120, 217.5, -122.5); //7
    glVertex3f(120, 217.5, -127.5); //6
    glEnd();

    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(120, 212.5, -122.5); //8
    glVertex3f(-120, 212.5, -127.5); //1
    glVertex3f(-120, 217.5, -127.5); //2
    glVertex3f(120, 217.5, -122.5); //7
    glEnd();

    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(-120, 217.5, -122.5); //3
    glVertex3f(-120, 212.5, -122.5); //4
    glVertex3f(120, 217.5, -127.5); //6
    glVertex3f(120, 212.5, -127.5); //5
    glEnd();
    glPopMatrix();

    //garis 4
    glPushMatrix();
    glTranslatef(0, 0, 250);
    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(-120, 212.5, -127.5); //1
    glVertex3f(-120, 217.5, -127.5); //2
    glVertex3f(-120, 217.5, -122.5); //3
    glVertex3f(-120, 212.5, -122.5); //4
    glEnd();

    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(120, 212.5, -122.5); //8
    glVertex3f(120, 217.5, -122.5); //7
    glVertex3f(120, 217.5, -127.5); //6
    glVertex3f(120, 212.5, -127.5); //5
    glEnd();

    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(-120, 212.5, -127.5); //1
    glVertex3f(-120, 212.5, -122.5); //4
    glVertex3f(120, 212.5, -122.5); //8
    glVertex3f(120, 212.5, -127.5); //5
    glEnd();

    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(-120, 217.5, -127.5); //2
    glVertex3f(-120, 217.5, -122.5); //3
    glVertex3f(120, 217.5, -122.5); //7
    glVertex3f(120, 217.5, -127.5); //6
    glEnd();

    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(120, 212.5, -122.5); //8
    glVertex3f(-120, 212.5, -127.5); //1
    glVertex3f(-120, 217.5, -127.5); //2
    glVertex3f(120, 217.5, -122.5); //7
    glEnd();

    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(-120, 217.5, -122.5); //3
    glVertex3f(-120, 212.5, -122.5); //4
    glVertex3f(120, 217.5, -127.5); //6
    glVertex3f(120, 212.5, -127.5); //5
    glEnd();
    glPopMatrix();

    //garis 3
    glPushMatrix();
    glRotatef(90, 0, 100, 0);
    glTranslatef(0, 0, 0);
    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(-120, 212.5, -127.5); //1
    glVertex3f(-120, 217.5, -127.5); //2
    glVertex3f(-120, 217.5, -122.5); //3
    glVertex3f(-120, 212.5, -122.5); //4
    glEnd();

    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(120, 212.5, -122.5); //8
    glVertex3f(120, 217.5, -122.5); //7
    glVertex3f(120, 217.5, -127.5); //6
    glVertex3f(120, 212.5, -127.5); //5
    glEnd();

    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(-120, 212.5, -127.5); //1
    glVertex3f(-120, 212.5, -122.5); //4
    glVertex3f(120, 212.5, -122.5); //8
    glVertex3f(120, 212.5, -127.5); //5
    glEnd();

    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(-120, 217.5, -127.5); //2
    glVertex3f(-120, 217.5, -122.5); //3
    glVertex3f(120, 217.5, -122.5); //7
    glVertex3f(120, 217.5, -127.5); //6
    glEnd();

    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(120, 212.5, -122.5); //8
    glVertex3f(-120, 212.5, -127.5); //1
    glVertex3f(-120, 217.5, -127.5); //2
    glVertex3f(120, 217.5, -122.5); //7
    glEnd();

    glBegin(GL_POLYGON); //depan
    glColor3ub(237, 91, 23);
    glVertex3f(-120, 217.5, -122.5); //3
    glVertex3f(-120, 212.5, -122.5); //4
    glVertex3f(120, 217.5, -127.5); //6
    glVertex3f(120, 212.5, -127.5); //5
    glEnd();
    glPopMatrix();

}

void pagar_lantai3() {

    //Pilar 1
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-90, 470, 100);
    glVertex3f(-100, 470, 100);
    glVertex3f(-100, 470, 90);
    glVertex3f(-90, 470, 90);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-100, 430, 100);
    glVertex3f(-100, 470, 100);
    glVertex3f(-100, 470, 90);
    glVertex3f(-100, 430, 90);
    glEnd();

    glPushMatrix();
    glTranslatef(10, 0, 0);
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-100, 430, 100);
    glVertex3f(-100, 470, 100);
    glVertex3f(-100, 470, 90);
    glVertex3f(-100, 430, 90);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-190, 0, 0);
    glRotatef(90, 0, 10, 0);
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-100, 430, 100);
    glVertex3f(-100, 470, 100);
    glVertex3f(-100, 470, 90);
    glVertex3f(-100, 430, 90);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-190, 0, -10);
    glRotatef(90, 0, 10, 0);
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-100, 430, 100);
    glVertex3f(-100, 470, 100);
    glVertex3f(-100, 470, 90);
    glVertex3f(-100, 430, 90);
    glEnd();
    glPopMatrix();

    //Pilar2
    glPushMatrix();
    glTranslatef(190, 0, 0);

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-90, 470, 100);
    glVertex3f(-100, 470, 100);
    glVertex3f(-100, 470, 90);
    glVertex3f(-90, 470, 90);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-100, 430, 100);
    glVertex3f(-100, 470, 100);
    glVertex3f(-100, 470, 90);
    glVertex3f(-100, 430, 90);
    glEnd();

    glPushMatrix();
    glTranslatef(10, 0, 0);
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-100, 430, 100);
    glVertex3f(-100, 470, 100);
    glVertex3f(-100, 470, 90);
    glVertex3f(-100, 430, 90);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-190, 0, 0);
    glRotatef(90, 0, 10, 0);
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-100, 430, 100);
    glVertex3f(-100, 470, 100);
    glVertex3f(-100, 470, 90);
    glVertex3f(-100, 430, 90);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-190, 0, -10);
    glRotatef(90, 0, 10, 0);
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-100, 430, 100);
    glVertex3f(-100, 470, 100);
    glVertex3f(-100, 470, 90);
    glVertex3f(-100, 430, 90);
    glEnd();
    glPopMatrix();

    glPopMatrix();

    //Pilar3
    glPushMatrix();
    glTranslatef(190, 0, -190);

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-90, 470, 100);
    glVertex3f(-100, 470, 100);
    glVertex3f(-100, 470, 90);
    glVertex3f(-90, 470, 90);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-100, 430, 100);
    glVertex3f(-100, 470, 100);
    glVertex3f(-100, 470, 90);
    glVertex3f(-100, 430, 90);
    glEnd();

    glPushMatrix();
    glTranslatef(10, 0, 0);
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-100, 430, 100);
    glVertex3f(-100, 470, 100);
    glVertex3f(-100, 470, 90);
    glVertex3f(-100, 430, 90);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-190, 0, 0);
    glRotatef(90, 0, 10, 0);
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-100, 430, 100);
    glVertex3f(-100, 470, 100);
    glVertex3f(-100, 470, 90);
    glVertex3f(-100, 430, 90);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-190, 0, -10);
    glRotatef(90, 0, 10, 0);
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-100, 430, 100);
    glVertex3f(-100, 470, 100);
    glVertex3f(-100, 470, 90);
    glVertex3f(-100, 430, 90);
    glEnd();
    glPopMatrix();

    glPopMatrix();

    //Pilar2
    glPushMatrix();
    glTranslatef(0, 0, -190);

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-90, 470, 100);
    glVertex3f(-100, 470, 100);
    glVertex3f(-100, 470, 90);
    glVertex3f(-90, 470, 90);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-100, 430, 100);
    glVertex3f(-100, 470, 100);
    glVertex3f(-100, 470, 90);
    glVertex3f(-100, 430, 90);
    glEnd();

    glPushMatrix();
    glTranslatef(10, 0, 0);
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-100, 430, 100);
    glVertex3f(-100, 470, 100);
    glVertex3f(-100, 470, 90);
    glVertex3f(-100, 430, 90);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-190, 0, 0);
    glRotatef(90, 0, 10, 0);
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-100, 430, 100);
    glVertex3f(-100, 470, 100);
    glVertex3f(-100, 470, 90);
    glVertex3f(-100, 430, 90);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-190, 0, -10);
    glRotatef(90, 0, 10, 0);
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-100, 430, 100);
    glVertex3f(-100, 470, 100);
    glVertex3f(-100, 470, 90);
    glVertex3f(-100, 430, 90);
    glEnd();
    glPopMatrix();

    glPopMatrix();

    //tiang
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(97.5, 462.5, -90);
    glVertex3f(97.5, 467.5, -90);
    glVertex3f(97.5, 467.5, 90);
    glVertex3f(97.5, 462.5, 90);
    glEnd();

    glPushMatrix();
    glTranslatef(-5, 0, 0);
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(97.5, 462.5, -90);
    glVertex3f(97.5, 467.5, -90);
    glVertex3f(97.5, 467.5, 90);
    glVertex3f(97.5, 462.5, 90);
    glEnd();
    glPopMatrix();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(92.5, 467.5, -90);
    glVertex3f(97.5, 467.5, -90);
    glVertex3f(97.5, 467.5, 90);
    glVertex3f(92.5, 467.5, 90);
    glEnd();

    glPushMatrix();
    glTranslatef(0, -5, 0);
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(92.5, 467.5, -90);
    glVertex3f(97.5, 467.5, -90);
    glVertex3f(97.5, 467.5, 90);
    glVertex3f(92.5, 467.5, 90);
    glEnd();
    glPopMatrix();

    //tiang 2

    glPushMatrix();
    glTranslatef(-190, 0, 0);

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(97.5, 462.5, -90);
    glVertex3f(97.5, 467.5, -90);
    glVertex3f(97.5, 467.5, 90);
    glVertex3f(97.5, 462.5, 90);
    glEnd();

    glPushMatrix();
    glTranslatef(-5, 0, 0);
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(97.5, 462.5, -90);
    glVertex3f(97.5, 467.5, -90);
    glVertex3f(97.5, 467.5, 90);
    glVertex3f(97.5, 462.5, 90);
    glEnd();
    glPopMatrix();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(92.5, 467.5, -90);
    glVertex3f(97.5, 467.5, -90);
    glVertex3f(97.5, 467.5, 90);
    glVertex3f(92.5, 467.5, 90);
    glEnd();

    glPushMatrix();
    glTranslatef(0, -5, 0);
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(92.5, 467.5, -90);
    glVertex3f(97.5, 467.5, -90);
    glVertex3f(97.5, 467.5, 90);
    glVertex3f(92.5, 467.5, 90);
    glEnd();
    glPopMatrix();

    glPopMatrix();

    //tiang 3
    glPushMatrix();
    glRotatef(90, 0, 10, 0);

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(97.5, 462.5, -90);
    glVertex3f(97.5, 467.5, -90);
    glVertex3f(97.5, 467.5, 90);
    glVertex3f(97.5, 462.5, 90);
    glEnd();

    glPushMatrix();
    glTranslatef(-5, 0, 0);
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(97.5, 462.5, -90);
    glVertex3f(97.5, 467.5, -90);
    glVertex3f(97.5, 467.5, 90);
    glVertex3f(97.5, 462.5, 90);
    glEnd();
    glPopMatrix();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(92.5, 467.5, -90);
    glVertex3f(97.5, 467.5, -90);
    glVertex3f(97.5, 467.5, 90);
    glVertex3f(92.5, 467.5, 90);
    glEnd();

    glPushMatrix();
    glTranslatef(0, -5, 0);
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(92.5, 467.5, -90);
    glVertex3f(97.5, 467.5, -90);
    glVertex3f(97.5, 467.5, 90);
    glVertex3f(92.5, 467.5, 90);
    glEnd();
    glPopMatrix();

    glPopMatrix();

    //tiang 4
    glPushMatrix();
    glTranslatef(0, 0, 190);
    glRotatef(90, 0, 10, 0);

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(97.5, 462.5, -90);
    glVertex3f(97.5, 467.5, -90);
    glVertex3f(97.5, 467.5, 90);
    glVertex3f(97.5, 462.5, 90);
    glEnd();

    glPushMatrix();
    glTranslatef(-5, 0, 0);
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(97.5, 462.5, -90);
    glVertex3f(97.5, 467.5, -90);
    glVertex3f(97.5, 467.5, 90);
    glVertex3f(97.5, 462.5, 90);
    glEnd();
    glPopMatrix();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(92.5, 467.5, -90);
    glVertex3f(97.5, 467.5, -90);
    glVertex3f(97.5, 467.5, 90);
    glVertex3f(92.5, 467.5, 90);
    glEnd();

    glPushMatrix();
    glTranslatef(0, -5, 0);
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(92.5, 467.5, -90);
    glVertex3f(97.5, 467.5, -90);
    glVertex3f(97.5, 467.5, 90);
    glVertex3f(92.5, 467.5, 90);
    glEnd();
    glPopMatrix();
    glPopMatrix();
}

void pohon() {

    //pohon 1
    glPushMatrix();

    //Daon
    glPushMatrix();
    glColor3f(0, 1, 0);
    glTranslatef(200, 175, -300);
    glRotatef(-90, 10, 0, 0);
    glutSolidCone(50, 175, 20, 0);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 1, 0);
    glTranslatef(200, 100, -300);
    glRotatef(-90, 10, 0, 0);
    glutSolidCone(60, 175, 20, 0);
    glPopMatrix();

    //Kayu
    glColor3ub(105, 50, 12);
    glPushMatrix();
    glTranslatef(200, 0, -300);
    glRotatef(-90, 10, 0, 0);
    gluCylinder(gluNewQuadric(), 25, 20, 100, 32, 100);
    glPopMatrix();

    glPopMatrix();

    //Pohon 2

    glPushMatrix();
    glTranslatef(0, 0, -150);

    //Daon
    glPushMatrix();
    glColor3f(0, 1, 0);
    glTranslatef(200, 175, -300);
    glRotatef(-90, 10, 0, 0);
    glutSolidCone(50, 175, 20, 0);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 1, 0);
    glTranslatef(200, 100, -300);
    glRotatef(-90, 10, 0, 0);
    glutSolidCone(60, 175, 20, 0);
    glPopMatrix();

    //Kayu
    glColor3ub(105, 50, 12);
    glPushMatrix();
    glTranslatef(200, 0, -300);
    glRotatef(-90, 10, 0, 0);
    gluCylinder(gluNewQuadric(), 25, 20, 100, 32, 100);
    glPopMatrix();

    glPopMatrix();

    //pohon 3
    glPushMatrix();

    //Daon
    glPushMatrix();
    glColor3f(0, 1, 0);
    glTranslatef(-200, 175, -300);
    glRotatef(-90, 10, 0, 0);
    glutSolidCone(50, 175, 20, 0);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 1, 0);
    glTranslatef(-200, 100, -300);
    glRotatef(-90, 10, 0, 0);
    glutSolidCone(60, 175, 20, 0);
    glPopMatrix();

    //Kayu
    glColor3ub(105, 50, 12);
    glPushMatrix();
    glTranslatef(-200, 0, -300);
    glRotatef(-90, 10, 0, 0);
    gluCylinder(gluNewQuadric(), 25, 20, 100, 32, 100);
    glPopMatrix();

    glPopMatrix();

    //Pohon 4

    glPushMatrix();
    glTranslatef(0, 0, -150);

    //Daon
    glPushMatrix();
    glColor3f(0, 1, 0);
    glTranslatef(-200, 175, -300);
    glRotatef(-90, 10, 0, 0);
    glutSolidCone(50, 175, 20, 0);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 1, 0);
    glTranslatef(-200, 100, -300);
    glRotatef(-90, 10, 0, 0);
    glutSolidCone(60, 175, 20, 0);
    glPopMatrix();

    //Kayu
    glColor3ub(105, 50, 12);
    glPushMatrix();
    glTranslatef(-200, 0, -300);
    glRotatef(-90, 10, 0, 0);
    gluCylinder(gluNewQuadric(), 25, 20, 100, 32, 100);
    glPopMatrix();

    glPopMatrix();
}

void gerbang() {
    //Tiang Kiri
    glColor3f(1, 0, 0);
    glPushMatrix();
    glTranslatef(100, 0, -600);
    glRotatef(-90, 10, 0, 0);
    gluCylinder(gluNewQuadric(), 15, 15, 250, 32, 100);
    glPopMatrix();

    //Tiang Kanan
    glColor3f(1, 0, 0);
    glPushMatrix();
    glTranslatef(-100, 0, -600);
    glRotatef(-90, 10, 0, 0);
    gluCylinder(gluNewQuadric(), 15, 15, 250, 32, 100);
    glPopMatrix();

    //Mistar 1
    glBegin(GL_POLYGON);
    glColor3f(1, 0, 0.0);
    glVertex3f(-150, 200, -610);
    glVertex3f(-150, 175, -610);
    glVertex3f(150, 175, -610);
    glVertex3f(150, 200, -610);
    glEnd();

    glPushMatrix();
    glTranslatef(0, 0, 20);
    glBegin(GL_POLYGON);
    glColor3f(1, 0, 0.0);
    glVertex3f(-150, 200, -610);
    glVertex3f(-150, 175, -610);
    glVertex3f(150, 175, -610);
    glVertex3f(150, 200, -610);
    glEnd();
    glPopMatrix();

    glBegin(GL_POLYGON);
    glColor3f(1, 0, 0.0);
    glVertex3f(-150, 200, -610);
    glVertex3f(-150, 200, -590);
    glVertex3f(150, 200, -590);
    glVertex3f(150, 200, -610);
    glEnd();

    glPushMatrix();
    glTranslatef(0, -25, 0);
    glBegin(GL_POLYGON);
    glColor3f(1, 0, 0.0);
    glVertex3f(-150, 200, -610);
    glVertex3f(-150, 200, -590);
    glVertex3f(150, 200, -590);
    glVertex3f(150, 200, -610);
    glEnd();
    glPopMatrix();

    glBegin(GL_POLYGON);
    glColor3f(1, 0, 0.0);
    glVertex3f(-150, 175, -590);
    glVertex3f(-150, 175, -610);
    glVertex3f(-150, 200, -610);
    glVertex3f(-150, 200, -590);
    glEnd();

    glPushMatrix();
    glTranslatef(300, 0, 0);
    glBegin(GL_POLYGON);
    glColor3f(1, 0, 0.0);
    glVertex3f(-150, 175, -590);
    glVertex3f(-150, 175, -610);
    glVertex3f(-150, 200, -610);
    glVertex3f(-150, 200, -590);
    glEnd();
    glPopMatrix();

    //Mistar 2
    glBegin(GL_POLYGON);
    glColor3f(1, 0, 0.0);
    glVertex3f(-160, 250, -610);
    glVertex3f(-170, 275, -610);
    glVertex3f(170, 275, -610);
    glVertex3f(160, 250, -610);
    glEnd();

    glPushMatrix();
    glTranslatef(0, 0, 20);
    glBegin(GL_POLYGON);
    glColor3f(1, 0, 0.0);
    glVertex3f(-160, 250, -610);
    glVertex3f(-170, 275, -610);
    glVertex3f(170, 275, -610);
    glVertex3f(160, 250, -610);
    glEnd();
    glPopMatrix();

    glBegin(GL_POLYGON);
    glColor3f(1, 0, 0.0);
    glVertex3f(-160, 250, -590);
    glVertex3f(-160, 250, -610);
    glVertex3f(160, 250, -610);
    glVertex3f(160, 250, -590);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 0, 0.0);
    glVertex3f(-160, 250, -590);
    glVertex3f(-160, 250, -610);
    glVertex3f(160, 250, -610);
    glVertex3f(160, 250, -590);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 0, 0.0);
    glVertex3f(160, 250, -610);
    glVertex3f(170, 275, -610);
    glVertex3f(170, 275, -590);
    glVertex3f(160, 250, -590);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 0, 0.0);
    glVertex3f(-160, 250, -610);
    glVertex3f(-170, 275, -610);
    glVertex3f(-170, 275, -590);
    glVertex3f(160, 250, -590);
    glEnd();

    //Mistar 3
    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0.0);
    glVertex3f(-270, 280, -615);
    glVertex3f(-290, 315, -615);
    glVertex3f(-230, 310, -615);
    glVertex3f(230, 310, -615);
    glVertex3f(290, 315, -615);
    glVertex3f(270, 280, -615);
    glVertex3f(210, 275, -615);
    glVertex3f(-210, 275, -615);
    glEnd();

    glPushMatrix();
    glTranslatef(0, 0, 30);
    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0.0);
    glVertex3f(-270, 280, -615);
    glVertex3f(-290, 315, -615);
    glVertex3f(-230, 310, -615);
    glVertex3f(230, 310, -615);
    glVertex3f(290, 315, -615);
    glVertex3f(270, 280, -615);
    glVertex3f(210, 275, -615);
    glVertex3f(-210, 275, -615);
    glEnd();
    glPopMatrix();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0.0);
    glVertex3f(-270, 280, -585);
    glVertex3f(-210, 275, -585);
    glVertex3f(210, 275, -585);
    glVertex3f(270, 280, -585);
    glVertex3f(270, 280, -615);
    glVertex3f(210, 275, -615);
    glVertex3f(-210, 275, -615);
    glVertex3f(-270, 280, -615);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0.0);
    glVertex3f(-230, 310, -615);
    glVertex3f(230, 310, -615);
    glVertex3f(230, 310, -585);
    glVertex3f(-230, 310, -585);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0.0);
    glVertex3f(-290, 315, -615);
    glVertex3f(-230, 310, -615);
    glVertex3f(-230, 310, -585);
    glVertex3f(-290, 315, -585);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0.0);
    glVertex3f(230, 310, -615);
    glVertex3f(290, 315, -615);
    glVertex3f(290, 315, -585);
    glVertex3f(230, 310, -585);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0.0);
    glVertex3f(270, 280, -615);
    glVertex3f(290, 315, -615);
    glVertex3f(290, 315, -585);
    glVertex3f(270, 280, -585);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0.0);
    glVertex3f(-270, 280, -585);
    glVertex3f(-290, 315, -585);
    glVertex3f(-290, 315, -615);
    glVertex3f(-270, 280, -615);
    glEnd();
}

void bulat() {
    //Lingkaran 1

    glPushMatrix();
    glTranslatef(195, 70, 195);
    glColor3f(0, 0, 0);
    glutSolidSphere(5, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-195, 70, -195);
    glColor3f(0, 0, 0);
    glutSolidSphere(5, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(195, 70, -195);
    glColor3f(0, 0, 0);
    glutSolidSphere(5, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-195, 70, 195);
    glColor3f(0, 0, 0);
    glutSolidSphere(5, 30, 30);
    glPopMatrix();

    //Lingkaran 2
    glPushMatrix();
    glTranslatef(125, 225, 125);
    glColor3f(0, 0, 0);
    glutSolidSphere(5, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-125, 225, -125);
    glColor3f(0, 0, 0);
    glutSolidSphere(5, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(125, 225, -125);
    glColor3f(0, 0, 0);
    glutSolidSphere(5, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-125, 225, 125);
    glColor3f(0, 0, 0);
    glutSolidSphere(5, 30, 30);
    glPopMatrix();

    //Lingkaran 3
    glPushMatrix();
    glTranslatef(95, 475, 95);
    glColor3f(0, 0, 0);
    glutSolidSphere(5, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-95, 475, -95);
    glColor3f(0, 0, 0);
    glutSolidSphere(5, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-95, 475, 95);
    glColor3f(0, 0, 0);
    glutSolidSphere(5, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(95, 475, -95);
    glColor3f(0, 0, 0);
    glutSolidSphere(5, 30, 30);
    glPopMatrix();

}

void sudut1() {
    //Detail Bangun 1
    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(80, -60, 80);
    glRotatef(-90, 18, 0, 0);
    gluCylinder(gluNewQuadric(), 10.65, 10.65, 230, 32, 100);
    glEnd();
    glPopMatrix();

    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(-80, -60, 80);
    glRotatef(-90, 18, 0, 0);
    gluCylinder(gluNewQuadric(), 10.65, 10.65, 230, 32, 100);
    glEnd();
    glPopMatrix();

    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(-80, -60, -80);
    glRotatef(-90, 18, 0, 0);
    gluCylinder(gluNewQuadric(), 10.65, 10.65, 230, 32, 100);
    glEnd();
    glPopMatrix();

    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(80, -60, -80);
    glRotatef(-90, 18, 0, 0);
    gluCylinder(gluNewQuadric(), 10.65, 10.65, 230, 32, 100);
    glEnd();
    glPopMatrix();


    //Detail Bangun 2

    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(70, 140, -70);
    glRotatef(-90, 18, 0, 0);
    gluCylinder(gluNewQuadric(), 10.65, 10.65, 190, 32, 100);
    glEnd();
    glPopMatrix();

    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(-70, 140, -70);
    glRotatef(-90, 18, 0, 0);
    gluCylinder(gluNewQuadric(), 10.65, 10.65, 190, 32, 100);
    glEnd();
    glPopMatrix();

    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(70, 140, 70);
    glRotatef(-90, 18, 0, 0);
    gluCylinder(gluNewQuadric(), 10.65, 10.65, 190, 32, 100);
    glEnd();
    glPopMatrix();

    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(-70, 140, 70);
    glRotatef(-90, 18, 0, 0);
    gluCylinder(gluNewQuadric(), 10.65, 10.65, 190, 32, 100);
    glEnd();
    glPopMatrix();

    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(70, 140, -70);
    glRotatef(-90, 18, 0, 0);
    gluCylinder(gluNewQuadric(), 10.65, 10.65, 190, 32, 100);
    glEnd();
    glPopMatrix();

    //Detail Bangun 3

    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(50, 350, 50);
    glRotatef(-90, 18, 0, 0);
    gluCylinder(gluNewQuadric(), 10.65, 10.65, 50, 32, 100);
    glEnd();
    glPopMatrix();

    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(-50, 350, -50);
    glRotatef(-90, 18, 0, 0);
    gluCylinder(gluNewQuadric(), 10.65, 10.65, 50, 32, 100);
    glEnd();
    glPopMatrix();

    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(-50, 350, 50);
    glRotatef(-90, 18, 0, 0);
    gluCylinder(gluNewQuadric(), 10.65, 10.65, 50, 32, 100);
    glEnd();
    glPopMatrix();

    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(50, 350, -50);
    glRotatef(-90, 18, 0, 0);
    gluCylinder(gluNewQuadric(), 10.65, 10.65, 50, 32, 100);
    glEnd();
    glPopMatrix();

    //Detail Gedung 4

    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(60, 430, 60);
    glRotatef(-90, 18, 0, 0);
    gluCylinder(gluNewQuadric(), 10, 10, 120, 32, 100);
    glEnd();
    glPopMatrix();

    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(-60, 430, -60);
    glRotatef(-90, 18, 0, 0);
    gluCylinder(gluNewQuadric(), 10, 10, 120, 32, 100);
    glEnd();
    glPopMatrix();

    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(-60, 430, 60);
    glRotatef(-90, 18, 0, 0);
    gluCylinder(gluNewQuadric(), 10, 10, 120, 32, 100);
    glEnd();
    glPopMatrix();

    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(60, 430, -60);
    glRotatef(-90, 18, 0, 0);
    gluCylinder(gluNewQuadric(), 10, 10, 120, 32, 100);
    glEnd();
    glPopMatrix();
}

void pintu() {
    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(0, 235, -140.5);
    glRotatef(90, 0, 10, 0);
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-77.7, 180, -22.5); //8
    glVertex3f(-77.7, 245, -22.5); //1
    glVertex3f(-77.7, 245, 22.5); //4
    glVertex3f(-77.7, 180, 22.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, -22.5); //8
    glVertex3f(-72.7, 245, -22.5); //1
    glVertex3f(-72.7, 245, -17.5); //4
    glVertex3f(-72.7, 180, -17.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, 22.5); //8
    glVertex3f(-72.7, 245, 22.5); //1
    glVertex3f(-72.7, 245, 17.5); //4
    glVertex3f(-72.7, 180, 17.5); //5
    glEnd();

    //
    //
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, 22.5); //8
    glVertex3f(-72.7, 245, 22.5); //1
    glVertex3f(-77.7, 245, 22.5); //4
    glVertex3f(-77.7, 180, 22.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, -22.5); //8
    glVertex3f(-72.7, 245, -22.5); //1
    glVertex3f(-77.7, 245, -22.5); //4
    glVertex3f(-77.7, 180, -22.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, 17.5); //8
    glVertex3f(-72.7, 245, 17.5); //1
    glVertex3f(-77.7, 245, 17.5); //4
    glVertex3f(-77.7, 180, 17.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, -17.5); //8
    glVertex3f(-72.7, 245, -17.5); //1
    glVertex3f(-77.7, 245, -17.5); //4
    glVertex3f(-77.7, 180, -17.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 240, 22.5); //8
    glVertex3f(-72.7, 245, 22.5); //1
    glVertex3f(-72.7, 245, -22.5); //4
    glVertex3f(-72.7, 240, -22.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 245, 22.5); //8
    glVertex3f(-77.7, 245, 22.5); //1
    glVertex3f(-77.7, 245, -22.5); //4
    glVertex3f(-72.7, 245, -22.5); //5
    glEnd();
    //
    //
    glBegin(GL_POLYGON); //sisi1
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-77.6, 180, -17.5); //8
    glVertex3f(-77.6, 240, -17.5); //1
    glVertex3f(-77.6, 240, 17.5); //4
    glVertex3f(-77.6, 180, 17.5); //5
    glEnd();
    glPopMatrix();


    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(0, 0, -155);
    glRotatef(90, 0, 10, 0);
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-77.7, 180, -22.5); //8
    glVertex3f(-77.7, 245, -22.5); //1
    glVertex3f(-77.7, 245, 22.5); //4
    glVertex3f(-77.7, 180, 22.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, -22.5); //8
    glVertex3f(-72.7, 245, -22.5); //1
    glVertex3f(-72.7, 245, -17.5); //4
    glVertex3f(-72.7, 180, -17.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, 22.5); //8
    glVertex3f(-72.7, 245, 22.5); //1
    glVertex3f(-72.7, 245, 17.5); //4
    glVertex3f(-72.7, 180, 17.5); //5
    glEnd();

    //
    //
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, 22.5); //8
    glVertex3f(-72.7, 245, 22.5); //1
    glVertex3f(-77.7, 245, 22.5); //4
    glVertex3f(-77.7, 180, 22.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, -22.5); //8
    glVertex3f(-72.7, 245, -22.5); //1
    glVertex3f(-77.7, 245, -22.5); //4
    glVertex3f(-77.7, 180, -22.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, 17.5); //8
    glVertex3f(-72.7, 245, 17.5); //1
    glVertex3f(-77.7, 245, 17.5); //4
    glVertex3f(-77.7, 180, 17.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, -17.5); //8
    glVertex3f(-72.7, 245, -17.5); //1
    glVertex3f(-77.7, 245, -17.5); //4
    glVertex3f(-77.7, 180, -17.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 240, 22.5); //8
    glVertex3f(-72.7, 245, 22.5); //1
    glVertex3f(-72.7, 245, -22.5); //4
    glVertex3f(-72.7, 240, -22.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 245, 22.5); //8
    glVertex3f(-77.7, 245, 22.5); //1
    glVertex3f(-77.7, 245, -22.5); //4
    glVertex3f(-72.7, 245, -22.5); //5
    glEnd();
    //
    //


    glBegin(GL_POLYGON); //sisi1
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-77.6, 180, -17.5); //8
    glVertex3f(-77.6, 240, -17.5); //1
    glVertex3f(-77.6, 240, 17.5); //4
    glVertex3f(-77.6, 180, 17.5); //5
    glEnd();

    glPopMatrix();

    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(0, 0, 155);
    glRotatef(270, 0, 10, 0);
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-77.7, 180, -22.5); //8
    glVertex3f(-77.7, 245, -22.5); //1
    glVertex3f(-77.7, 245, 22.5); //4
    glVertex3f(-77.7, 180, 22.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, -22.5); //8
    glVertex3f(-72.7, 245, -22.5); //1
    glVertex3f(-72.7, 245, -17.5); //4
    glVertex3f(-72.7, 180, -17.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, 22.5); //8
    glVertex3f(-72.7, 245, 22.5); //1
    glVertex3f(-72.7, 245, 17.5); //4
    glVertex3f(-72.7, 180, 17.5); //5
    glEnd();
    //
    //
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, 22.5); //8
    glVertex3f(-72.7, 245, 22.5); //1
    glVertex3f(-77.7, 245, 22.5); //4
    glVertex3f(-77.7, 180, 22.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, -22.5); //8
    glVertex3f(-72.7, 245, -22.5); //1
    glVertex3f(-77.7, 245, -22.5); //4
    glVertex3f(-77.7, 180, -22.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, 17.5); //8
    glVertex3f(-72.7, 245, 17.5); //1
    glVertex3f(-77.7, 245, 17.5); //4
    glVertex3f(-77.7, 180, 17.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, -17.5); //8
    glVertex3f(-72.7, 245, -17.5); //1
    glVertex3f(-77.7, 245, -17.5); //4
    glVertex3f(-77.7, 180, -17.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 240, 22.5); //8
    glVertex3f(-72.7, 245, 22.5); //1
    glVertex3f(-72.7, 245, -22.5); //4
    glVertex3f(-72.7, 240, -22.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 245, 22.5); //8
    glVertex3f(-77.7, 245, 22.5); //1
    glVertex3f(-77.7, 245, -22.5); //4
    glVertex3f(-72.7, 245, -22.5); //5
    glEnd();
    //
    //
    glBegin(GL_POLYGON); //sisi1
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-77.6, 180, -17.5); //8
    glVertex3f(-77.6, 240, -17.5); //1
    glVertex3f(-77.6, 240, 17.5); //4
    glVertex3f(-77.6, 180, 17.5); //5
    glEnd();

    glPopMatrix();

    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(-155, 0, 0);
    glRotatef(180, 0, 10, 0);
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-77.7, 180, -22.5); //8
    glVertex3f(-77.7, 245, -22.5); //1
    glVertex3f(-77.7, 245, 22.5); //4
    glVertex3f(-77.7, 180, 22.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, -22.5); //8
    glVertex3f(-72.7, 245, -22.5); //1
    glVertex3f(-72.7, 245, -17.5); //4
    glVertex3f(-72.7, 180, -17.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, 22.5); //8
    glVertex3f(-72.7, 245, 22.5); //1
    glVertex3f(-72.7, 245, 17.5); //4
    glVertex3f(-72.7, 180, 17.5); //5
    glEnd();
    //
    //
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, 22.5); //8
    glVertex3f(-72.7, 245, 22.5); //1
    glVertex3f(-77.7, 245, 22.5); //4
    glVertex3f(-77.7, 180, 22.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, -22.5); //8
    glVertex3f(-72.7, 245, -22.5); //1
    glVertex3f(-77.7, 245, -22.5); //4
    glVertex3f(-77.7, 180, -22.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, 17.5); //8
    glVertex3f(-72.7, 245, 17.5); //1
    glVertex3f(-77.7, 245, 17.5); //4
    glVertex3f(-77.7, 180, 17.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, -17.5); //8
    glVertex3f(-72.7, 245, -17.5); //1
    glVertex3f(-77.7, 245, -17.5); //4
    glVertex3f(-77.7, 180, -17.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 240, 22.5); //8
    glVertex3f(-72.7, 245, 22.5); //1
    glVertex3f(-72.7, 245, -22.5); //4
    glVertex3f(-72.7, 240, -22.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 245, 22.5); //8
    glVertex3f(-77.7, 245, 22.5); //1
    glVertex3f(-77.7, 245, -22.5); //4
    glVertex3f(-72.7, 245, -22.5); //5
    glEnd();
    //
    //
    glBegin(GL_POLYGON); //sisi1
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-77.6, 180, -17.5); //8
    glVertex3f(-77.6, 240, -17.5); //1
    glVertex3f(-77.6, 240, 17.5); //4
    glVertex3f(-77.6, 180, 17.5); //5
    glEnd();
    glPopMatrix();
    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(155, 0, 0);
    glRotatef(0, 0, 10, 0);
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-77.7, 180, -22.5); //8
    glVertex3f(-77.7, 245, -22.5); //1
    glVertex3f(-77.7, 245, 22.5); //4
    glVertex3f(-77.7, 180, 22.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, -22.5); //8
    glVertex3f(-72.7, 245, -22.5); //1
    glVertex3f(-72.7, 245, -17.5); //4
    glVertex3f(-72.7, 180, -17.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, 22.5); //8
    glVertex3f(-72.7, 245, 22.5); //1
    glVertex3f(-72.7, 245, 17.5); //4
    glVertex3f(-72.7, 180, 17.5); //5
    glEnd();
    //
    //
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, 22.5); //8
    glVertex3f(-72.7, 245, 22.5); //1
    glVertex3f(-77.7, 245, 22.5); //4
    glVertex3f(-77.7, 180, 22.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, -22.5); //8
    glVertex3f(-72.7, 245, -22.5); //1
    glVertex3f(-77.7, 245, -22.5); //4
    glVertex3f(-77.7, 180, -22.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, 17.5); //8
    glVertex3f(-72.7, 245, 17.5); //1
    glVertex3f(-77.7, 245, 17.5); //4
    glVertex3f(-77.7, 180, 17.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, -17.5); //8
    glVertex3f(-72.7, 245, -17.5); //1
    glVertex3f(-77.7, 245, -17.5); //4
    glVertex3f(-77.7, 180, -17.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 240, 22.5); //8
    glVertex3f(-72.7, 245, 22.5); //1
    glVertex3f(-72.7, 245, -22.5); //4
    glVertex3f(-72.7, 240, -22.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 245, 22.5); //8
    glVertex3f(-77.7, 245, 22.5); //1
    glVertex3f(-77.7, 245, -22.5); //4
    glVertex3f(-72.7, 245, -22.5); //5
    glEnd();
    //
    //
    glBegin(GL_POLYGON); //sisi1
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-77.6, 180, -17.5); //8
    glVertex3f(-77.6, 240, -17.5); //1
    glVertex3f(-77.6, 240, 17.5); //4
    glVertex3f(-77.6, 180, 17.5); //5
    glEnd();
    glPopMatrix();

    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(0, -155, -165);
    glRotatef(90, 0, 10, 0);
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-77.7, 180, -22.5); //8
    glVertex3f(-77.7, 245, -22.5); //1
    glVertex3f(-77.7, 245, 22.5); //4
    glVertex3f(-77.7, 180, 22.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, -22.5); //8
    glVertex3f(-72.7, 245, -22.5); //1
    glVertex3f(-72.7, 245, -17.5); //4
    glVertex3f(-72.7, 180, -17.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, 22.5); //8
    glVertex3f(-72.7, 245, 22.5); //1
    glVertex3f(-72.7, 245, 17.5); //4
    glVertex3f(-72.7, 180, 17.5); //5
    glEnd();

    //
    //
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, 22.5); //8
    glVertex3f(-72.7, 245, 22.5); //1
    glVertex3f(-77.7, 245, 22.5); //4
    glVertex3f(-77.7, 180, 22.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, -22.5); //8
    glVertex3f(-72.7, 245, -22.5); //1
    glVertex3f(-77.7, 245, -22.5); //4
    glVertex3f(-77.7, 180, -22.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, 17.5); //8
    glVertex3f(-72.7, 245, 17.5); //1
    glVertex3f(-77.7, 245, 17.5); //4
    glVertex3f(-77.7, 180, 17.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, -17.5); //8
    glVertex3f(-72.7, 245, -17.5); //1
    glVertex3f(-77.7, 245, -17.5); //4
    glVertex3f(-77.7, 180, -17.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 240, 22.5); //8
    glVertex3f(-72.7, 245, 22.5); //1
    glVertex3f(-72.7, 245, -22.5); //4
    glVertex3f(-72.7, 240, -22.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 245, 22.5); //8
    glVertex3f(-77.7, 245, 22.5); //1
    glVertex3f(-77.7, 245, -22.5); //4
    glVertex3f(-72.7, 245, -22.5); //5
    glEnd();
    //
    //


    glBegin(GL_POLYGON); //sisi1
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-77.6, 180, -17.5); //8
    glVertex3f(-77.6, 240, -17.5); //1
    glVertex3f(-77.6, 240, 17.5); //4
    glVertex3f(-77.6, 180, 17.5); //5
    glEnd();

    glPopMatrix();
}

void pagar_floor3() {
    //Pilar 1
    glPushMatrix();
    glTranslatef(12.5, -75, -12.5);

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-90, 450, 100);
    glVertex3f(-100, 450, 100);
    glVertex3f(-100, 450, 90);
    glVertex3f(-90, 450, 90);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-100, 430, 100);
    glVertex3f(-100, 450, 100);
    glVertex3f(-100, 450, 90);
    glVertex3f(-100, 430, 90);
    glEnd();

    glPushMatrix();
    glTranslatef(10, 0, 0);
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-100, 430, 100);
    glVertex3f(-100, 450, 100);
    glVertex3f(-100, 450, 90);
    glVertex3f(-100, 430, 90);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-190, 0, 0);
    glRotatef(90, 0, 10, 0);
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-100, 430, 100);
    glVertex3f(-100, 450, 100);
    glVertex3f(-100, 450, 90);
    glVertex3f(-100, 430, 90);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-190, 0, -10);
    glRotatef(90, 0, 10, 0);
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-100, 430, 100);
    glVertex3f(-100, 450, 100);
    glVertex3f(-100, 450, 90);
    glVertex3f(-100, 430, 90);
    glEnd();
    glPopMatrix();

    glPopMatrix();

    //Pilar 2
    glPushMatrix();
    glTranslatef(177.5, -75, -12.5);

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-90, 450, 100);
    glVertex3f(-100, 450, 100);
    glVertex3f(-100, 450, 90);
    glVertex3f(-90, 450, 90);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-100, 430, 100);
    glVertex3f(-100, 450, 100);
    glVertex3f(-100, 450, 90);
    glVertex3f(-100, 430, 90);
    glEnd();

    glPushMatrix();
    glTranslatef(10, 0, 0);
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-100, 430, 100);
    glVertex3f(-100, 450, 100);
    glVertex3f(-100, 450, 90);
    glVertex3f(-100, 430, 90);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-190, 0, 0);
    glRotatef(90, 0, 10, 0);
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-100, 430, 100);
    glVertex3f(-100, 450, 100);
    glVertex3f(-100, 450, 90);
    glVertex3f(-100, 430, 90);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-190, 0, -10);
    glRotatef(90, 0, 10, 0);
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-100, 430, 100);
    glVertex3f(-100, 450, 100);
    glVertex3f(-100, 450, 90);
    glVertex3f(-100, 430, 90);
    glEnd();
    glPopMatrix();

    glPopMatrix();

    //Pilar 3
    glPushMatrix();
    glTranslatef(177.5, -75, -177.5);

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-90, 450, 100);
    glVertex3f(-100, 450, 100);
    glVertex3f(-100, 450, 90);
    glVertex3f(-90, 450, 90);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-100, 430, 100);
    glVertex3f(-100, 450, 100);
    glVertex3f(-100, 450, 90);
    glVertex3f(-100, 430, 90);
    glEnd();

    glPushMatrix();
    glTranslatef(10, 0, 0);
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-100, 430, 100);
    glVertex3f(-100, 450, 100);
    glVertex3f(-100, 450, 90);
    glVertex3f(-100, 430, 90);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-190, 0, 0);
    glRotatef(90, 0, 10, 0);
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-100, 430, 100);
    glVertex3f(-100, 450, 100);
    glVertex3f(-100, 450, 90);
    glVertex3f(-100, 430, 90);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-190, 0, -10);
    glRotatef(90, 0, 10, 0);
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-100, 430, 100);
    glVertex3f(-100, 450, 100);
    glVertex3f(-100, 450, 90);
    glVertex3f(-100, 430, 90);
    glEnd();
    glPopMatrix();

    glPopMatrix();

    //Pilar 4
    glPushMatrix();
    glTranslatef(12.5, -75, -177.5);

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-90, 450, 100);
    glVertex3f(-100, 450, 100);
    glVertex3f(-100, 450, 90);
    glVertex3f(-90, 450, 90);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-100, 430, 100);
    glVertex3f(-100, 450, 100);
    glVertex3f(-100, 450, 90);
    glVertex3f(-100, 430, 90);
    glEnd();

    glPushMatrix();
    glTranslatef(10, 0, 0);
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-100, 430, 100);
    glVertex3f(-100, 450, 100);
    glVertex3f(-100, 450, 90);
    glVertex3f(-100, 430, 90);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-190, 0, 0);
    glRotatef(90, 0, 10, 0);
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-100, 430, 100);
    glVertex3f(-100, 450, 100);
    glVertex3f(-100, 450, 90);
    glVertex3f(-100, 430, 90);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-190, 0, -10);
    glRotatef(90, 0, 10, 0);
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(-100, 430, 100);
    glVertex3f(-100, 450, 100);
    glVertex3f(-100, 450, 90);
    glVertex3f(-100, 430, 90);
    glEnd();
    glPopMatrix();

    glPopMatrix();

    //tiang 1
    glPushMatrix();
    glTranslatef(-12.5, -95, 0);
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(97.5, 462.5, -80);
    glVertex3f(97.5, 467.5, -80);
    glVertex3f(97.5, 467.5, 80);
    glVertex3f(97.5, 462.5, 80);
    glEnd();

    glPushMatrix();
    glTranslatef(-5, 0, 0);
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(97.5, 462.5, -80);
    glVertex3f(97.5, 467.5, -80);
    glVertex3f(97.5, 467.5, 80);
    glVertex3f(97.5, 462.5, 80);
    glEnd();
    glPopMatrix();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(92.5, 467.5, -80);
    glVertex3f(97.5, 467.5, -80);
    glVertex3f(97.5, 467.5, 80);
    glVertex3f(92.5, 467.5, 80);
    glEnd();

    glPushMatrix();
    glTranslatef(0, -5, 0);
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(92.5, 467.5, -80);
    glVertex3f(97.5, 467.5, -80);
    glVertex3f(97.5, 467.5, 80);
    glVertex3f(92.5, 467.5, 80);
    glEnd();
    glPopMatrix();

    glPopMatrix();

    //tiang 2
    glPushMatrix();
    glTranslatef(-177.5, -95, 0);
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(97.5, 462.5, -80);
    glVertex3f(97.5, 467.5, -80);
    glVertex3f(97.5, 467.5, 80);
    glVertex3f(97.5, 462.5, 80);
    glEnd();

    glPushMatrix();
    glTranslatef(-5, 0, 0);
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(97.5, 462.5, -80);
    glVertex3f(97.5, 467.5, -80);
    glVertex3f(97.5, 467.5, 80);
    glVertex3f(97.5, 462.5, 80);
    glEnd();
    glPopMatrix();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(92.5, 467.5, -80);
    glVertex3f(97.5, 467.5, -80);
    glVertex3f(97.5, 467.5, 80);
    glVertex3f(92.5, 467.5, 80);
    glEnd();

    glPushMatrix();
    glTranslatef(0, -5, 0);
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(92.5, 467.5, -80);
    glVertex3f(97.5, 467.5, -80);
    glVertex3f(97.5, 467.5, 80);
    glVertex3f(92.5, 467.5, 80);
    glEnd();
    glPopMatrix();

    glPopMatrix();

    //tiang 3
    glPushMatrix();
    glTranslatef(2.5, -95, -12.5);
    glRotatef(-90, 0, 10, 0);
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(97.5, 462.5, -80);
    glVertex3f(97.5, 467.5, -80);
    glVertex3f(97.5, 467.5, 80);
    glVertex3f(97.5, 462.5, 80);
    glEnd();

    glPushMatrix();
    glTranslatef(-5, 0, 0);
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(97.5, 462.5, -80);
    glVertex3f(97.5, 467.5, -80);
    glVertex3f(97.5, 467.5, 80);
    glVertex3f(97.5, 462.5, 80);
    glEnd();
    glPopMatrix();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(92.5, 467.5, -80);
    glVertex3f(97.5, 467.5, -80);
    glVertex3f(97.5, 467.5, 80);
    glVertex3f(92.5, 467.5, 80);
    glEnd();

    glPushMatrix();
    glTranslatef(0, -5, 0);
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(92.5, 467.5, -80);
    glVertex3f(97.5, 467.5, -80);
    glVertex3f(97.5, 467.5, 80);
    glVertex3f(92.5, 467.5, 80);
    glEnd();
    glPopMatrix();

    glPopMatrix();

    //tiang 4
    glPushMatrix();
    glTranslatef(2.5, -95, -177.5);
    glRotatef(-90, 0, 10, 0);
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(97.5, 462.5, -80);
    glVertex3f(97.5, 467.5, -80);
    glVertex3f(97.5, 467.5, 80);
    glVertex3f(97.5, 462.5, 80);
    glEnd();

    glPushMatrix();
    glTranslatef(-5, 0, 0);
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(97.5, 462.5, -80);
    glVertex3f(97.5, 467.5, -80);
    glVertex3f(97.5, 467.5, 80);
    glVertex3f(97.5, 462.5, 80);
    glEnd();
    glPopMatrix();

    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(92.5, 467.5, -80);
    glVertex3f(97.5, 467.5, -80);
    glVertex3f(97.5, 467.5, 80);
    glVertex3f(92.5, 467.5, 80);
    glEnd();

    glPushMatrix();
    glTranslatef(0, -5, 0);
    glBegin(GL_POLYGON);
    glColor3ub(237, 91, 23);
    glVertex3f(92.5, 467.5, -80);
    glVertex3f(97.5, 467.5, -80);
    glVertex3f(97.5, 467.5, 80);
    glVertex3f(92.5, 467.5, 80);
    glEnd();
    glPopMatrix();

    glPopMatrix();

}

void pintu3() {
    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(-135,135,0);
    glRotatef(180, 0, 10, 0);
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-77.7, 180, -17.5); //8
    glVertex3f(-77.7, 245, -17.5); //1
    glVertex3f(-77.7, 245, 17.5); //4
    glVertex3f(-77.7, 180, 17.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, -17.5); //8
    glVertex3f(-72.7, 245, -17.5); //1
    glVertex3f(-72.7, 245, -12.5); //4
    glVertex3f(-72.7, 180, -12.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, 17.5); //8
    glVertex3f(-72.7, 245, 17.5); //1
    glVertex3f(-72.7, 245, 12.5); //4
    glVertex3f(-72.7, 180, 12.5); //5
    glEnd();

    //
    //
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, 17.5); //8
    glVertex3f(-72.7, 245, 17.5); //1
    glVertex3f(-77.7, 245, 17.5); //4
    glVertex3f(-77.7, 180, 17.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, -17.5); //8
    glVertex3f(-72.7, 245, -17.5); //1
    glVertex3f(-77.7, 245, -17.5); //4
    glVertex3f(-77.7, 180, -17.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, 12.5); //8
    glVertex3f(-72.7, 245, 12.5); //1
    glVertex3f(-77.7, 245, 12.5); //4
    glVertex3f(-77.7, 180, 12.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, -12.5); //8
    glVertex3f(-72.7, 245, -12.5); //1
    glVertex3f(-77.7, 245, -12.5); //4
    glVertex3f(-77.7, 180, -12.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 240, 17.5); //8
    glVertex3f(-72.7, 245, 17.5); //1
    glVertex3f(-72.7, 245, -17.5); //4
    glVertex3f(-72.7, 240, -17.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 245, 17.5); //8
    glVertex3f(-77.7, 245, 17.5); //1
    glVertex3f(-77.7, 245, -17.5); //4
    glVertex3f(-72.7, 245, -17.5); //5
    glEnd();
    //
    //
    glBegin(GL_POLYGON); //sisi1
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-77.6, 180, -17.5); //8
    glVertex3f(-77.6, 240, -17.5); //1
    glVertex3f(-77.6, 240, 17.5); //4
    glVertex3f(-77.6, 180, 17.5); //5
    glEnd();

    glPopMatrix();

    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(0,135,135);
    glRotatef(270, 0, 10, 0);
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-77.7, 180, -17.5); //8
    glVertex3f(-77.7, 245, -17.5); //1
    glVertex3f(-77.7, 245, 17.5); //4
    glVertex3f(-77.7, 180, 17.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, -17.5); //8
    glVertex3f(-72.7, 245, -17.5); //1
    glVertex3f(-72.7, 245, -12.5); //4
    glVertex3f(-72.7, 180, -12.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, 17.5); //8
    glVertex3f(-72.7, 245, 17.5); //1
    glVertex3f(-72.7, 245, 12.5); //4
    glVertex3f(-72.7, 180, 12.5); //5
    glEnd();

    //
    //
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, 17.5); //8
    glVertex3f(-72.7, 245, 17.5); //1
    glVertex3f(-77.7, 245, 17.5); //4
    glVertex3f(-77.7, 180, 17.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, -17.5); //8
    glVertex3f(-72.7, 245, -17.5); //1
    glVertex3f(-77.7, 245, -17.5); //4
    glVertex3f(-77.7, 180, -17.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, 12.5); //8
    glVertex3f(-72.7, 245, 12.5); //1
    glVertex3f(-77.7, 245, 12.5); //4
    glVertex3f(-77.7, 180, 12.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, -12.5); //8
    glVertex3f(-72.7, 245, -12.5); //1
    glVertex3f(-77.7, 245, -12.5); //4
    glVertex3f(-77.7, 180, -12.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 240, 17.5); //8
    glVertex3f(-72.7, 245, 17.5); //1
    glVertex3f(-72.7, 245, -17.5); //4
    glVertex3f(-72.7, 240, -17.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 245, 17.5); //8
    glVertex3f(-77.7, 245, 17.5); //1
    glVertex3f(-77.7, 245, -17.5); //4
    glVertex3f(-72.7, 245, -17.5); //5
    glEnd();
    //
    //
    glBegin(GL_POLYGON); //sisi1
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-77.6, 180, -17.5); //8
    glVertex3f(-77.6, 240, -17.5); //1
    glVertex3f(-77.6, 240, 17.5); //4
    glVertex3f(-77.6, 180, 17.5); //5
    glEnd();

    glPopMatrix();

    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(135,135,0);
    glRotatef(0, 0, 10, 0);
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-77.7, 180, -17.5); //8
    glVertex3f(-77.7, 245, -17.5); //1
    glVertex3f(-77.7, 245, 17.5); //4
    glVertex3f(-77.7, 180, 17.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, -17.5); //8
    glVertex3f(-72.7, 245, -17.5); //1
    glVertex3f(-72.7, 245, -12.5); //4
    glVertex3f(-72.7, 180, -12.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, 17.5); //8
    glVertex3f(-72.7, 245, 17.5); //1
    glVertex3f(-72.7, 245, 12.5); //4
    glVertex3f(-72.7, 180, 12.5); //5
    glEnd();

    //
    //
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, 17.5); //8
    glVertex3f(-72.7, 245, 17.5); //1
    glVertex3f(-77.7, 245, 17.5); //4
    glVertex3f(-77.7, 180, 17.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, -17.5); //8
    glVertex3f(-72.7, 245, -17.5); //1
    glVertex3f(-77.7, 245, -17.5); //4
    glVertex3f(-77.7, 180, -17.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, 12.5); //8
    glVertex3f(-72.7, 245, 12.5); //1
    glVertex3f(-77.7, 245, 12.5); //4
    glVertex3f(-77.7, 180, 12.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, -12.5); //8
    glVertex3f(-72.7, 245, -12.5); //1
    glVertex3f(-77.7, 245, -12.5); //4
    glVertex3f(-77.7, 180, -12.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 240, 17.5); //8
    glVertex3f(-72.7, 245, 17.5); //1
    glVertex3f(-72.7, 245, -17.5); //4
    glVertex3f(-72.7, 240, -17.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 245, 17.5); //8
    glVertex3f(-77.7, 245, 17.5); //1
    glVertex3f(-77.7, 245, -17.5); //4
    glVertex3f(-72.7, 245, -17.5); //5
    glEnd();
    //
    //
    glBegin(GL_POLYGON); //sisi1
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-77.6, 180, -17.5); //8
    glVertex3f(-77.6, 240, -17.5); //1
    glVertex3f(-77.6, 240, 17.5); //4
    glVertex3f(-77.6, 180, 17.5); //5
    glEnd();

    glPopMatrix();

    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(0,135,-135);
    glRotatef(90, 0, 10, 0);
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-77.7, 180, -17.5); //8
    glVertex3f(-77.7, 245, -17.5); //1
    glVertex3f(-77.7, 245, 17.5); //4
    glVertex3f(-77.7, 180, 17.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, -17.5); //8
    glVertex3f(-72.7, 245, -17.5); //1
    glVertex3f(-72.7, 245, -12.5); //4
    glVertex3f(-72.7, 180, -12.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, 17.5); //8
    glVertex3f(-72.7, 245, 17.5); //1
    glVertex3f(-72.7, 245, 12.5); //4
    glVertex3f(-72.7, 180, 12.5); //5
    glEnd();

    //
    //
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, 17.5); //8
    glVertex3f(-72.7, 245, 17.5); //1
    glVertex3f(-77.7, 245, 17.5); //4
    glVertex3f(-77.7, 180, 17.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, -17.5); //8
    glVertex3f(-72.7, 245, -17.5); //1
    glVertex3f(-77.7, 245, -17.5); //4
    glVertex3f(-77.7, 180, -17.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, 12.5); //8
    glVertex3f(-72.7, 245, 12.5); //1
    glVertex3f(-77.7, 245, 12.5); //4
    glVertex3f(-77.7, 180, 12.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, -12.5); //8
    glVertex3f(-72.7, 245, -12.5); //1
    glVertex3f(-77.7, 245, -12.5); //4
    glVertex3f(-77.7, 180, -12.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 240, 17.5); //8
    glVertex3f(-72.7, 245, 17.5); //1
    glVertex3f(-72.7, 245, -17.5); //4
    glVertex3f(-72.7, 240, -17.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 245, 17.5); //8
    glVertex3f(-77.7, 245, 17.5); //1
    glVertex3f(-77.7, 245, -17.5); //4
    glVertex3f(-72.7, 245, -17.5); //5
    glEnd();
    //
    //
    glBegin(GL_POLYGON); //sisi1
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-77.6, 180, -17.5); //8
    glVertex3f(-77.6, 240, -17.5); //1
    glVertex3f(-77.6, 240, 17.5); //4
    glVertex3f(-77.6, 180, 17.5); //5
    glEnd();

    glPopMatrix();
}

void pintu2() {
    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(140, 235, 0);
    glRotatef(0, 0, 10, 0);
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-77.7, 180, -22.5); //8
    glVertex3f(-77.7, 245, -22.5); //1
    glVertex3f(-77.7, 245, 22.5); //4
    glVertex3f(-77.7, 180, 22.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, -22.5); //8
    glVertex3f(-72.7, 245, -22.5); //1
    glVertex3f(-72.7, 245, -17.5); //4
    glVertex3f(-72.7, 180, -17.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, 22.5); //8
    glVertex3f(-72.7, 245, 22.5); //1
    glVertex3f(-72.7, 245, 17.5); //4
    glVertex3f(-72.7, 180, 17.5); //5
    glEnd();

    //
    //
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, 22.5); //8
    glVertex3f(-72.7, 245, 22.5); //1
    glVertex3f(-77.7, 245, 22.5); //4
    glVertex3f(-77.7, 180, 22.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, -22.5); //8
    glVertex3f(-72.7, 245, -22.5); //1
    glVertex3f(-77.7, 245, -22.5); //4
    glVertex3f(-77.7, 180, -22.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, 17.5); //8
    glVertex3f(-72.7, 245, 17.5); //1
    glVertex3f(-77.7, 245, 17.5); //4
    glVertex3f(-77.7, 180, 17.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, -17.5); //8
    glVertex3f(-72.7, 245, -17.5); //1
    glVertex3f(-77.7, 245, -17.5); //4
    glVertex3f(-77.7, 180, -17.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 240, 22.5); //8
    glVertex3f(-72.7, 245, 22.5); //1
    glVertex3f(-72.7, 245, -22.5); //4
    glVertex3f(-72.7, 240, -22.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 245, 22.5); //8
    glVertex3f(-77.7, 245, 22.5); //1
    glVertex3f(-77.7, 245, -22.5); //4
    glVertex3f(-72.7, 245, -22.5); //5
    glEnd();
    //
    //


    glBegin(GL_POLYGON); //sisi1
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-77.6, 180, -17.5); //8
    glVertex3f(-77.6, 240, -17.5); //1
    glVertex3f(-77.6, 240, 17.5); //4
    glVertex3f(-77.6, 180, 17.5); //5
    glEnd();

    glPopMatrix();

    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(0,235,140);
    glRotatef(270, 0, 10, 0);
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-77.7, 180, -22.5); //8
    glVertex3f(-77.7, 245, -22.5); //1
    glVertex3f(-77.7, 245, 22.5); //4
    glVertex3f(-77.7, 180, 22.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, -22.5); //8
    glVertex3f(-72.7, 245, -22.5); //1
    glVertex3f(-72.7, 245, -17.5); //4
    glVertex3f(-72.7, 180, -17.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, 22.5); //8
    glVertex3f(-72.7, 245, 22.5); //1
    glVertex3f(-72.7, 245, 17.5); //4
    glVertex3f(-72.7, 180, 17.5); //5
    glEnd();

    //
    //
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, 22.5); //8
    glVertex3f(-72.7, 245, 22.5); //1
    glVertex3f(-77.7, 245, 22.5); //4
    glVertex3f(-77.7, 180, 22.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, -22.5); //8
    glVertex3f(-72.7, 245, -22.5); //1
    glVertex3f(-77.7, 245, -22.5); //4
    glVertex3f(-77.7, 180, -22.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, 17.5); //8
    glVertex3f(-72.7, 245, 17.5); //1
    glVertex3f(-77.7, 245, 17.5); //4
    glVertex3f(-77.7, 180, 17.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, -17.5); //8
    glVertex3f(-72.7, 245, -17.5); //1
    glVertex3f(-77.7, 245, -17.5); //4
    glVertex3f(-77.7, 180, -17.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 240, 22.5); //8
    glVertex3f(-72.7, 245, 22.5); //1
    glVertex3f(-72.7, 245, -22.5); //4
    glVertex3f(-72.7, 240, -22.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 245, 22.5); //8
    glVertex3f(-77.7, 245, 22.5); //1
    glVertex3f(-77.7, 245, -22.5); //4
    glVertex3f(-72.7, 245, -22.5); //5
    glEnd();
    //
    //


    glBegin(GL_POLYGON); //sisi1
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-77.6, 180, -17.5); //8
    glVertex3f(-77.6, 240, -17.5); //1
    glVertex3f(-77.6, 240, 17.5); //4
    glVertex3f(-77.6, 180, 17.5); //5
    glEnd();

    glPopMatrix();

    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(-140,235,0);
    glRotatef(180, 0, 10, 0);
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-77.7, 180, -22.5); //8
    glVertex3f(-77.7, 245, -22.5); //1
    glVertex3f(-77.7, 245, 22.5); //4
    glVertex3f(-77.7, 180, 22.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, -22.5); //8
    glVertex3f(-72.7, 245, -22.5); //1
    glVertex3f(-72.7, 245, -17.5); //4
    glVertex3f(-72.7, 180, -17.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, 22.5); //8
    glVertex3f(-72.7, 245, 22.5); //1
    glVertex3f(-72.7, 245, 17.5); //4
    glVertex3f(-72.7, 180, 17.5); //5
    glEnd();

    //
    //
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, 22.5); //8
    glVertex3f(-72.7, 245, 22.5); //1
    glVertex3f(-77.7, 245, 22.5); //4
    glVertex3f(-77.7, 180, 22.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, -22.5); //8
    glVertex3f(-72.7, 245, -22.5); //1
    glVertex3f(-77.7, 245, -22.5); //4
    glVertex3f(-77.7, 180, -22.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, 17.5); //8
    glVertex3f(-72.7, 245, 17.5); //1
    glVertex3f(-77.7, 245, 17.5); //4
    glVertex3f(-77.7, 180, 17.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 180, -17.5); //8
    glVertex3f(-72.7, 245, -17.5); //1
    glVertex3f(-77.7, 245, -17.5); //4
    glVertex3f(-77.7, 180, -17.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 240, 22.5); //8
    glVertex3f(-72.7, 245, 22.5); //1
    glVertex3f(-72.7, 245, -22.5); //4
    glVertex3f(-72.7, 240, -22.5); //5
    glEnd();
    glBegin(GL_POLYGON); //sisi1
    glVertex3f(-72.7, 245, 22.5); //8
    glVertex3f(-77.7, 245, 22.5); //1
    glVertex3f(-77.7, 245, -22.5); //4
    glVertex3f(-72.7, 245, -22.5); //5
    glEnd();
    //
    //


    glBegin(GL_POLYGON); //sisi1
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-77.6, 180, -17.5); //8
    glVertex3f(-77.6, 240, -17.5); //1
    glVertex3f(-77.6, 240, 17.5); //4
    glVertex3f(-77.6, 180, 17.5); //5
    glEnd();

    glPopMatrix();
}


void garis_garis_1() {

    //tambahan kanan

    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(85, -55, -45);
    glRotatef(-90, 18, 0, 0);
    gluCylinder(gluNewQuadric(), 4, 4, 230, 32, 100);
    glEnd();
    glPopMatrix();

    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(85, -55, -15);
    glRotatef(-90, 18, 0, 0);
    gluCylinder(gluNewQuadric(), 4, 4, 230, 32, 100);
    glEnd();
    glPopMatrix();

    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(85, -55, 15);
    glRotatef(-90, 18, 0, 0);
    gluCylinder(gluNewQuadric(), 4, 4, 230, 32, 100);
    glEnd();
    glPopMatrix();

    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(85, -55, 45);
    glRotatef(-90, 18, 0, 0);
    gluCylinder(gluNewQuadric(), 4, 4, 230, 32, 100);
    glEnd();
    glPopMatrix();

    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(85, 115, -85);
    glRotatef(0, 18, 0, 0);
    gluCylinder(gluNewQuadric(), 4, 4, 160, 32, 100);
    glEnd();
    glPopMatrix();

    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(85, 65, -85);
    glRotatef(0, 18, 0, 0);
    gluCylinder(gluNewQuadric(), 4, 4, 160, 32, 100);
    glEnd();
    glPopMatrix();

    //tambahan kiri
    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(-85, -55, -45);
    glRotatef(-90, 18, 0, 0);
    gluCylinder(gluNewQuadric(), 4, 4, 230, 32, 100);
    glEnd();
    glPopMatrix();

    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(-85, -55, -15);
    glRotatef(-90, 18, 0, 0);
    gluCylinder(gluNewQuadric(), 4, 4, 230, 32, 100);
    glEnd();
    glPopMatrix();

    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(-85, -55, 15);
    glRotatef(-90, 18, 0, 0);
    gluCylinder(gluNewQuadric(), 4, 4, 230, 32, 100);
    glEnd();
    glPopMatrix();

    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(-85, -55, 45);
    glRotatef(-90, 18, 0, 0);
    gluCylinder(gluNewQuadric(), 4, 4, 230, 32, 100);
    glEnd();
    glPopMatrix();

    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(-85, 115, -85);
    glRotatef(0, 18, 0, 0);
    gluCylinder(gluNewQuadric(), 4, 4, 160, 32, 100);
    glEnd();
    glPopMatrix();

    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(-85, 65, -85);
    glRotatef(0, 18, 0, 0);
    gluCylinder(gluNewQuadric(), 4, 4, 160, 32, 100);
    glEnd();
    glPopMatrix();

    //depan
    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(45, -60, 85);
    glRotatef(-90, 18, 0, 0);
    gluCylinder(gluNewQuadric(), 4, 4, 230, 32, 100);
    glEnd();
    glPopMatrix();

    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(15, -60, 85);
    glRotatef(-90, 18, 0, 0);
    gluCylinder(gluNewQuadric(), 4, 4, 230, 32, 100);
    glEnd();
    glPopMatrix();

    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(-15, -60, 85);
    glRotatef(-90, 18, 0, 0);
    gluCylinder(gluNewQuadric(), 4, 4, 230, 32, 100);
    glEnd();
    glPopMatrix();

    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(-45, -60, 85);
    glRotatef(-90, 18, 0, 0);
    gluCylinder(gluNewQuadric(), 4, 4, 230, 32, 100);
    glEnd();
    glPopMatrix();

    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(-80, 115, 85);
    glRotatef(90, 0, 10, 0);
    gluCylinder(gluNewQuadric(), 4, 4, 160, 32, 100);
    glEnd();
    glPopMatrix();

    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(-80, 65, 85);
    glRotatef(90, 0, 10, 0);
    gluCylinder(gluNewQuadric(), 4, 4, 160, 32, 100);
    glEnd();
    glPopMatrix();
    //belakang
    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(45, -60, -85);
    glRotatef(-90, 18, 0, 0);
    gluCylinder(gluNewQuadric(), 4, 4, 230, 32, 100);
    glEnd();
    glPopMatrix();


    glColor3ub(237, 91, 23);
    glPushMatrix();
    glTranslatef(-45, -60, -85);
    glRotatef(-90, 18, 0, 0);
    gluCylinder(gluNewQuadric(), 4, 4, 230, 32, 100);
    glEnd();
    glPopMatrix();
    //Detail Bangun 2
}

void draw() {
    // Mulai tuliskan isi pikiranmu disini
    lantai1();
    pintu3();
    garis_garis_1();
    pagar_floor3();
    bangun_lantai1();
    pintu2();
    lantai2();
    bangun_lantai2();
    atap1();
    lantai3();
    atap2();
    floor3();
    bangun_lantai4();
    atas_bangun4();
    atap_ujung();
    pilar();
    kotak_atap();
    tangga();
    pagar1();
    pagar_lantai2();
    pagar_lantai3();
    pohon();
    gerbang();
    bulat();
    sudut1();
    pintu();
    ground();
  
    //glTranslatef(x_geser, y_geser, z_geser);
    cout << " X_GESER = " << x_geser << "   Y_GESER = " << y_geser << " Z_GESER = " << z_geser << endl;
    glFlush();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    camera();
    draw();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50, 16.0 / 9.0, 2, 10000);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int) {
    glutPostRedisplay();
    glutWarpPointer(width / 2, height / 2);
    glutTimerFunc(1000 / FPS, timer, 0);
}

void passive_motion(int x, int y) {
    int dev_x, dev_y;
    dev_x = (width / 2) - x;
    dev_y = (height / 2) - y;
    yaw += (float)dev_x / 20.0;
    pitch += (float)dev_y / 20.0;
}

void camera() {
    if (motion.Forward) {
        camX += cos((yaw + 90) * TO_RADIANS) * 2;
        camZ -= sin((yaw + 90) * TO_RADIANS) * 2;
    }
    if (motion.Backward) {
        camX += cos((yaw + 90 + 180) * TO_RADIANS) * 2;
        camZ -= sin((yaw + 90 + 180) * TO_RADIANS) * 2;
    }
    if (motion.Left) {
        camX += cos((yaw + 90 + 90) * TO_RADIANS) * 2;
        camZ -= sin((yaw + 90 + 90) * TO_RADIANS) * 2;
    }
    if (motion.Right) {
        camX += cos((yaw + 90 - 90) * TO_RADIANS) * 2;
        camZ -= sin((yaw + 90 - 90) * TO_RADIANS) * 2;
    }
    if (motion.Naik) {
        terbang -= 2.0;
    }
    if (motion.Turun) {
        terbang += 2.0;
    }

    if (pitch >= 70)
        pitch = 70;
    if (pitch <= -90)
        pitch = -90;


    glRotatef(-pitch, 1.0, 0.0, 0.0);
    glRotatef(-yaw, 0.0, 1.0, 0.0);

    glTranslatef(-camX, -terbang, -350 - camZ);
    if (terbang < 25)
        terbang = 24;
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'W':
    case 'w':
        motion.Forward = true;
        break;
    case 'A':
    case 'a':
        motion.Left = true;
        break;
    case 'S':
    case 's':
        motion.Backward = true;
        break;
    case 'D':
    case 'd':
        motion.Right = true;
        break;
    case 'E':
    case 'e':
        motion.Naik = true;
        break;
    case 'Q':
    case 'q':
        motion.Turun = true;
        break;
    case '6':
        x_geser += 0.5;
        break;
    case '4':
        x_geser -= 0.5;
        break;
    case '8':
        y_geser += 0.5;
        break;
    case '2':
        y_geser -= 0.5;
        break;
    case '9':
        z_geser -= 0.5;
        break;
    case '1':
        z_geser += 0.5;
        break;
    case 'p':
        y_geser += 5.0;
        break;
    case 'o':
        y_geser -= 5.0;
        break;
    case '=':
        x_geser += 5.0;
        break;
    case '-':
        x_geser -= 5.0;
        break;
    case 'l':
        z_geser -= 5.0;
        break;
    case 'k':
        z_geser += 5.0;
        break;
    case '`': // KELUAR DARI PROGRAM
        exit(1);
    }
}

void keyboard_up(unsigned char key, int x, int y) {
    switch (key) {
    case 'W':
    case 'w':
        motion.Forward = false;
        break;
    case 'A':
    case 'a':
        motion.Left = false;
        break;
    case 'S':
    case 's':
        motion.Backward = false;
        break;
    case 'D':
    case 'd':
        motion.Right = false;
        break;
    case 'E':
    case 'e':
        motion.Naik = false;
        break;
    case 'Q':
    case 'q':
        motion.Turun = false;
        break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("TR GRAFKOM KELOMPOK X");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutPassiveMotionFunc(passive_motion);
    glutTimerFunc(0, timer, 0);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboard_up);

    glutMainLoop();
    return 0;
}