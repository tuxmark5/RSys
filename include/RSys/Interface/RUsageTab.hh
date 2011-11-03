#ifndef RSYS_INTERFACE_RUSAGE_TAB_HH
#define RSYS_INTERFACE_RUSAGE_TAB_HH

/**********************************************************************************************/
#include <RSys/RSys.hh>
#include <QtGui/QScrollArea>
/********************************************* RS *********************************************/
/*                                         RUsageTab                                          */
/**********************************************************************************************/

class RUsageTab: public QScrollArea
{
  Q_OBJECT

  public:
    _M Vacuum       RUsageTab(QWidget* parent = 0);
    _V Vacuum       ~RUsageTab();
    _V void         resizeEvent(QResizeEvent* event);
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RUSAGE_TAB_HH */
