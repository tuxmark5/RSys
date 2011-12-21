#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpinBox>
#include <QtGui/QStackedLayout>
#include <RSys/Interface/RSearchForm.hh>
#include <RSys/Logic/RResults.hh>

/********************************************* RS *********************************************/
/*                                        RSearchForm                                         */
/**********************************************************************************************/

Vacuum RSearchForm :: RSearchForm(RResults* results, QWidget* parent):
  QWidget(parent),
  m_results(results)
{
  QVBoxLayout*    layout          = new QVBoxLayout();
  QHBoxLayout*    layout0         = new QHBoxLayout();
  QWidget*        widget0         = new QWidget(this);
  QWidget*        widget1         = new QWidget(this);
  QHBoxLayout*    seasonLayout0   = new QHBoxLayout(widget0);
  QGridLayout*    seasonLayout1   = new QGridLayout(widget1);

  m_seasonLayout    = new QStackedLayout();

  layout0->addWidget(new QLabel(R_S("Į sezoniškumą")));
  layout0->addWidget(m_seasonalRelevanceButton = new QRadioButton(R_S("Atsižvelgiama")));
  layout0->addWidget(new QRadioButton(R_S("Neatsižvelgiama")));
  layout0->setSizeConstraint(QLayout::SetMaximumSize);

  seasonLayout0->addWidget(new QLabel(R_S("Reikalingo intervalo ilgis:")));
  seasonLayout0->addWidget(m_defaultBox = new QSpinBox());
  seasonLayout0->addWidget(new QLabel(R_S("diena (-os)")));

  seasonLayout1->addWidget(new QLabel(R_S("Darbai žiemą:")), 0, 0);
  seasonLayout1->addWidget(m_winterBox = new QSpinBox(), 0, 1);
  seasonLayout1->addWidget(new QLabel(R_S("diena (-os) Darbai pavasarį:")), 0, 2);
  seasonLayout1->addWidget(m_springBox = new QSpinBox(), 0, 3);
  seasonLayout1->addWidget(new QLabel(R_S("diena (-os)")), 0, 4);

  seasonLayout1->addWidget(new QLabel(R_S("Darbai vasarą:")), 1, 0);
  seasonLayout1->addWidget(m_summerBox = new QSpinBox(), 1, 1);
  seasonLayout1->addWidget(new QLabel(R_S("diena (-os) Darbai rudenį:")), 1, 2);
  seasonLayout1->addWidget(m_fallBox = new QSpinBox(), 1, 3);
  seasonLayout1->addWidget(new QLabel(R_S("diena (-os)")), 1, 4);

  m_winterBox ->setRange(1, 365);
  m_springBox ->setRange(1, 365);
  m_summerBox ->setRange(1, 365);
  m_fallBox   ->setRange(1, 365);
  m_defaultBox->setRange(1, 365);

  m_seasonLayout->addWidget(widget0);
  m_seasonLayout->addWidget(widget1);
  setSeasonRelevance(true);

  layout->addLayout(layout0);
  layout->addLayout(m_seasonLayout);
  layout->addWidget(m_searchButton = new QPushButton(R_S("Ieškoti mažiausios apkrovos intervalo")));

  setLayout(layout);

  m_seasonalRelevanceButton->setChecked(true);

  QRadioButton::connect(m_seasonalRelevanceButton, SIGNAL(toggled(bool)),
    this, SLOT(setSeasonRelevance(bool)));
  QPushButton::connect(m_searchButton, SIGNAL(clicked()), this, SLOT(onFindPressed()));
}

/**********************************************************************************************/

Vacuum RSearchForm :: ~RSearchForm()
{

}

/**********************************************************************************************/

void RSearchForm :: getSeasonalLengths(int* lengths)
{
  if (m_seasonalRelevanceButton->isChecked())
  {
    lengths[0] = m_winterBox->value();
    lengths[1] = m_springBox->value();
    lengths[2] = m_summerBox->value();
    lengths[3] = m_fallBox->value();
  }
  else
  {
    lengths[0] = m_defaultBox->value();
    lengths[1] = lengths[0];
    lengths[2] = lengths[0];
    lengths[3] = lengths[0];
  }
}

/**********************************************************************************************/

void RSearchForm :: onFindPressed()
{
  int     lengths[4];
  int     maxValue  = 1;
  QDate   interval0 = m_results->interval0();
  QDate   interval1 = m_results->interval1();
  int     delta     = interval0.daysTo(interval1);

  getSeasonalLengths(lengths);
  maxValue = qMax(maxValue, lengths[0]);
  maxValue = qMax(maxValue, lengths[1]);
  maxValue = qMax(maxValue, lengths[2]);
  maxValue = qMax(maxValue, lengths[3]);

  if (maxValue > delta)
  {
    emit message(R_S("Ieškomas intervalas yra ilgesnis už paieškos sritį "
                     "(<b>%1</b> d &gt; <b>%2</b> d).<br/>"
                     "Paieškos sritis: nuo <b>%3</b> iki <b>%4</b>")
                 .arg(maxValue).arg(delta)
                 .arg(R_DATE_TO_S(interval0), R_DATE_TO_S(interval1)),
                 InvalidSearchInterval, RERROR);
  }
  else
  {
    emit findIntervalPressed();
  }
}

/**********************************************************************************************/

void RSearchForm :: setSeasonRelevance(bool relevant)
{
  m_seasonLayout->setCurrentIndex(relevant);
}

/**********************************************************************************************/
