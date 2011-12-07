#include <QtGui/QLabel>
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>
#include <RSys/Interface/RModel1D.hh>
#include <RSys/Interface/RModel2D.hh>
#include <RSys/Interface/RTab.hh>
#include <RSys/Interface/RTableView.hh>

/********************************************* RS *********************************************/
/*                                            RTab                                            */
/**********************************************************************************************/

Vacuum RTab :: RTab(const QString& title, QWidget* parent):
  QWidget(parent)
{
  QVBoxLayout*  layout  = new QVBoxLayout(this);
  m_label               = new QLabel(title);

  m_label->setFrameStyle(QLabel::Box | QLabel::Plain);
  m_label->setLineWidth(1);
  m_label->setMinimumHeight(20);

  layout->addWidget(m_label);
}

/**********************************************************************************************/

Vacuum RTab :: ~RTab()
{
}

/**********************************************************************************************/

void RTab :: makeTable1DTab(RContainer* container)
{
  RModel1D*   model     = new RModel1D(container, this);
  RTableView* tableView = new RTableView(model, this);

  tableView->setSortingEnabled(true);
  layout()->addWidget(tableView);  
}

/**********************************************************************************************/

RModel2D* RTab :: makeTable2DTab(RContainer* containerX, RContainer* containerY)
{
  RModel2D*   model     = new RModel2D(containerX, containerY, this);
  RTableView* tableView = new RTableView(model, this);

  layout()->addWidget(tableView);
  return model;
}

/**********************************************************************************************/

void RTab :: makeTree1DTab(RContainer* container)
{
  RModel1D*   model     = new RModel1D(container, this);
  QTreeView*  treeView  = new QTreeView(this);

  treeView->setModel(model);
  treeView->setSortingEnabled(true);
  layout()->addWidget(treeView);
}

/**********************************************************************************************/

void RTab :: setEditable(bool editable)
{
  if (RTableView* tableView = findChild<RTableView*>())
  {
    static_cast<RAbstractItemModel*>(tableView->model())->setEditable(editable);
  }
}

/**********************************************************************************************/
