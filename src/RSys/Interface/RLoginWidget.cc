#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <RSys/Interface/RLoginWidget.hh>

/********************************************* RS *********************************************/
/*                                        RLoginWidget                                        */
/**********************************************************************************************/

Vacuum RLoginWidget :: RLoginWidget(QWidget* parent):
  QGroupBox("Prisijungimo duomenys", parent)
{
  QGridLayout* layout = new QGridLayout(this);

  setMinimumSize(400, 200);
  setMaximumSize(600, 200);

  layout->addWidget(new QLabel(QString::fromUtf8("Duomenų bazės adresas")),     0, 0);
  layout->addWidget(m_dbAddressField = new QLineEdit(this), 0, 1);

  layout->addWidget(new QLabel(QString::fromUtf8("Duomenų bazės pavadinimas")), 1, 0);
  layout->addWidget(m_dbNameField = new QLineEdit(this), 1, 1);

  layout->addWidget(new QLabel(QString::fromUtf8("Vartotojo vardas")),          2, 0);
  layout->addWidget(m_usernameField = new QLineEdit(this), 2, 1);

  layout->addWidget(new QLabel(QString::fromUtf8("Slaptažodis")),               3, 0);
  layout->addWidget(m_passwordField = new QLineEdit(this), 3, 1);
  m_passwordField->setEchoMode(QLineEdit::Password);

  m_loginButton = new QPushButton("Prisijungti", this);
  layout->addWidget(m_loginButton, 4, 1);
}

/**********************************************************************************************/

Vacuum RLoginWidget :: ~RLoginWidget()
{
}

/**********************************************************************************************/
