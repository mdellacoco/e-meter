/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WatchDir.cpp
 * Author: Margarita E. Della Sera
 * 
 * Created on April 6, 2016, 10:07 AM
 */

#include "WatchDir.h"
/**
 * Constructor
 */

WatchDir::WatchDir(std::string dir):m_dir(dir) {
    this->init();
}

/**
 * Copy constructor
 */

WatchDir::WatchDir(const WatchDir& orig) {
}
/**
 * Destructor
 */

WatchDir::~WatchDir() {
}

/** 
 * The init() function initializes the directory watch. 
 */

void WatchDir::init() {

    
    m_fd = inotify_init();
    
    if(m_fd < 0)
     cout << "Error" << endl;  
    
    //Add watch

    m_wd = inotify_add_watch(m_fd, m_dir.c_str(),
            IN_CREATE | IN_MODIFY);
    
}
/** 
 * initDB() initializes the database handler with the parameters passed in 
 the structure dbParams
 */

void WatchDir::initDB(dbValues *dbParams, std::string soLibName) {
 m_dbHandler.setDBParams(dbParams);
 m_dbHandler.setSOlib(soLibName);
 m_dbHandler.init();
}
/** 
 * When a new file is created this function is called to 
 * create a new table in the database
 */

void WatchDir::onFileCreated(){
    //create a new table in the database
}
/** 
 * this function calls the db handler function populateTable to add the latest
 * reading to the corresponding table 
 */
void WatchDir::onFileModified(std::string filename){
   
    std::string pathAndFilename;
    pathAndFilename = m_dir + "/" + filename;
    m_dbHandler.populateTable(pathAndFilename.c_str());
}
/** 
 * THis function sends an error message to the admin about the deletion of files 
 * in the directory that it is being watched 
 */
void WatchDir::onFileDeleted() {
  //  
}
/** This function watches the directory and calls respective function depending 
 on the returned mask
 */

void WatchDir::watch(){
    
 char buf[BUF_LEN];
 const struct inotify_event *pEvent;
 int i = 0, len;
 char *ptr;
     
 len = read(m_fd, buf, BUF_LEN); 
    
 for(ptr = buf; ptr < (buf + len); 
      ptr += sizeof(struct inotify_event) + pEvent->len) {
      
         pEvent = (const struct inotify_event*) ptr; 

         if(pEvent->len) {
            if(pEvent->mask & IN_CREATE){
             }
            else if(pEvent->mask & IN_DELETE) {
              
             }
             else if (pEvent->mask & IN_MODIFY) {
                 onFileModified(pEvent->name);  
          }
      }
   }
}
