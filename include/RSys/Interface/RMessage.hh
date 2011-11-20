#ifndef RSYS_INTERFACE_RMESSAGE_HH
#define RSYS_INTERFACE_RMESSAGE_HH

/**********************************************************************************************/
#include <RSys/Interface/RStatusWidget.hh>
/********************************************* RS *********************************************/
/*                                          RMessage                                          */
/**********************************************************************************************/

class RMessage: public RStatusWidget
{
  Q_OBJECT

  public:
    _M QObject*       m_owner;

  public:
    _M Vacuum         RMessage(const QString& message, int timeout = 1500, QWidget* parent = 0);
    _V Vacuum         ~RMessage();
    _S QColor         backgroundColorFor(RMessageLevel level);
    _M QObject*       owner() const { return m_owner; }
    _M void           setOwner(QObject* owner);
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RMESSAGE_HH */
