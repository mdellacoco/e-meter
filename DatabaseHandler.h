/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DatabaseHandler.h
 * Author: Margarita E. Della Sera
 *
 * Created on April 6, 2016, 9:57 AM
 */

#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <dlfcn.h>


#include "ReadStreamPopulateDB.h"
#include "dbParameters.h"
#include <string>

#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

/**This class intiates objects to handle a database*/

class DatabaseHandler {
public:
    DatabaseHandler();
    DatabaseHandler(const DatabaseHandler& orig);
    virtual ~DatabaseHandler();
    void init();
    void setDBParams(dbValues* dbParams){m_mysqlParams = dbParams;} /*Sets theDB parameters for the database*/
    void setTableName(std::string tableName){m_mysqlParams->tableName = tableName;} /**Sets the table name to be written to*/
    void setSOlib(std::string soLib){m_soLib = soLib;}
    void populateTable(const char* filename);
private:
    int getNumEntries();
    int getIndex();
    std::string getLastEntryDate(int index);
    
private:
    sql::Driver*                 m_pDriver;
    sql::Connection*             m_pCon;
    sql::Statement*              m_pStmt;
    sql::ResultSet*              m_pRes;
    sql::PreparedStatement*      m_pPStmt;
    dbValues*                    m_mysqlParams;
    std::string                  m_soLib;      //name of shared library
        

};


#endif /* DATABASEHANDLER_H */

