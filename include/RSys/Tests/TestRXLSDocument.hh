#ifndef TESTRXLSDOCUMENT_HH
#define TESTRXLSDOCUMENT_HH

#include <QtTest/QTest>
#include <RSys/Import/RXLSDocument.hh>


class TestRXLSDocument: public QObject
{

    Q_OBJECT

  private:
    _M void     checkMeasures(RXLSTable *table);
    _M void     checkDivisions(RXLSTable *table);
    _M void     checkSystems(RXLSTable *table);
    _M void     checkDivisionsSystems(RXLSTable *table);
    _M void     checkMeasuresAdministration(RXLSTable *table);
    _M void     checkAmounts(RXLSTable *table);
  private slots:
    _M void     testOpenningExampleFile();
  };


#endif // TESTRXLSDOCUMENT_HH
