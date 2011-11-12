#include <QtGui/QLabel>
#include <QtGui/QPainter>
#include <QtGui/QPushButton>
#include <QtGui/QStackedLayout>
#include <RSys/Core/RUnit.hh>
#include <RSys/Interface/RChart.hh>
#include <RSys/Interface/RResultsModel.hh>
#include <RSys/Interface/RTableView.hh>
#include <RSys/Interface/RUsageWidget.hh>
#include <RSys/Logic/RResults.hh>

/**********************************************************************************************/

template <class Class>
Class* ensure(RUsageWidget* self)
{
  Class* object = qobject_cast<Class*>(self->widget());

  if (!object)
    self->setWidget(object = new Class(self->model()));
  return object;
}

/********************************************* RS *********************************************/
/*                                        RUsageWidget                                        */
/**********************************************************************************************/

Vacuum RUsageWidget :: RUsageWidget(RUnit* unit, RResults* results, QWidget* parent):
  RLayerWidget(parent),
  m_unit(unit),
  m_results(results),
  m_model(new RResultsModel(results, this))
{
  m_header = new QLabel();
  m_header->setFrameStyle(QFrame::Box | QFrame::Plain);
  layout()->addWidget(m_header);

  setMinimumWidth(600);
  setFixedHeight(200);

  setBarChartMode();
}

/**********************************************************************************************/

Vacuum RUsageWidget :: ~RUsageWidget()
{
}

/**********************************************************************************************/

void RUsageWidget :: createButtons(const ButtonCallback& callback)
{
  QPushButton* buttonBar    = new QPushButton("B");
  QPushButton* buttonLine   = new QPushButton("L");
  QPushButton* buttonTable  = new QPushButton("T");

  QPushButton::connect(buttonBar, SIGNAL(clicked()), this, SLOT(setBarChartMode()));
  QPushButton::connect(buttonLine, SIGNAL(clicked()), this, SLOT(setLineChartMode()));
  QPushButton::connect(buttonTable, SIGNAL(clicked()), this, SLOT(setTableMode()));

  callback(buttonBar);
  callback(buttonLine);
  callback(buttonTable);
}

/**********************************************************************************************/

void RUsageWidget :: setBarChartMode()
{
  setTitle("Apkrovos");
  m_model->removeFields();
  m_results->addUsage1Field(m_model, m_unit);

  ensure<RChart>(this)->setType(RChart::Bar);
}

/**********************************************************************************************/

void RUsageWidget :: setLineChartMode()
{
  setTitle("Apkrovos");
  m_model->removeFields();
  m_results->addUsage1Field(m_model, m_unit);

  ensure<RChart>(this)->setType(RChart::Line);
}

/**********************************************************************************************/

void RUsageWidget :: setTableMode()
{
  setTitle("Apkrovų ir jų skirtumų lentelė");
  m_model->removeFields();
  m_model->setOrientation(Qt::Horizontal);
  m_results->addUsage0Field(m_model, m_unit);
  m_results->addUsage1Field(m_model, m_unit);
  m_results->addDeltaUsageField(m_model, m_unit);
  m_results->addDeltaPUsageField(m_model, m_unit);

  ensure<RTableView>(this)->setFrameStyle(QFrame::NoFrame);
}

/**********************************************************************************************/

void RUsageWidget :: setTitle(const char* title)
{
  m_title = QString::fromUtf8(title);
  updateHeader();
}

/**********************************************************************************************/

void RUsageWidget :: updateHeader()
{
  QString text = QString("<b>%1</b> (<i>%2</i>): %3")
      .arg(m_unit->identifier())
      .arg(m_unit->name())
      .arg(m_title);

  m_header->setText(text);
}

/**********************************************************************************************/
