#ifndef RSYS_INTERFACE_RLOGIN_WIDGET_HH
#define RSYS_INTERFACE_RLOGIN_WIDGET_HH

/**********************************************************************************************/
#include <QtCore/QPointer>
#include <QtGui/QGroupBox>
#include <RSys/RSys.hh>
/********************************************* RS *********************************************/
/*                                        RLoginWidget                                        */
/**********************************************************************************************/

class RLoginWidget: public QWidget
{
  Q_OBJECT

  public:
    _T QPointer<RMessage> RMessagePtr;

  private:
    _M RDatabase*       m_database;
    _M QGridLayout*     m_innerLayout;

    _M QLineEdit*       m_dbAddressField;
    _M QLineEdit*       m_dbNameField;
    _M QLineEdit*       m_usernameField;
    _M QLineEdit*       m_passwordField;

    _M QLineEdit*       m_dbFileField;
    _M RMessagePtr      m_message;

  public:
    _M Vacuum           RLoginWidget(RDatabase* database, QWidget* parent = 0);
    _V Vacuum           ~RLoginWidget();

  private:
    _M QWidget*         createLocalTab();
    _M QWidget*         createRemoteTab();
    _M void             loadData();

  public slots:
    _M void             showMessage(const QString& message);

  protected slots:
    _M void             onLocalCreatePressed();
    _M void             onLocalLoginPressed();
    _M void             onOpenDatabasePressed();
    _M void             onRemoteLoginPressed();

  signals:
    _M void             loginBegin();
    _M void             loginEnd(bool success);
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RLOGIN_WIDGET_HH */
