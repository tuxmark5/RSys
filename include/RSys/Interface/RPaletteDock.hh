#ifndef RSYS_INTERFACE_RPALETTE_DOCK_HH
#define RSYS_INTERFACE_RPALETTE_DOCK_HH

/**********************************************************************************************/
#include <RSys/RSys.hh>
#include <QtGui/QDockWidget>
/********************************************* RS *********************************************/
/*                                        RPaletteDock                                        */
/**********************************************************************************************/

class RPaletteDock: public QDockWidget
{
  Q_OBJECT

  private:
    _M QTableView*  m_filter;
    _M bool         m_mode;

  public:
    _M Vacuum       RPaletteDock(RMainWindow* parent = 0);
    _V Vacuum       ~RPaletteDock();
    _M QString      modeName() const;

  public slots:
    _M void         setMode(bool mode);
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RPALETTE_DOCK_HH */
