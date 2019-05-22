#include "resizewidget.h"

#include "QVBoxLayout"
#include "QPushButton"


ResizeWidget::ResizeWidget(QWidget *parent) : QWidget(parent)
{

  QPushButton* LeftStepButton = new QPushButton("<",this);
  LeftStepButton->setFlat(true);

  QPushButton* AllLeftStepsButton = new QPushButton("<<" ,this);
  AllLeftStepsButton->setFlat(true);

  QPushButton* RightStepButton = new QPushButton(">",this);
  RightStepButton->setFlat(true);

  QPushButton* AllRightStepsButton = new QPushButton(">>" ,this);
  AllRightStepsButton->setFlat(true);

  QVBoxLayout* Layout = new QVBoxLayout(this);
  Layout->addWidget(LeftStepButton);
  Layout->addWidget(AllLeftStepsButton);
  Layout->addWidget(RightStepButton);
  Layout->addWidget(AllRightStepsButton);

  Layout->addStretch(1);

  Layout->setMargin(0);

  setFixedWidth(20);

  //connect(,,this,);

 // setMask(LeftStepButton->mask() );

}
