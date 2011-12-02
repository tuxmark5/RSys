#include <RSys/Util/RSignal.hh>

/********************************************* RS *********************************************/
/*                                        RConnection                                         */
/**********************************************************************************************/

Vacuum RConnection :: RConnection(RSignal* signal, int identifier):
  m_signal(signal),
  m_identifier(identifier)
{
}

/**********************************************************************************************/

void RConnection :: disconnect()
{
  R_GUARD(m_signal, Vacuum);

  m_signal->disconnect(m_identifier);
  m_signal      = 0;
  m_identifier  = 0;
}

/********************************************* RS *********************************************/
/*                                          RSignal                                           */
/**********************************************************************************************/

void RSignal :: disconnect(int connId)
{
  for (auto it = m_connections.begin(); it != m_connections.end(); )
  {
    if (std::get<0>(*it) == connId)
      it = m_connections.erase(it);
    else
      ++it;
  }
}

/**********************************************************************************************/

void RSignal :: disconnectAll()
{
  m_connections.clear();
}

/**********************************************************************************************/
