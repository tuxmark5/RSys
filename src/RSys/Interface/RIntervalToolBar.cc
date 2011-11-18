#include <QtGui/QComboBox>
#include <QtGui/QDateEdit>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <RSys/Interface/RIntervalToolBar.hh>
#include <RSys/Interface/RMainWindow.hh>

/********************************************* RS *********************************************/
/*                                      RIntervalToolBar                                      */
/**********************************************************************************************/

Vacuum RIntervalToolBar :: RIntervalToolBar(RMainWindow* parent):
  QToolBar("Intervalo nustatymai", parent)
{
  QDate currDate  = QDate::currentDate();
  QDate date1     = QDate(currDate.year(), currDate.month(), 1);
  QDate date0     = date1.addYears(-1);

  m_interval0     = new QDateEdit(date0, this);
  m_interval1     = new QDateEdit(date1, this);
  m_intervalLen   = new QComboBox(this);
  m_applyButton   = new QPushButton("Rodyti", this);

  QDateEdit::connect(m_interval0, SIGNAL(dateChanged(QDate)), this, SLOT(validate()));
  QDateEdit::connect(m_interval1, SIGNAL(dateChanged(QDate)), this, SLOT(validate()));
  QDateEdit::connect(m_applyButton, SIGNAL(clicked()), this, SLOT(onApplyClicked()));

  setContentsMargins(0, 0, 0, 0);
  addWidget(new QLabel(" Rodyti: nuo"));
  addWidget(m_interval0);
  addWidget(new QLabel("iki"));
  addWidget(m_interval1);
  addWidget(new QLabel("po"));
  addWidget(m_intervalLen);
  addWidget(m_applyButton);
}

/**********************************************************************************************/

Vacuum RIntervalToolBar :: ~RIntervalToolBar()
{

}

/**********************************************************************************************/

QDate RIntervalToolBar :: date0() const
{
  return m_interval0->date();
}

/**********************************************************************************************/

QDate RIntervalToolBar :: date1() const
{
  return m_interval1->date();
}

/**********************************************************************************************/

void RIntervalToolBar :: onApplyClicked()
{
  if (validate(true))
  {
    emit intervalChanged(date0(), date1());
  }
}

/**********************************************************************************************/

void RIntervalToolBar :: setValid(bool valid)
{
  if (valid)
  {
    m_interval0->setPalette(QPalette());
    m_interval1->setPalette(QPalette());
  }
  else
  {
    QPalette invalidPalette;

    invalidPalette.setColor(QPalette::Base, Qt::red);
    m_interval0->setPalette(invalidPalette);
    m_interval1->setPalette(invalidPalette);
  }

  //m_applyButton->setEnabled(valid);
}

/**********************************************************************************************/

bool RIntervalToolBar :: validate(bool emitMessage)
{
  QDate   date0       = m_interval0->date();
  QDate   date1       = m_interval1->date();
  bool    okDeltaMax  = qAbs(date0.year() - date1.year()) < 10;
  bool    okDeltaMin  = date0.daysTo(date1) != 1;
  bool    okOrder     = date0 < date1;
  bool    valid       = okDeltaMax && okDeltaMin && okOrder;

  if (emitMessage)
  {
    if (!okDeltaMax)
      emit message(R_S("Per ilgas intervalas. Ilgiausias leistinas intervalo ilgis yra 10 metų"), 8000);
    else if (!okDeltaMin)
      emit message(R_S("Per trumpas intervalas."), 8000);
    else if (!okOrder)
      emit message(R_S("Intervalo pabaigos data turi būti vėliau už intervalo pradžią."), 8000);
  }

  setValid(valid);
  return valid;
}

/**********************************************************************************************/
