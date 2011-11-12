#ifndef RSYS_INTERFACE_RSEARCH_FORM_HH
#define RSYS_INTERFACE_RSEARCH_FORM_HH

/**********************************************************************************************/
#include <RSys/Interface/RStatusWidget.hh>
/********************************************* RS *********************************************/
/*                                        RSearchForm                                         */
/**********************************************************************************************/

class RSearchForm: public RStatusWidget
{
  Q_OBJECT

  private:
    _M QStackedLayout*  m_seasonLayout;
    _M QSpinBox*        m_defaultBox;
    _M QSpinBox*        m_winterBox;
    _M QSpinBox*        m_springBox;
    _M QSpinBox*        m_summerBox;
    _M QSpinBox*        m_autumnBox;

  public:
    _M Vacuum           RSearchForm(QWidget* parent = 0);
    _V Vacuum           ~RSearchForm();

  public slots:
    _M void             setSeasonRelevance(bool relevant);
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RSEARCH_FORM_HH */
