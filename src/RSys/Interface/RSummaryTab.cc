#include <QtGui/QLayout>
#include <RSys/Core/RData.hh>
#include <RSys/Interface/RMainWindow.hh>
#include <RSys/Interface/RSummaryTab.hh>
#include <RSys/Interface/RSummaryWidget.hh>

/********************************************* RS *********************************************/
/*                                        RSummaryTab                                         */
/**********************************************************************************************/

Vacuum RSummaryTab :: RSummaryTab(RMainWindow* parent):
  RTab(R_S("Apžvalga"), parent)
{
  m_widget = new RSummaryWidget(parent->results(), this);

  RData::connect(parent->data(), SIGNAL(elementChanged(RElement*,int)),
    m_widget, SLOT(updateElement(RElement*,int)));
  connect(parent, SIGNAL(unitsChanged(RUnitPtrList*)), m_widget, SLOT(setUnits(RUnitPtrList*)));

  static_cast<QVBoxLayout*>(layout())->setSizeConstraint(QLayout::SetMinAndMaxSize);
  layout()->addWidget(m_widget);
}

/**********************************************************************************************/

Vacuum RSummaryTab :: ~RSummaryTab()
{
}

/**********************************************************************************************/
