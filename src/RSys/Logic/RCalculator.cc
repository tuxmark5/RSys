#include <QtCore/QDate>
#include <RSys/Logic/RCalculator.hh>

/********************************************* RS *********************************************/
/*                                        RCalculator                                         */
/**********************************************************************************************/

Vacuum RCalculator :: RCalculator(RData* data)
{

}

/**********************************************************************************************/

Vacuum RCalculator :: ~RCalculator()
{

}

/**********************************************************************************************/

#include <random>

QVector<double> RCalculator :: calcUsages(QDate from, QDate to)
{
  QVector<double>   random;
  std::mt19937      eng(time(NULL));

  std::uniform_real_distribution<double> gen(0.0, 2.0);

  while (from < to)
  {
    random.append(gen(eng));
    from.addDays(1);
  }
}

/**********************************************************************************************/
