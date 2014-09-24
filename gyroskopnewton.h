#ifndef GYROSKOPNEWTON_H
#define GYROSKOPNEWTON_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
class CGyroskopNewton
{
public:
  CGyroskopNewton();
  ~CGyroskopNewton();
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
  void setDPsi(double val);
//   
  
private:
  char message[160];
  struct df_t{
    double phi,theta,psi;
    double w1,w2,w3;
  }df;//degrees of freedom
  
  struct param_t{
    double I,J,r,m,g;
  }param;
  double time;
  
  GLUquadricObj *quadratic;
  
};

#endif // GYROSKOPNEWTON_H
