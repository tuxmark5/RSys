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
  connect(this, SIGNAL(activated(QModelIndex)), this, SLOT(onActivated(QModelIndex)));
}

/**********************************************************************************************/

Vacuum RTableView :: ~RTableView()
{

}

/**********************************************************************************************/

void RTableView :: onActivated(const QModelIndex& index)
{
  if (RModel1D* model = qobject_cast<RModel1D*>(this->model()))
  {
    if (model->rowCount(QModelIndex()) == index.row())
    {
      model->addRow();
    }
  }
}

/**********************************************************************************************/
