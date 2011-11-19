#include <QtGui/QComboBox>
#include <QtGui/QDateEdit>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <RSys/Interface/RIntervalToolBar.hh>
#include <RSys/Interface/RMainWindow.hh>
#include <RSys/Logic/RResults.hh>

/********************************************* RS *********************************************/
/*                                      RIntervalToolBar                                      */
/**********************************************************************************************/

Vacuum RIntervalToolBar :: RIntervalToolBar(RMainWindow* parent):
  QToolBar("Intervalo nustatymai", parent),
  m_results(parent->results())
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

  m_intervalLen->addItem(R_S("savaites"),     (int) ByWeek);
  m_intervalLen->addItem(R_S("mėnesius"),     (int) ByMonth);
  m_intervalLen->addItem(R_S("ketvirčius"),   (int) ByQuarter);
  m_intervalLen->addItem(R_S("metus"),        (int) ByYear);
  m_intervalLen->setCurrentIndex(1);
  //m_intervalLen->addItem(R_S("lygias 10 dalių"));
  //m_intervalLen->addItem(R_S("lygias 12 dalių"));

  //m_interval0->setDisplayFormat("yyyy-MM");
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
  R_GUARD(validate(true), Vacuum);

  RIntervalFun  fun;
  int           num   = 0;
  QDate         date0 = m_interval0->date();
  QDate         date1 = m_interval1->date();

  switch (m_intervalLen->currentIndex())
  {
    case ByWeek:
      date0   = date0.addDays(-(date0.dayOfWeek() - 1));
      date1   = date1.addDays(-(date1.dayOfWeek() - 1));
      num     = date0.daysTo(date1) / 7;
      fun     = [date0](int x) -> RInterval
      {
        return RInterval(date0.addDays(x * 7), date0.addDays(x * 7 + 7));
      };
      break;

    case ByMonth:
      date0   = QDate(date0.year(), date0.month(), 1);
      date1   = QDate(date1.year(), date1.month(), 1).addMonths(1);
      num     = (date1.year() - date0.year()) * 12 + (date1.month() - date0.month());
      fun     = [date0](int x) -> RInterval
      {
        return RInterval(date0.addMonths(x), date0.addMonths(x + 1));
      };
      break;

    case ByQuarter:
      date0   = QDate(date0.year(), date0.month() - date0.month() % 4, 1);
      date1   = QDate(date1.year(), date1.month() - date1.month() % 4, 1);
      num     = date0.daysTo(date1) / 120;
      fun     = [date0](int x) -> RInterval
      {
        return RInterval(date0.addMonths(x * 4), date0.addMonths(x * 4 + 4));
      };
      break;

    case ByYear:
      date0   = QDate(date0.year(), 1, 1);
      date1   = QDate(date1.year(), 1, 1);
      num     = date1.year() - date0.year() + 1;
      fun     = [date0](int x) -> RInterval
      {
        return RInterval(date0.addYears(x), date0.addYears(x + 1));
      };
      break;
  }

  message(R_S("Rodomas intervalas: nuo <b>%1</b> iki <b>%2</b>")
          .arg(date0.toString(Qt::DefaultLocaleShortDate))
          .arg(date1.toString(Qt::DefaultLocaleShortDate)), 8000);

  m_results->setInterval(std::move(fun), num);

  //emit intervalChanged(date0(), date1());
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
