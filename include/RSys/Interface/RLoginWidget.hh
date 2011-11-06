#ifndef RSYS_INTERFACE_RLOGIN_WIDGET_HH
#define RSYS_INTERFACE_RLOGIN_WIDGET_HH

/**********************************************************************************************/
#include <RSys/RSys.hh>
#include <QtGui/QGroupBox>
/********************************************* RS *********************************************/
/*                                        RLoginWidget                                        */
/**********************************************************************************************/

class RLoginWidget: public QGroupBox
{
  Q_OBJECT

  private:
    _M QLineEdit*     m_dbAddressField;
    _M QLineEdit*     m_dbNameField;
    _M QLineEdit*     m_usernameField;
    _M QLineEdit*     m_passwordField;
    _M QPushButton*   m_loginButton;

  public:
    _M Vacuum         RLoginWidget(QWidget* parent = 0);
    _V Vacuum         ~RLoginWidget();
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RLOGIN_WIDGET_HH */
