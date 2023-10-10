#ifndef LSO_H_INCLUDED
#define LSO_H_INCLUDED
#define SIZE 300
#include "envios.h"
#include <ctype.h>


typedef struct{
    Deliveries deliveriesList[SIZE];
    int last;
}list;


void init(list *lso){  //Inicializar la lista es poner last en -1 (vacia)
    lso->last = -1;
}


/*
Codificacion de Localizacion:
return 0 - Fracaso, no esta el elemento
return 1 - Exito
*/
int localizarLSO(list lso, char c[], int *position, float *costo){   //Localizar 
    int i = 0;
    float cost = 0.0;

    while((i <= lso.last) && strcmp(lso.deliveriesList[i].code, c) < 0){   //Porque esta ordenada de menor a mayor
        cost += 1;
        i++;
    }

    *position = i;  
    if(i <= lso.last){
        cost += 1;
        *costo = cost;
        if(strcmp(lso.deliveriesList[i].code, c) == 0){  
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        *costo = cost;
        return 0;
    } 
}


/*
Codificacion del Alta:
return 0 - Fracaso por lista llena
return 1 - Fracaso por elemento existente
return 2 - Exito
*/
int altaLSO(list *lso, Deliveries dev, float *costo){    //Alta
    int position, last;
    float cost = 0.0;
    float costLoc = 0.0;

    last = lso->last;  //Variable last para no modificar el valor de lso.last

    if(last < (SIZE - 1)){
        if(localizarLSO(*lso, dev.code, &position, &costLoc) == 1){  //Elemento localizado en la lista
            return 1; 
        }
        else{
            //El elemento no existe en la lista
            while(position <= last){   //Realizar shifteo a derecha
                lso->deliveriesList[last + 1] = lso->deliveriesList[last];
                cost += 1;  //1 por la celda consultada y 0.5 por la copia de datos
                last = last - 1;
            }
            lso->deliveriesList[position] = dev;   //Ingresar el nuevo elemento en el sitio adecuado
            lso->last = lso->last + 1;   //Actualizar el valor de lso.last
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
int bajaLSO(list *lso, Deliveries dev, float *costo){      //Baja
    int position, ok;
    float costLoc = 0.0;
    float cost = 0.0;
    
    if(localizarLSO(*lso, dev.code, &position, &costLoc) == 0){
        return 0;   //No podemos dar de baja porque no existe el elemento
    }
    else{
        int a = strcmp((dev).code, lso->deliveriesList[position].code);
        int b = strcmp((dev).name, lso->deliveriesList[position].name);
        int c = strcmp((dev).nameSender, lso->deliveriesList[position].nameSender);
        int d = strcmp((dev).address, lso->deliveriesList[position].address);
        int e = strcmp((dev).dateSender, lso->deliveriesList[position].dateSender);
        int f = strcmp((dev).dateReceived, lso->deliveriesList[position].dateReceived);
        if(a == 0 && b == 0 && c == 0 && d == 0 && e == 0 && f == 0 && (dev.doc == lso->deliveriesList[position].doc) && (dev.docSender == lso->deliveriesList[position].docSender)){
            if(position == lso->last){
                lso->last = lso->last - 1;
            }
            else{
                while(position < lso->last){
                    lso->deliveriesList[position] = lso->deliveriesList[position + 1];
                    position = position + 1;
                    cost += 1;  //1 por la celda consultada y 0.5 por la copia de datos
                }
                lso->last = lso->last - 1;
                *costo = cost;
            }
            return 2;  //Baja exitosa
        }
        else{
            return 3; //Fracaso por no coincidir
        }
    }
}


/*
Codificacion de la Evocacion:
return 0 - Fracaso por no existir coincidencias
return 1 - Exito
*/
int evocacionLSO(list lso, Deliveries *dev, float *costo){    //Evocacion
    int position;
    float costLoc = 0.0;

    if((localizarLSO(lso, (*dev).code, &position, &costLoc)) == 0){
        *costo = costLoc;
        return 0;
    }
    else{
        strcpy((*dev).code, lso.deliveriesList[position].code);
        (*dev).doc = lso.deliveriesList[position].doc;
        (*dev).docSender = lso.deliveriesList[position].docSender;
        strcpy((*dev).name, lso.deliveriesList[position].name);
        strcpy((*dev).nameSender, lso.deliveriesList[position].nameSender);
        strcpy((*dev).address, lso.deliveriesList[position].address);
        strcpy((*dev).dateSender, lso.deliveriesList[position].dateSender);
        strcpy((*dev).dateReceived, lso.deliveriesList[position].dateReceived);
        *costo = costLoc;
        return 1;
    }
}


void mostrarLSO(list lso){      //Mostrar
    int i, enter, cont = 0;

    for(i = 0; i <= lso.last; i++){
        printf("\n|========================================|");
        printf("\n| Codigo: %s", lso.deliveriesList[i].code);
        printf("\n| Dni receptor: %ld", lso.deliveriesList[i].doc);
        printf("\n| Dni remitente: %ld", lso.deliveriesList[i].docSender);
        printf("\n| Nombre y apellido del receptor: %s", lso.deliveriesList[i].name);
        printf("\n| Nombre y apellido del remitente: %s", lso.deliveriesList[i].nameSender);
        printf("\n| Domicilio del envio: %s", lso.deliveriesList[i].address);
        printf("\n| Fecha de envio: %s", lso.deliveriesList[i].dateSender);
        printf("\n| Fecha de recepcion: %s", lso.deliveriesList[i].dateReceived);
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