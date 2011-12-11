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
    _M RResults*        m_results;
    _M QStackedLayout*  m_seasonLayout;
    _M QRadioButton*    m_seasonalRelevanceButton;
    _M QSpinBox*        m_defaultBox;
    _M QSpinBox*        m_springBox;
    _M QSpinBox*        m_summerBox;
    _M QSpinBox*        m_fallBox;
    _M QSpinBox*        m_winterBox;
    _M QPushButton*     m_searchButton;

  public:
    _M Vacuum           RSearchForm(RResults* results, QWidget* parent = 0);
    _V Vacuum           ~RSearchForm();
    _M void             getSeasonalLengths(int* lengths);

  public slots:
    _M void             setSeasonRelevance(bool relevant);

  private slots:
    _M void             onFindPressed();

  signals:
    _M void             findIntervalPressed();
    _M void             message(QString message, int id = -1, int type = -1);
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RSEARCH_FORM_HH */
