#include "gyroskop.h"
#include <stdio.h>
#include <cmath>
CGyroskop::CGyroskop()
{
  quadratic = gluNewQuadric();          // Create A Pointer To The Quadric Object ( NEW )
  gluQuadricNormals(quadratic, GLU_SMOOTH);   // Create Smooth Normals ( NEW )
  gluQuadricTexture(quadratic, GL_TRUE);  
  param.g=9.81;	//m*s^(-2)
  param.m=0.1;	//Kg
  param.r=0.1;	//m

  param.I=9+param.m*param.r*param.r;
  param.J=0.1;

  
  setDefaultDF();
  time=0;
};

CGyroskop::~CGyroskop()
{
  gluDeleteQuadric(quadratic);
}

void CGyroskop::setDefaultDF()
{
  df.phi =M_PI/4 ;
  df.theta = M_PI/3;
  df.psi = 1;
  df.dPhi = 0;
  df.dTheta = 0;
  df.dPsi = -100;
}


void CGyroskop::gyroDraw()
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

    glColor3f(1,1,1);
    gluCylinder(quadratic, 10, 10, 2, 40, 5);
    
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

// void CGyroskop::update(double dT)
// {
//   struct df_t dfnew;
//   dfnew.w1 = df.w1 + dT*(param.r*param.m*param.g*sin(df.theta)*sin(df.psi) - df.w2*df.w3*(param.J-param.I))/param.I;
//   dfnew.w2 = df.w2 + dT*(param.r*param.m*param.g*sin(df.theta)*cos(df.psi) - df.w1*df.w3*(param.I-param.J))/param.I;
//   dfnew.w3 = df.w3 + dT*(-df.w1*df.w2*(param.I-param.J))/param.J;
//   dfnew.phi = df.phi + dT*(-df.w1*cos(df.psi)+df.w2*sin(df.psi))/sin(df.theta);
//   dfnew.theta = df.theta + dT*(df.w1*sin(df.psi)+df.w2*cos(df.psi));
//   dfnew.psi = df.psi + dT*(df.w3-(cos(df.theta)/sin(df.theta))*(-df.w1*cos(df.psi)+df.w2*sin(df.psi)));
//   df = dfnew;
// }w1->dPhi,w2->dTheta,w3->dPsi
inline double sqr(double a)
{
  return a*a;
}
int CGyroskop::updateEq(double dT)
{
  struct df_t dfnew;
  double diff;
  
  //! d/dt dPhi
  diff = param.J/(param.I*sin(df.theta))*(df.dTheta*df.dPsi+df.dTheta*df.dPhi)-2*cos(df.theta)/sin(df.theta)*(df.dTheta*df.dPhi);  
  //! check for NAN
  if(diff != diff || std::isinf(diff))
  {
    diff=0;
    return -1;
  }
  else if(fabs(diff)>1000.0)
    printf("%f (1): %f\n",time,diff);
  fflush(stdout);
  
  dfnew.dPhi = df.dPhi + dT*diff;	//! Euler Integration
  //! d/dt Phi
  diff = df.dPhi;
  dfnew.phi = df.phi + dT*diff;		//! Euler Integration
  
  //! d/dt dTheta
  diff = (param.I-param.J)/param.I*sin(df.theta)*cos(df.theta)*sqr(df.dPhi) + param.J/param.I*sin(df.theta)*(df.dPhi*df.dPsi) + 1/param.I*param.m*param.g*param.r*sin(df.theta);
    //! check for NAN
  if(diff != diff || std::isinf(diff))
  {
    diff=0;
    return -1;
  }
  else if(fabs(diff)>1000.0)
    printf("%f (2): %f\n",time,diff);
  fflush(stdout);
  dfnew.dTheta = df.dTheta + dT*diff;	//! Euler Integration
  //! d/dt theta
  diff = df.dTheta;
  dfnew.theta = df.theta + dT*diff;	//! Euler Integration
  
  
  //! d/dt dPsi
  diff = (2*sqr(cos(df.theta))/sin(df.theta) - (param.J/param.I)*cos(df.theta)/sin(df.theta) - sin(df.theta))*(df.dTheta*df.dPhi)
  - (param.J/param.I)*cos(df.theta)/sin(df.theta)*(df.dTheta*df.dPsi);
  //! check for NAN
  if(diff != diff || std::isinf(diff))
  {
    diff=0;
    return -1;
  }
  else   if(fabs(diff)>1000.0)
    printf("%f (3): %f\n",time,diff);
  fflush(stdout);
  dfnew.dPsi = df.dPsi + dT*diff;	//! Euler Integration
  //! d/dt psi
  diff = df.dPsi;
  dfnew.psi = df.psi + dT*diff;		//! Euler Integration
  
  //! finalize
  df = dfnew;
  time+=dT;
  return 0;
}

// void CGyroskop::set(double aPhi, double aTheta, double aPsi, double aDPhi, double aDTheta, double aDPsi)
// {
//   df.phi = aPhi;
//   df.theta = aTheta;
//   df.psi = aPsi;
//   df.dPhi = aDPhi;
//   df.dTheta = aDTheta;
//   df.dPsi = aDPsi;
// }



char * CGyroskop::getMessage()
{
  sprintf(message, "%5.4f\t%5.4f\t%5.4f\t|\t%5.4f\t%5.4f\t%5.4f\n",df.phi,df.theta,df.psi,df.dPhi,df.dTheta,df.dPsi);
  return message;
}



double CGyroskop::getPhi()
{
  return df.phi;
}
double CGyroskop::getTheta()
{
  return df.theta;
}
double CGyroskop::getPsi()
{
  return df.psi;
}

double CGyroskop::getDPhi()
{
  return df.dPhi;
}
double CGyroskop::getDTheta()
{
  return df.dTheta;
}
double CGyroskop::getDPsi()
{
  return df.dPsi;
}



