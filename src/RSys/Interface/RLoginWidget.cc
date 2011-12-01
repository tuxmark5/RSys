#include <QtCore/QSettings>
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
  QLabel*       logo    = new QLabel();
  QGroupBox*    group   = new QGroupBox("Prisijungimo duomenys", this);
  m_innerLayout         = new QGridLayout(group);

  group->setMinimumSize(400, 200);
  group->setMaximumSize(600, 200);

  m_usernameField     = new QLineEdit(this);
  m_passwordField     = new QLineEdit(this);
  m_loginButton       = new QPushButton("Prisijungti", this);
  m_dbAddressField    = new QLineEdit(this);
  m_dbNameField       = new QLineEdit(this);

  m_innerLayout->addWidget(new QLabel(QString::fromUtf8("Duomenų bazės adresas")),     0, 0);
  m_innerLayout->addWidget(m_dbAddressField, 0, 1);

  m_innerLayout->addWidget(new QLabel(QString::fromUtf8("Duomenų bazės pavadinimas")), 1, 0);
  m_innerLayout->addWidget(m_dbNameField, 1, 1);

  m_innerLayout->addWidget(new QLabel(QString::fromUtf8("Vartotojo vardas")),          2, 0);
  m_innerLayout->addWidget(m_usernameField, 2, 1);

  m_innerLayout->addWidget(new QLabel(QString::fromUtf8("Slaptažodis")),               3, 0);
  m_innerLayout->addWidget(m_passwordField, 3, 1);
  m_passwordField->setEchoMode(QLineEdit::Password);

  m_loginButton->setDefault(true);

  RDatabase::connect(m_database, SIGNAL(message(QString)), this, SLOT(showMessage(QString)));
  QLineEdit::connect(m_dbAddressField, SIGNAL(returnPressed()), this, SLOT(onLoginPressed()));
  QLineEdit::connect(m_dbNameField, SIGNAL(returnPressed()), this, SLOT(onLoginPressed()));
  QLineEdit::connect(m_usernameField, SIGNAL(returnPressed()), this, SLOT(onLoginPressed()));
  QLineEdit::connect(m_passwordField, SIGNAL(returnPressed()), this, SLOT(onLoginPressed()));
  QPushButton::connect(m_loginButton, SIGNAL(clicked()), this, SLOT(onLoginPressed()));

  m_innerLayout->addWidget(m_loginButton, 4, 1);

  logo->setPixmap(QPixmap(":/logo.png"));
  layout0->addWidget(logo, 0, 0, 1, 1, Qt::AlignHCenter);
  layout0->addWidget(group, 1, 0, 1, 1, Qt::AlignTop);

  m_dbAddressField->setText(g_settings->value("dbAddress", "127.0.0.1").toString());
  m_dbNameField->setText(g_settings->value("dbName", "test.db").toString());
  m_usernameField->setText(g_settings->value("dbUser", "user").toString());
}

/**********************************************************************************************/

Vacuum RLoginWidget :: ~RLoginWidget()
{
}

/**********************************************************************************************/

void RLoginWidget :: showMessage(const QString& message)
{
  if (m_message)
    m_message->deleteLater();
  m_message = new RMessage(message, 10000);
  m_innerLayout->addWidget(m_message, m_innerLayout->rowCount(), 0, 1, 2);
}

/**********************************************************************************************/

void RLoginWidget :: onLoginPressed()
{
  QString   dbAddress   = m_dbAddressField->text();
  QString   dbName      = m_dbNameField->text();
  QString   userName    = m_usernameField->text();
  QString   password    = m_passwordField->text();

  g_settings->setValue("dbAddress",   dbAddress);
  g_settings->setValue("dbName",      dbName);
  g_settings->setValue("dbUser",      userName);

  if (m_database->login(dbAddress, dbName, userName, password))
  {
    emit loggedIn();
  }
}

/**********************************************************************************************/
