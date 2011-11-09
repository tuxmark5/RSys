#include <QtCore/QLocale>
#include <QtGui/QApplication>
#include <RSys/Interface/RMainWindow.hh>

/********************************************* RS *********************************************/
/*                                            main                                            */
/**********************************************************************************************/

int main(int argc, char** argv)
{
  QLocale       locale(QLocale::Lithuanian, QLocale::Lithuania);
  QLocale::setDefault(locale);
  QApplication  app(argc, argv);
  RMainWindow   mainWnd;

  mainWnd.show();
  return app.exec();
}

/**********************************************************************************************/
