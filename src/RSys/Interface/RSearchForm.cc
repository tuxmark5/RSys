#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpinBox>
#include <QtGui/QStackedLayout>
#include <RSys/Interface/RSearchForm.hh>

/********************************************* RS *********************************************/
/*                                        RSearchForm                                         */
/**********************************************************************************************/

Vacuum RSearchForm :: RSearchForm(QWidget* parent):
  QWidget(parent)
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

  m_seasonLayout->addWidget(widget0);
  m_seasonLayout->addWidget(widget1);
  setSeasonRelevance(true);

  layout->addLayout(layout0);
  layout->addLayout(m_seasonLayout);
  layout->addWidget(m_searchButton = new QPushButton(R_S("Ieškoti mažiausiai apkrauto intervalo")));

  setLayout(layout);

  m_seasonalRelevanceButton->setChecked(true);

  QRadioButton::connect(m_seasonalRelevanceButton, SIGNAL(toggled(bool)),
    this, SLOT(setSeasonRelevance(bool)));
  QPushButton::connect(m_searchButton, SIGNAL(clicked()), this, SIGNAL(findIntervalPressed()));
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
    lengths[0] = m_springBox->value();
    lengths[1] = m_summerBox->value();
    lengths[2] = m_fallBox->value();
    lengths[3] = m_winterBox->value();
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

void RSearchForm :: setSeasonRelevance(bool relevant)
{
  m_seasonLayout->setCurrentIndex(relevant);
}

/**********************************************************************************************/
