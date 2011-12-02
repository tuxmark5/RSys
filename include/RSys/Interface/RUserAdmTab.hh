#ifndef RSYS_INTERFACE_RUSER_ADM_TAB_HH
#define RSYS_INTERFACE_RUSER_ADM_TAB_HH

/**********************************************************************************************/
#include <RSys/Interface/RTab.hh>
/********************************************* RS *********************************************/
/*                                        RUserAdmTab                                         */
/**********************************************************************************************/

class RUserAdmTab: public RTab
{
  Q_OBJECT

  public:
    _T QHash<QObject*, QString> FieldHash;

  private:
    _M RUser*         m_user;
    _M RUserPtrList*  m_users;
    _M QWidget*       m_widget;
    _M FieldHash      m_fields;
    _M QLineEdit*     m_passField;

  public:
    _M Vacuum         RUserAdmTab(RUserTab* userTab, RMainWindow* parent = 0);
    _V Vacuum         ~RUserAdmTab();
    _M void           addField(const QString& title, QWidget* widget);
    _M void           addField2(const QString& key, const QString& title);
    _M void           addField3(const QString& key, const QString& title);
    _M void           addPasswordField();

  public slots:
    _M void           setUser(RUser* user);

  private slots:
    _M void           onActivated(const QModelIndex& index);
    _M void           onField2Changed(bool value);
    _M void           onField3Changed(int newIndex);
    _M void           onPasswordChanged(const QString& newPass);
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RUSER_ADM_TAB_HH */
