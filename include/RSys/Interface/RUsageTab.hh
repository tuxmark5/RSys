#ifndef RSYS_INTERFACE_RUSAGE_TAB_HH
#define RSYS_INTERFACE_RUSAGE_TAB_HH

/**********************************************************************************************/
#include <RSys/Interface/RTab.hh>
/********************************************* RS *********************************************/
/*                                         RUsageTab                                          */
/**********************************************************************************************/

class RUsageTab: public RTab, public RIObserver
{
  Q_OBJECT

  private:
    _M RMainWindow*   m_mainWindow;
    _M QScrollArea*   m_scrollArea;
    _M QVBoxLayout*   m_innerLayout;
    _M QWidget*       m_innerWidget;

    _M RResults*      m_results;
    _M RUnitPtrList*  m_units;
    _M int            m_defaultMode;

  public:
    _M Vacuum         RUsageTab(RMainWindow* parent = 0);
    _V Vacuum         ~RUsageTab();
    _V void           insert1(int i0, int i1);
    _V bool           remove0(int i0, int i1);
    _V void           resetObservable0();
    _V void           resetObservable();
    _V void           resizeEvent(QResizeEvent* event);

  protected:
    _V void           clearUnits();
    _M RUsageWidget*  createWidget(RUnit* unit);
    _V void           populateUnits();

  public slots:
    _M void           setMode();
    _M void           setUnits(RUnitPtrList* units);
    _M void           updateElement(RElement* unit, int updateType);
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RUSAGE_TAB_HH */
