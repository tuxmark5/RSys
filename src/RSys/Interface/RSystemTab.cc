#include <RSys/Core/RSystem.hh>
#include <RSys/Interface/RMainWindow.hh>
#include <RSys/Interface/RSystemTab.hh>
#include <RSys/Util/RContainer.hh>

/********************************************* RS *********************************************/
/*                                         RSystemTab                                         */
/**********************************************************************************************/

Vacuum RSystemTab :: RSystemTab(RSystemList* systems, RMainWindow* parent):
  RTab("AAA", parent)
{
  auto c = newContainer(systems);

  c->addColumn<QString, &RSystem::identifier, &RSystem::setIdentifier> (QString::fromUtf8("Pavadinimas"));
  c->addColumn<QString, &RSystem::name,       &RSystem::setName>       (QString::fromUtf8("Aprašymas"));
  c->setAlloc([]() { return new RSystem(0); });

  makeTable1DTab(c);
}

/**********************************************************************************************/

Vacuum RSystemTab :: ~RSystemTab()
{
}

/**********************************************************************************************/
