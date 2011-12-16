#include <QtGui/QLayout>
#include <QtGui/QHeaderView>
#include <RSys/Interface/RItemDelegate.hh>
#include <RSys/Interface/RMainWindow.hh>
#include <RSys/Interface/RMeasureTab.hh>
#include <RSys/Interface/RModel1D.hh>
#include <RSys/Interface/RTableView.hh>

/********************************************* RS *********************************************/
/*                                        RMeasureTab                                         */
/**********************************************************************************************/

Vacuum RMeasureTab :: RMeasureTab(RMainWindow* parent):
  RTab(R_S("Paramos priemonės"), parent)
{
  RModel1D*       model       = new RModel1D(parent->measureContainer(), this);
  RTableView*     tableView   = new RTableView(model, this);
  QHeaderView*    header      = tableView->horizontalHeader();
  QItemDelegate*  delegate    = new RItemDelegate(model, parent->data(), parent->groupContainer(), tableView);

  tableView->setItemDelegate(delegate);
  tableView->setSortingEnabled(true);

  header->setResizeMode(QHeaderView::Interactive);
  header->resizeSection(0, 60);
  header->resizeSection(1, 400);
  header->resizeSection(2, 200);

  layout()->addWidget(tableView);
}

/**********************************************************************************************/

Vacuum RMeasureTab :: ~RMeasureTab()
{
}

/**********************************************************************************************/
