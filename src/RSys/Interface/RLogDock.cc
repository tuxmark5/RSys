#include <QtCore/QRegExp>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QStandardItemModel>
#include <QtGui/QSortFilterProxyModel>
#include <RSys/Interface/RLogDock.hh>
#include <RSys/Interface/RMainWindow.hh>
#include <RSys/Interface/RLogFilterModel.hh>
#include <RSys/Interface/RTableView.hh>

/**********************************************************************************************/
QRegExp g_htmlTagRegExp("\\</?\\w+\\>");
/********************************************* RS *********************************************/
/*                                          RLogDock                                          */
/**********************************************************************************************/

Vacuum RLogDock :: RLogDock(RMainWindow* parent):
  QDockWidget(parent),
  m_model(new QStandardItemModel(this)),
  m_messageIndex(0),
  m_autoShow(true)
{
  RLogFilterModel*  filterModel = new RLogFilterModel();
  RTableView*       tableView   = new RTableView(filterModel);
  QWidget*          titleBar    = new QWidget();
  QHBoxLayout*      titleLayout = new QHBoxLayout(titleBar);
  QLabel*           label1      = new QLabel(R_S("<b>Pranešimų žurnalas</b>"));
  QCheckBox*        autoShowBox = new QCheckBox(R_S("Rodyti žurnalą įvykus klaidai"));
  QLabel*           label2      = new QLabel(R_S("Rodyti bent:"));
  QComboBox*        levelBox    = new QComboBox();
  QPushButton*      clearButton = new QPushButton(R_S("Valyti"));
  QPushButton*      closeButton = new QPushButton(R_S("Slėpti"));

  filterModel->setSourceModel(m_model);

  label1->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
  label1->setTextInteractionFlags(Qt::NoTextInteraction);

  autoShowBox->setChecked(true);

  levelBox->addItem(R_S("Visus pranešimus"));
  levelBox->addItem(R_S("Informacinius pranešimus"));
  levelBox->addItem(R_S("Įspėjamuosius pranešimus"));
  levelBox->addItem(R_S("Klaidos pranešimus"));
  levelBox->addItem(R_S("Kritinius pranešimus"));

  titleLayout->addWidget(label1);
  titleLayout->addWidget(label2);
  titleLayout->addWidget(levelBox);
  titleLayout->addWidget(clearButton);
  titleLayout->addWidget(autoShowBox);
  titleLayout->addWidget(closeButton);
  titleLayout->setSpacing(5);

  m_model->setColumnCount(4);
  m_model->setHeaderData(0, Qt::Horizontal, R_S("Lygis"), Qt::DisplayRole);
  m_model->setHeaderData(1, Qt::Horizontal, R_S("Tipas"), Qt::DisplayRole);
  m_model->setHeaderData(2, Qt::Horizontal, R_S("Laikas"), Qt::DisplayRole);
  m_model->setHeaderData(3, Qt::Horizontal, R_S("Pranešimas"), Qt::DisplayRole);

  tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
  //setFeatures(QDockWidget::DockWidgetClosable);
  setTitleBarWidget(titleBar);
  setWindowTitle(R_S("Pranešimų žurnalas"));
  setWidget(tableView);

  connect(autoShowBox, SIGNAL(toggled(bool)), this, SLOT(setAutoShow(bool)));
  connect(clearButton, SIGNAL(clicked()), this, SLOT(clearLog()));
  connect(closeButton, SIGNAL(clicked()), this, SLOT(hide()));
  connect(levelBox, SIGNAL(currentIndexChanged(int)), filterModel, SLOT(setMinimumLevel(int)));
}

/**********************************************************************************************/

Vacuum RLogDock :: ~RLogDock()
{

}

/**********************************************************************************************/

void RLogDock :: addMessage(const QString& message, int id, int level)
{
  ItemList        items;
  QString         message1  = message;
  QStandardItem*  item;
  QString         timeStamp = QDateTime::currentDateTime().toString(Qt::DefaultLocaleShortDate);

  message1.remove(g_htmlTagRegExp);

  items << (item = new QStandardItem(levelName(level)));
  item->setData(level, Qt::UserRole);
  items << (item = new QStandardItem(QString::number(id)));
  items << (item = new QStandardItem(timeStamp));
  items << (item = new QStandardItem(message1));

  m_model->appendRow(items);
  m_model->setHeaderData(m_model->rowCount(), Qt::Vertical, m_messageIndex++, Qt::DisplayRole);

  if (m_autoShow && isHidden())
    show();
}

/**********************************************************************************************/

void RLogDock :: clearLog()
{
  m_model->removeRows(0, m_model->rowCount());
}

/**********************************************************************************************/

QString RLogDock :: levelName(int level)
{
  switch (level)
  {
    case RDEBUG:      return R_S("");
    case RINFO:       return R_S("Informacija");
    case RWARNING:    return R_S("Įspėjimas");
    case RERROR:      return R_S("Klaida");
    case RCRITICAL:   return R_S("Kritinė klaida");
  }

  return R_S("Nežinomas");
}

/**********************************************************************************************/

void RLogDock :: setAutoShow(bool autoShow)
{
  m_autoShow = autoShow;
}

/**********************************************************************************************/
