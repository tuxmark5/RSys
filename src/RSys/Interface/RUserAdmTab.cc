#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QItemSelection>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <RSys/Core/RData.hh>
#include <RSys/Core/RUser.hh>
#include <RSys/Interface/RMainWindow.hh>
#include <RSys/Interface/RTableView.hh>
#include <RSys/Interface/RUserAdmTab.hh>
#include <RSys/Interface/RUserTab.hh>

/**********************************************************************************************/
QStringList g_mode3 = QStringList()
  << R_S("Nerodyti")
  << R_S("Leisti skaityti")
  << R_S("Leisti skaityti ir rašyti");
/********************************************* RS *********************************************/
/*                                        RUserAdmTab                                         */
/**********************************************************************************************/

Vacuum RUserAdmTab :: RUserAdmTab(RUserTab* userTab, RMainWindow* parent):
  RTab(R_S("Naudotojų administravimas"), parent),
  m_user((RUser*) 1), // overwritten by setUser
  m_users(parent->data()->users()),
  m_widget(new QWidget(this))
{
  QGridLayout*  layout1   = new QGridLayout(m_widget);
  QSpacerItem*  spacer    = new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
  RTableView*   tableView = userTab->findChild<RTableView*>();

  connect(tableView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
    this, SLOT(onSelectionChanged(QItemSelection,QItemSelection)));

  addField3("mea",  R_S("Paramos priem."));
  addField3("div",  R_S("Padaliniai"));
  addField3("sys",  R_S("IS"));
  addField3("meaA", R_S("Paramos priem. adm."));
  addField3("sysA", R_S("IS adm."));
  addField3("sub",  R_S("Istoriniai duomenys"));

  addField2("dM",   R_S("Rodyti režimą: padaliniai"));
  addField2("sM",   R_S("Rodyti režimą: IS"));
  addField2("res",  R_S("Rodyti rezultatų kortelę"));
  addField2("sum",  R_S("Rodyti apžvalgos kortelę"));
  addField2("imp",  R_S("Leisti importuoti duomenis"));
  addPasswordField();
  layout1->addItem(spacer, layout1->rowCount(), 0, 1, 2);

  m_widget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

  layout()->addWidget(m_widget);
  setMinimumHeight(350);
  setUser(0);
}

/**********************************************************************************************/

Vacuum RUserAdmTab :: ~RUserAdmTab()
{
}

/**********************************************************************************************/

void RUserAdmTab :: addField(const QString& title, QWidget* widget)
{
  QGridLayout*  layout    = static_cast<QGridLayout*>(m_widget->layout());
  QLabel*       label     = new QLabel(title);
  int           row       = layout->rowCount();

  layout->addWidget(label, row, 0, 1, 1);
  layout->addWidget(widget, row, 1, 1, 1);
}

/**********************************************************************************************/

void RUserAdmTab :: addField2(const QString& key, const QString& title)
{
  QCheckBox*    checkBox  = new QCheckBox();

  addField(title, checkBox);
  connect(checkBox, SIGNAL(toggled(bool)), this, SLOT(onField2Changed(bool)));
  m_fields.insert(checkBox, key);
}

/**********************************************************************************************/

void RUserAdmTab :: addField3(const QString& key, const QString& title)
{
  QComboBox*    comboBox  = new QComboBox();

  addField(title, comboBox);
  comboBox->addItems(g_mode3);
  connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onField3Changed(int)));
  m_fields.insert(comboBox, key);
}

/**********************************************************************************************/

void RUserAdmTab :: addPasswordField()
{
  m_passField = new QLineEdit();
  m_passField->setEchoMode(QLineEdit::PasswordEchoOnEdit);
  addField(R_S("Naujas slaptažodis"), m_passField);
  connect(m_passField, SIGNAL(textEdited(QString)), this, SLOT(onPasswordChanged(QString)));
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
  if (key == "mea")
    m_user->setProperty("grp", newIndex);
}

/**********************************************************************************************/

void RUserAdmTab :: onPasswordChanged(const QString& newPass)
{
  m_user->setPassword(newPass);
}

/**********************************************************************************************/

void RUserAdmTab :: onSelectionChanged(const QItemSelection& sel1, const QItemSelection& sel0)
{
  Q_UNUSED(sel0);

  RUser* user = [&]() -> RUser*
  {
    QModelIndexList sel1List  = sel1.indexes();
    R_GUARD(sel1List.size() >= 1, 0);
    QModelIndex     index     = sel1List.first();
    R_GUARD(index.isValid() && index.row() < m_users->size(), 0);
    return m_users->at(index.row());
  }();

  setUser(user);
}

/**********************************************************************************************/

void RUserAdmTab :: setUser(RUser* user)
{
  R_GUARD(m_user != user, Vacuum);

  if ((m_user = user))
  {
    m_label->setText(R_S("Sistemos naudotojų administravimas"));
    m_widget->setEnabled(true);
  }
  else
  {
    m_label->setText(R_S("Pasirinkite naudotoją kortelėje <b>Naudotojai</b>"));
    m_widget->setEnabled(false);
  }

  R_GUARD(user, Vacuum);

  for (auto it = m_fields.begin(); it != m_fields.end(); ++it)
  {
    int value = m_user->property(*it);

    /**/ if (QCheckBox* checkBox = qobject_cast<QCheckBox*>(it.key()))
      checkBox->setChecked(value);
    else if (QComboBox* comboBox = qobject_cast<QComboBox*>(it.key()))
      comboBox->setCurrentIndex(value);
  }

  m_passField->setText(QString());
}

/**********************************************************************************************/
