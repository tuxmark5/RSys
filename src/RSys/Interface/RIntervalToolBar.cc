#include <QtGui/QComboBox>
#include <QtGui/QDateEdit>
#include <QtGui/QKeyEvent>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <RSys/Core/RData.hh>
#include <RSys/Interface/RIntervalToolBar.hh>
#include <RSys/Interface/RMainWindow.hh>
#include <RSys/Logic/RResults.hh>

/********************************************* RS *********************************************/
/*                                      RIntervalToolBar                                      */
/**********************************************************************************************/

Vacuum RIntervalToolBar :: RIntervalToolBar(RMainWindow* parent):
  QToolBar("Intervalo nustatymai", parent),
  m_results(parent->results()),
  m_validInterval(true)
{
  QDate         currDate  = QDate::currentDate();
  QDate         date1     = QDate(currDate.year(), currDate.month(), 1);
  QDate         date0     = date1.addYears(-1);
  QPushButton*  decMonth  = new QPushButton("-");
  QPushButton*  decYear   = new QPushButton("-");
  QPushButton*  incMonth  = new QPushButton("+");
  QPushButton*  incYear   = new QPushButton("+");

  m_interval0     = new QDateEdit(date0, this);
  m_interval1     = new QDateEdit(date1, this);
  m_intervalLen   = new QComboBox(this);
  m_applyButton   = new QPushButton("Rodyti", this);

  QDateEdit::connect(m_interval0, SIGNAL(dateChanged(QDate)), this, SLOT(validate()));
  QDateEdit::connect(m_interval1, SIGNAL(dateChanged(QDate)), this, SLOT(validate()));
  QDateEdit::connect(m_applyButton, SIGNAL(clicked()), this, SLOT(applyInterval()));
  m_interval0->installEventFilter(this);
  m_interval1->installEventFilter(this);

  setContentsMargins(0, 0, 0, 0);
  addWidget(new QLabel(" Rodyti: nuo"));
  addWidget(m_interval0);
  addWidget(new QLabel("iki"));
  addWidget(m_interval1);
  addWidget(new QLabel("po"));
  addWidget(m_intervalLen);
  addSeparator();
  addWidget(decYear);
  addWidget(new QLabel("Metai"));
  addWidget(incYear);
  addSeparator();
  addWidget(decMonth);
  addWidget(new QLabel(R_S("Mėnuo")));
  addWidget(incMonth);
  addSeparator();
  addWidget(m_applyButton);

  connect(decMonth, SIGNAL(clicked()), this, SLOT(decMonth()));
  connect(decYear,  SIGNAL(clicked()), this, SLOT(decYear()));
  connect(incMonth, SIGNAL(clicked()), this, SLOT(incMonth()));
  connect(incYear,  SIGNAL(clicked()), this, SLOT(incYear()));

  decMonth->setFixedWidth(25);
  decYear->setFixedWidth(25);
  incMonth->setFixedWidth(25);
  incYear->setFixedWidth(25);

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

bool RIntervalToolBar :: adjustInterval(QDate& date0, QDate& date1)
{
  RData*        data      = m_results->data1();
  bool          modified  = false;

  if (date0 < data->interval0()) { date0 = data->interval0(); modified = true; }
  if (date1 > data->interval1()) { date1 = data->interval1(); modified = true; }
  return modified;
}

/**********************************************************************************************/

bool RIntervalToolBar :: applyInterval()
{
  R_GUARD(validate(true), false);

  RIntervalFun  fun;
  int           num       = 0;
  QDate         date0     = m_interval0->date();
  QDate         date1     = m_interval1->date();
  bool          modified  = adjustInterval(date0, date1);

  getInterval(date0, date1, fun, num);

  QString       msgText   = R_S("Rodomas intervalas: nuo <b>%1</b> iki <b>%2</b>")
    .arg(date0.toString(Qt::DefaultLocaleShortDate))
    .arg(date1.toString(Qt::DefaultLocaleShortDate));

  if (modified)
  {
    msgText += R_S("<br>Nes pateikti intervalo galai viršyja duomenų apimtis, tai"
                   "<br>itervalas buvo pakoreguotas, kad atitiktų turimus duomenis.");
  }

  emit message(msgText, -1);

  m_results->setInterval(m_interval0->date(), m_interval1->date());
  m_results->setInterval(std::move(fun), num);
  emit intervalChanged();
  return true;
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

void RIntervalToolBar :: decMonth()
{
  modifyDate(0, -1);
}

/**********************************************************************************************/

void RIntervalToolBar :: decYear()
{
  modifyDate(-1, 0);
}

/**********************************************************************************************/

void RIntervalToolBar :: emitErrorMessage(int error)
{
  switch (error)
  {
    case Correct:
      break;

    case TooLong:
      emit message(R_S("Per ilgas intervalas. Ilgiausias leistinas intervalo ilgis yra 10 metų"), 8000);
      break;

    case TooShort:
      emit message(R_S("Per trumpas intervalas."), 8000);
      break;

    case InvalidOrder:
      emit message(R_S("Intervalo pabaigos data turi būti vėliau už intervalo pradžią."), 8000);
      break;
  }
}

/**********************************************************************************************/

bool RIntervalToolBar :: eventFilter(QObject* watched, QEvent* event)
{
  if (watched == m_interval0 || watched == m_interval1)
  {
    if (event->type() == QEvent::KeyPress)
    {
      QKeyEvent* event1 = static_cast<QKeyEvent*>(event);
      if (event1->key() == Qt::Key_Enter || event1->key() == Qt::Key_Return)
        applyInterval();
    }
  }
  return QToolBar::eventFilter(watched, event);
}

/**********************************************************************************************/

void RIntervalToolBar :: getInterval(QDate& date0, QDate& date1, RIntervalFun& fun, int& num)
{
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
}

/**********************************************************************************************/

void RIntervalToolBar :: incMonth()
{
  modifyDate(0, +1);
}

/**********************************************************************************************/

void RIntervalToolBar :: incYear()
{
  modifyDate(+1, 0);
}

/**********************************************************************************************/

void RIntervalToolBar :: modifyDate(int deltaYear, int deltaMonth)
{
  QDate date0 = m_interval0->date();
  QDate date1 = m_interval1->date();

  date0 = date0.addYears(deltaYear).addMonths(deltaMonth);
  date1 = date1.addYears(deltaYear).addMonths(deltaMonth);

  m_interval0->setDate(date0);
  m_interval1->setDate(date1);

  if (isIntervalValid())
    applyInterval();
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
  int     error       = Correct;

  if (error == Correct)
    error = date0.daysTo(date1) != 1 ? Correct : TooShort;

  if (error == Correct)
    error = date0 < date1 ? Correct : InvalidOrder;

  if (error == Correct)
  {
    adjustInterval(date0, date1);
    error = qAbs(date0.year() - date1.year()) <= 10 ? Correct : TooLong;
  }

  if (emitMessage)
  {
    emitErrorMessage(error);
  }

  setValid(m_validInterval = (error == Correct));
  return m_validInterval;
}

/**********************************************************************************************/
