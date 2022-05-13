/**
 * @file    myStone.h
 * @author  Wilfrid Le Valégant
 * @brief   
 * @version 1.0
 * @date    2022-04-20
 **/
#ifndef MYSTONE_H
#define MYSTONE_H

#include <string>
#include "MySerial.h"

//Structure local utilisés pour garder les informations lues de l'écran
struct datasRead {
    int id; //Si 0 alors il n'y a pas de données, <0 Numero commande non traitée, >1 Numero de la commande traité
    char command[80];
    char name[80];
    int type;
    char line[2048];
};

class MyStone {
    private:
        MySerial *mySerial;
        //Transfert de ces deux méthodes en privées depuis la version 1.2
        int writeIt(std::string cmdFormat2);
        int readIt(char *data, int len);
    public:
        MyStone(int speed, uint32_t config, int rxd, int txd);
        ~MyStone() { };
        datasRead getValidsDatasIfExists();
       
        //Nouvelles méthodes ajoutées dans la version 1.2
        void changePage(const char *pageName = "");
        void setLabel(const char *labelName, const char *value);
        void getVersion();
   }; 
#endif