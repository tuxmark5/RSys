#include <RSys/Core/RMeasure.hh>
#include <RSys/Interface/RMainWindow.hh>
#include <RSys/Interface/RMeasureTab.hh>
#include <RSys/Util/RContainer.hh>

/********************************************* RS *********************************************/
/*                                        RMeasureTab                                         */
/**********************************************************************************************/

Vacuum RMeasureTab :: RMeasureTab(RMeasureList* measures, RMainWindow* parent):
  RTab("AAA", parent)
{
  auto c = newContainer(measures);

  c->addColumn<QString, &RMeasure::identifier, &RMeasure::setIdentifier> (QString::fromUtf8("Pavadinimas"));
  c->addColumn<QString, &RMeasure::name,       &RMeasure::setName>       (QString::fromUtf8("Aprašymas"));
  c->setAlloc([]() { return new RMeasure(0); });

  makeTable1DTab(c);
}

/**********************************************************************************************/

Vacuum RMeasureTab :: ~RMeasureTab()
{
}

/**********************************************************************************************/
