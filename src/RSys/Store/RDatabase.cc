#include <QtSql/QSqlQuery>
#include <RSys/Core/RData.hh>
#include <RSys/Core/RUser.hh>
#include <RSys/Store/RDatabase.hh>
#include <RSys/Store/REntity1D.hh>
#include <RSys/Store/REntity2D.hh>
#include <RSys/Store/RSqlEntity.hh>

/**********************************************************************************************/
using namespace std::placeholders;
/**********************************************************************************************/
typedef REntity2DI<RDivisionPtr, RMeasurePtr, double>   DivisionMeasureE;
typedef REntity2DI<RDivisionPtr, RSystemPtr, double>    DivisionSystemE;
typedef REntity2DI<RUserPtr,     QString, int>          UserPropertyE;
/**********************************************************************************************/

template <class Value>
struct alloc
{
  template <typename Arg>
  static std::function<Value* ()> make(Arg arg)
  {
    return [=]() -> Value* { return new Value(arg); };
  }
};

/********************************************* RS *********************************************/
/*                                         RDatabase                                          */
/**********************************************************************************************/

Vacuum RDatabase :: RDatabase(RData* data, QObject* parent):
  QObject(parent),
  m_data(data),
  m_sqlEntity(0)
{
}

/**********************************************************************************************/

Vacuum RDatabase :: ~RDatabase()
{
  logout();
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

  return result;
}

/**********************************************************************************************/

void RDatabase :: createAdminDataEntities()
{
  auto toUser       = [=](const QVariant& var)  -> RUser*     { return m_data->user(var.toLongLong()); };
  auto toKey        = [=](const QVariant& var)  -> QString    { return var.toString(); };
  auto fromUser     = [ ](RUser* user)          -> QVariant   { return user->id(); };
  auto fromKey      = [ ](const QString& key)   -> QVariant   { return key; };
  auto setValue     = [ ](RUser* u, const QString& k, int v) { u->setProperty(k, v); };

  auto de = newEntity1D("users", this, m_data->users(), alloc<RUser>::make(m_data));
  de->addField<RID>     ("uid")       >> &RUser::id           << &RUser::setId;
  de->addField<QString> ("username")  >> &RUser::userName     << &RUser::setUserName;
  de->addField<QString> ("descr")     >> &RUser::description  << &RUser::setDescription;

  auto uae = new UserPropertyE("userAdm", this, "uid", "key", "value");
  (*m_data)[RUser::propertySet]   << std::bind(&UserPropertyE::onSet, uae, _1, _2, _3);
  (*m_data)[RUser::propertyUnset] << std::bind(&UserPropertyE::onUnset, uae, _1, _2);
  uae->setKey0(fromUser,  toUser);
  uae->setKey1(fromKey,   toKey);
  uae->setSetter(setValue);

  m_entities << de << uae;
}

/**********************************************************************************************/

void RDatabase :: createDataEntities()
{
  auto de = newEntity1D("divisions", this, m_data->divisions(), alloc<RDivision>::make(m_data));
  de->addField<RID>     ("id")    >> &RDivision::id           << &RDivision::setId;
  de->addField<QString> ("ident") >> &RDivision::identifier   << &RDivision::setIdentifier;
  de->addField<QString> ("name")  >> &RDivision::name         << &RDivision::setName;

  auto me = newEntity1D("measures", this, m_data->measures(), alloc<RMeasure>::make(m_data));
  me->addField<RID>     ("id")    >> &RMeasure::id            << &RMeasure::setId;
  me->addField<QString> ("ident") >> &RMeasure::identifier    << &RMeasure::setIdentifier;
  me->addField<QString> ("name")  >> &RMeasure::name          << &RMeasure::setName;

  auto se = newEntity1D("systems", this, m_data->systems(), alloc<RSystem>::make(m_data));
  se->addField<RID>     ("id")    >> &RSystem::id             << &RSystem::setId;
  se->addField<QString> ("ident") >> &RSystem::identifier     << &RSystem::setIdentifier;
  se->addField<QString> ("name")  >> &RSystem::name           << &RSystem::setName;

  auto ue = newEntity1D("submissions", this, m_data->submissions(), alloc<RSubmission>::make(m_data));
  ue->addField<RID>     ("id")      >> &RSubmission::id         << &RSubmission::setId;
  ue->addField<RID>     ("measure") >> &RSubmission::measureId  << &RSubmission::setMeasureId;
  ue->addField<int>     ("count")   >> &RSubmission::count      << &RSubmission::setCount;
  ue->addField<QDate>   ("date0")   >> &RSubmission::date0      << &RSubmission::setDate0;
  ue->addField<QDate>   ("date1")   >> &RSubmission::date1      << &RSubmission::setDate1;

  auto toDivision   = [=](const QVariant& var) -> RDivision* { return m_data->division(var.toLongLong()); };
  auto toMeasure    = [=](const QVariant& var) -> RMeasure*  { return m_data->measure(var.toLongLong()); };
  auto toSystem     = [=](const QVariant& var) -> RSystem*   { return m_data->system(var.toLongLong()); };
  auto fromDivision = [ ](RDivision* unit)     -> QVariant   { return unit->id(); };
  auto fromMeasure  = [ ](RMeasure* unit)      -> QVariant   { return unit->id(); };
  auto fromSystem   = [ ](RSystem* unit)       -> QVariant   { return unit->id(); };
  auto setMeasure   = [ ](RDivision* d, RMeasure* m, double v) { d->setMeasure(m, v); };
  auto setSystem    = [ ](RDivision* d, RSystem* s, double v) { d->setSystem(s, v); };

  auto mae = new DivisionMeasureE("measureAdm", this, "division", "measure", "weight");
  (*m_data)[RDivision::onMeasureSet] << std::bind(&DivisionMeasureE::onSet, mae, _1, _2, _3);
  (*m_data)[RDivision::onMeasureUnset] << std::bind(&DivisionMeasureE::onUnset, mae, _1, _2);
  mae->setKey0(fromDivision, toDivision);
  mae->setKey1(fromMeasure, toMeasure);
  mae->setSetter(setMeasure);

  auto sae = new DivisionSystemE("systemAdm", this, "division", "system", "weight");
  (*m_data)[RDivision::onSystemSet] << std::bind(&DivisionSystemE::onSet, sae, _1, _2, _3);
  (*m_data)[RDivision::onSystemUnset] << std::bind(&DivisionSystemE::onUnset, sae, _1, _2);
  sae->setKey0(fromDivision, toDivision);
  sae->setKey1(fromSystem, toSystem);
  sae->setSetter(setSystem);

  m_entities << de << me << se << ue << mae << sae;
}

