#ifndef RSYS_INTERFACE_RIMPORT_FORM_HH
#define RSYS_INTERFACE_RIMPORT_FORM_HH

/**********************************************************************************************/
#include <QtGui/QWidget>
#include <RSys/RSys.hh>
/********************************************* RS *********************************************/
/*                                        RImportForm                                         */
/**********************************************************************************************/

class RImportForm: public QWidget
{
  Q_OBJECT

  public:
    _E DataType
    {
      Systems       = 0,
      SystemAdm     = 1,
      Submissions   = 2,
      Divisions     = 3,
      MeasureAdm    = 4,
      Measures      = 5,
      LastDataType  = 5,
      Unknown       = 10
    };

  public:
    _T QMap<QString, int>   ModeMap;

  private:
    _S QStringList    s_modeNames;
    _M QPushButton*   m_importButton;

  public:
    _M Vacuum         RImportForm(QWidget* parent = 0);
    _V Vacuum         ~RImportForm();
    _M void           setModeMap(const ModeMap& modeMap);

  public slots:
    _M void           import();
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RIMPORT_FORM_HH */
