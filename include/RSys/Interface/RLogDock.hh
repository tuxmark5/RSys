#ifndef RSYS_INTERFACE_RLOG_DOCK_HH
#define RSYS_INTERFACE_RLOG_DOCK_HH

/**********************************************************************************************/
#include <QtGui/QDockWidget>
#include <RSys/RSys.hh>
/********************************************* RS *********************************************/
/*                                          RLogDock                                          */
/**********************************************************************************************/

class RLogDock: public QDockWidget
{
  Q_OBJECT

  public:
    _T QList<QStandardItem*>    ItemList;
    _T QStandardItemModel       Model;

  private:
    _M Model*         m_model;
    _M int            m_messageIndex;
    _M bool           m_autoShow: 1;

  public:
    _M Vacuum         RLogDock(RMainWindow* parent = 0);
    _V Vacuum         ~RLogDock();
    _S QString        levelName(int level);

  public slots:
    _M void           addMessage(const QString& message, int id, int level);
    _M void           clearLog();
    _M void           setAutoShow(bool autoShow);
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RLOG_DOCK_HH */
