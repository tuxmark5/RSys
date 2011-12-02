#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QPushButton>
#include <RSys/Interface/RImportForm.hh>
#include <RSys/Parse/RParser.hh>

/**********************************************************************************************/
QStringList RImportForm :: s_modeNames;
/********************************************* RS *********************************************/
/*                                        RImportForm                                         */
/**********************************************************************************************/

Vacuum RImportForm :: RImportForm(RParser* parser, RData* data, QWidget* parent):
  QWidget(parent),
  m_parser(parser),
  m_data(data)
{
  QGridLayout* layout = new QGridLayout(this);

  if (s_modeNames.isEmpty())
  {
    s_modeNames << R_S("Informacinės sistemos");
    s_modeNames << R_S("Informacinių sistemų administravimas");
    s_modeNames << R_S("Istoriniai duomenys");
    s_modeNames << R_S("Padaliniai");
    s_modeNames << R_S("Paramos priemonių administravimas");
    s_modeNames << R_S("Paramos priemonės");
  }

  m_importButton  = new QPushButton(R_S("Importuoti"));
  connect(m_importButton, SIGNAL(clicked()), this, SLOT(import()));

  setMinimumHeight(40);
  setMinimumWidth(80);
}

/**********************************************************************************************/

Vacuum RImportForm :: ~RImportForm()
{
  delete m_parser;
}

/**********************************************************************************************/

void RImportForm :: import()
{
  (*this)[importBegin]();
  m_parser->read(m_data, m_importModes);
  (*this)[importEnd]();
  emit closed();
}

/**********************************************************************************************/

void RImportForm :: onImportModeChanged(bool enabled)
{
  int   id    = m_widgetHash.value(sender(), -1);
  R_GUARD(id != -1, Vacuum);

  int&  mode  = std::get<1>(m_importModes[id]);

  mode &= 0x100;
  if (!enabled)
    mode |= 0x100;
}

/**********************************************************************************************/

void RImportForm :: onImportModeChanged(int newMode)
{
  int id = m_widgetHash.value(sender(), -1);
  R_GUARD(id != -1, Vacuum);

  std::get<1>(m_importModes[id]) = newMode;
}

/**********************************************************************************************/

void RImportForm :: setImportModes(const RImportModes& importModes)
{
  QGridLayout*  layout    = static_cast<QGridLayout*>(this->layout());
  int           height    = 0;

  for (auto it = importModes.begin(); it != importModes.end(); ++it, ++height)
  {
    QString       sheetName = std::get<0>(*it);
    int           guess     = std::get<1>(*it);
    QCheckBox*    checkBox  = new QCheckBox(sheetName, this);
    QComboBox*    comboBox  = new QComboBox(this);

    connect(checkBox, SIGNAL(toggled(bool)), comboBox, SLOT(setEnabled(bool)));
    connect(checkBox, SIGNAL(clicked(bool)), this, SLOT(onImportModeChanged(bool)));
    connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onImportModeChanged(int)));
    checkBox->setChecked(guess != RUNKNOWN);
    comboBox->addItems(s_modeNames);
    comboBox->setCurrentIndex(guess);

    layout->addWidget(checkBox, height, 0);
    layout->addWidget(comboBox, height, 1);
    m_widgetHash.insert(checkBox, height);
    m_widgetHash.insert(comboBox, height);
  }

  layout->addWidget(m_importButton, height, 0, 1, 2);
  m_importModes = importModes;
}

/**********************************************************************************************/
