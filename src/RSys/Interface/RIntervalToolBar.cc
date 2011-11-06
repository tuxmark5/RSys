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
  m_interval0   = new QDateEdit(this);
  m_interval1   = new QDateEdit(this);
  m_applyButton = new QPushButton("Rodyti", this);

  setContentsMargins(0, 0, 0, 0);
  addWidget(new QLabel(" Rodyti: nuo"));
  addWidget(m_interval0);
  addWidget(new QLabel("iki"));
  addWidget(m_interval1);
  addWidget(m_applyButton);
}

/**********************************************************************************************/

Vacuum RIntervalToolBar :: ~RIntervalToolBar()
{

}

/**********************************************************************************************/
