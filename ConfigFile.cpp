/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ConfigFile.cpp
 * Author: Margarita E. Della Sera
 * 
 * Created on April 6, 2016, 11:36 AM
 */

#include "ConfigFile.h"

/**
 * Constructor
 */

ConfigFile::ConfigFile() {
}

/**
 * Copy constructor
 * @param orig
 */

ConfigFile::ConfigFile(const ConfigFile& orig) {
}
/**
 * Destructor
 */

ConfigFile::~ConfigFile() {
}

/**
 * This function reads the conf parameters written in a given config file and
 * stores them locally in variables.
 */

void ConfigFile::ReadConfigParams(){
    
    int fd;
    std::filebuf fb;
    std::string configParams[7] = {"", "", "", "", "", "", ""};
  
    char part1[256]; //part 1 of line with the written parameters
    char part2[256]; // part 2 of line.

    int i = 0;   
    
    if (fb.open (_fileProperties.FILENAME.c_str() ,std::ios::in)) {
        std::istream is(&fb);
 
        while (!is.eof()) {  

            is.getline(part1, 256, ' ');
            is.getline(part2, 256);

            configParams[i] = part2;
            i++;          
        }
      _config._wDirectoryName = configParams[0];
      _config._dbParams.serverName = configParams[1];
      _config._dbParams.user = configParams[2];
      _config._dbParams.paswd = configParams[3];
      _config._dbParams.dbName = configParams[4];
      _config._dbParams.tableName = configParams[5];
        
    }    
}


