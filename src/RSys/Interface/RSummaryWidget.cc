#include <QtGui/QAction>
#include <QtGui/QMenu>
#include <QtGui/QPushButton>
#include <RSys/Core/RData.hh>
#include <RSys/Core/RUnit.hh>
#include <RSys/Interface/RChart.hh>
#include <RSys/Interface/RResultsModel.hh>
#include <RSys/Interface/RSummaryWidget.hh>
#include <RSys/Interface/RTableView.hh>
#include <RSys/Logic/RResults.hh>

/**********************************************************************************************/

template <class Class>
Class* ensure(RSummaryWidget* self)
{
  Class* object = qobject_cast<Class*>(self->widget());

  if (!object)
    self->setWidget(object = new Class(self->model()));
  return object;
}

/********************************************* RS *********************************************/
/*                                       RSummaryWidget                                       */
/**********************************************************************************************/

Vacuum RSummaryWidget :: RSummaryWidget(RResults* results, QWidget* parent):
  RLayerWidget(parent),
  m_results(results),
  m_resultsModel(new RResultsModel(m_results, this)),
  m_units(0)
{
  setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
  setMode(RResultsModel::Usage1 | Table);
}

/**********************************************************************************************/

Vacuum RSummaryWidget :: ~RSummaryWidget()
{
  if (m_units)
    m_units->removeObserver(this);
}

/**********************************************************************************************/

int RSummaryWidget :: countVisible(int till)
{
  int numVisible = 0;

  for (int i = 0; i < till; i++)
    numVisible += m_units->at(i)->visible();
  return numVisible;
}

/**********************************************************************************************/

#define MODE(menu, name, mode) menu->addAction(R_S(name), this, SLOT(setMode()))->setData(int(mode));

void RSummaryWidget :: createButtons(const ButtonCallback& callback)
{
  QPushButton*  button        = new QPushButton(R_S("Rodyti"));
  QMenu*        menu          = new QMenu();
  QMenu*        usage1        = menu->addMenu(R_S("Apkrovas"));
  QMenu*        usageD        = menu->addMenu(R_S("Skirtumus"));
  QMenu*        usageDP       = menu->addMenu(R_S("Procentinius skirtumus"));

  MODE(usage1,  "Stulpeline diagrama", RResultsModel::Usage1 | Bar);
  MODE(usage1,  "Linijine diagrama",   RResultsModel::Usage1 | Line);
  MODE(usage1,  "Lentele",             RResultsModel::Usage1 | Table);

  MODE(usageD,  "Stulpeline diagrama", RResultsModel::UsageD | Bar);
  MODE(usageD,  "Linijine diagrama",   RResultsModel::UsageD | Line);
  MODE(usageD,  "Lentele",             RResultsModel::UsageD | Table);

  MODE(usageDP, "Stulpeline diagrama", RResultsModel::UsageDP | Bar);
  MODE(usageDP, "Linijine diagrama",   RResultsModel::UsageDP | Line);
  MODE(usageDP, "Lentele",             RResultsModel::UsageDP | Table);

  connect(menu, SIGNAL(aboutToHide()), menu, SLOT(deleteLater()));
  button->setMenu(menu);
  callback(button);
}

/**********************************************************************************************/

void RSummaryWidget :: insert1(int i0, int i1)
{
  Q_UNUSED(i1);

  m_resultsModel->insertField(countVisible(i0), m_fieldType, m_units->at(i0));
}

/**********************************************************************************************/

bool RSummaryWidget :: remove0(int i0, int i1)
{
  Q_UNUSED(i1);

  m_resultsModel->removeField(countVisible(i0));
  return true;
}

/**********************************************************************************************/

void RSummaryWidget :: resetObservable()
{
  setUnits(m_units);
}

/**********************************************************************************************/

void RSummaryWidget :: setMode()
{
  if (QAction* action = qobject_cast<QAction*>(sender()))
  {
    setMode(action->data().toInt());
  }
}

/**********************************************************************************************/

void RSummaryWidget :: setMode(int mode)
{
  m_fieldType = (mode & 0x0FF) | RResultsModel::Identifier;
  setUnits(m_units);
  //setTitle(RResultsModel::longTitleForField(mode));

  switch (mode & 0xF00)
  {
    case Bar:
      if (RChart* chart = ensure<RChart>(this))
      {
        chart->setType(RChart::Bar);
        chart->setShowLegend(true);
      }
      break;

    case Line:
      if (RChart* chart = ensure<RChart>(this))
      {
        chart->setType(RChart::Line);
        chart->setShowLegend(true);
      }
      break;

    case Table:
      m_resultsModel->setOrientation(Qt::Horizontal);
      ensure<RTableView>(this)->setFrameStyle(QFrame::NoFrame);
      break;
  }
}

/**********************************************************************************************/

void RSummaryWidget :: setUnits(RUnitPtrList* units)
{
  if (m_units)
  {
    m_units->removeObserver(this);
    m_resultsModel->removeFields();
  }

  if ((m_units = units))
  {
    m_units->addObserver(this);

    for (auto it = m_units->begin(); it != m_units->end(); ++it)
    {
      if ((*it)->visible())
        m_resultsModel->addField(m_fieldType, *it);
    }
  }
}

/**********************************************************************************************/

void RSummaryWidget :: updateElement(RElement* unit, int updateType)
{
  if (updateType == RData::Visibility)
  {
    int index = m_units->indexOf(static_cast<RUnit*>(unit));
    R_GUARD(index != -1, Vacuum);

    if (unit->visible())
      insert1(index, index);
    else
      remove0(index, index);
  }
}

/**********************************************************************************************/
