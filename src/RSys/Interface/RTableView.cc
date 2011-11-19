#include <QtGui/QHeaderView>
#include <QtGui/QMenu>
#include <RSys/Interface/RModel1D.hh>
#include <RSys/Interface/RTableView.hh>

/********************************************* RS *********************************************/
/*                                         RTableView                                         */
/**********************************************************************************************/

Vacuum RTableView :: RTableView(QAbstractItemModel* model, QWidget* parent):
  QTableView(parent)
{
  horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
  verticalHeader()->setDefaultSectionSize(20);
  setContextMenuPolicy(Qt::ActionsContextMenu);
  setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
  setModel(model);
  //setSortingEnabled(true);

  if (RModel1D* model = qobject_cast<RModel1D*>(this->model()))
  {
    if (model->writable())
    {
      QAction* deleteAction = new QAction(R_S("Pašalinti"), this);

      deleteAction->setShortcut(QKeySequence("Ctrl+-"));
      connect(deleteAction, SIGNAL(triggered()), this, SLOT(deleteRows()));
      addAction(deleteAction);
      setSelectionBehavior(QAbstractItemView::SelectRows);
    }
  }
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

void RTableView :: deleteRows()
{
  QAbstractItemModel*   model   = this->model();
  QModelIndexList       rows    = selectionModel()->selectedRows();
  int                   delta   = 0;

  for (auto it = rows.begin(); it != rows.end(); ++delta, ++it)
    model->removeRow(it->row() - delta);
}

/**********************************************************************************************/

/*void RTableView :: onContextMenu(const QPoint& point)
{
  RModel1D* model = qobject_cast<RModel1D*>(this->model());
  R_GUARD(model,              Vacuum);
  R_GUARD(model->writable(),  Vacuum);

  QMenu     menu;
  QAction*  deleteAction = menu.addAction(R_S("Pašalinti"));

  connect(deleteAction, SIGNAL(triggered()), this, SLOT(deleteRow()));
}*/

/**********************************************************************************************/

void RTableView :: setStretch(bool stretch)
{
  auto mode = stretch ? QHeaderView::Stretch : QHeaderView::ResizeToContents;

  horizontalHeader()->setResizeMode(mode);
}

/**********************************************************************************************/
