#include <RSys/Import/RXLSTable.hh>

/********************************************* RS *********************************************/
/*                                         RXLSTable                                          */
/**********************************************************************************************/

            RXLSTable::RXLSTable(BasicExcelWorksheet* table) {
    m_table  = table;
    QString title = QString::fromWCharArray(m_table->GetUnicodeSheetName());
    if (title == 0)
        title = m_table->GetAnsiSheetName();
    m_title  = title;
    m_width  = m_table->GetTotalCols();
    m_height = m_table->GetTotalRows();
}

            RXLSTable::~RXLSTable() {

}

QVariant    RXLSTable::cell(int x, int y) const {
    BasicExcelCell* cell = m_table->Cell(y,x);
    int type = cell->Type();
    switch(type) {
        case BasicExcelCell::INT: {
            return cell->GetInteger();
        }
        case BasicExcelCell::DOUBLE: {
            return cell->GetDouble();
        }
        case BasicExcelCell::STRING: {
            QString string = cell->GetString();
            return string;
        }
        case BasicExcelCell::WSTRING: {
            QString wstring = QString::fromWCharArray(cell->GetWString());
            return wstring;
        }
        default: {
            return 0;
        }
    }
}

QString     RXLSTable::title() const {
    return m_title;
}

int         RXLSTable::height() const {
    return m_height;
}

int         RXLSTable::width() const {
    return m_width;
}

/**********************************************************************************************/

