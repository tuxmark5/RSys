#include <QtGui/QHeaderView>
#include <RSys/Interface/RModel1D.hh>
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

bool RTableView :: edit(const QModelIndex& index, EditTrigger trigger, QEvent* event)
{ 
  if (trigger != CurrentChanged)
  {
    if (RModel1D* model = qobject_cast<RModel1D*>(this->model()))
      if (model->rowCount(QModelIndex()) - 1 == index.row())
        model->addRow();
  }

  if (QTableView::edit(index, trigger, event))
    return true;
  return false;
}

/**********************************************************************************************/
