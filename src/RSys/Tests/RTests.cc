#include <RSys/Tests/RTests.hh>

extern std::function<QDate (QDate)> g_dateIncrementor;

void run_all_tests(int argc, char *argv[])
{

  g_dateIncrementor = [](QDate d) -> QDate { return d.addDays(7); };

  TestRXLSDocument test1;
  QTest::qExec(&test1, argc, argv);

  TestRValidator test2;
  QTest::qExec(&test2, argc, argv);

  TestRParser test3;
  QTest::qExec(&test3, argc, argv);
}
