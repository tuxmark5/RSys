#include <QtGui/QApplication>
#include <RSys/Interface/RMainWindow.hh>

/********************************************* RS *********************************************/
/*                                            main                                            */
/**********************************************************************************************/

int main(int argc, char** argv)
{
  QApplication  app(argc, argv);
  RMainWindow   mainWnd;

  mainWnd.show();
  return app.exec();
}

/**********************************************************************************************/
