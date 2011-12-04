#ifndef RSYS_INTERFACE_RSUMMARY_TAB_HH
#define RSYS_INTERFACE_RSUMMARY_TAB_HH

/**********************************************************************************************/
#include <RSys/Interface/RTab.hh>
/********************************************* RS *********************************************/
/*                                        RSummaryTab                                         */
/**********************************************************************************************/

class RSummaryTab: public RTab
{
  Q_OBJECT

  public:
    _M RResultsModel*   m_resultsModel;
    _M RSummaryWidget*  m_widget;

  public:
    _M Vacuum           RSummaryTab(RMainWindow* parent = 0);
    _V Vacuum           ~RSummaryTab();

  public slots:
    _M void             updateModeName();
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RSUMMARY_TAB_HH */
