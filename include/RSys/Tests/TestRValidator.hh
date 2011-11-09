#ifndef TESTRVALIDATOR_HH
#define TESTRVALIDATOR_HH

#include <QtTest/QTest>
#include <RSys/Import/RValidator.hh>
#include <RSys/Import/RXLSDocument.hh>

class TestRValidator: public QObject
{

    Q_OBJECT

  private:
  private slots:
    _M void     testReadingMeasures();
    _M void     testReadingXLSDocument();

};


#endif // TESTRVALIDATOR_HH
