#ifndef RSYS_INTERFACE_RSEARCH_FORM_HH
#define RSYS_INTERFACE_RSEARCH_FORM_HH

/**********************************************************************************************/
#include <QtGui/QWidget>
#include <RSys/RSys.hh>
/********************************************* RS *********************************************/
/*                                        RSearchForm                                         */
/**********************************************************************************************/

class RSearchForm: public QWidget
{
  Q_OBJECT

  public:
    _F class RMainWindow;

  private:
    _M QStackedLayout*  m_seasonLayout;
    _M QRadioButton*    m_seasonalRelevanceButton;
    _M QSpinBox*        m_defaultBox;
    _M QSpinBox*        m_springBox;
    _M QSpinBox*        m_summerBox;
    _M QSpinBox*        m_fallBox;
    _M QSpinBox*        m_winterBox;
    _M QPushButton*     m_searchButton;

  public:
    _M Vacuum           RSearchForm(QWidget* parent = 0);
    _V Vacuum           ~RSearchForm();
    _M void             getSeasonalLengths(int* lengths);

  public slots:
    _M void             setSeasonRelevance(bool relevant);

  signals:
    _M void             findIntervalPressed();
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RSEARCH_FORM_HH */
