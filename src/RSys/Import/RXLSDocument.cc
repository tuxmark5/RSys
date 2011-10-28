#include <RSys/Import/RXLSDocument.hh>

/********************************************* RS *********************************************/
/*                                        RXLSDocument                                        */
/**********************************************************************************************/

            RXLSDocument :: RXLSDocument() {
    m_document = new BasicExcel();
}

            RXLSDocument :: RXLSDocument(QString name) {
    m_document = new BasicExcel();
    open(name);
}

            RXLSDocument :: ~RXLSDocument() {
    close();
}

void        RXLSDocument :: open(QString name) {
    m_document->Load(name.toAscii().constData());
}

void        RXLSDocument :: close() {
    m_document->Close();
}

QString     RXLSDocument :: nameAt(int index) const {
    if(index - 1 > numTables())
        return 0;
    QString name = QString::fromWCharArray(m_document->GetUnicodeSheetName(index));
    if(name == 0)
        name = m_document->GetAnsiSheetName(index);
    return name;
}

int         RXLSDocument :: numTables() const {
    return m_document->GetTotalWorkSheets();
}

RXLSTable*    RXLSDocument :: tableAt(int index) const {
    RXLSTable* table = new RXLSTable(m_document->GetWorksheet(index));
    return table;
}

/**********************************************************************************************/

