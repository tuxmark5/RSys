#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <RSys/Core/RData.hh>
#include <RSys/Core/RUser.hh>
#include <RSys/Interface/RMainWindow.hh>
#include <RSys/Interface/RTableView.hh>
#include <RSys/Interface/RUserAdmTab.hh>
#include <RSys/Interface/RUserTab.hh>

/**********************************************************************************************/
QStringList g_mode3 = QStringList()
  << R_S("Nerodyti")
  << R_S("Leisti tik skaityti")
  << R_S("Leisti ir rašyti");
/********************************************* RS *********************************************/
/*                                        RUserAdmTab                                         */
/**********************************************************************************************/

Vacuum RUserAdmTab :: RUserAdmTab(RUserTab* userTab, RMainWindow* parent):
  RTab(R_S("Naudotojų administravimas"), parent),
  m_user(0),
  m_users(parent->data()->users()),
  m_widget(new QWidget(this))
{
  QGridLayout*  layout1   = new QGridLayout(m_widget);
  QSpacerItem*  spacer    = new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
  RTableView*   tableView = userTab->findChild<RTableView*>();

  connect(tableView, SIGNAL(activated(QModelIndex)), this, SLOT(onActivated(const QModelIndex&)));

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

  m_widget->setEnabled(false);
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

  connect(checkBox, SIGNAL(toggled(bool)), this, SLOT(onField2Changed(bool)));
  m_fields.insert(checkBox, key);
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

  connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onField3Changed(int)));
  m_fields.insert(comboBox, key);
}

/**********************************************************************************************/

void RUserAdmTab :: onActivated(const QModelIndex& index)
{
  if (index.isValid() && index.row() < m_users->size())
    setUser(m_users->at(index.row()));
  else
    setUser(0);
}

/**********************************************************************************************/

void RUserAdmTab :: onField2Changed(bool value)
{
  QString key = m_fields.value(sender());
  m_user->setProperty(key, value);
}

/**********************************************************************************************/

void RUserAdmTab :: onField3Changed(int newIndex)
{
  QString key = m_fields.value(sender());
  m_user->setProperty(key, newIndex);
}

/**********************************************************************************************/

void RUserAdmTab :: setUser(RUser* user)
{
  m_user = user;
  m_widget->setEnabled(bool(user));

  if (user)
  {
    for (auto it = m_fields.begin(); it != m_fields.end(); ++it)
    {
      int value = m_user->property(*it);

      /**/ if (QCheckBox* checkBox = qobject_cast<QCheckBox*>(it.key()))
        checkBox->setChecked(value);
      else if (QComboBox* comboBox = qobject_cast<QComboBox*>(it.key()))
        comboBox->setCurrentIndex(value);
    }
  }
}

/**********************************************************************************************/
