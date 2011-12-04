#include <QtGui/QLabel>
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

  connect(parent->data(), SIGNAL(elementChanged(RElement*,int)),
    m_widget, SLOT(updateElement(RElement*,int)));
  connect(parent, SIGNAL(unitsChanged(RUnitPtrList*)), m_widget, SLOT(setUnits(RUnitPtrList*)));
  connect(m_widget, SIGNAL(modeChanged()), this, SLOT(updateModeName()));

  static_cast<QVBoxLayout*>(layout())->setSizeConstraint(QLayout::SetMinAndMaxSize);
  layout()->addWidget(m_widget);

  updateModeName();
}

/**********************************************************************************************/

Vacuum RSummaryTab :: ~RSummaryTab()
{
}

/**********************************************************************************************/

void RSummaryTab :: updateModeName()
{
  m_label->setText(R_S("Apžvalga: %1").arg(m_widget->modeName()));
}

/**********************************************************************************************/
