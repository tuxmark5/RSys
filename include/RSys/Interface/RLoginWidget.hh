#ifndef RSYS_INTERFACE_RLOGIN_WIDGET_HH
#define RSYS_INTERFACE_RLOGIN_WIDGET_HH

/**********************************************************************************************/
#include <RSys/RSys.hh>
#include <QtGui/QGroupBox>
/********************************************* RS *********************************************/
/*                                        RLoginWidget                                        */
/**********************************************************************************************/

class RLoginWidget: public QWidget
{
  Q_OBJECT

  private:
    _M QGridLayout*   m_innerLayout;
    _M QLineEdit*     m_dbAddressField;
    _M QLineEdit*     m_dbNameField;
    _M QLineEdit*     m_usernameField;
    _M QLineEdit*     m_passwordField;
    _M QPushButton*   m_loginButton;

  public:
    _M Vacuum         RLoginWidget(QWidget* parent = 0);
    _V Vacuum         ~RLoginWidget();
    _M QPushButton*   loginButton() const { return m_loginButton; }

  protected slots:
    _M void           onLoginPressed();

  signals:
    _M void           loggedIn();
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RLOGIN_WIDGET_HH */
