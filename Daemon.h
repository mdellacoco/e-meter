/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Daemon.h
 * Author: Margarita E. Della Sera
 *
 * Created on April 6, 2016, 10:36 AM
 */

#ifndef DAEMON_H
#define DAEMON_H

#include <string.h>
#include <stdio.h>
#include <errno.h>  //strerror()
#include <fcntl.h> //open()
#include <syslog.h>
#include <unistd.h>  //dup()
#include <stdlib.h>  // exit, EXIT_FAILURE
#include <stdexcept>
#include <sys/file.h> //lockf()
#include <sys/types.h>
#include <sys/stat.h>

/**
 * This class intiates objects that creates daemons.
 */

class Daemon {
public:
    Daemon(const char *rundir, const char *pidfileName);
    Daemon(const Daemon& orig);
    virtual ~Daemon();
    int getPidNo(){return pidNo;}
    void daemonize();
    
private:
    void pidFileCreate();
    void stdFileDescriptorRoute();
    
    int         m_childPid;
    int         m_sid;
    int         pidNo;
    int         m_pidfileHandler;
    const char* m_pRunDir;
    const char* m_pPidFileName;
};

#endif /* DAEMON_H */