/**********************************************************************************************/

void RDatabase :: emitPSQLError(const QSqlError& error)
{
  QString   text = error.databaseText();
  QString   msg;

  switch (error.type())
  {
    case QSqlError::ConnectionError:
      /**/ if (text.startsWith("fe_send"))
        msg = R_S("Nenurodytas slaptažodis");
      else if (text.startsWith("timeout expired"))
        msg = R_S("Nepavyko prisijungti prie duomenų bazės<br>"
                  "(pasibaigė prisijungimui skirtas laikas)<br>"
                  "Gal nurodytas blogas serverio adresas?");
      else if (text.contains("authentication failed"))
        msg = R_S("Neteisingas naudotojo vardas arba slaptažodis");
      break;

    default:
      break;
  }

  if (msg.isNull())
    msg = R_S("Klaida: %1").arg(text);

  emit message(msg);
}

/**********************************************************************************************/

void RDatabase :: emitSQLiteError(const QSqlError& error)
{
  Q_UNUSED(error);

  emit message(R_S("Nepavyko atidaryti DB."));
}

/**********************************************************************************************/

bool RDatabase :: load()
{
  if (m_postgres)
    createAdminDataEntities();
  createDataEntities();
  m_sqlEntity = new RSqlEntity();
  m_entities << m_sqlEntity;

  emit loggedIn();
  return true;
}

/**********************************************************************************************/

bool RDatabase :: login(const QString& dbFile)
{
  m_database  = QSqlDatabase::addDatabase("QSQLITE");
  m_postgres  = 0;

  if (!m_database.isValid())
  {
    emit message(R_S("Nerasta <b>SQLite</b> QT tvarkyklė <b>QSQLITE</b>"));
    return false;
  }

  m_database.setDatabaseName(dbFile);

  if (m_database.open())
    return load();

  emitSQLiteError(m_database.lastError());
  return false;
}

/**********************************************************************************************/

bool RDatabase :: login(const QString& addr, const QString& db, const QString& user, const QString& pass)
{
  m_database = QSqlDatabase::addDatabase("QPSQL");
  m_postgres = 1;
  m_database.setConnectOptions("connect_timeout=1");

  if (!m_database.isValid())
  {
    emit message(R_S("Nerasta <b>PostgreSQL</b> QT tvarkyklė <b>QPSQL</b>"));
    return false;
  }

  m_database.setHostName(addr);
  m_database.setDatabaseName(db);
  m_database.setUserName(user);
  m_database.setPassword(pass);

  if (m_database.open())
    return load();

  emitPSQLError(m_database.lastError());
  return false;
}

/**********************************************************************************************/

void RDatabase :: logout()
{
  m_database.close();
  qDeleteAll(m_entities);
  m_entities.clear();
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

  if (m_postgres)
    m_user = m_data->user(m_database.userName());
  else
    m_user = RUser::createSuperUser(m_data);
  return true;
}

/**********************************************************************************************/
