#include <QtGui/QApplication>
#include <RSys/Interface/RMainWindow.hh>
#include <RSys/Tests/RTests.hh>

/********************************************* RS *********************************************/
/*                                            main                                            */
/**********************************************************************************************/

int main(int argc, char** argv)
{
  run_all_tests(argc, argv);
  return 0;

//QApplication  app(argc, argv);
//RMainWindow   mainWnd;

//mainWnd.show();
//return app.exec();
}

/**********************************************************************************************/
