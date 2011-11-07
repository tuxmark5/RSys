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
  QMenu* viewMenu     = new QMenu("&Rodyti",   this);
  QMenu* helpMenu     = new QMenu("&Apie",     this);

  systemMenu->addAction(parent->m_openAction);
  systemMenu->addSeparator();
  systemMenu->addAction(parent->m_saveAction);
  systemMenu->addSeparator();
  systemMenu->addAction(parent->m_importAction);
  systemMenu->addSeparator();
  systemMenu->addAction(parent->m_disconnectAction);
  systemMenu->addAction(parent->m_exitAction);

  editMenu->addAction(parent->m_searchAction);

  viewMenu->addAction(parent->m_divisionsStateAction);
  viewMenu->addAction(parent->m_systemsStateAction);

  helpMenu->addAction(parent->m_helpAction);

  addMenu(systemMenu);
  addMenu(editMenu);
  addMenu(viewMenu);
  addMenu(helpMenu);
}

/**********************************************************************************************/

Vacuum RMainMenuBar :: ~RMainMenuBar()
{
}

/**********************************************************************************************/
