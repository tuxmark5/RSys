#ifndef TESTRVALIDATOR_HH
#define TESTRVALIDATOR_HH

#include <QtTest/QTest>
#include <RSys/Parse/RValidator.hh>
#include <RSys/Import/RXLSDocument.hh>

class TestRValidator: public QObject
{

    Q_OBJECT

  private:
  private slots:
    _M void     testReadingMeasures();
    _M void     testReadingSystems();
    _M void     testReadingDivisions();
    _M void     testReadingDivisionsSystems();
    _M void     testReadingDivisionsMeasures();
    _M void     testReadingSubmissions();
    _M void     testTableTypeDetection();
    _M void     testImportingXLSFile();

};


#endif // TESTRVALIDATOR_HH
