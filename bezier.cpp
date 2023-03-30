#include<windows.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include<iostream>
using namespace std;
#include<vector>
#include<math.h>

static int flag=1;
void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480);
    glClearColor(0,0,0,0.5);
}

class Point
{
public:
    float x;
    float y;
};

void plot(Point p)
{
    glColor3d(1,1,1);
    glBegin(GL_POINTS);
    glVertex2d(p.x,p.y);
    glEnd();
    glFlush();
}



void bezierCurve(vector<Point> p)
{
    vector<Point> pts;
    double xt=0.0,yt=0.0,t=0.1;
    while(t<=1)
    {
        Point pt;
        xt=pow((1-t),3)*p[0].x+3*(pow((1-t),2))*t*p[1].x+3*(1-t)*pow(t,2)*p[2].x+pow(t,3)*p[3].x;
        yt=pow((1-t),3)*p[0].y+3*(pow((1-t),2))*t*p[1].y+3*(1-t)*pow(t,2)*p[2].y+pow(t,3)*p[3].y;
        pt.x=xt;
        pt.y=yt;
        pts.push_back(pt);
        t+=0.1;
    }

    glBegin(GL_LINE_STRIP);

    for(int i=0;i<pts.size();i++)
    {
        glVertex2d(pts[i].x,pts[i].y);
    }
    glEnd();
    glFlush();

}

vector<Point> poly;
void mousePt(int button,int state,int mx,int my)
{

    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        Point pt;
        pt.x=mx;
        pt.y=480-my;
        plot(pt);
        poly.push_back(pt);


    }
    else if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
    {
        bezierCurve(poly);
        poly.clear();
        cout<<poly[0].x<<" "<<poly[0].y<<endl;
    }

}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0,0,0,1);
    glFlush();
}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

    glutCreateWindow("GLUT Shapes");

    glutDisplayFunc(display);
    glutMouseFunc(mousePt);
    glutDisplayFunc(display);
    init();
    glutMainLoop();

    return EXIT_SUCCESS;
}
