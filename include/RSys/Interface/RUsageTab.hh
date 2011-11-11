#ifndef RSYS_INTERFACE_RTAB_HH
#define RSYS_INTERFACE_RTAB_HH

/**********************************************************************************************/
#include <RSys/Interface/RTab.hh>
/********************************************* RS *********************************************/
/*                                         RUsageTab                                          */
/**********************************************************************************************/

class RUsageTab: public RTab, public RIObserver
{
  Q_OBJECT

  private:
    _T ROList<RElement*>  List;

  private:
    _M QScrollArea*   m_scrollArea;
    _M QVBoxLayout*   m_innerLayout;
    _M QWidget*       m_innerWidget;
    _M bool           m_systemsMode: 1;

    _M List*          m_current;
    _M List*          m_divisions;
    _M List*          m_systems;

  public:
    _M Vacuum         RUsageTab(RMainWindow* parent = 0);
    _V Vacuum         ~RUsageTab();
    _V void           insert1(int i0, int i1);
    _V bool           remove0(int i0, int i1);
    _V void           resizeEvent(QResizeEvent* event);

  protected:
    _M void           destroyWidgets();
    _M void           populateWidgets();

  public slots:
    _M void           setMode(bool systems);
    _M void           showElement(RElement* element, bool show);
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RTAB_HH */
