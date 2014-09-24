#include "gui.h"
#include <QGridLayout>
#include <QLabel>
#include <QTextEdit>
#include <QString>
#include <QSlider>
CGui::CGui(QWidget * parent): QWidget(parent)
{
  setMinimumWidth(600);
  setMinimumHeight(600);
  glw = new CGlw(this);
  QGridLayout * layout = new QGridLayout(this);
  QGridLayout * layout2 = new QGridLayout();
  QVBoxLayout * vertLayout = new QVBoxLayout();
  layout->addWidget(glw,1,1);
  
  //! Phi
  labelPhi = new QLabel(this);
  labelPhi->setText("Phi:");
  layout2->addWidget(labelPhi,1,1);
  textPhi = new QTextEdit(this);
  textPhi->setEnabled(false); 
  layout2->addWidget(textPhi,1,2);
  
  //! Theta
  labelTheta = new QLabel(this);
  labelTheta->setText("Theta:");
  layout2->addWidget(labelTheta,2,1);
  textTheta = new QTextEdit(this);
  textTheta->setEnabled(false); 
  layout2->addWidget(textTheta,2,2);
  
  //! Psi
  labelPsi = new QLabel(this);
  labelPsi->setText("Psi:");
  layout2->addWidget(labelPsi,3,1);
  textPsi = new QTextEdit(this);
  textPsi->setEnabled(false); 
  layout2->addWidget(textPsi,3,2);
  
  //!dPhi
  labelDPhi = new QLabel(this);
  labelDPhi->setText("d/dt Phi:");
  layout2->addWidget(labelDPhi,4,1);
  textDPhi = new QTextEdit(this);
  textDPhi->setEnabled(false); 
  layout2->addWidget(textDPhi,4,2);
  
  //! dTheta
  labelDTheta = new QLabel(this);
  labelDTheta->setText("d/dt Theta:");
  layout2->addWidget(labelDTheta,5,1);
  textDTheta = new QTextEdit(this);
  textDTheta->setEnabled(false); 
  layout2->addWidget(textDTheta,5,2);
  
  //! DPsi
  labelDPsi = new QLabel(this);
  labelDPsi->setText("d/dt Psi:");
  layout2->addWidget(labelDPsi,6,1);
  textDPsi = new QTextEdit(this);
  textDPsi->setEnabled(false); 
  layout2->addWidget(textDPsi,6,2);
 
  //!	speed
  speedSlider = new QSlider(Qt::Horizontal);
  connect(speedSlider,SIGNAL(valueChanged(int)),this,SLOT(speedSliderValueChangedSlot(int)));
  //! 	speed TEXT
  speedEdit=new QTextEdit(this);
  speedEdit->setEnabled(false); 
  
  
  
  
  layout->setColumnStretch(1,1);
  vertLayout->addLayout(layout2,1);
  vertLayout->addWidget(speedSlider,2);
  vertLayout->addWidget(speedEdit,3);
  vertLayout->addStretch(1);
  layout->addLayout(vertLayout,1,2);
  connect(glw,SIGNAL(newDataAvailable()),this,SLOT(updateValues()));
  show();
}
void CGui::updateValues()
{
  textPhi->setText(QString::number(glw->getPhi()*180.0/M_PI));
  textTheta->setText(QString::number(glw->getTheta()*180.0/M_PI));
  textPsi->setText(QString::number(glw->getPsi()*180.0/M_PI));
  
  textDPhi->setText(QString::number(glw->getDPhi()*180.0/M_PI));
  textDTheta->setText(QString::number(glw->getDTheta()*180.0/M_PI));
  textDPsi->setText(QString::number(glw->getDPsi()*180.0/M_PI));
}


void CGui::speedSliderValueChangedSlot(int val)
{
  double valinrad;
  const int range = 2000;
  valinrad = static_cast<double>(val);
  valinrad = (valinrad+0.5)/100.0*range*2;
  valinrad -= range;
  glw->setDPsi(valinrad);
  speedEdit->setText(QString::number(valinrad));
  
}
