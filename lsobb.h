#ifndef LSOBB_H_INCLUDED
#define LSOBB_H_INCLUDED
#define SIZE 300
#include "envios.h"
#include <ctype.h>
#include <math.h>


typedef struct{
    Deliveries deliveriesListBB[SIZE];
    int last;
}listBB;


void initLSOBB(listBB *lso){  //Inicializar la listBBa es poner last en -1 (vacia)
    lso->last = -1;
}


/*
Codificacion de Localizacion:
return 0 - Fracaso, no esta el elemento
return 1 - Exito
*/
int localizarLSOBB(listBB lsobb, char c[], int *position, float *costo){   //Localizar 

    int li = -1;
    int ls = lsobb.last;
    int t = (li + ls + 2)/2;
    int vector[lsobb.last+1], i;
    float costLoc = 0.0;

    if(lsobb.last == -1){
        *position = 0;   //Posicion donde deberia ir el elemento a cargar
        *costo = costLoc;
        return 0;        //Lista vacia, por tanto fracasa la localizacion
    }
    else{
        //Inicializacion del vector de costos
        for(i = 0; i < (lsobb.last + 1); i++){
            vector[i] = 0;
        }

        while((li + 1) < ls){   
            
            if((strcmp(lsobb.deliveriesListBB[t].code, c) < 0) || (strcmp(lsobb.deliveriesListBB[t].code, c) == 0)){  
                li = t - 1;   //elemento buscado es mayor o igual que lo que tengo en t
            }
            else{
                ls = t - 1;   //elemento buscado es menor que lo que tengo en t
            }

            if(vector[t] == 0){
                costLoc += 1;
                vector[t] = 1;
            }
            t = (li + ls + 2)/2;
        }

        if(vector[ls] == 0){
            costLoc += 1;
            vector[ls] = 1;
        }
        *costo = costLoc;
        
        if(strcmp(lsobb.deliveriesListBB[ls].code, c) == 0){
            *position = ls;
            return 1;
        }
        else{
            if(strcmp(lsobb.deliveriesListBB[ls].code, c) < 0){
                *position = ls + 1;
            }
            else{
                *position = ls;
            }
            return 0;
        }
    }
}


/*
Codificacion del Alta:
return 0 - Fracaso por lista llena
return 1 - Fracaso por elemento existente
return 2 - Exito
*/
int altaLSOBB(listBB *lsobb, Deliveries dev, float *costo){    //Alta
    int position, last;
    float costLoc = 0.0;
    float cost = 0.0;

    last = lsobb->last;  //Variable last para no modificar el valor de lso.last

    if(last < (SIZE - 1)){
        if(localizarLSOBB(*lsobb, dev.code, &position, &costLoc) == 1){  //Elemento localizado en la lista
            return 1; 
        }
        else{
            //El elemento no existe en la lista
            while(position <= last){   //Realizar shifteo a derecha
                lsobb->deliveriesListBB[last + 1] = lsobb->deliveriesListBB[last];
                cost += 1;
                last = last - 1;
            }
            lsobb->deliveriesListBB[position] = dev;   //Ingresar el nuevo elemento en el sitio adecuado
            lsobb->last = lsobb->last + 1;   //Actualizar el valor de lso.last
            *costo = cost;
            return 2; 
        }
    }
    else{
        return 0;  //No hay espacio en la lista
    }
}


/*
Codificacion de Baja:
return 0 - Fracaso por elemento inexistente en lista
return 1 - Fracaso por no confirmar la baja
return 2 - Exito
return 3 - Fracaso por coincidir en codigo, pero no la nupla completa
*/
int bajaLSOBB(listBB *lsobb, Deliveries dev, float *costo){      //Baja
    int position, ok;
    float costLoc = 0.0;
    float cost = 0.0;
    
    if(localizarLSOBB(*lsobb, dev.code, &position, &costLoc) == 0){
        return 0;   //No podemos dar de baja porque no existe el elemento
    }
    else{
        int a = strcmp((dev).code, lsobb->deliveriesListBB[position].code);
        int b = strcmp((dev).name, lsobb->deliveriesListBB[position].name);
        int c = strcmp((dev).nameSender, lsobb->deliveriesListBB[position].nameSender);
        int d = strcmp((dev).address, lsobb->deliveriesListBB[position].address);
        int e = strcmp((dev).dateSender, lsobb->deliveriesListBB[position].dateSender);
        int f = strcmp((dev).dateReceived, lsobb->deliveriesListBB[position].dateReceived);
        if(a == 0 && b == 0 && c == 0 && d == 0 && e == 0 && f == 0 && (dev.doc == lsobb->deliveriesListBB[position].doc) && (dev.docSender == lsobb->deliveriesListBB[position].docSender)){
            if(position == lsobb->last){
                lsobb->last = lsobb->last - 1;
            }
            else{
                while(position < lsobb->last){
                    lsobb->deliveriesListBB[position] = lsobb->deliveriesListBB[position + 1];
                    position = position + 1;
                    cost += 1;
                }
                lsobb->last = lsobb->last - 1;
                *costo = cost;
            }
            return 2;  //Baja exitosa
        }
        else{
            return 3;
        }
    }
}


