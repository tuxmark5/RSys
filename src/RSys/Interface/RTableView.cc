#include <QtGui/QHeaderView>
#include <RSys/Interface/RTableView.hh>

/********************************************* RS *********************************************/
/*                                         RTableView                                         */
/**********************************************************************************************/

Vacuum RTableView :: RTableView(QAbstractItemModel* model, QWidget* parent):
  QTableView(parent)
{
  horizontalHeader()->setResizeMode(QHeaderView::Stretch);
  verticalHeader()->setDefaultSectionSize(20);
  setModel(model);
}

/**********************************************************************************************/

Vacuum RTableView :: ~RTableView()
{

}

/**********************************************************************************************/
