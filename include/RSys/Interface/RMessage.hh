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
    _M Vacuum         RMessage(const QString& message, int timeout = 1500, QWidget* parent = 0);
    _V Vacuum         ~RMessage();
    _S QColor         backgroundColorFor(RMessageLevel level);
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RMESSAGE_HH */
