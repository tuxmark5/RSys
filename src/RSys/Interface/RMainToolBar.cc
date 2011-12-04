#include <RSys/Interface/RMainToolBar.hh>
#include <RSys/Interface/RMainWindow.hh>

/********************************************* RS *********************************************/
/*                                        RMainToolBar                                        */
/**********************************************************************************************/

Vacuum RMainToolBar :: RMainToolBar(RMainWindow* parent):
  QToolBar(QString::fromUtf8("Pagrindinė įrankių juosta"), parent)
{
  setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

  addAction(parent->m_importAction);

  addSeparator();
  addAction(parent->m_commitAction);
  addAction(parent->m_rollbackAction);

  addSeparator();
  addAction(parent->m_searchAction);

  addSeparator();
  addAction(parent->m_disconnectAction);
  addAction(parent->m_exitAction);

  addSeparator();
  addAction(parent->m_helpAction);
}

/**********************************************************************************************/

Vacuum RMainToolBar :: ~RMainToolBar()
{

}

/**********************************************************************************************/
