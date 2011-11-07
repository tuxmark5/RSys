#include <RSys/Interface/RMainToolBar.hh>
#include <RSys/Interface/RMainWindow.hh>

/********************************************* RS *********************************************/
/*                                        RMainToolBar                                        */
/**********************************************************************************************/

Vacuum RMainToolBar :: RMainToolBar(RMainWindow* parent):
  QToolBar(QString::fromUtf8("Pagrindinė įrankių juosta"), parent)
{
  setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

  addAction(parent->m_openAction);
  addSeparator();
  addAction(parent->m_saveAction);
  addSeparator();
  addAction(parent->m_importAction);
  addSeparator();
  addAction(parent->m_disconnectAction);
  addAction(parent->m_exitAction);

  addAction(parent->m_searchAction);

  addAction(parent->m_helpAction);
}

/**********************************************************************************************/

Vacuum RMainToolBar :: ~RMainToolBar()
{

}

/**********************************************************************************************/
