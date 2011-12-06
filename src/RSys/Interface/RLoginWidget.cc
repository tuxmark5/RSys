#include <QtCore/QSettings>
#include <QtGui/QFileDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTabWidget>
#include <RSys/Interface/RLoginWidget.hh>
#include <RSys/Interface/RMessage.hh>
#include <RSys/Store/RDatabase.hh>

/**********************************************************************************************/

struct RSquare: public QWidget
{
  _M QWidget*   m_widget;
  _M Vacuum     RSquare(QWidget* widget):
    m_widget(widget) { widget->setParent(this); }

  _M void       resizeEvent(QResizeEvent*)
  {
    int   a = qMin(width(), height());
    int   x = (width() - a) / 2;
    int   y = (height() - a) / 2;
    m_widget->setGeometry(x, y, a, a);
  }

  _M QSize      sizeHint() const
  { return m_widget->sizeHint(); }
};

/********************************************* RS *********************************************/
/*                                        RLoginWidget                                        */
/**********************************************************************************************/

Vacuum RLoginWidget :: RLoginWidget(RDatabase* database, QWidget* parent):
  QWidget(parent),
  m_database(database)
{
  QGridLayout*  layout0     = new QGridLayout(this);
  QLabel*       logo        = new QLabel();
  QTabWidget*   tabWidget   = new QTabWidget();
  QSpacerItem*  spacer      = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

  tabWidget->setMinimumSize(400, 200);
  tabWidget->setMaximumSize(600, 300);
  tabWidget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

  tabWidget->addTab(createRemoteTab(),  R_S("Nuotolinis prisijungimas"));
  tabWidget->addTab(createLocalTab(),   R_S("Vietinė DB"));

  logo->setPixmap(QPixmap(":/logo.png"));
  logo->setScaledContents(true);

  layout0->addWidget(tabWidget,         0, 0, 1, 1, Qt::AlignVCenter);
  layout0->addWidget(new RSquare(logo), 0, 1, 1, 1, Qt::AlignVCenter);

  //layout0->addItem(spacer, 2, 0, 1, 1);
  //layout0->setRowStretch(0, 1);
  //layout0->setRowStretch(2, 1);

  m_dbAddressField->setText(g_settings->value("dbAddress", "127.0.0.1").toString());
  m_dbNameField->setText(g_settings->value("dbName", "test.db").toString());
  m_usernameField->setText(g_settings->value("dbUser", "user").toString());
  m_dbFileField->setText(g_settings->value("dbFile", "").toString());

  connect(m_database, SIGNAL(message(QString)), this, SLOT(showMessage(QString)));
}

/**********************************************************************************************/

Vacuum RLoginWidget :: ~RLoginWidget()
{
}

/**********************************************************************************************/

QWidget* RLoginWidget :: createLocalTab()
{
  QWidget*      widget        = new QWidget();
  QGridLayout*  layout        = new QGridLayout(widget);
  QPushButton*  loginButton   = new QPushButton("Atverti");
  QPushButton*  openButton    = new QPushButton("...");

  openButton->setFixedSize(25, 20);

  m_dbFileField = new QLineEdit();

  layout->addWidget(new QLabel(R_S("Duomenų bazė")), 0, 0);
  layout->addWidget(m_dbFileField, 0, 1);
  layout->addWidget(openButton, 0, 2);

  layout->addWidget(loginButton, 1, 1, 1, 2);

  connect(openButton, SIGNAL(clicked()), this, SLOT(onOpenDatabasePressed()));
  connect(loginButton, SIGNAL(clicked()), this, SLOT(onLocalLoginPressed()));

  return widget;
}

/**********************************************************************************************/

QWidget* RLoginWidget :: createRemoteTab()
{
  QWidget*      widget  = new QWidget();
  QGridLayout*  layout  = new QGridLayout(widget);
  QPushButton*  loginButton;

  m_usernameField     = new QLineEdit(this);
  m_passwordField     = new QLineEdit(this);
  loginButton         = new QPushButton("Prisijungti", this);
  m_dbAddressField    = new QLineEdit(this);
  m_dbNameField       = new QLineEdit(this);

  layout->addWidget(new QLabel(R_S("Duomenų bazės adresas")),     0, 0);
  layout->addWidget(m_dbAddressField, 0, 1);

  layout->addWidget(new QLabel(R_S("Duomenų bazės pavadinimas")), 1, 0);
  layout->addWidget(m_dbNameField, 1, 1);

  layout->addWidget(new QLabel(R_S("Naudotojo vardas")),          2, 0);
  layout->addWidget(m_usernameField, 2, 1);

  layout->addWidget(new QLabel(R_S("Slaptažodis")),               3, 0);
  layout->addWidget(m_passwordField, 3, 1);
  m_passwordField->setEchoMode(QLineEdit::Password);

  layout->addWidget(loginButton, 4, 1);
  loginButton->setDefault(true);

  QLineEdit::connect(m_dbAddressField, SIGNAL(returnPressed()), this, SLOT(onRemoteLoginPressed()));
  QLineEdit::connect(m_dbNameField, SIGNAL(returnPressed()), this, SLOT(onRemoteLoginPressed()));
  QLineEdit::connect(m_usernameField, SIGNAL(returnPressed()), this, SLOT(onRemoteLoginPressed()));
  QLineEdit::connect(m_passwordField, SIGNAL(returnPressed()), this, SLOT(onRemoteLoginPressed()));
  QPushButton::connect(loginButton, SIGNAL(clicked()), this, SLOT(onRemoteLoginPressed()));

  return widget;
}

/**********************************************************************************************/

void RLoginWidget :: showMessage(const QString& message)
{
  if (m_message)
    m_message->deleteLater();
  m_message = new RMessage(message, 10000);
  m_message->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Minimum);

  if (QGridLayout* l = static_cast<QGridLayout*>(layout()))
    l->addWidget(m_message, l->rowCount() - 1, 0, 1, 1, Qt::AlignTop);
}

/**********************************************************************************************/

void RLoginWidget :: onLocalLoginPressed()
{
  QString dbFile = m_dbFileField->text();

  g_settings->setValue("dbFile", dbFile);

  if (m_database->login(dbFile))
  {
    emit loggedIn();
  }
}

/**********************************************************************************************/

void RLoginWidget :: onOpenDatabasePressed()
{
  QString dbFile = QFileDialog::getOpenFileName(this, R_S("Duomenų bazė"));

  if (!dbFile.isNull())
  {
    m_dbFileField->setText(dbFile);
  }
}

/**********************************************************************************************/

void RLoginWidget :: onRemoteLoginPressed()
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
