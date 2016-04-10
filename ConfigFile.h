/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ConfigFile.h
 * Author: victoria
 *
 * Created on April 6, 2016, 11:36 AM
 */

#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include <string>
#include <iostream>
#include <fstream>
#include "dbParameters.h"

using namespace std;

typedef struct {
    const std::string FILENAME = "/etc/emeter/emeter.conf";
    std::string DELIM          =  "=";
    const int MAX_BUFFER       = 1024;
    int NUM_LINES              = 4;    
}fileProperties;

typedef struct {
        std::string _daemonDir      = "/var/run";
        std::string _daemonPidFile  = "/var/run/e-meter.pid";
        std::string _wDirectoryName = "";
        dbValues    _dbParams;
    }config;
/**
 * This class defines the values in the app config file.
 */

class ConfigFile {
public:
    ConfigFile();
    ConfigFile(const ConfigFile& orig);
    virtual ~ConfigFile();
    
    void ReadConfigParams();
    config* getConfigParams(){return &_config;}
private:
    fileProperties _fileProperties;
    config         _config;   

};

#endif /* CONFIGFILE_H */

