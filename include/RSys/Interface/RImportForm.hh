#ifndef RSYS_INTERFACE_RIMPORT_FORM_HH
#define RSYS_INTERFACE_RIMPORT_FORM_HH

/**********************************************************************************************/
#include <QtGui/QWidget>
#include <RSys/Util/RSignal.hh>
/********************************************* RS *********************************************/
/*                                        RImportForm                                         */
/**********************************************************************************************/

class RImportForm: public QWidget, public RSignal
{
  Q_OBJECT

  public:
    _T QHash<QObject*, int> WidgetHash;

  private:
    _S QStringList    s_modeNames;
    _M RParser*       m_parser;
    _M RData*         m_data;
    _M QPushButton*   m_importButton;
    _M RImportModes   m_importModes;
    _M WidgetHash     m_widgetHash;

  public:
    _M Vacuum         RImportForm(RParser* parser, RData* data, QWidget* parent = 0);
    _V Vacuum         ~RImportForm();
    _M void           setImportModes(const RImportModes& importModes);

  public slots:
    _M void           import();

  private slots:
    _M void           onImportModeChanged(bool enabled);
    _M void           onImportModeChanged(int newMode);

  public:
    _G(void,          importBegin);
    _G(void,          importEnd);

  signals:
    _M void           closed();
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RIMPORT_FORM_HH */
