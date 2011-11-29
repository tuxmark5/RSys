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

  private:
    _M RMainWindow*   m_mainWindow;
    _M QWidget*       m_widget;

  public:
    _M Vacuum         RUserAdmTab(RMainWindow* parent = 0);
    _V Vacuum         ~RUserAdmTab();
    _M void           addField2(const QString& key, const QString& title);
    _M void           addField3(const QString& key, const QString& title);
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RUSER_ADM_TAB_HH */