/*
Codificacion de la Evocacion:
return 0 - Fracaso por no existir coincidencias
return 1 - Exito
*/
int evocacionLSOBB(listBB lsobb, Deliveries *dev, float *costo){    //Evocacion
    int position;
    float costLoc = 0.0;

    if((localizarLSOBB(lsobb, (*dev).code, &position, &costLoc)) == 0){
        *costo = costLoc;
        return 0;
    }
    else{
        strcpy((*dev).code, lsobb.deliveriesListBB[position].code);
        (*dev).doc = lsobb.deliveriesListBB[position].doc;
        (*dev).docSender = lsobb.deliveriesListBB[position].docSender;
        strcpy((*dev).name, lsobb.deliveriesListBB[position].name);
        strcpy((*dev).nameSender, lsobb.deliveriesListBB[position].nameSender);
        strcpy((*dev).address, lsobb.deliveriesListBB[position].address);
        strcpy((*dev).dateSender, lsobb.deliveriesListBB[position].dateSender);
        strcpy((*dev).dateReceived, lsobb.deliveriesListBB[position].dateReceived);
        *costo = costLoc;
        return 1;
    }
}


/*
Codificacion de Pertenece:
return 0 - Fracaso por no existir elemento
return 1 - Fracaso por existir elemento, pero no coincide con los atributos
return 2 - Exito
*/
int perteneceLSOBB(Deliveries dev, listBB lsobb){   //Pertenece
    int position;
    float costLoc = 0.0;
    
    if((localizarLSOBB(lsobb, dev.code, &position, &costLoc)) == 1){
        int a = strcmp((dev).code, lsobb.deliveriesListBB[position].code);
        int b = strcmp((dev).name, lsobb.deliveriesListBB[position].name);
        int c = strcmp((dev).nameSender, lsobb.deliveriesListBB[position].nameSender);
        int d = strcmp((dev).address, lsobb.deliveriesListBB[position].address);
        int e = strcmp((dev).dateSender, lsobb.deliveriesListBB[position].dateSender);
        int f = strcmp((dev).dateReceived, lsobb.deliveriesListBB[position].dateReceived);

        if(a == 0 && b == 0 && c == 0 && d == 0 && e == 0 && f == 0 && (dev.doc == lsobb.deliveriesListBB[position].doc) && (dev.docSender == lsobb.deliveriesListBB[position].docSender)){
            return 2;
        }
        else{
            return 1;
        }
    }
    else{
        return 0;
    }
}


