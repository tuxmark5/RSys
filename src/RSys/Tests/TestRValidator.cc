#include <RSys/Tests/TestRValidator.hh>


void TestRValidator::testReadingMeasures()
{
  RXLSDocument document(QString::fromUtf8("../../RSys/static/test2.xls"));
  QCOMPARE(document.nameAt(0),
           QString::fromUtf8("Paramos priemonės"));

  RValidator validator;
  RData data;
  RMeasureList *measures = data.measures();

  QCOMPARE(
        validator.validateMeasures(document.tableAt(0), &data, measures),
        true);

  for (auto it = measures->begin(); it != measures->end(); it++)
  {
    qDebug() << "Priemonė: " << (*it)->identifier() << (*it)->name();
  }
  qDebug() << "Baigė.";
}
