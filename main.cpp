#include <QApplication>
#include "gui.h"
#include <GL/glut.h>
int main(int argc, char * argv[])
{
  QApplication app(argc,argv);
  glutInit(&argc,argv);
  CGui * gui = new CGui(NULL);
  app.exec();

}
