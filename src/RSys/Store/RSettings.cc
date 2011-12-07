#include <QtCore/QSettings>
#include <RSys/Core/RData.hh>
#include <RSys/Store/RSettings.hh>

/********************************************* RS *********************************************/
/*                                         RSettings                                          */
/**********************************************************************************************/

QString RSettings :: keyForUnit(RUnit* unit)
{
  QString key;

  switch (unit->type())
  {
    case RUnit::Division: key = "div_"; break;
    case RUnit::Measure:  key = "mea_"; break;
    case RUnit::System:   key = "sys_"; break;
  }

  return key + QString::number(unit->id(), 16);
}

/**********************************************************************************************/

void RSettings :: loadUnitSettings(RData* data)
{
  loadUnitSettings(data->divisions()->cast<RUnitPtr>());
  loadUnitSettings(data->systems()->cast<RUnitPtr>());
}

/**********************************************************************************************/

void RSettings :: loadUnitSettings(RUnitPtrList* units)
{
  for (auto it = units->begin(); it != units->end(); ++it)
  {
    QString key = keyForUnit(*it);
    (*it)->setViewMode(g_settings->value(key + "_vm", -1).toInt());
    (*it)->setVisibleRaw(g_settings->value(key + "_vs", true).toBool());
  }
}

/**********************************************************************************************/

void RSettings :: saveUnitSettings(RData* data)
{
  saveUnitSettings(data->divisions()->cast<RUnitPtr>());
  saveUnitSettings(data->systems()->cast<RUnitPtr>());
}

/**********************************************************************************************/

void RSettings :: saveUnitSettings(RUnitPtrList* units)
{
  for (auto it = units->begin(); it != units->end(); ++it)
  {
    if ((*it)->id() != -1)
    {
      QString key = keyForUnit(*it);
      g_settings->setValue(key + "_vm", (*it)->viewMode());
      g_settings->setValue(key + "_vs", (*it)->isVisible());
    }
  }
}

/**********************************************************************************************/
