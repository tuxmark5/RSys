#ifndef RSYS_INTERFACE_RUSAGE_WIDGET_HH
#define RSYS_INTERFACE_RUSAGE_WIDGET_HH

/**********************************************************************************************/
#include <RSys/Interface/RLayerWidget.hh>
/********************************************* RS *********************************************/
/*                                        RUsageWidget                                        */
/**********************************************************************************************/

class RUsageWidget: public RLayerWidget
{
  Q_OBJECT

  private:
    _M RElement*      m_element;

  public:
    _M Vacuum         RUsageWidget(RElement* element, QWidget* parent = 0);
    _V Vacuum         ~RUsageWidget();
    _V QString        nameAt(int index) const;
    _V int            numWidgets() const;
    _V QWidget*       widgetAt(int index);
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RUSAGE_WIDGET_HH */
