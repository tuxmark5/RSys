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

  public:
    _M Vacuum         RLogDock(RMainWindow* parent = 0);
    _V Vacuum         ~RLogDock();

  public slots:
    _M void           addMessage(RMessageLevel level, RID id, const QString& message);
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RLOG_DOCK_HH */
