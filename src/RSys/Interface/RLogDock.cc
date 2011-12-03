#include <QtCore/QRegExp>
#include <QtGui/QComboBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
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
  RTableView*   tableView   = new RTableView(m_model);
  QWidget*      titleBar    = new QWidget();
  QHBoxLayout*  titleLayout = new QHBoxLayout(titleBar);
  QLabel*       label1      = new QLabel(R_S("<b>Pranešimų žurnalas</b>"));
  QLabel*       label2      = new QLabel(R_S("Rodyti tik:"));
  QComboBox*    levelBox    = new QComboBox();
  QPushButton*  clearButton = new QPushButton(R_S("Valyti"));
  QPushButton*  closeButton = new QPushButton(R_S("Slėpti"));

  /*titleBar->setContentsMargins(0, 0, 0, 0);
  label1->setContentsMargins(0, 0, 0, 0);
  label2->setContentsMargins(0, 0, 0, 0);
  levelBox->setContentsMargins(0, 0, 0, 0);*/
  //closeButton->setFlat(true);

  label1->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
  label1->setTextInteractionFlags(Qt::NoTextInteraction);

  levelBox->addItem(R_S("Visus pranešimus"));
  levelBox->addItem(R_S("Įspėjamuosius pranešimus"));
  levelBox->addItem(R_S("Klaidos pranešimus"));

  titleLayout->addWidget(label1);
  titleLayout->addWidget(label2);
  titleLayout->addWidget(levelBox);
  titleLayout->addWidget(clearButton);
  titleLayout->addWidget(closeButton);
  titleLayout->setSpacing(5);

  m_model->setColumnCount(3);
  m_model->setHeaderData(0, Qt::Horizontal, R_S("Lygis"), Qt::DisplayRole);
  m_model->setHeaderData(1, Qt::Horizontal, R_S("Klaida"), Qt::DisplayRole);
  m_model->setHeaderData(2, Qt::Horizontal, R_S("Pranešimas"), Qt::DisplayRole);

  tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
  //setFeatures(QDockWidget::DockWidgetClosable);
  setTitleBarWidget(titleBar);
  setWindowTitle(R_S("Pranešimų žurnalas"));
  setWidget(tableView);

  connect(clearButton, SIGNAL(clicked()), this, SLOT(clearLog()));
  connect(closeButton, SIGNAL(clicked()), this, SLOT(hide()));
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

  if (isHidden())
    show();
}

/**********************************************************************************************/

void RLogDock :: clearLog()
{
  m_model->removeRows(0, m_model->rowCount());
}

/**********************************************************************************************/

void RLogDock :: filterLog(int level)
{

}

/**********************************************************************************************/
