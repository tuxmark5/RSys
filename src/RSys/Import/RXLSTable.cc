#include <RSys/Import/RXLSTable.hh>

/********************************************* RS *********************************************/
/*                                         RXLSTable                                          */
/**********************************************************************************************/

Vacuum RXLSTable :: RXLSTable(BasicExcelWorksheet* table):
  m_table(table)
{
}

/**********************************************************************************************/

Vacuum RXLSTable :: ~RXLSTable()
{
  delete m_table;
}

/**********************************************************************************************/

QVariant RXLSTable::cell(int x, int y) const
{
  BasicExcelCell* cell = m_table->Cell(y, x);
  int             type = cell->Type();

  switch(type)
  {
    case BasicExcelCell::INT:
      return cell->GetInteger();

    case BasicExcelCell::DOUBLE:
      return cell->GetDouble();

    case BasicExcelCell::STRING:
      return QString(cell->GetString());

    case BasicExcelCell::WSTRING:
      return QString::fromWCharArray(cell->GetWString());
  }

  return QVariant();
}

/**********************************************************************************************/

QString RXLSTable :: title() const
{
  return QString::fromWCharArray(m_table->GetUnicodeSheetName());
}

/**********************************************************************************************/

int RXLSTable :: height() const
{
  return m_table->GetTotalRows();
}

/**********************************************************************************************/

int RXLSTable :: width() const
{
  return m_table->GetTotalCols();
}

/**********************************************************************************************/

