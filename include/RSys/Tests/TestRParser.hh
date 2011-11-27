#ifndef TESTRPARSER_HH
#define TESTRPARSER_HH

#include <QtTest/QTest>
#include <RSys/Parse/RParser.hh>

class TestRParser: public QObject
{

    Q_OBJECT

  private:
  private slots:
    _M void     testNormalFile();
    _M void     testNotExistingFile();
    _M void     testDetectionByColumns();
};

#endif // TESTRPARSER_HH
