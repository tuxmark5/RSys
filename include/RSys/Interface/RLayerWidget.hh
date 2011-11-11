#ifndef RSYS_INTERFACE_RLAYER_WIDGET_HH
#define RSYS_INTERFACE_RLAYER_WIDGET_HH

/**********************************************************************************************/
#include <RSys/RSys.hh>
#include <QtGui/QWidget>
/********************************************* RS *********************************************/
/*                                        RLayerWidget                                        */
/**********************************************************************************************/

class RLayerWidget: public QWidget
{
  Q_OBJECT

  public:
    _M Vacuum         RLayerWidget(QWidget* parent = 0);
    _V Vacuum         ~RLayerWidget();
    _V QString        nameAt(int index) const;
    _V int            numWidgets() const;
    _V QWidget*       widgetAt(int index);

  protected:
    _V void           enterEvent(QEvent* event);
    _V bool           event(QEvent* event);
    _V void           leaveEvent(QEvent* event);
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RLAYER_WIDGET_HH */
