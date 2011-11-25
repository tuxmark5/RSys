#include <QtGui/QLabel>
#include <RSys/Interface/RMessage.hh>

/********************************************* RS *********************************************/
/*                                          RMessage                                          */
/**********************************************************************************************/

Vacuum RMessage :: RMessage(const QString& message, int timeout, QWidget* parent):
  RStatusWidget(0, parent),
  m_owner(0)
{
  QLabel* label = new QLabel(message);

  setBackgroundColor(Qt::yellow);
  setWidget(label);
  startTimer(timeout);
}

/**********************************************************************************************/

Vacuum RMessage :: ~RMessage()
{
}

/**********************************************************************************************/

QColor RMessage :: backgroundColorFor(RMessageLevel level)
{
  switch (level)
  {
    case RINFO:     return Qt::white;
    case RWARNING:  return Qt::yellow;
    case RERROR:    return Qt::red;
  }
  return QColor();
}

/**********************************************************************************************/

void RMessage :: setOwner(QObject* owner)
{
  m_owner = owner;
}

/**********************************************************************************************/
