#include <QtCore/QSettings>
#include <QtGui/QComboBox>
#include <QtGui/QDateEdit>
#include <QtGui/QKeyEvent>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <RSys/Core/RData.hh>
#include <RSys/Interface/RIntervalToolBar.hh>
#include <RSys/Interface/RMainWindow.hh>
#include <RSys/Logic/RResults.hh>

/**********************************************************************************************/
std::function<QDate (QDate)> g_dateIncrementor;
/********************************************* RS *********************************************/
/*                                      RIntervalToolBar                                      */
/**********************************************************************************************/

Vacuum RIntervalToolBar :: RIntervalToolBar(RMainWindow* parent):
  QToolBar("Intervalo nustatymai", parent),
  m_mainWindow(parent),
  m_validInterval(true)
{
  QIcon         arrowL    = QIcon(":/icons/arrow_left.png");
  QIcon         arrowR    = QIcon(":/icons/arrow_right.png");
  QPushButton*  decMonth  = new QPushButton(arrowL, QString());
  QPushButton*  decYear   = new QPushButton(arrowL, QString());
  QPushButton*  incMonth  = new QPushButton(arrowR, QString());
  QPushButton*  incYear   = new QPushButton(arrowR, QString());

  decMonth->setFixedSize(16, 21);
  decYear->setFixedSize(16, 21);
  incMonth->setFixedSize(16, 21);
  incYear->setFixedSize(16, 21);

  m_interval0     = new QDateEdit(this);
  m_interval1     = new QDateEdit(this);
  m_intervalLen   = new QComboBox(this);
  m_applyButton   = new QPushButton("Rodyti", this);

  setDefaultInterval();
  m_intervalLen->addItem(R_S("savaites"),     (int) ByWeek);
  m_intervalLen->addItem(R_S("mėnesius"),     (int) ByMonth);
  m_intervalLen->addItem(R_S("ketvirčius"),   (int) ByQuarter);
  m_intervalLen->addItem(R_S("metus"),        (int) ByYear);
  m_intervalLen->setCurrentIndex(1);

  connect(m_interval0, SIGNAL(dateChanged(QDate)), this, SLOT(validate()));
  connect(m_interval1, SIGNAL(dateChanged(QDate)), this, SLOT(validate()));
  connect(m_intervalLen, SIGNAL(currentIndexChanged(int)), this, SLOT(applyInterval()));
  connect(m_applyButton, SIGNAL(clicked()), this, SLOT(applyInterval()));

  m_interval0->installEventFilter(this);
  m_interval1->installEventFilter(this);

  setContentsMargins(0, 0, 0, 0);
  addLabel(u"Rodyti: nuo");
  addWidget(m_interval0);
  addLabel(u"iki");
  addWidget(m_interval1);
  addWidget(m_applyButton);

  addSeparator();
  addLabel(u"po");
  addWidget(m_intervalLen);

  addSeparator();
  addWidget(decYear);
  addLabel(u"Metai");
  addWidget(incYear);

  addSeparator();
  addWidget(decMonth);
  addLabel(u"Mėnuo");
  addWidget(incMonth);

  connect(decMonth, SIGNAL(clicked()), this, SLOT(decMonth()));
  connect(decYear,  SIGNAL(clicked()), this, SLOT(decYear()));
  connect(incMonth, SIGNAL(clicked()), this, SLOT(incMonth()));
  connect(incYear,  SIGNAL(clicked()), this, SLOT(incYear()));

  decMonth->setFixedWidth(25);
  decYear->setFixedWidth(25);
  incMonth->setFixedWidth(25);
  incYear->setFixedWidth(25);
  //m_intervalLen->addItem(R_S("lygias 10 dalių"));
  //m_intervalLen->addItem(R_S("lygias 12 dalių"));

  //m_interval0->setDisplayFormat("yyyy-MM");
}

/**********************************************************************************************/

Vacuum RIntervalToolBar :: ~RIntervalToolBar()
{

}

/**********************************************************************************************/

void RIntervalToolBar :: addLabel(const char16_t* label)
{
  QLabel* widget = new QLabel(QString::fromUtf16((ushort*) label));
  widget->setContentsMargins(10, 0, 10, 0);
  addWidget(widget);
}

