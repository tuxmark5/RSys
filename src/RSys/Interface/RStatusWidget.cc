#include <QtCore/QPropertyAnimation>
#include <QtCore/QTimer>
#include <QtGui/QHBoxLayout>
#include <QtGui/QPushButton>
#include <RSys/Interface/RStatusWidget.hh>

/********************************************* RS *********************************************/
/*                                        RStatusWidget                                       */
/**********************************************************************************************/

Vacuum RStatusWidget :: RStatusWidget(QWidget* parent):
  QFrame(parent),
  m_closing(false)
{
  QHBoxLayout*    layout      = new QHBoxLayout(this);
  QPushButton*    closeButton = new QPushButton("X");

  closeButton->setFixedSize(16, 16);

  setFrameStyle(QFrame::Box | QFrame::Plain);
  setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);

  layout->setMargin(0);
  layout->addWidget(closeButton);

  QPushButton::connect(closeButton, SIGNAL(clicked()), this, SLOT(onCloseClicked()));
}

/**********************************************************************************************/

Vacuum RStatusWidget :: ~RStatusWidget()
{
}

/**********************************************************************************************/

void RStatusWidget :: animateHeight(int from, int to, const char* slot)
{
  QPropertyAnimation* animation = new QPropertyAnimation(this, "height", this);

  animation->setDuration(100);
  animation->setStartValue(from);
  animation->setEndValue(to);
  animation->start(QAbstractAnimation::DeleteWhenStopped);

  if (slot)
  {
    connect(animation, SIGNAL(finished()), this, slot);
  }
}

/**********************************************************************************************/

void RStatusWidget :: onCloseClicked()
{
  R_GUARD(!m_closing, Vacuum);

  animateHeight(height(), 0, SLOT(deleteLater()));
  m_closing = true;
}

/**********************************************************************************************/

void RStatusWidget :: setBackgroundColor(const QColor& color)
{
  QPalette palette = this->palette();

  palette.setColor(backgroundRole(), color);
  setAutoFillBackground(true);
  setPalette(palette);
}

/**********************************************************************************************/

void RStatusWidget :: setLayout(QLayout* layout1)
{
  QHBoxLayout* layout = static_cast<QHBoxLayout*>(this->layout());

  layout->insertLayout(0, layout1);
  animateHeight(0, sizeHint().height(), 0);
}

/**********************************************************************************************/

void RStatusWidget :: setWidget(QWidget* widget)
{
  QHBoxLayout* layout = static_cast<QHBoxLayout*>(this->layout());

  layout->insertWidget(0, widget);
  animateHeight(0, sizeHint().height(), 0);
}

/**********************************************************************************************/

void RStatusWidget :: startTimer(int timeout)
{
  QTimer* timer = new QTimer(this);

  connect(timer, SIGNAL(timeout()), this, SLOT(onCloseClicked()));

  timer->setInterval(timeout);
  timer->setSingleShot(true);
  timer->start();
}

/**********************************************************************************************/

