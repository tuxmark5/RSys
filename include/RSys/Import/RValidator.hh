#ifndef RVALIDATOR_HH
#define RVALIDATOR_HH

#include <RSys/Core/RMeasure.hh>
#include <RSys/Import/RIDocument.hh>
#include <RSys/Core/RData.hh>


class RValidator: public QObject
{

    Q_OBJECT

  public slots:
//  _M  bool validate(QString filename, RData *data);
//  _M  bool validate(RIDocument *document, RData *data);
    _M  bool validateMeasures(RITable *table, RData *, RMeasureList *list);


  signals:
    _M  void log(RLEVEL level, QString message);
    _M  void parsed(double part);

};

#endif // RVALIDATOR_HH
