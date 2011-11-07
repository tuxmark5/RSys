#include <QtGui/QLabel>
#include <QtGui/QVBoxLayout>
#include <RSys/Interface/RTab.hh>

/********************************************* RS *********************************************/
/*                                            RTab                                            */
/**********************************************************************************************/

Vacuum RTab :: RTab(const QString& title, QWidget* parent):
  QWidget(parent)
{
  QVBoxLayout*  layout  = new QVBoxLayout(this);
  QLabel*       label   = new QLabel(title);

  label->setFrameStyle(QLabel::HLine | QLabel::Plain);
  label->setLineWidth(1);
  label->setMinimumHeight(20);

  layout->addWidget(label);
}

/**********************************************************************************************/

Vacuum RTab :: ~RTab()
{
}

/**********************************************************************************************/
