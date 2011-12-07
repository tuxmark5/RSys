#ifndef RSYS_INTERFACE_RPALETTE_DOCK_HH
#define RSYS_INTERFACE_RPALETTE_DOCK_HH

/**********************************************************************************************/
#include <RSys/RSys.hh>
#include <QtGui/QDockWidget>
/********************************************* RS *********************************************/
/*                                        RPaletteDock                                        */
/**********************************************************************************************/

class RPaletteDock: public QDockWidget
{
  Q_OBJECT

  public:
    _T QList<RUnit*>    UnitList;

  private:
    _M RMainWindow*     m_mainWindow;
    _M RTableView*      m_filter;
    _M bool             m_mode;

    _M RModel1D*        m_model;
    _M RContainerPtr    m_divisionContainer;
    _M RContainerPtr    m_systemContainer;

  public:
    _M Vacuum           RPaletteDock(RMainWindow* parent = 0);
    _V Vacuum           ~RPaletteDock();
    _M void             createContainers(RMainWindow* main);
    _M QString          modeName() const;
    _M UnitList         selectedUnits() const;

  public slots:
    _M void             checkAll();
    _M void             inverseChecks();
    _M void             setChecked(bool checked);
    _M void             setMode(bool mode);
    _M void             uncheckAll();
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RPALETTE_DOCK_HH */
