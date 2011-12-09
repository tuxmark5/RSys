#ifndef RSYS_INTERFACE_RHELP_HH
#define RSYS_INTERFACE_RHELP_HH

/**********************************************************************************************/
#include <RSys/Interface/RTab.hh>
/********************************************* RS *********************************************/
/*                                           RHelp                                            */
/**********************************************************************************************/

class RHelp: public QObject
{
  Q_OBJECT

  private:
    _M QProcess*      m_assistant;

  public:
    _M Vacuum         RHelp(QObject* parent = 0);
    _V Vacuum         ~RHelp();

  public slots:
    _M bool           launch();
    _M void           showDocumentation(const QString& page);
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RHELP_HH */
