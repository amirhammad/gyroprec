#include "glw.h"
#include <QWidget>
#include <QGLWidget>
#include <GL/glut.h>
#include <GL/glu.h>
#include <QTimer>
#include <math.h>
#include <QMouseEvent>
#include <stdio.h>
CGlw::CGlw(QWidget *parent): QGLWidget(QGLFormat(QGL::DoubleBuffer), parent)
{
  makeCurrent();
  setMinimumSize(500, 500);
  setAutoFillBackground(false);
  setMouseTracking(true);
   
  //setup refresh timer
  connect(&refreshTimer,SIGNAL(timeout()), this, SLOT(refresh()));
  refreshTimer.setSingleShot(false);
  refreshTimer.setInterval(16);
  refreshTimer.start();
  
  //init variables
  rotation = 0;
  mouseMove.active=0;
  mouseMove.zoom=0;
  //showFullScreen();
  show();
  
  
}
void CGlw::initializeGL()
{
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
  glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
  qglClearColor(Qt::black);
}

void CGlw::paintGL()
{
  
  makeCurrent();
  
  glMatrixMode(GL_MODELVIEW);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  
  // rendering
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glTranslatef(0,0,-300+mouseMove.zoom);
  
  glRotatef(mouseMove.rotation[1]*1,1,0,0); 
  glRotatef(mouseMove.rotation[0]*1,0,1,0);
  

  glMatrixMode(GL_MODELVIEW);
  //coords
  glPushMatrix();
  glLineWidth(4);
  glScalef(10,10,10);
    glBegin(GL_LINES);
    glColor3f(1,0,0);//red
    glVertex3f(0,0,0);
    glVertex3f(1,0,0);
    glColor3f(0,1,0);
    glVertex3f(0,0,0);
    glVertex3f(0,1,0);
    glColor3f(0,0,1);
    glVertex3f(0,0,0);
    glVertex3f(0,0,1);
    glEnd();
  
  glPopMatrix();
  
  //CUBE 1
  glPushMatrix();
    glTranslatef(10,0,0);
    glRotatef(rotation, 0, 1, 0);
    
    glColor3f(0,0.5,0.3);
    glutSolidCube(0.5);
  glPopMatrix();
  //CUBE 2
  glPushMatrix();
    glTranslatef(0,10,0);
    glRotatef(rotation, 0, 1, 0);
    
    
    glColor3f(0,0.2,0.8);
    glutSolidCube(0.5);
  glPopMatrix();
  //CUBE 3
  glPushMatrix();
    glTranslatef(0,0,10);
    glRotatef(rotation, 0, 1, 0);
    
    
    glColor3f(1,0,1);
    glutSolidCube(0.5);
  glPopMatrix();
  
  glScalef(0.1,0.1,0.1);
  gyroDraw();
   
  
}
void CGlw::resizeGL(int width, int height)
{
  int side = qMin(width, height);
  glViewport((width - side) / 2, (height - side) / 2, side, side);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  
  glFrustum(-1,1,-1,1,30,10000);

  glMatrixMode(GL_MODELVIEW);
  
}
QSize CGlw::sizeHint() const
{
  return QSize(800,800);
}


void CGlw::refresh()
{
  static int k=0;
  rotation += 4;
    getMessage();
  int i,n=100000;
  for(i=0;i<n;i++)
  {
    updateEq(0.016/n);
  }
  emit newDataAvailable();
  
      //printf("%1.2f \n",(++k)*0.016);
      //fflush(stdout);
  updateGL();
}

void CGlw::mouseMoveEvent(QMouseEvent * event)
{
  if(event->buttons()&(Qt::LeftButton|Qt::NoButton))
  {
    if(mouseMove.active)
    {
      mouseMove.rotation[0] -= mouseMove.X - event->x();
      mouseMove.rotation[1] -= mouseMove.Y - event->y();
      mouseMove.X = event->x();
      mouseMove.Y = event->y();
    }
  }
}

void CGlw::mousePressEvent(QMouseEvent * event)
{
  if(event->buttons()&Qt::RightButton)
  {
    mouseMove.rotation[0] = 0;
    mouseMove.rotation[1] = 0;
    mouseMove.X=0;
    mouseMove.Y=0;
  }
  if(event->buttons()&Qt::LeftButton)
  {
    mouseMove.X = event->x();
    mouseMove.Y = event->y();
    mouseMove.active = 1;
  }
}
void CGlw::wheelEvent(QWheelEvent * event)
{
  mouseMove.zoom += 0.1*event->delta();
}

void CGlw::mouseReleaseEvent(QMouseEvent * event)
{
  mouseMove.active = 0;
}
void CGlw::keyPressEvent(QKeyEvent*event)
{
  if(event->key()==Qt::Key_Escape)
  {
    close();
    event->accept();
  }
}

void CGlw::speedSliderValueChangedSlot(int val)
{
  setDPsi(val);
}
