#ifndef DELIVERIES_H_INCLUDED
#define DELIVERIES_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include <malloc.h>


#define CODE 8
#define NAME 81
#define DATE 11


typedef struct{
    float maxCostInsert;   //Costo maximo alta
    float medCostInsert;   //Costo medio alta
    float costAcumInsert;  //Costo acumulado alta
    int cantInsert;        //Cantidad de costos alta

    float maxCostSupress;  //Costo maximo baja
    float medCostSupress;  //Costo medio baja
    float costAcumSupress; //Costo acumulado baja
    int cantSupress;       //Cantidad de costos baja

    float maxCostSucEvo;   //Costo maximo Exito evocacion
    float medCostSucEvo;   //Costo medio Exito evocacion
    float costAcumSucEvo;  //Costo acumulado exito evocacion
    int cantSucEvo;        //Cantidad de costos exito evocacion

    float maxCostFailEvo;  //Costo maximo Fracaso evocacion
    float medCostFailEvo;  //Costo medio Fracaso evocacion
    float costAcumFailEvo; //Costo acumulado fracaso evocacion
    int cantFailEvo;       //Cantidad de costos fracaso evocacion
}Cost;


typedef struct{
   Cost lso;
   Cost lsobb; 
   Cost abb;
}StructCost;


void initStructCost(StructCost *st){
    st->lso.maxCostInsert = 0;
    st->lso.medCostInsert = 0;
    st->lso.maxCostSupress = 0;
    st->lso.medCostSupress = 0;
    st->lso.maxCostSucEvo = 0;
    st->lso.medCostSucEvo = 0;
    st->lso.maxCostFailEvo = 0;
    st->lso.medCostFailEvo = 0;
    st->lso.costAcumInsert = 0;
    st->lso.costAcumSupress = 0;
    st->lso.costAcumSucEvo = 0;
    st->lso.costAcumFailEvo = 0;
    st->lso.cantInsert = 0;
    st->lso.cantSupress = 0;
    st->lso.cantSucEvo = 0;
    st->lso.cantFailEvo = 0;

    st->lsobb.maxCostInsert = 0;
    st->lsobb.medCostInsert = 0;
    st->lsobb.maxCostSupress = 0;
    st->lsobb.medCostSupress = 0;
    st->lsobb.maxCostSucEvo = 0;
    st->lsobb.medCostSucEvo = 0;
    st->lsobb.maxCostFailEvo = 0;
    st->lsobb.medCostFailEvo = 0; 
    st->lsobb.costAcumInsert = 0;
    st->lsobb.costAcumSupress = 0;
    st->lsobb.costAcumSucEvo = 0;
    st->lsobb.costAcumFailEvo = 0;
    st->lsobb.cantInsert = 0;
    st->lsobb.cantSupress = 0;
    st->lsobb.cantSucEvo = 0;
    st->lsobb.cantFailEvo = 0; 
    

    st->abb.maxCostInsert = 0;
    st->abb.medCostInsert = 0;
    st->abb.maxCostSupress = 0;
    st->abb.medCostSupress = 0;
    st->abb.maxCostSucEvo = 0;
    st->abb.medCostSucEvo = 0;
    st->abb.maxCostFailEvo = 0;
    st->abb.medCostFailEvo = 0;  
    st->abb.costAcumInsert = 0;
    st->abb.costAcumSupress = 0;
    st->abb.costAcumSucEvo = 0;
    st->abb.costAcumFailEvo = 0;
    st->abb.cantInsert = 0;
    st->abb.cantSupress = 0;
    st->abb.cantSucEvo = 0;
    st->abb.cantFailEvo = 0;
}

typedef struct{
    char code[CODE];
    long doc, docSender;
    char name[NAME];
    char nameSender[NAME];
    char address[NAME];
    char dateSender[DATE];
    char dateReceived[DATE];
}Deliveries;


void initDev(Deliveries *dev){
    dev->doc = 0;
    dev->docSender = 0;
    strcpy(dev->code, "ZZZZZZZ");
    strcpy(dev->name, "0");
    strcpy(dev->nameSender, "0");
    strcpy(dev->address, "0");
    strcpy(dev->dateSender, "0");
    strcpy(dev->dateReceived, "0");
    //Valores invalidos
}

#endif