/*
Codificacion del modificar:
return 0 - Fracaso por elemento inexistente en listBBa
return 1 - Exito en la modificacion
*/
int modificarLSOBB(listBB *lsobb, Deliveries *dev){  //Modificar
    int position, i, j = 0, option;
    char n[NAME], date[DATE];
    float costLoc = 0.0;

    if((localizarLSOBB(*lsobb, (*dev).code, &position, &costLoc)) == 1){
       
        (*dev) = lsobb->deliveriesListBB[position];

        printf("\n==================================================================");
        printf("\n               Esta por modificar datos. Estos son:         ");
        printf("\n==================================================================\n");
        printf("\n| Codigo: %s", lsobb->deliveriesListBB[position].code);
        printf("\n| Dni receptor: %ld", lsobb->deliveriesListBB[position].doc);
        printf("\n| Dni remitente: %ld", lsobb->deliveriesListBB[position].docSender);
        printf("\n| Nombre y apellido del receptor: %s", lsobb->deliveriesListBB[position].name);
        printf("\n| Nombre y apellido del remitente: %s", lsobb->deliveriesListBB[position].nameSender);
        printf("\n| Domicilio del envio: %s", lsobb->deliveriesListBB[position].address);
        printf("\n| Fecha de envio: %s", lsobb->deliveriesListBB[position].dateSender);
        printf("\n| Fecha de recepcion: %s", lsobb->deliveriesListBB[position].dateReceived);
        printf("\n===================================================================\n");

        do{
            do{
                printf("\n");
                printf("\n|--------------------------------------------|");
                printf("\n|         ¿Que dato desea modificar?         |");
                printf("\n|--------------------------------------------|");
                printf("\n| 1.Documento del receptor                   |");
                printf("\n| 2.Documento del emisor                     |");
                printf("\n| 3.Nombre del receptor                      |");
                printf("\n| 4.Nombre del emisor                        |");
                printf("\n| 5.Domicilio                                |");
                printf("\n| 6.Fecha de envio                           |");
                printf("\n| 7.Fecha de recepcion                       |");
                printf("\n|--------------------------------------------|\n");
                scanf("%d", &option);
            }while(option < 1 || option > 7);

            switch(option){
                case 1: printf("|--------------------------------------|\n");
                        printf("|  Ingrese el documento del receptor:  |\n");
                        scanf("%ld", &(*dev).doc);
                        break;

                case 2: printf("|-------------------------------------|\n");
                        printf("|  Ingrese el documento del emisor:   |\n");
                        scanf("%ld", &(*dev).docSender);
                        break;

                case 3: printf("|------------------------------------|\n");
                        printf("|  Ingrese el nombre del receptor:   |\n");
                        scanf(" %[^\n]", n);
                        for(i = 0; n[i] != '\0'; i++){
                            n[i] = toupper(n[i]);
                        }
                        strcpy((*dev).name, n);
                        break;

                case 4: printf("|---------------------------------|\n");
                        printf("|  Ingrese el nombre del emisor:  |\n");
                        scanf(" %[^\n]", n);
                        for(i = 0; n[i] != '\0'; i++){
                            n[i] = toupper(n[i]);
                        }
                        strcpy((*dev).nameSender, n);
                        break;

                case 5: printf("|-----------------------------------|\n");
                        printf("|  Ingrese la direccion del envio:  |\n");
                        scanf(" %[^\n]", n);
                        for(i = 0; n[i] != '\0'; i++){
                            n[i] = toupper(n[i]);
                        }
                        strcpy((*dev).address, n);
                        break;

                case 6: printf("|------------------------------|\n");
                        printf("|  Ingrese la fecha de envio:  |\n");
                        scanf(" %[^\n]", date);
                        for(i = 0; date[i] != '\0'; i++){
                            date[i] = toupper(date[i]);
                        }
                        strcpy((*dev).dateSender, date);
                        break;

                case 7: printf("|----------------------------------|\n");
                        printf("|  Ingrese la fecha de recepcion:  |\n");
                        scanf(" %[^\n]", date);
                        for(i = 0; date[i] != '\0'; i++){
                            date[i] = toupper(date[i]);
                        }
                        strcpy((*dev).dateReceived, date);
                        break;
            }

            do{
                printf("\n");
                printf("|---------------------------------------------|\n");
                printf("| Ingrese 1 si desea seguir modificando datos |\n");
                printf("|---------------------------------------------|\n");
                printf("|          Ingrese 0 si desea salir           |\n");
                printf("|---------------------------------------------|\n");
                scanf("%d", &j);
            }while(j > 1 || j < 0);

        }while(j == 1);
        
        lsobb->deliveriesListBB[position] = (*dev);
        return 1;    //Modificacion exitosa
    }
    else{
        return 0;   //No podemos modificar porque no existe el elemento
    }
}


void mostrarLSOBB(listBB lsobb){      //Mostrar
    int i, enter, cont = 0;

    for(i = 0; i <= lsobb.last; i++){
        printf("\n|========================================|");
        printf("\n| Codigo: %s", lsobb.deliveriesListBB[i].code);
        printf("\n| Dni receptor: %ld", lsobb.deliveriesListBB[i].doc);
        printf("\n| Dni remitente: %ld", lsobb.deliveriesListBB[i].docSender);
        printf("\n| Nombre y apellido del receptor: %s", lsobb.deliveriesListBB[i].name);
        printf("\n| Nombre y apellido del remitente: %s", lsobb.deliveriesListBB[i].nameSender);
        printf("\n| Domicilio del envio: %s", lsobb.deliveriesListBB[i].address);
        printf("\n| Fecha de envio: %s", lsobb.deliveriesListBB[i].dateSender);
        printf("\n| Fecha de recepcion: %s", lsobb.deliveriesListBB[i].dateReceived);
        printf("\n|========================================|\n\n");
        cont++;

        if(cont == 3){
            cont = 0;
            do{
                printf("\n|---------------------------------|");
                printf("\n|     Ingrese 1 para continuar    |");
                printf("\n|---------------------------------|\n");
                scanf("%d", &enter);
            }while(enter != 1);
        }
    }
}


#endif