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

  label->setContentsMargins(0, -8, 0, -8);
  label->setWordWrap(true);
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
    case RDEBUG:    return Qt::gray;
    case RINFO:     return Qt::white;
    case RWARNING:  return Qt::yellow;
    case RERROR:    return Qt::red;
    default:        break;
  }
  return QColor();
}

/**********************************************************************************************/

void RMessage :: setOwner(QObject* owner)
{
  m_owner = owner;
}

/**********************************************************************************************/
