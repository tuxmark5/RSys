#include <RSys/Core/RData.hh>
#include <RSys/Core/RUser.hh>
#include <RSys/Interface/RMainWindow.hh>
#include <RSys/Interface/RUserTab.hh>
#include <RSys/Util/RContainer.hh>

/********************************************* RS *********************************************/
/*                                          RUserTab                                          */
/**********************************************************************************************/

Vacuum RUserTab :: RUserTab(RMainWindow* parent):
  RTab(R_S("Sistemos naudotojai"), parent)
{
  auto uc = newContainer(parent->data()->users());
  uc->addColumn("Naudotojas");
  uc->addColumn("Pilnas vardas");
  uc->addAccessor2<QString>(0, Qt::DisplayRole) >> &RUser::userName     << &RUser::setUserName;
  uc->addAccessor2<QString>(0, Qt::ToolTipRole) >> &RUser::description;
  uc->addAccessor2<QString>(1, Qt::DisplayRole) >> &RUser::description  << &RUser::setDescription;
  uc->setAlloc([=]() { return RUser::createUser(parent->data()); });

  makeTable1DTab(m_userContainer = uc);
}

/**********************************************************************************************/

Vacuum RUserTab :: ~RUserTab()
{

}

/**********************************************************************************************/
