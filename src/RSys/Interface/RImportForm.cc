#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QPushButton>
#include <RSys/Interface/RImportForm.hh>

/**********************************************************************************************/
QStringList RImportForm :: s_modeNames;
/********************************************* RS *********************************************/
/*                                        RImportForm                                         */
/**********************************************************************************************/

Vacuum RImportForm :: RImportForm(QWidget* parent):
  QWidget(parent)
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

  m_importButton = new QPushButton(R_S("Importuoti"), this);

  setMinimumHeight(40);
  setMinimumWidth(80);
}

/**********************************************************************************************/

Vacuum RImportForm :: ~RImportForm()
{
}

/**********************************************************************************************/

void RImportForm :: import()
{

}

/**********************************************************************************************/

void RImportForm :: setModeMap(const ModeMap& modeMap)
{
  QGridLayout*  layout    = static_cast<QGridLayout*>(this->layout());
  int           height    = 0;

  for (auto it = modeMap.begin(); it != modeMap.end(); ++it, ++height)
  {
    QCheckBox*    checkBox  = new QCheckBox(it.key(), this);
    QComboBox*    comboBox  = new QComboBox(this);

    comboBox->addItems(s_modeNames);
    comboBox->setCurrentIndex(it.value());

    layout->addWidget(checkBox, height, 0);
    layout->addWidget(comboBox, height, 1);
  }

  layout->addWidget(m_importButton, height, 0, 1, 2);
}

/**********************************************************************************************/
