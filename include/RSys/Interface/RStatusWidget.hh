#ifndef RSYS_INTERFACE_RSTATUS_WIDGET_HH
#define RSYS_INTERFACE_RSTATUS_WIDGET_HH

/**********************************************************************************************/
#include <QtGui/QFrame>
#include <RSys/RSys.hh>
/********************************************* RS *********************************************/
/*                                        RStatusWidget                                       */
/**********************************************************************************************/

class RStatusWidget: public QFrame
{
  Q_OBJECT
  Q_PROPERTY(int height READ height WRITE setFixedHeight)

  public:
    _M bool           m_closing: 1;

  public:
    _M Vacuum         RStatusWidget(QWidget* parent = 0);
    _V Vacuum         ~RStatusWidget();
    _M void           animateHeight(int from, int to, const char* slot);
    _M void           setBackgroundColor(const QColor& color);
    _M void           setLayout(QLayout* layout);
    _M void           setWidget(QWidget* widget);

  public slots:
    _M void           onCloseClicked();
    _M void           startTimer(int timeout = 1500);
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RSTATUS_WIDGET_HH */
