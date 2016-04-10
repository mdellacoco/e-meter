/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WatchDir.h
 * Author: Margarita E. Della Sera
 *
 * Created on April 6, 2016, 10:07 AM
 */

#ifndef WATCHDIR_H
#define WATCHDIR_H

#include <sstream>
#include <iostream>
#include <stdio.h>
#include <dirent.h>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/inotify.h>
#include <sys/types.h>

#include "DatabaseHandler.h"
#include "dbParameters.h"


using namespace std;

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )

/** This class initiates objects of directories to be watched for changes*/

class WatchDir {
public:
    WatchDir(std::string dir);
    WatchDir(const WatchDir& orig);
    virtual ~WatchDir();
    void initDB(dbValues *dbParams, std::string soLibName);
private:
    void init();
    void onFileCreated();
    void onFileModified(std::string filename);
    void onFileDeleted();
public:
    void watch();
private:
    std::string         m_dir; /* holds the directory name to watch */
    int                 m_fd;  // file descriptor
    int                 m_wd;  //watch descriptor
    DatabaseHandler     m_dbHandler;  //DB handler

};

#endif /* WATCHDIR_H */

