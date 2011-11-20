#include <QtSql/QSqlQuery>
#include <RSys/Core/RData.hh>
#include <RSys/Store/RDatabase.hh>
#include <RSys/Store/REntity1D.hh>
#include <RSys/Store/REntity2D.hh>

/********************************************* RS *********************************************/
/*                                         RDatabase                                          */
/**********************************************************************************************/

Vacuum RDatabase :: RDatabase(RData* data, QObject* parent):
  QObject(parent),
  m_data(data)
{
  auto de = newEntity1D("divisions", data->divisions(), this);
  de->addField<RID>     ("id")    >> &RDivision::id           << &RDivision::setId;
  de->addField<QString> ("ident") >> &RDivision::identifier   << &RDivision::setIdentifier;
  de->addField<QString> ("name")  >> &RDivision::name         << &RDivision::setName;

  auto me = newEntity1D("measures", data->measures(), this);
  me->addField<RID>     ("id")    >> &RMeasure::id            << &RMeasure::setId;
  me->addField<QString> ("ident") >> &RMeasure::identifier    << &RMeasure::setIdentifier;
  me->addField<QString> ("name")  >> &RMeasure::name          << &RMeasure::setName;

  auto se = newEntity1D("systems", data->systems(), this);
  se->addField<RID>     ("id")    >> &RSystem::id             << &RSystem::setId;
  se->addField<QString> ("ident") >> &RSystem::identifier     << &RSystem::setIdentifier;
  se->addField<QString> ("name")  >> &RSystem::name           << &RSystem::setName;

  auto ue = newEntity1D("submissions", data->submissions(), this);
  ue->addField<RID>     ("id")      >> &RSubmission::id         << &RSubmission::setId;
  ue->addField<RID>     ("measure") >> &RSubmission::measureId  << &RSubmission::setMeasureId;
  ue->addField<int>     ("count")   >> &RSubmission::count      << &RSubmission::setCount;
  ue->addField<QDate>   ("date0")   >> &RSubmission::date0      << &RSubmission::setDate0;
  ue->addField<QDate>   ("date0")   >> &RSubmission::date1      << &RSubmission::setDate1;

  m_entities << de << me << se << ue;
}

/**********************************************************************************************/

Vacuum RDatabase :: ~RDatabase()
{
  // id, entity
}

/**********************************************************************************************/

bool RDatabase :: commit()
{
  QSqlQuery   query(m_database);
  bool        result = true;

  m_database.transaction();
  for (auto it = m_entities.begin(); it != m_entities.end(); ++it)
  {
    if (!(*it)->commit(query))
    {
      qDebug() << "FAIL";
      result = false;
    }
  }
  m_database.commit();

  return result ;
}

/**********************************************************************************************/

bool RDatabase :: login(const QString& addr, const QString& db, const QString& user, const QString& pass)
{
  R_GUARD(user == "user", false);

  if (!m_database.isValid())
    m_database = QSqlDatabase::addDatabase("QSQLITE");
  m_database.setHostName(addr);
  m_database.setDatabaseName(db);
  m_database.setUserName(user);
  m_database.setPassword(pass);

  if (m_database.open())
  {
    if (select())
    {
      emit loggedIn();
      return true;
    }
    m_database.close();
  }

  return false;
}

/**********************************************************************************************/

void RDatabase :: logout()
{
}

/**********************************************************************************************/

bool RDatabase :: rollback()
{
  for (auto it = m_entities.begin(); it != m_entities.end(); ++it)
    (*it)->rollback();
  return true;
}

/**********************************************************************************************/

bool RDatabase :: select()
{
  QSqlQuery   query(m_database);

  for (auto it = m_entities.begin(); it != m_entities.end(); ++it)
  {
    (*it)->init();
    if (!(*it)->select(query))
    {
      qDebug() << "FAIL";
      return false;
    }
  }

  return true;
}

/**********************************************************************************************/
