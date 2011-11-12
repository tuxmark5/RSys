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
    _T std::function<void (QPushButton*)> ButtonCallback;

  private:
    _M QWidget*       m_widget;

  public:
    _M Vacuum         RLayerWidget(QWidget* parent = 0);
    _V Vacuum         ~RLayerWidget();
    _M void           setWidget(QWidget* widget);
    _V QWidget*       widget() const { return m_widget; }

  protected:
    _V void           createButtons(const ButtonCallback& callback);
    _V void           enterEvent(QEvent* event);
    _V bool           event(QEvent* event);
    _V void           leaveEvent(QEvent* event);
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RLAYER_WIDGET_HH */
