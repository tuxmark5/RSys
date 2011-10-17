#ifndef RSYS_INTERFACE_RMAIN_WINDOW_HH
#define RSYS_INTERFACE_RMAIN_WINDOW_HH

/**********************************************************************************************/
#include <RSys/RSys.hh>
#include <QtGui/QMainWindow>
/********************************************* RS *********************************************/
/*                                        RMainWindow                                         */
/**********************************************************************************************/

class RMainWindow: public QMainWindow
{
  Q_OBJECT

  private:
    _M QSplitter*   m_splitter;
    _M QTabWidget*  m_tabWidgetL;
    _M QTabWidget*  m_tabWidgetR;

  public:
    _M              RMainWindow();
    _V              ~RMainWindow();
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RMAIN_WINDOW_HH */