/**********************************************************************************************/

bool RIntervalToolBar :: adjustInterval(QDate& date0, QDate& date1)
{
  RData*        data              = results()->data1();
  bool          modified0         = false;
  bool          modified1         = false;
  QDate         globalInterval0   = data->interval0();
  QDate         globalInterval1   = data->interval1();

  if (globalInterval0.isValid() && globalInterval1.isValid())
  {
    globalInterval1 = globalInterval1.addYears(5); // maksimalus prognozavimas
    if (date0 < globalInterval0) { date0 = globalInterval0; modified0 = true; }
    if (date1 > globalInterval1) { date1 = globalInterval1; modified1 = true; }
  }

  if (date0 >= date1)
  {
    /**/ if (modified0 && !modified1)
      date1 = date0.addDays(1);
    else if (!modified0 && modified1)
      date0 = date1.addDays(-1);
  }

  return modified0 || modified1;
}

/**********************************************************************************************/

bool RIntervalToolBar :: applyInterval()
{
  R_GUARD(validate(true), false);

  RIntervalFun  fun;
  int           num       = 0;
  QDate         date0     = m_interval0->date();
  QDate         date1     = m_interval1->date();
  g_settings->setValue("date0", date0);
  g_settings->setValue("date1", date1);

  QDate         date0Org  = date0;
  QDate         date1Org  = date1;
  bool          modified0 = adjustInterval(date0, date1);
  getInterval(date0, date1, fun, num);
  bool          modified1 = (date0 != date0Org) || (date1 != date1Org.addDays(1));

  QString       msgText   = R_S("<html>Rodomas intervalas: nuo <b>%1</b> iki <b>%2</b>")
    .arg(R_DATE_TO_S(date0), R_DATE_TO_S(date1.addDays(-1)));

  if (modified0 || modified1)
  {
    msgText += R_S("<br>Intervalas buvo pataisytas, kad:<ul style='margin-top:0px'>");
    if (modified0)
      msgText += R_S("<li>Atitiktų turimus duomenis (nuo <b>%1</b> iki <b>%2</b>)</li>")
        .arg(R_DATE_TO_S(globalInterval0()), R_DATE_TO_S(globalInterval1()));
    if (modified1)
      msgText += getIntervalMessage(date0, date1, num);
    msgText += "</ul>";
  }

  msgText += "</html>";

  emit message(msgText);
  results()->setInterval(std::move(fun), num);
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
      emit message(R_S("Per ilgas intervalas. Ilgiausias leistinas intervalo ilgis yra 10 metų."),
        IntervalTooLong, RERROR);
      break;

    case TooShort:
      emit message(R_S("Per trumpas intervalas."),
        IntervalTooShort, RERROR);
      break;

    case InvalidOrder:
      emit message(R_S("Intervalo pabaigos data turi būti vėliau už intervalo pradžią."),
        IntervalEndpointsInvalid, RERROR);
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
  static std::function<QDate (QDate)>& inc = g_dateIncrementor;

  switch (m_intervalLen->currentIndex())
  {
    case ByWeek:
      date0   = date0.addDays(-(date0.dayOfWeek() - 1));
      date1   = date1.addDays(-(date1.dayOfWeek() - 1));
      num     = date0.daysTo(date1) / 7;
      inc     = [](QDate d) -> QDate { return d.addDays(7); };
      fun     = [date0](int x) -> RInterval
      {
        return RInterval(date0.addDays(x * 7), date0.addDays(x * 7 + 7));
      };
      break;

    case ByMonth:
      date0   = QDate(date0.year(), date0.month(), 1);
      date1   = QDate(date1.year(), date1.month(), 1).addMonths(1);
      num     = (date1.year() - date0.year()) * 12 + (date1.month() - date0.month());
      inc     = [](QDate d) -> QDate { return d.addMonths(1); };
      fun     = [date0](int x) -> RInterval
      {
        return RInterval(date0.addMonths(x), date0.addMonths(x + 1));
      };
      break;

    case ByQuarter:
      //date0   = QDate(date0.year(), date0.month(), 1).addMonths(0 - date0.month() % 3);
      //date1   = QDate(date1.year(), date1.month(), 1).addMonths(3 - date1.month() % 3);
      date0   = QDate(date0.year(), date0.month(), 1).addMonths(0 - (date0.month() - 1) % 3);
      date1   = QDate(date1.year(), date1.month(), 1).addMonths(3 - (date1.month() - 1) % 3);
      num     = date0.daysTo(date1) / 120;
      inc     = [](QDate d) -> QDate { return d.addMonths(4); };
      fun     = [date0](int x) -> RInterval
      {
        return RInterval(date0.addMonths(x * 4), date0.addMonths(x * 4 + 4));
      };
      break;

    case ByYear:
      date0   = QDate(date0.year(), 1, 1);
      date1   = QDate(date1.year(), 1, 1);
      num     = date1.year() - date0.year() + 1;
      inc     = [](QDate d) -> QDate { return d.addYears(1); };
      fun     = [date0](int x) -> RInterval
      {
        return RInterval(date0.addYears(x), date0.addYears(x + 1));
      };
      break;
  }
}

