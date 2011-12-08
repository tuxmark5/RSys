#include <QtGui/QAction>
#include <QtGui/QMenu>
#include <QtGui/QPushButton>
#include <RSys/Core/RData.hh>
#include <RSys/Core/RUnit.hh>
#include <RSys/Interface/RChart.hh>
#include <RSys/Interface/RResultsModel.hh>
#include <RSys/Interface/RSummaryWidget.hh>
#include <RSys/Interface/RTableView.hh>
#include <RSys/Interface/RUsageWidget.hh>
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
  setMode(RUsageWidget::Usage1 | RUsageWidget::Hours | RUsageWidget::Table);

  connect(results->data1(), SIGNAL(globalIntervalChanged()), this, SLOT(updateGlobalInterval()));
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
    numVisible += m_units->at(i)->isVisible();
  return numVisible;
}

/**********************************************************************************************/

int RSummaryWidget :: fieldType() const
{
  return (m_mode & 0x0FF) | RResultsModel::Identifier;
}

/**********************************************************************************************/

#define MODE(menu, name, mode) menu->addAction(R_S(name), this, SLOT(setMode()))->setData(int(mode));

void RSummaryWidget :: createButtons(const ButtonCallback& callback)
{
  QPushButton*  button  = new QPushButton(R_S("Rodyti"));
  QMenu*        menu    = RUsageWidget::createModeMenu(this, SLOT(modifyMode()), m_mode);

  connect(menu, SIGNAL(aboutToHide()), menu, SLOT(deleteLater()));
  button->setMenu(menu);
  callback(button);
}

/**********************************************************************************************/

void RSummaryWidget :: insert1(int i0, int i1)
{
  Q_UNUSED(i1);

  m_resultsModel->insertField(countVisible(i0), fieldType(), m_units->at(i0));
}

/**********************************************************************************************/

QString RSummaryWidget :: modeName() const
{
  QString modeName = RResultsModel::longTitleForField(m_mode);

  switch (m_mode & RUsageWidget::ViewMask)
  {
    case RUsageWidget::Bar:   modeName += R_S(" (stulpelinė diagrama)");  break;
    case RUsageWidget::Line:  modeName += R_S(" (linijinė diagrama)");    break;
    case RUsageWidget::Table: modeName += R_S(" (sumarinė lentelė)");     break;
  }

  return modeName;
}

/**********************************************************************************************/

void RSummaryWidget :: modifyMode()
{
  if (QAction* action = qobject_cast<QAction*>(sender()))
  {
    int modifier = action->data().toInt();

    m_mode &= modifier >> 16;
    m_mode |= modifier & 0xFFFF;
    setMode(m_mode);
  }
}

/**********************************************************************************************/

bool RSummaryWidget :: remove0(int i0, int i1)
{
  Q_UNUSED(i1);

  m_resultsModel->removeField(countVisible(i0));
  return true;
}

/**********************************************************************************************/

void RSummaryWidget :: resetBegin()
{
  R_GUARD(m_units, Vacuum);

  m_units->removeObserver(this);
  m_resultsModel->removeFields();
}

/**********************************************************************************************/

void RSummaryWidget :: resetEnd()
{
  R_GUARD(m_units, Vacuum);

  m_units->addObserver(this);

  for (auto it = m_units->begin(); it != m_units->end(); ++it)
  {
    if ((*it)->isVisible())
      m_resultsModel->addField(fieldType(), *it);
  }
}

/**********************************************************************************************/

void RSummaryWidget :: resetObservable()
{
  resetBegin();
  resetEnd();
}

/**********************************************************************************************/

void RSummaryWidget :: setMode(int mode)
{
  m_mode = mode;
  setUnits(m_units);

  switch (mode & RUsageWidget::ViewMask)
  {
    case RUsageWidget::Bar:
      if (RChart* chart = ensure<RChart>(this))
      {
        chart->setType(RChart::Bar);
        chart->setShowLegend(true);
      }
      updateGlobalInterval();
      break;

    case RUsageWidget::Line:
      if (RChart* chart = ensure<RChart>(this))
      {
        chart->setType(RChart::Line);
        chart->setShowLegend(true);
      }
      updateGlobalInterval();
      break;

    case RUsageWidget::Table:
      m_resultsModel->setOrientation(Qt::Horizontal);
      ensure<RTableView>(this)->setFrameStyle(QFrame::NoFrame);
      break;
  }

  emit modeChanged();
}

/**********************************************************************************************/

void RSummaryWidget :: setUnits(RUnitPtrList* units)
{
  resetBegin();
  m_units = units;
  resetEnd();
}

/**********************************************************************************************/

void RSummaryWidget :: updateGlobalInterval()
{
  if (RChart* chart = qobject_cast<RChart*>(widget()))
  {
    chart->setFillRange(1, m_results->data1()->interval1(), QDate(5000, 1, 1));
  }
}

/**********************************************************************************************/

void RSummaryWidget :: updateUnit(RUnit* unit)
{
  int index = m_units->indexOf(unit);
  R_GUARD(index != -1, Vacuum);

  if (unit->isVisible())
    insert1(index, index);
  else
    remove0(index, index);
}

/**********************************************************************************************/
