#include <RSys/Core/RDivision.hh>
#include <RSys/Interface/RMainWindow.hh>
#include <RSys/Interface/RDivisionTab.hh>
#include <RSys/Util/RContainer.hh>

/********************************************* RS *********************************************/
/*                                        RDivisionTab                                        */
/**********************************************************************************************/

Vacuum RDivisionTab :: RDivisionTab(RDivisionList* divisions, RMainWindow* parent):
  RTab("AAA", parent)
{
  auto c = newContainer(divisions);

  c->addColumn<QString, &RDivision::identifier, &RDivision::setIdentifier> (QString::fromUtf8("Pavadinimas"));
  c->addColumn<QString, &RDivision::name,       &RDivision::setName>       (QString::fromUtf8("Aprašymas"));
  c->setAlloc([]() { return new RDivision(0); });

  makeTable1DTab(c);
}

/**********************************************************************************************/

Vacuum RDivisionTab :: ~RDivisionTab()
{
}

/**********************************************************************************************/