/**********************************************************************************************/

QString RIntervalToolBar :: getIntervalMessage(QDate date0, QDate date1, int num)
{
  Q_UNUSED(date0);
  Q_UNUSED(date1);

  switch (m_intervalLen->currentIndex())
  {
    case ByWeek:
      return R_S("<li>Prasidėtų pirmadiniu</li>"
                 "<li>Į jį tilptų tikslus savaičių sk. (<b>%1</b>)</li>")
            .arg(num);

    case ByMonth:
      return R_S("<li>Prasidėtų pirmąja mėnesio diena</li>"
                 "<li>Į jį tilptų tikslus mėnesių sk. (<b>%1</b>)</li>")
            .arg(num);

    case ByQuarter:
      return R_S("<li>Prasidėtų ketvirčio pradžia</li>"
                 "<li>Į jį tilptų tikslus ketvirčių sk. (<b>%1</b>)</li>")
            .arg(num);

    case ByYear:
      return R_S("<li>Prasidėtų pirmąja metų diena</li>"
                 "<li>Į jį tilptų tikslus metų sk.(<b>%1</b>)</li>")
            .arg(num);
  }

  return QString();
}

/**********************************************************************************************/

QDate RIntervalToolBar :: globalInterval0() const
{
  return m_mainWindow->results()->data1()->interval0();
}

/**********************************************************************************************/

QDate RIntervalToolBar :: globalInterval1() const
{
  return m_mainWindow->results()->data1()->interval1();
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

RResults* RIntervalToolBar :: results() const
{
  return m_mainWindow->results();
}

/**********************************************************************************************/

void RIntervalToolBar :: setDefaultInterval()
{
  QDate     date0     = g_settings->value("date0").toDate();
  QDate     date1     = g_settings->value("date1").toDate();

  if (!date0.isValid() || !date1.isValid())
  {
    QDate currDate = QDate::currentDate();

    date0 = QDate(currDate.year() - 1, currDate.month(),  1);
    date1 = QDate(currDate.year(),     currDate.month(), 31);
  }

  m_interval0->setDate(date0);
  m_interval1->setDate(date1);
}

/**********************************************************************************************/

void RIntervalToolBar :: setValid(bool valid)
{
  if (valid)
  {
    m_interval0->setPalette(QPalette());
    m_interval1->setPalette(QPalette());
    results()->setInterval(m_interval0->date(), m_interval1->date());
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
    error = date0 < date1 ? Correct : InvalidOrder;

  //if (error == Correct)
  //  error = date0.daysTo(date1) != 1 ? Correct : TooShort;

  if (error == Correct)
    adjustInterval(date0, date1);

  if (error == Correct)
    error = qAbs(date0.year() - date1.year()) <= 10 ? Correct : TooLong;

  if (emitMessage)
  {
    emitErrorMessage(error);
  }

  setValid(m_validInterval = (error == Correct));
  return m_validInterval;
}

/**********************************************************************************************/
