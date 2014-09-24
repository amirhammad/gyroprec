#ifndef CSEGWAY_H
#define CSEGWAY_H
#include <QWidget>
#include <QGLWidget>
#include <QTimer>
#include <QMouseEvent>
#include "gyroskop.h"
#include "gyroskopnewton.h"
class CGlw:public QGLWidget,public CGyroskopNewton
{
  Q_OBJECT
public:
  CGlw(QWidget * parent);
  QSize sizeHint() const;
signals:
  void newDataAvailable();

private:
  void initializeGL();
  void paintGL();
  void resizeGL(int width, int height);
  QTimer refreshTimer;
  float rotation;
  class CMouseMove{
    public: 
      float X,Y;
      float rotation[2];
      int active;
      int zoom;
  }mouseMove;
  void mouseMoveEvent(QMouseEvent * event);
  void mousePressEvent(QMouseEvent * event);
  void mouseReleaseEvent(QMouseEvent * event);
  void wheelEvent(QWheelEvent * event);
  void keyPressEvent(QKeyEvent*event);
public:
  void speedSliderValueChangedSlot(int val);
private slots:
  void refresh();
  
};

#endif // CSEGWAY_H
