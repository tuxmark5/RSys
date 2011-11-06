#ifndef RSYS_INTERFACE_RINTERVAL_TOOL_BAR_HH
#define RSYS_INTERFACE_RINTERVAL_TOOL_BAR_HH

/**********************************************************************************************/
#include <RSys/RSys.hh>
#include <QtGui/QToolBar>
/********************************************* RS *********************************************/
/*                                      RIntervalToolBar                                      */
/**********************************************************************************************/

class RIntervalToolBar: public QToolBar
{
  Q_OBJECT

  private:
    _M QDateEdit*     m_interval0;
    _M QDateEdit*     m_interval1;
    _M QPushButton*   m_applyButton;

  public:
    _M Vacuum         RIntervalToolBar(RMainWindow* parent = 0);
    _V Vacuum         ~RIntervalToolBar();
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RINTERVAL_TOOL_BAR_HH */
