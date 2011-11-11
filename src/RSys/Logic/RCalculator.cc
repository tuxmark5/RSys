#include <QtCore/QDate>
#include <RSys/Logic/RCalculator.hh>
#include <random>

/********************************************* RS *********************************************/
/*                                        RCalculator                                         */
/**********************************************************************************************/

Vacuum RCalculator :: RCalculator()
{

}

/**********************************************************************************************/

Vacuum RCalculator :: ~RCalculator()
{

}

/**********************************************************************************************/

QVector<double> RCalculator :: calcUsages(RDivision* division, QDate from, QDate to)
{
  QVector<double>   random;
  std::mt19937      eng(time(NULL));

  std::uniform_real_distribution<double> gen(0.0, 2.0);

  while (from < to)
  {
    random.append(gen(eng));
    from.addDays(1);
  }

  return random;
}

/**********************************************************************************************/

QVector<double> RCalculator :: calcUsages(RSystem* system, QDate from, QDate to)
{
  return calcUsages((RDivision*) 0, from, to);
}

/**********************************************************************************************/
