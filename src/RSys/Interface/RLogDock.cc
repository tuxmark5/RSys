#include <QtCore/QRegExp>
#include <QtGui/QStandardItemModel>
#include <RSys/Interface/RLogDock.hh>
#include <RSys/Interface/RMainWindow.hh>
#include <RSys/Interface/RTableView.hh>

/**********************************************************************************************/
QRegExp g_htmlTagRegExp("\\</?\\w+\\>");
/********************************************* RS *********************************************/
/*                                          RLogDock                                          */
/**********************************************************************************************/

Vacuum RLogDock :: RLogDock(RMainWindow* parent):
  QDockWidget(parent),
  m_model(new QStandardItemModel(this)),
  m_messageIndex(0)
{
  RTableView* tableView = new RTableView(m_model);

  m_model->setColumnCount(3);
  m_model->setHeaderData(0, Qt::Horizontal, R_S("Lygis"), Qt::DisplayRole);
  m_model->setHeaderData(1, Qt::Horizontal, R_S("Klaida"), Qt::DisplayRole);
  m_model->setHeaderData(2, Qt::Horizontal, R_S("Pranešimas"), Qt::DisplayRole);

  tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
  setFeatures(QDockWidget::DockWidgetClosable);
  setWindowTitle(R_S("Pranešimų žurnalas"));
  setWidget(tableView);
}

/**********************************************************************************************/

Vacuum RLogDock :: ~RLogDock()
{

}

/**********************************************************************************************/

void RLogDock :: addMessage(RMessageLevel level, RID id, const QString& message)
{
  ItemList    items;
  QString     message1 = message;

  message1.remove(g_htmlTagRegExp);
  items << new QStandardItem(QString::number(level));
  items << new QStandardItem(QString::number(id));
  items << new QStandardItem(message);
  m_model->appendRow(items);
  m_model->setHeaderData(m_model->rowCount(), Qt::Vertical, m_messageIndex++, Qt::DisplayRole);
}

/**********************************************************************************************/
