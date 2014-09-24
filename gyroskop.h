#ifndef GYROSKOP_H
#define GYROSKOP_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
class CGyroskop
{
public:
  CGyroskop();
  ~CGyroskop();
  //void set(double aPhi,double aTheta, double aPsi,double aW1, double aW2, double aW3);
  void setDefaultDF();
  int updateEq(double dT);
  void gyroDraw();
  char * getMessage();
  double getPhi();
  double getTheta();
  double getPsi();
  
  double getDPhi();
  double getDTheta();
  double getDPsi();
  
  
private:
  char message[160];
  struct df_t{
    double phi,theta,psi;
    double dPhi,dTheta,dPsi;
  }df;//degrees of freedom
  
  struct param_t{
    double I,J,r,m,g;
  }param;
  double time;
  
  GLUquadricObj *quadratic;
};

#endif // GYROSKOP_H
