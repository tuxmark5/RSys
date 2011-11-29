#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <RSys/Interface/RMainWindow.hh>
#include <RSys/Interface/RUserAdmTab.hh>

/**********************************************************************************************/
QStringList g_mode3 = QStringList()
  << R_S("Nerodyti")
  << R_S("Leisti tik skaityti")
  << R_S("Leisti ir rašyti");
/********************************************* RS *********************************************/
/*                                        RUserAdmTab                                         */
/**********************************************************************************************/

Vacuum RUserAdmTab :: RUserAdmTab(RMainWindow* parent):
  RTab(R_S("Naudotojų administravimas"), parent),
  m_widget(new QWidget(this))
{
  QGridLayout*  layout1   = new QGridLayout(m_widget);
  QSpacerItem*  spacer    = new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

  addField3("mea",  R_S("Paramos priem."));
  addField3("div",  R_S("Padaliniai"));
  addField3("sys",  R_S("IS"));
  addField3("meaA", R_S("Paramos priem. adm."));
  addField3("sysA", R_S("IS adm."));
  addField3("sub",  R_S("Istoriniai duomenys"));

  addField2("dM",   R_S("Rėžimas: padaliniai"));
  addField2("dS",   R_S("Rėžimas: IS"));
  addField2("res",  R_S("Rezultatų kortelė"));
  addField2("sum",  R_S("Apžvalgos kortelė"));
  layout1->addItem(spacer, layout1->rowCount(), 0, 1, 2);

  m_widget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

  layout()->addWidget(m_widget);
}

/**********************************************************************************************/

Vacuum RUserAdmTab :: ~RUserAdmTab()
{
}

/**********************************************************************************************/

void RUserAdmTab :: addField2(const QString& key, const QString& title)
{
  QGridLayout*  layout    = static_cast<QGridLayout*>(m_widget->layout());
  QLabel*       label     = new QLabel(title);
  QCheckBox*    checkBox  = new QCheckBox();
  int           row       = layout->rowCount();

  layout->addWidget(label, row, 0, 1, 1);
  layout->addWidget(checkBox, row, 1, 1, 1);
}

/**********************************************************************************************/

void RUserAdmTab :: addField3(const QString& key, const QString& title)
{
  QGridLayout*  layout    = static_cast<QGridLayout*>(m_widget->layout());
  QLabel*       label     = new QLabel(title);
  QComboBox*    comboBox  = new QComboBox();
  int           row       = layout->rowCount();

  comboBox->addItems(g_mode3);
  layout->addWidget(label, row, 0, 1, 1);
  layout->addWidget(comboBox, row, 1, 1, 1);
}

/**********************************************************************************************/
