#include <RSys/Tests/TestRValidator.hh>


void TestRValidator::testReadingMeasures()
{
  RXLSDocument document(QString::fromUtf8("../../RSys/static/test2.xls"));
  QCOMPARE(document.nameAt(0),
           QString::fromUtf8("Paramos priemonės"));

  RValidator validator;
  RData data;
  RMeasureList *measures = data.measures();

  QCOMPARE(validator.validateMeasures(document.tableAt(0), &data), true);

  QCOMPARE(measures->size(), 27);
  QCOMPARE(
        measures->at(26)->identifier(),
        QString::fromUtf8("P4-3"));
  QCOMPARE(
        measures->at(26)->name(),
        QString::fromUtf8("3. Parama VVG veiklai, įgūdžiams "
                          "įgyti ir aktyviai pritaikyti"));

//for (auto it = measures->begin(); it != measures->end(); it++)
//{
//  qDebug() << "Priemonė: " << (*it)->identifier() << (*it)->name();
//}
}

void TestRValidator::testTableTypeDetection()
{
  RXLSDocument document(QString::fromUtf8("../../RSys/static/test2.xls"));
  RValidator validator;
  RData data;

  QCOMPARE(validator.validate(document.tableAt(0), &data), true);
  QCOMPARE(validator.validate(document.tableAt(1), &data), false);
}
