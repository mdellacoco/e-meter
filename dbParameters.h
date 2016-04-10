/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   dbParameters.h
 * Author: Margarita E. Della Sera
 *
 * Created on April 6, 2016, 10:31 AM
 */

#ifndef DBPARAMETERS_H
#define DBPARAMETERS_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct {
  std::string serverName = "";
  std::string user = "";
  std::string paswd = "";
  std::string dbName = "";
  std::string tableName;
} dbValues;



#ifdef	__cplusplus
}
#endif

#endif /* DBPARAMETERS_H */

