#include <QtCore/QLocale>
#include <QtCore/QSettings>
#include <QtGui/QApplication>
#include <RSys/Interface/RMainWindow.hh>
#include <RSys/Tests/RTests.hh>

/**********************************************************************************************/
bool        g_postgres = true;
QSettings*  g_settings = 0;
/********************************************* RS *********************************************/
/*                                            main                                            */
/**********************************************************************************************/

int main(int argc, char** argv)
{
  TestRParser test3;
  test3.testNormalFile();
  test3.testWithMissingData();
  return 0;
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
    QSettings     settings("ReSoft", "RSys");
    g_settings = &settings;
    RMainWindow   mainWnd;

    mainWnd.showMaximized();
    return app.exec();
  }
}

/**********************************************************************************************/
