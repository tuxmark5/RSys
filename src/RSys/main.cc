#include <QtCore/QLocale>
#include <QtGui/QApplication>
#include <RSys/Interface/RMainWindow.hh>
#include <RSys/Tests/RTests.hh>

/**********************************************************************************************/

/********************************************* RS *********************************************/
/*                                            main                                            */
/**********************************************************************************************/

int main(int argc, char** argv)
{
  if (!qgetenv("R_TEST").isEmpty())
  {
    run_all_tests(argc, argv);
    return 0;
  }
  else
  {
    QLocale       locale(QLocale::Lithuanian, QLocale::Lithuania);
    QLocale::setDefault(locale);
    QApplication  app(argc, argv);
    RMainWindow   mainWnd;

    mainWnd.showMaximized();
    return app.exec();
  }
}

/**********************************************************************************************/
