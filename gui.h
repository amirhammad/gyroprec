#ifndef GUI_H
#define GUI_H
#include <QWidget>
#include <QTextEdit>
#include <QLabel>
#include <QSlider>
#include "glw.h"
class CGui:public QWidget
{
  Q_OBJECT
public:
  CGui(QWidget * parent);
private slots:
  void updateValues();
  void speedSliderValueChangedSlot(int val);
private:
  CGlw *glw;
  QTextEdit *textPhi;
  QTextEdit *textTheta;
  QTextEdit *textPsi;
  QTextEdit *textDPhi;
  QTextEdit *textDTheta;
  QTextEdit *textDPsi;
  
  QLabel *labelPhi;
  QLabel *labelTheta;
  QLabel *labelPsi;
  QLabel *labelDPhi;
  QLabel *labelDTheta;
  QLabel *labelDPsi;
  
  QSlider * speedSlider;
  QTextEdit * speedEdit;
};

#endif // GUI_H
