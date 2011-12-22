#ifndef TESTRPARSER_HH
#define TESTRPARSER_HH

#include <QtTest/QTest>
#include <RSys/Parse/RParser.hh>

class TestRParser: public QObject
{

    Q_OBJECT

  private:
    _M void     checkReadData(RParser *parser, RParser::GuessList list);

  private slots:
    _M void     testNormalFile();
    _M void     testNotExistingFile();
    _M void     testImageFile();
    _M void     testBrokenSheet();
    _M void     testDetectionByColumns();
    _M void     testWithMissingData();
};

#endif // TESTRPARSER_HH
