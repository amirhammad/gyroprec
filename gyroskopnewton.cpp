#include "gyroskopnewton.h"

#include "gyroskopnewton.h"
#include <stdio.h>
#include <cmath>
CGyroskopNewton::CGyroskopNewton()
{
  quadratic = gluNewQuadric();          // Create A Pointer To The Quadric Object ( NEW )
  gluQuadricNormals(quadratic, GLU_SMOOTH);   // Create Smooth Normals ( NEW )
  gluQuadricTexture(quadratic, GL_TRUE);  
  param.g=9.81;	//m*s^(-2)
  param.m=10;	//Kg
  param.r=0.5;	//m

  param.I=0.9;
  param.J=0.2;

  
  setDefaultDF();
  time=0;
};

CGyroskopNewton::~CGyroskopNewton()
{
  gluDeleteQuadric(quadratic);
}

void CGyroskopNewton::setDefaultDF()
{
  df.phi =M_PI/4 ;
  df.theta = 0.1;
  df.psi = 1;
  df.w1 = 0;
  df.w2 = 0;
  df.w3 = 100;
}



void CGyroskopNewton::gyroDraw()
{
  
   glPushMatrix();
   
   
   glRotatef(-90,1,0,0);
   glRotatef(-180,0,0,1); 
    //! rotate by phi

    glRotated(df.phi*180/M_PI,0,0,1);
    //! rotate by theta

    glRotated(df.theta*180/M_PI,0,1,0);
    
    glColor3f(1,0,0);
    gluCylinder(quadratic, 1, 1, param.r*40, 40, 5);
    glTranslatef(0,0,param.r*40);
    
    //! rotate by psi
    glRotated(df.psi*180.0/M_PI,0,0,1);

    glColor3f(1,0,1);
    gluCylinder(quadratic, 10, 10, 2, 40, 5);
    glColor3f(1,1,1);
    glTranslatef(0,0,2);
    gluDisk(quadratic,0,10,40,10);
    glPushMatrix();
      
      glTranslatef(0,0,0.001);
      glColor3f(1,0,0);
      glBegin(GL_TRIANGLES);
	glVertex3f(0,0,0);
	glVertex3f(1,5,0);
	glVertex3f(0,sqrt(26),0);
      glEnd();
      
      glColor3f(0.7,0,0.3);
      glTranslatef(0,0,-2.002);
      glBegin(GL_TRIANGLES);
	glNormal3f(0,0,-1);
	glVertex3f(0,0,0);
	glVertex3f(0,sqrt(26),0);
	glVertex3f(1,5,0);

      glEnd();
      
    glPopMatrix();
    
    glColor3f(1,1,1);
    glRotatef(180,1,0,0);
    glTranslatef(0,0,2);
    gluDisk(quadratic,0,10,40,10);
  glPopMatrix();
  
 
}

inline double sqr(double a)
{
  return a*a;
}
int CGyroskopNewton::updateEq(double dT)
{
  struct df_t dfnew;
  dfnew.w1 = df.w1 + dT*(param.r*param.m*param.g*sin(df.theta)*sin(df.psi) - df.w2*df.w3*(param.J-param.I))/param.I;
  dfnew.w2 = df.w2 + dT*(param.r*param.m*param.g*sin(df.theta)*cos(df.psi) - df.w1*df.w3*(param.I-param.J))/param.I;
  dfnew.w3 = df.w3 + dT*((-df.w1*df.w2*(param.I-param.J))/param.J);
  dfnew.phi = df.phi + dT*(-df.w1*cos(df.psi)+df.w2*sin(df.psi))/sin(df.theta);
  dfnew.theta = df.theta + dT*(df.w1*sin(df.psi)+df.w2*cos(df.psi));
  //dfnew.psi = df.psi + dT*(df.w3-(cos(df.theta)/sin(df.theta))*(-df.w1*cos(df.psi)+df.w2*sin(df.psi)));
  dfnew.psi = df.psi + dT*(df.w3-(1/tan(df.theta))*(-df.w1*cos(df.psi)+df.w2*sin(df.psi)) ) ;
  df = dfnew;
}

char * CGyroskopNewton::getMessage()
{
//   sprintf(message, "%5.4f\t%5.4f\t%5.4f\t|\t%5.4f\t%5.4f\t%5.4f\n",df.phi,df.theta,df.psi,df.dPhi,df.dTheta,df.dPsi);
  return message;
}



double CGyroskopNewton::getPhi()
{
  return df.phi;
}
double CGyroskopNewton::getTheta()
{
  return df.theta;
}
double CGyroskopNewton::getPsi()
{
  return df.psi;
}

double CGyroskopNewton::getDPhi()
{
  return df.w1;
}
double CGyroskopNewton::getDTheta()
{
  return df.w2;
}
double CGyroskopNewton::getDPsi()
{
  return df.w3;
}
void CGyroskopNewton::setDPsi(double val)
{
    df.w3=val;
}


