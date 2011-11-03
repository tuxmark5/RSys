#include <RSys/Interface/RMainWindow.hh>
#include <RSys/Interface/RMeasureModel.hh>
#include <RSys/Interface/RUsageTab.hh>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListView>
#include <QtGui/QSplitter>
#include <QtGui/QScrollArea>
#include <QtGui/QTableView>
#include <QtGui/QTabWidget>

/********************************************* RS *********************************************/
/*                                        RMainWindow                                         */
/**********************************************************************************************/

RMainWindow :: RMainWindow()
{
  m_tabWidgetL  = new QTabWidget(this);
  m_tabWidgetL->setTabPosition(QTabWidget::South);
  m_tabWidgetL->addTab(new QLabel("TEST1"), "LTAB");

  m_tabWidgetR  = new QTabWidget(this);
  m_sa_results  = new QScrollArea(this);

  m_splitter    = new QSplitter(this);
  setCentralWidget(m_splitter);
  m_splitter->addWidget(m_tabWidgetL);
  m_splitter->addWidget(m_tabWidgetR);


  QTableView* v = new QTableView();
  v->setModel(new RMeasureModel(this));
  v->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
  //v->horizontalHeader()->set
  v->verticalHeader()->setDefaultSectionSize(20); //setHeight

  m_tabWidgetL->addTab(v, QString::fromUtf8("Priemonės"));

  m_tabWidgetR->setTabPosition(QTabWidget::South);
  m_tabWidgetR->addTab(new QLabel("TEST2"), "RTAB");
  m_tabWidgetR->addTab(new RUsageTab(), "RTAB");
}

/**********************************************************************************************/

RMainWindow :: ~RMainWindow()
{
}

/**********************************************************************************************/
