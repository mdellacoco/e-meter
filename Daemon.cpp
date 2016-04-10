/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Daemon.cpp
 * Author: Margarita E. Della Sera
 * 
 * Created on April 6, 2016, 10:36 AM
 */

#include "Daemon.h"
/**
 * Constructor
 * @param rundir
 * @param pidfileName
 */
Daemon::Daemon(const char *rundir, const char *pidfileName):
m_childPid(0),
m_sid(0),
pidNo(0),
m_pidfileHandler(0),
m_pRunDir(rundir),
m_pPidFileName(pidfileName) {
}
/**
 * Copy constructor
 * @param orig
 */

Daemon::Daemon(const Daemon& orig) {
}
/**
 * Destructor
 */

Daemon::~Daemon() {
    close(m_pidfileHandler);
}
/**
 * Sets the file descriptor route.
 */

void Daemon::stdFileDescriptorRoute(){
  int i;
  i = open("/dev/null", O_RDWR); //open STDIN
  dup(i);  //STDOUT
  dup(i);  //STDERR
}
/**
 * Makes the application into a daemon.
 */

void Daemon::daemonize(){
//fork
	m_childPid = fork();

	if (m_childPid < 0) {   //An error occurred
			   //Log failure
			   throw std::runtime_error(strerror(errno));
	}
    else if (m_childPid != 0) {  //process created so exit parent
			   exit(EXIT_SUCCESS);
	}

    umask(0); //Change the file mode mask

   //Open any logs here

    m_sid = setsid(); //Create a new sid for the child process

    if (m_sid < 0) {   //An error occurred
		     	   //Log failure
	  throw std::runtime_error(strerror(errno));
	}

    chdir(m_pRunDir); // change running directory

		   //  if ((chdir("/")) < 0) {   //An error occurred
		          	   //Log failure
		         // 	   throw std::runtime_error(strerror(errno));
		        //     }
    this->pidFileCreate();
    this->stdFileDescriptorRoute();  //Route I/O connections

}

/**
 * Write the pid number into the pid file.
 */

void Daemon::pidFileCreate(){

	char str[10];

	m_pidfileHandler = open(m_pPidFileName, O_RDWR|O_CREAT, 0600);

	if (m_pidfileHandler == -1 ) {
            /* Couldn't open lock file */
          syslog(LOG_ERR, "Could not open PID lock file %s, exiting", m_pPidFileName);
            exit(EXIT_FAILURE);
       }


	 if(lockf(m_pidfileHandler,F_TLOCK,0) == -1) { // Try to lock file
           /* Couldn't get lock on lock file */
        syslog(LOG_INFO, "Could not lock PID lock file %s, exiting", m_pPidFileName);
        exit(EXIT_FAILURE);
	  }
	 pidNo = getpid();
	 sprintf(str,"%d\n", pidNo); //Get and format PID

     write(m_pidfileHandler, str, strlen(str)); //write pid to lockfile
}
