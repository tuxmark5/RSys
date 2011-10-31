#include <RSys/Import/RXLSDocument.hh>

/********************************************* RS *********************************************/
/*                                        RXLSDocument                                        */
/**********************************************************************************************/

Vacuum RXLSDocument :: RXLSDocument():
  m_document(new BasicExcel())
{
}

/**********************************************************************************************/

Vacuum RXLSDocument :: RXLSDocument(const QString& name):
  m_document(new BasicExcel())
{
  open(name);
}

/**********************************************************************************************/

Vacuum RXLSDocument :: ~RXLSDocument()
{
  close();
  delete m_document;
}

/**********************************************************************************************/

void RXLSDocument :: open(const QString& name)
{
  m_document->Load(name.toAscii().constData());
}

/**********************************************************************************************/

void RXLSDocument :: close()
{
  m_document->Close();
}

/**********************************************************************************************/

QString RXLSDocument :: nameAt(int index) const
{
  R_GUARD(index < numTables(), QString());

  QString name = QString::fromWCharArray(m_document->GetUnicodeSheetName(index));
  if (name.isEmpty())
    name = m_document->GetAnsiSheetName(index);
  return name;
}

/**********************************************************************************************/

int RXLSDocument :: numTables() const
{
  return m_document->GetTotalWorkSheets();
}

/**********************************************************************************************/

RXLSTable* RXLSDocument :: tableAt(int index) const
{
  return new RXLSTable(m_document->GetWorksheet(index));
}

/**********************************************************************************************/
