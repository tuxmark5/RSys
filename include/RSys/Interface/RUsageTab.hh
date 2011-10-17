#ifndef RSYS_INTERFACE_RUSAGE_TAB_HH
#define RSYS_INTERFACE_RUSAGE_TAB_HH

/**********************************************************************************************/
#include <RSys/RSys.hh>
#include <QtGui/QWidget>
/********************************************* RS *********************************************/
/*                                         RUsageTab                                          */
/**********************************************************************************************/

class RUsageTab: public QWidget
{
  Q_OBJECT

  public:
    _M              RUsageTab(QWidget* parent = 0);
    _V              ~RUsageTab();
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RUSAGE_TAB_HH */
