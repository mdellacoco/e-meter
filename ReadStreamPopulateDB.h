/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ReadStreamPopulateDB.h
 * Author: victoria
 *
 * Created on April 5, 2016, 11:31 PM
 */

#ifndef READSTREAMPOPULATEDB_H
#define READSTREAMPOPULATEDB_H

#include <string>
#include <iostream>
#include <stdio.h>

#include "mysql_connection.h"
#include "cppconn/driver.h"
#include "cppconn/exception.h"
#include "cppconn/resultset.h"
#include "cppconn/statement.h"
#include "cppconn/prepared_statement.h"

typedef struct {
    std::string clientName = "";
    std::string appName = "";
    std::string appNo = "";
}clientParams;

typedef struct {
    std::string date = "";  //2016-04-07
    std::string time = "";  // 15:49:00
    std::string dateTime = "";
}dateTime;

typedef struct{
   int index;
   //std::string dateTime;
   std::string tableName;
   //std::string client;
   //std::string appName;
   clientParams _clientParms;
   dateTime     _dateTime;
}dBCommonVar;


class ReadStreamPopulateDB {
public:
    ReadStreamPopulateDB();
    ReadStreamPopulateDB(const ReadStreamPopulateDB& orig);
    virtual ~ReadStreamPopulateDB();
    
    void setIndex(int index){m_dbCommonVar.index = index;}
    int getIndex(){return m_dbCommonVar.index;}
    void setTableName(std::string tableName){m_dbCommonVar.tableName = tableName;}
    std::string getDateTime() {return m_dbCommonVar._dateTime.dateTime;}
    void setDateTime(std::string dateTime){m_dbCommonVar._dateTime.dateTime = dateTime;}
    
    void setDBConnection(sql::Connection* pCon){m_pCon = pCon;}
    void setDBPreparedStatement(sql::PreparedStatement* pPStmt){m_pPStmt = pPStmt;}
    
    friend std::istream& operator>> (std::istream& in, ReadStreamPopulateDB& b) {  //done like this because friend class cannot be virtual
        b.readStream(in, b);
        return in;
    } 
    friend std::ostream& operator<< (std::ostream& out, ReadStreamPopulateDB* b) {
      //b->writeDB(out, b);
      return out;
    }
    virtual void prepareInsertStatement() {};//= 0; 
    virtual void writeDB(ReadStreamPopulateDB* b) {printf("base class");}; //{
    
protected:
     virtual void readStream(std::istream& input, ReadStreamPopulateDB& b){}// {printf("hmmm\n");}
    // virtual void writeDB(std::ostream& out, ReadStreamPopulateDB* b) {printf("base class");}; //{}//printf("base class");}
    
public:
    dBCommonVar                 m_dbCommonVar;
    sql::PreparedStatement*     m_pPStmt;
    
protected: 
    
    
    sql::Connection*            m_pCon;

};
/*The type of the class factory*/
typedef ReadStreamPopulateDB* create_t();
typedef void destroy_t(ReadStreamPopulateDB*);


#endif /* READSTREAMPOPULATEDB_H */

