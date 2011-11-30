#include <RSys/Interface/RMainMenuBar.hh>
#include <RSys/Interface/RMainWindow.hh>

/********************************************* RS *********************************************/
/*                                        RMainMenuBar                                        */
/**********************************************************************************************/

Vacuum RMainMenuBar :: RMainMenuBar(RMainWindow* parent):
  QMenuBar(parent)
{
  QMenu* systemMenu   = new QMenu("&Sistema",  this);
  QMenu* editMenu     = new QMenu("&Keisti",   this);
  m_viewMenu          = new QMenu("&Rodyti",   this);
  QMenu* helpMenu     = new QMenu("&Apie",     this);

  systemMenu->addAction(parent->m_importAction);
  systemMenu->addSeparator();
  systemMenu->addAction(parent->m_commitAction);
  systemMenu->addAction(parent->m_rollbackAction);
  systemMenu->addSeparator();
  systemMenu->addAction(parent->m_disconnectAction);
  systemMenu->addAction(parent->m_exitAction);

  editMenu->addAction(parent->m_searchAction);

  m_viewMenu->addAction(parent->m_divisionsStateAction);
  m_viewMenu->addAction(parent->m_systemsStateAction);

  helpMenu->addAction(parent->m_helpAction);

  addMenu(systemMenu);
  addMenu(editMenu);
  addMenu(m_viewMenu);
  addMenu(helpMenu);
}

/**********************************************************************************************/

Vacuum RMainMenuBar :: ~RMainMenuBar()
{
}

/**********************************************************************************************/
