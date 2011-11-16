#include <QtGui/QPushButton>
#include <RSys/Core/RData.hh>
#include <RSys/Core/RUnit.hh>
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
  setUsage1TableMode();
}

/**********************************************************************************************/

Vacuum RSummaryWidget :: ~RSummaryWidget()
{
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

void RSummaryWidget :: createButtons(const ButtonCallback& callback)
{
  QPushButton* buttonBar    = new QPushButton("B");
  QPushButton* buttonLine   = new QPushButton("L");
  QPushButton* buttonTable  = new QPushButton("T");

  /*QPushButton::connect(buttonBar, SIGNAL(clicked()), this, SLOT(setBarChartMode()));
  QPushButton::connect(buttonLine, SIGNAL(clicked()), this, SLOT(setLineChartMode()));
  QPushButton::connect(buttonTable, SIGNAL(clicked()), this, SLOT(setTableMode()));*/

  callback(buttonBar);
  callback(buttonLine);
  callback(buttonTable);
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

void RSummaryWidget :: setUnits(RUnitList* units)
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

void RSummaryWidget :: setUsage1BarMode()
{

}

/**********************************************************************************************/

void RSummaryWidget :: setUsage1TableMode()
{
  m_fieldType = RResultsModel::Usage1;
  setUnits(m_units);
  ensure<RTableView>(this);
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
