#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <RSys/Interface/RLoginWidget.hh>
#include <RSys/Interface/RMessage.hh>
#include <RSys/Store/RDatabase.hh>

/********************************************* RS *********************************************/
/*                                        RLoginWidget                                        */
/**********************************************************************************************/

Vacuum RLoginWidget :: RLoginWidget(RDatabase* database, QWidget* parent):
  QWidget(parent),
  m_database(database)
{
  QGridLayout*  layout0 = new QGridLayout(this);
  QGroupBox*    group   = new QGroupBox("Prisijungimo duomenys", this);
  m_innerLayout         = new QGridLayout(group);

  group->setMinimumSize(400, 200);
  group->setMaximumSize(600, 200);

  m_innerLayout->addWidget(new QLabel(QString::fromUtf8("Duomenų bazės adresas")),     0, 0);
  m_innerLayout->addWidget(m_dbAddressField = new QLineEdit(this), 0, 1);

  m_innerLayout->addWidget(new QLabel(QString::fromUtf8("Duomenų bazės pavadinimas")), 1, 0);
  m_innerLayout->addWidget(m_dbNameField = new QLineEdit(this), 1, 1);

  m_innerLayout->addWidget(new QLabel(QString::fromUtf8("Vartotojo vardas")),          2, 0);
  m_innerLayout->addWidget(m_usernameField = new QLineEdit(this), 2, 1);

  m_innerLayout->addWidget(new QLabel(QString::fromUtf8("Slaptažodis")),               3, 0);
  m_innerLayout->addWidget(m_passwordField = new QLineEdit(this), 3, 1);
  m_passwordField->setEchoMode(QLineEdit::Password);

  m_loginButton = new QPushButton("Prisijungti", this);
  m_loginButton->setDefault(true);

  QLineEdit::connect(m_dbAddressField, SIGNAL(returnPressed()), this, SLOT(onLoginPressed()));
  QLineEdit::connect(m_dbNameField, SIGNAL(returnPressed()), this, SLOT(onLoginPressed()));
  QLineEdit::connect(m_usernameField, SIGNAL(returnPressed()), this, SLOT(onLoginPressed()));
  QLineEdit::connect(m_passwordField, SIGNAL(returnPressed()), this, SLOT(onLoginPressed()));
  QPushButton::connect(m_loginButton, SIGNAL(clicked()), this, SLOT(onLoginPressed()));

  m_innerLayout->addWidget(m_loginButton, 4, 1);
  layout0->addWidget(group, 0, 0);

  m_dbAddressField->setText("127.0.0.1");
  m_dbNameField->setText("test.db");
  m_usernameField->setText("user");
}

/**********************************************************************************************/

Vacuum RLoginWidget :: ~RLoginWidget()
{
}

/**********************************************************************************************/

void RLoginWidget :: onLoginPressed()
{
  QString   dbAddress   = m_dbAddressField->text();
  QString   dbName      = m_dbNameField->text();
  QString   userName    = m_usernameField->text();
  QString   password    = m_passwordField->text();

  if (m_database->login(dbAddress, dbName, userName, password))
  {
    emit loggedIn();
  }
  else
  {
    QString text = QString::fromUtf8("Neteisingas vartotojo vardas arba slaptažodis");
    m_innerLayout->addWidget(new RMessage(text), m_innerLayout->rowCount(), 0, 1, 2);
  }
}

/**********************************************************************************************/
