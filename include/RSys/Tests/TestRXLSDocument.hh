#ifndef TESTRXLSDOCUMENT_HH
#define TESTRXLSDOCUMENT_HH

#include <QtTest/QTest>
#include <RSys/RSys.hh>
#include <RSys/Import/RXLSDocument.hh>


class TestRXLSDocument: public QObject
{

    Q_OBJECT

  private:
    _V void     checkMeasures(RXLSTable *table);
    _V void     checkDivisions(RXLSTable *table);
    _V void     checkSystems(RXLSTable *table);
    _V void     checkDivisionsSystems(RXLSTable *table);
    _V void     checkMeasuresAdministration(RXLSTable *table);
  private slots:
    _M void     testOpenningExampleFile();
  };


#endif // TESTRXLSDOCUMENT_HH
