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

  public:
    _M Vacuum         RUserAdmTab(RUserTab* userTab, RMainWindow* parent = 0);
    _V Vacuum         ~RUserAdmTab();
    _M void           addField2(const QString& key, const QString& title);
    _M void           addField3(const QString& key, const QString& title);

  public slots:
    _M void           setUser(RUser* user);

  private slots:
    _M void           onActivated(const QModelIndex& index);
    _M void           onField2Changed(bool value);
    _M void           onField3Changed(int newIndex);
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RUSER_ADM_TAB_HH */
