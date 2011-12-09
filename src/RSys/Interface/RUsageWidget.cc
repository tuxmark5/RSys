#include <QtGui/QAction>
#include <QtGui/QLabel>
#include <QtGui/QMenu>
#include <QtGui/QPushButton>
#include <QtGui/QStackedLayout>
#include <RSys/Core/RData.hh>
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

Vacuum RUsageWidget :: RUsageWidget(int mode, RUnit* unit, RResults* results, QWidget* parent):
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

  setMode(mode);
  updateGlobalInterval();

  connect(results->data1(), SIGNAL(globalIntervalChanged()), this, SLOT(updateGlobalInterval()));
}

/**********************************************************************************************/

Vacuum RUsageWidget :: ~RUsageWidget()
{
}

/**********************************************************************************************/


void RUsageWidget :: createButtons(const ButtonCallback& callback)
{
  QPushButton*  button  = new QPushButton(R_S("Rodyti"));
  QMenu*        menu    = createModeMenu(this, SLOT(modifyMode()), m_unit->viewMode());

  connect(menu, SIGNAL(aboutToHide()), menu, SLOT(deleteLater()));

  button->setMenu(menu);
  callback(button);
}

/**********************************************************************************************/

#define ACTION(menu, mode) menu->addAction(a)

QMenu* RUsageWidget :: createModeMenu(QObject* receiver, const char* slot, int initialMode)
{
  QMenu*        menu          = new QMenu();
  QActionGroup* dataGroup     = new QActionGroup(menu);
  QActionGroup* dmodGroup     = new QActionGroup(menu);
  QActionGroup* viewGroup     = new QActionGroup(menu);

  QAction*      usage0Action  = new QAction(R_S("Pradines apkrovas"), dataGroup);
  QAction*      usage1Action  = new QAction(R_S("Galines apkrovas"), dataGroup);
  QAction*      usageDAction  = new QAction(R_S("Apkrovų skirtumus"), dataGroup);
  QAction*      usageDPAction = new QAction(R_S("Apkrovų procentinius skirtumus"), dataGroup);

  QAction*      hourAction    = new QAction(R_S("Pagal valandas"), dmodGroup);
  QAction*      countsAction  = new QAction(R_S("Pagal paraiškų skaičių"), dmodGroup);

  QAction*      barAction     = new QAction(R_S("Stulpeline diagrama"), viewGroup);
  QAction*      lineAction    = new QAction(R_S("Linijine diagrama"), viewGroup);
  QAction*      tableAction   = new QAction(R_S("Sumarine lentele"), viewGroup);

  auto          init = [&](QAction* a, int mask, int data)
  {
    a->setCheckable(true);
    if ((mask & initialMode) == data)
      a->setChecked(true);
    connect(a, SIGNAL(triggered()), receiver, slot);
    menu->addAction(a);
    a->setData((~mask << 16) | data);
  };

  init(usage0Action,  DataMask, Usage0);
  init(usage1Action,  DataMask, Usage1);
  init(usageDAction,  DataMask, UsageD);
  init(usageDPAction, DataMask, UsageDP);
  menu->addSeparator();

  init(hourAction,    DataModMask,  Hours);
  init(countsAction,  DataModMask,  Counts);
  menu->addSeparator();

  init(barAction,     ViewMask, Bar);
  init(lineAction,    ViewMask, Line);
  init(tableAction,   ViewMask, Table);
  menu->addSeparator();

  return menu;
}

/**********************************************************************************************/

void RUsageWidget :: modifyMode()
{
  if (QAction* action = qobject_cast<QAction*>(sender()))
    modifyMode(action->data().toInt());
}

/**********************************************************************************************/

void RUsageWidget :: modifyMode(int modifier)
{
  int viewMode = m_unit->viewMode();
  viewMode &= modifier >> 16;
  viewMode |= modifier & 0xFFFF;
  setMode(viewMode);
}

/**********************************************************************************************/

void RUsageWidget :: onViewClicked(const QModelIndex& index)
{
  if (m_model->isHorizontal())
    m_results->setHighlightedInterval(index.column());
  else
    m_results->setHighlightedInterval(index.row());
}

/**********************************************************************************************/

void RUsageWidget :: setMode(int mode)
{
  R_NZ(m_unit)->setViewMode(mode);

  m_model->removeFields();

  switch (mode & ViewMask)
  {
    case Bar:
      ensure<RChart>(this)->setType(RChart::Bar);
      updateGlobalInterval();
      break;

    case Line:
      ensure<RChart>(this)->setType(RChart::Line);
      updateGlobalInterval();
      break;

    case Table:
    {
      int fieldMod = (mode & DataModMask) | RResultsModel::Background;
      m_model->addField(RResultsModel::Usage0   | fieldMod, m_unit);
      m_model->addField(RResultsModel::Usage1   | fieldMod, m_unit);
      m_model->addField(RResultsModel::UsageD   | fieldMod, m_unit);
      m_model->addField(RResultsModel::UsageDP  | fieldMod, m_unit);
      m_model->setOrientation(Qt::Horizontal);
      ensure<RTableView>(this)->setFrameStyle(QFrame::NoFrame);
      break;
    }

    default:
      qDebug() << "INVALID viewMode" << mode;
      break;
  }

  connect(widget(), SIGNAL(clicked(QModelIndex)), this, SLOT(onViewClicked(QModelIndex)), Qt::UniqueConnection);

  if ((mode & ViewMask) == Table)
  {
    setTitle(R_S("Apkrovų ir jų skirtumų lentelė"));
  }
  else
  {
    int field = (mode & (DataMask | DataModMask)) | RResultsModel::Background;

    setTitle(RResultsModel::longTitleForField(field));
    m_model->addField(field, m_unit);
  }
}

/**********************************************************************************************/

void RUsageWidget :: setSearchInterval(bool search)
{
  if (search)
    m_lowInterval = m_results->findLowUsageInterval(m_unit);
  else
    m_lowInterval = RInterval();

  if (RChart* chart = qobject_cast<RChart*>(widget()))
    chart->setFillRange(0, std::get<0>(m_lowInterval), std::get<1>(m_lowInterval));

  updateHeader();
}

/**********************************************************************************************/

void RUsageWidget :: setTitle(const QString& title)
{
  m_title = title;
  updateHeader();
}

/**********************************************************************************************/

void RUsageWidget :: updateGlobalInterval()
{
  if (RChart* chart = qobject_cast<RChart*>(widget()))
  {
    chart->setFillRange(1, m_results->data1()->interval1(), QDate(5000, 1, 1));
  }
}

/**********************************************************************************************/

void RUsageWidget :: updateHeader()
{
  QString text = QString("<b>%1</b> (<i>%2</i>): %3")
      .arg(m_unit->identifier())
      .arg(m_unit->name())
      .arg(m_title);

  if (!std::get<0>(m_lowInterval).isNull())
  {
    text += R_S("<br/><u>Mažiausios apkrovos intervalas:</u> nuo <b>%1</b> iki <b>%2</b>")
      .arg(std::get<0>(m_lowInterval).toString(Qt::DefaultLocaleShortDate))
      .arg(std::get<1>(m_lowInterval).toString(Qt::DefaultLocaleShortDate));
  }

  m_header->setText(text);
}

/**********************************************************************************************/
