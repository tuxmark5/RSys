#include <QtCore/QDir>
#include <QtCore/QLibraryInfo>
#include <QtCore/QProcess>
#include <RSys/Interface/RHelp.hh>

/********************************************* RS *********************************************/
/*                                           RHelp                                            */
/**********************************************************************************************/

Vacuum RHelp :: RHelp(QObject* parent):
  QObject(parent),
  m_assistant(0)
{

}

/**********************************************************************************************/

Vacuum RHelp :: ~RHelp()
{

}

/**********************************************************************************************/

bool RHelp :: launch()
{
  R_Z(m_assistant) = new QProcess();
  R_GUARD(m_assistant->state() != QProcess::Running, true);

  QString     app;
  QStringList args;

  app += QLibraryInfo::location(QLibraryInfo::BinariesPath);
  app += QDir::separator();
  app += "assistant";

  args  << QLatin1String("-collectionFile")
        << QLatin1String("RDoc.qhc")
        << QLatin1String("-enableRemoteControl");

  m_assistant->start(app, args);

  if (!m_assistant->waitForStarted())
  {
    qDebug() << "ERROR";
    return false;
  }

  return true;
}

/**********************************************************************************************/

void RHelp :: showDocumentation(const QString& page)
{
  R_GUARD(launch(), Vacuum);

  QByteArray cmd("SetSource ");

  cmd.append("qthelp://com.trolltech.examples.simpletextviewer/doc/");
  cmd.append(page.toLocal8Bit());
  cmd.append('\n');

  m_assistant->write(cmd);
}

/**********************************************************************************************/
