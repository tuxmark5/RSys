#ifndef RSYS_INTERFACE_RTABLE_VIEW_HH
#define RSYS_INTERFACE_RTABLE_VIEW_HH

/**********************************************************************************************/
#include <RSys/RSys.hh>
#include <QtGui/QTableView>
/********************************************* RS *********************************************/
/*                                         RTableView                                         */
/**********************************************************************************************/

class RTableView: public QTableView
{
  Q_OBJECT

  public:
    _M Vacuum       RTableView(QAbstractItemModel* model, QWidget* parent = 0);
    _V Vacuum       ~RTableView();

  protected:
    _V bool         edit(const QModelIndex& index, EditTrigger trigger, QEvent* event);
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RTABLE_VIEW_HH */
