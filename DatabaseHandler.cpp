/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DatabaseHandler.cpp
 * Author: Margarita E. Della Sera
 * 
 * Created on April 6, 2016, 9:57 AM
 */

#include "DatabaseHandler.h"

/**
 * Constructor
 */

DatabaseHandler::DatabaseHandler() : m_pDriver(NULL), 
                                     m_pCon(NULL), 
                                     m_pStmt(NULL),
                                     m_pRes(NULL),
                                     m_pPStmt(NULL),
                                     m_mysqlParams(NULL),
                                     m_soLib("") {
}

/**
 * Copy constructor
 */

DatabaseHandler::DatabaseHandler(const DatabaseHandler& orig) {
}

/**
 Destructor
 */

DatabaseHandler::~DatabaseHandler() {
    delete m_pCon;
    delete m_pStmt;
    delete m_pRes;
    delete m_pPStmt;
    delete m_mysqlParams;
    
}
/**
 * Initializes the DB Handler.
 */

void DatabaseHandler::init(){
   
 m_pDriver = get_driver_instance();
 
 m_pCon = m_pDriver->connect(m_mysqlParams->serverName.c_str(), 
         m_mysqlParams->user.c_str(), 
         m_mysqlParams->paswd.c_str());

 m_pCon->setSchema(m_mysqlParams->dbName.c_str()); 

}
/** 
 * Returns the numbers of entries in the table with name tableName
 */

int DatabaseHandler::getNumEntries() {
    int nRows = -1;
    
  m_pStmt = m_pCon->createStatement();
  m_pRes = m_pStmt->executeQuery("SELECT * From " + m_mysqlParams->tableName);

  if(m_pRes)
     nRows = m_pRes->rowsCount();  // this is the number of rows.
  
  return nRows;
}

/** 
 * Sets the next index for a new entry in the table. The index is set to 1 as 
 * in mysql, the id fields starts at 1
 */

int DatabaseHandler::getIndex(){
    int index = 1;
    index = getNumEntries();
    if(index)
        index = index + 1;
    
    return index;
}
/** 
 * It returns the last date/time entry in the table.
 */

std::string DatabaseHandler::getLastEntryDate(int index) {
  
 std::string lastEntryDate = "";
 std::stringstream id;
  
 id << index;
    
 std::string queryStr = "SELECT date FROM " + m_mysqlParams->tableName + 
          " WHERE id=" + id.str();
 
 m_pRes = m_pStmt->executeQuery(queryStr); 
 m_pRes->next();
 lastEntryDate = m_pRes->getString(1);
  
  return lastEntryDate;
}

/** 
 * This function populate the respective table with the latest e-meter line 
 * reading
 */

void DatabaseHandler::populateTable(const char* filename){
    
  std::fstream f_;  //file handler
  f_.open(filename, std::fstream::in);  //file to read streams from
  std::string datetime = "";
         
  typedef std::ostream_iterator<ReadStreamPopulateDB*> insertDB; 
  std::vector<ReadStreamPopulateDB*> params_;  //vector of e-meter readings XXX
  

  int index = getIndex();
      
  if(index)
    datetime = getLastEntryDate((index -1));
   
  if(f_.is_open()) {
      
     void* library = dlopen(m_soLib.c_str(), RTLD_LAZY);
     std::string errStr;
  
     if(!library){
         errStr = dlerror();
      printf("Cannot load library!. \n");
      //return 1;
     }
  
     dlerror(); //reset error;
  

     create_t* create = (create_t*)dlsym(library, "create");
  
     const char* dlsymError = dlerror();
   
     if(dlsymError){
       printf("Cannot load symbol create. %s\n", dlsymError);
      // return 1;
     }

     destroy_t* destroy = (destroy_t*)dlsym(library, "destroy");
   
     dlsymError = dlerror();
   
     if(dlsymError){
       printf("Cannot load symbol destroy. %s\n", dlsymError);
      // return 1;
     }

     ReadStreamPopulateDB* p_eMeterLib = create();
  
     p_eMeterLib->setDBPreparedStatement(m_pPStmt);
     p_eMeterLib->setDBConnection(m_pCon);
     p_eMeterLib->setTableName(m_mysqlParams->tableName);
     p_eMeterLib->setIndex(0);
   
     p_eMeterLib->prepareInsertStatement();
  
     while(f_ >> (*p_eMeterLib)){ 
       
        if(p_eMeterLib->getDateTime() > datetime) { //only if ew data is read, then will store in vector
           
           p_eMeterLib->setIndex(index);
           p_eMeterLib->writeDB(p_eMeterLib);
           
	   index++;
	            }       
       }
  
    std::cout << "Read " << params_.size() << " lines successfully\n";
    std::copy(params_.begin(), params_.end(), insertDB(std::cout, "\n"));
    std::cout.flush();
    
    destroy(p_eMeterLib);
            
    f_.close();  //close file from where data was read.      
  }
    
}


