/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: victoria
 *
 * Created on April 6, 2016, 9:56 AM
 */

#include <cstdlib>
#include "WatchDir.h"
#include "dbParameters.h"
#include "Daemon.h"
#include "ConfigFile.h"

using namespace std;

/*
 * the main function
 */
int main(int argc, char** argv) {
        
    char* soLibName;
    soLibName = argv[1];
    
    ConfigFile configFileParamsHd;  
    config* pConfigParams; 
    //Read configuration files
    configFileParamsHd.ReadConfigParams();  
    pConfigParams = configFileParamsHd.getConfigParams();
    
    dbValues myDBValues;
    myDBValues.serverName = pConfigParams->_dbParams.serverName;
    myDBValues.dbName = pConfigParams->_dbParams.dbName;
    myDBValues.user = pConfigParams->_dbParams.user;
    myDBValues.paswd = pConfigParams->_dbParams.paswd;
    myDBValues.tableName = pConfigParams->_dbParams.tableName;
    
     //Creates daemon for app
    Daemon deamon(pConfigParams->_daemonDir.c_str(), 
                  pConfigParams->_daemonPidFile.c_str());
       
    deamon.daemonize();
    
    WatchDir* wd = new WatchDir(pConfigParams->_wDirectoryName);
    wd->initDB(&myDBValues, soLibName);
    // keep watching directory for modification in files
    for(;;) {
        
      wd->watch();
      
      }
  
    delete(wd);
    return 0;
}

