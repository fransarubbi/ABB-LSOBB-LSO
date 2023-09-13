#ifndef ABB_H_INCLUDED
#define ABB_H_INCLUDED
#define SIZE 300
#include "envios.h"
#include <stdlib.h>


//Nodo del ABB
typedef struct Node{
    Deliveries abbDev;
    struct Node *rightSon;
    struct Node *leftSon;
}Node;


//ABB
typedef struct{
    int cant;
    Node *root;
    Node *father;
    Node *cursor;
}abb;


void initABB(abb *abbTree){
    //abb *arbol = (abb*)malloc(sizeof(abb));
    abbTree->root = NULL;
    abbTree->father = NULL;
    abbTree->cursor = NULL;
    abbTree->cant = 0;
}


int getCantABB(abb abbTree){
    return abbTree.cant;
}


/*
Codificacion de Localizacion:
return 0 - Fracaso, no existe elemento
return 1 - Exito
*/
int localizarABB(abb *abbTree, char c[]){

    //Colocamos los cursores en la raiz
    (*abbTree).father = abbTree->root;
    (*abbTree).cursor = abbTree->root;

   while((abbTree->cursor != NULL) && (strcmp(abbTree->cursor->abbDev.code, c) != 0)){
        if(strcmp(abbTree->cursor->abbDev.code, c) < 0){
            (*abbTree).father = abbTree->cursor;
            (*abbTree).cursor = abbTree->cursor->rightSon;
        }
        else{
            (*abbTree).father = abbTree->cursor;
            (*abbTree).cursor = abbTree->cursor->leftSon;
        }
    }

    if(abbTree->cursor != NULL){
        return 1;
    }
    else{
        return 0;
    }
}


/*
Codificacion del Alta:
return 0 - Fracaso por falta de memoria
return 1 - Fracaso por elemento existente
return 2 - Exito
*/
int altaABB(abb *abbTree, Deliveries dev){

    Node *nodo = (Node*)malloc(sizeof(Node));  //Primero verifico que haya memoria disponible
    if(nodo == NULL){
        free((void*)nodo);
        return 0;  //No hay espacio, fin alta
    }
    else{
        if(localizarABB(abbTree, dev.code) == 0){   //No encontro el elemento en el arbol
            nodo->abbDev = dev;     //Asignacion de datos al nodo auxiliar
            nodo->leftSon = NULL;   //Hijo izquierdo a null
            nodo->rightSon = NULL;  //Hijo derecho a null

            if(abbTree->root == NULL){  //Arbol vacio
                abbTree->root = nodo;   //Asignar el nodo auxiliar a la raiz del arbol
                abbTree->cant = abbTree->cant + 1;  //Sumar 1 a la cantidad de nodos del arbol
                return 2;
            }
            else{
                if(strcmp(abbTree->father->abbDev.code, nodo->abbDev.code) < 0){ 
                    abbTree->father->rightSon = nodo;  //Codigo del nuevo nodo, es mayor al codigo del padre
                    abbTree->cant = abbTree->cant + 1;  //Sumar 1 a la cantidad de nodos del arbol
                }
                else{
                    abbTree->father->leftSon = nodo;  //Codigo del nuevo nodo, es menor al codigo del padre
                    abbTree->cant = abbTree->cant + 1;  //Sumar 1 a la cantidad de nodos del arbol
                }
                return 2;
            }
        }
        else{
            free((void*)nodo);
            return 1; //Elemento existente
        }  
    }
}


/*
Codificacion de Baja:
return 0 - Fracaso por elemento inexistente en arbol
return 1 - Fracaso por no confirmar la baja
return 2 - Exito
*/
int bajaABB(abb *abbTree, char c[]){

    int ok;
    Node *aux1, *aux2;

    if(localizarABB(abbTree, c) == 1){
        do{
            printf("\n===========================================================");
            printf("\n            Esta por eliminar datos. Estos son:         ");
            printf("\n===========================================================\n");
            printf("\n| Codigo: %s", abbTree->cursor->abbDev.code);
            printf("\n| Dni receptor: %ld", abbTree->cursor->abbDev.doc);
            printf("\n| Dni remitente: %ld", abbTree->cursor->abbDev.docSender);
            printf("\n| Nombre y apellido del receptor: %s", abbTree->cursor->abbDev.name);
            printf("\n| Nombre y apellido del remitente: %s", abbTree->cursor->abbDev.nameSender);
            printf("\n| Domicilio del envio: %s", abbTree->cursor->abbDev.address);
            printf("\n| Fecha de envio: %s", abbTree->cursor->abbDev.dateSender);
            printf("\n| Fecha de recepcion: %s", abbTree->cursor->abbDev.dateReceived);
            printf("\n===========================================================");
            printf("\n                    ¿Esta de acuerdo?                    ");
            printf("\n             0.No                        1.Si            ");
            printf("\n===========================================================\n");
            scanf("%d", &ok);
        }while(ok < 0 || ok > 1);

        if(ok == 1){
            //Case 1: eliminar nodo sin descendencia
            if((abbTree->cursor->leftSon == NULL) && (abbTree->cursor->rightSon == NULL)){
                if(abbTree->cursor == abbTree->root){  //Posible caso en que se elimina la raiz
                    free((void*)(abbTree->cursor));
                    abbTree->root = NULL;
                    abbTree->cant = 0;  //Raiz sin descendencia, por lo que al eliminarla, habran 0 nodos
                    return 2;
                }
                else{
                    if(abbTree->father->leftSon == abbTree->cursor){
                        abbTree->father->leftSon == NULL;
                        free((void*)(abbTree->cursor));
                        abbTree->cant = abbTree->cant - 1;
                        return 2;
                    }
                    else{
                        abbTree->father->rightSon = NULL;
                        free((void*)(abbTree->cursor));
                        abbTree->cant = abbTree->cant - 1;
                        return 2;
                    }
                }
            }

            //Case 2: eliminar nodo con una descendencia (hijo en nodo derecho)
            if(abbTree->cursor->leftSon == NULL && abbTree->cursor->rightSon != NULL){
                if(abbTree->cursor == abbTree->root){
                    abbTree->root = abbTree->cursor->rightSon;
                    free((void*)(abbTree->cursor));
                    abbTree->cant = abbTree->cant - 1;
                    return 2;
                }
                else{
                    if(abbTree->father->leftSon == abbTree->cursor){
                        abbTree->father->leftSon = abbTree->cursor->rightSon;
                        free((void*)(abbTree->cursor));
                        abbTree->cant = abbTree->cant - 1;
                        return 2;
                    }
                    else{
                        abbTree->father->rightSon = abbTree->cursor->rightSon;
                        free((void*)(abbTree->cursor));
                        abbTree->cant = abbTree->cant - 1;
                        return 2;
                    }
                }
            }


            //Case 2: eliminar nodo con una descendencia (hijo nodo izquierdo) 
            if(abbTree->cursor->leftSon != NULL && abbTree->cursor->rightSon == NULL){
                if(abbTree->cursor == abbTree->root){
                    abbTree->root = abbTree->cursor->leftSon;
                    free((void*)(abbTree->cursor));
                    abbTree->cant = abbTree->cant - 1;
                    return 2;
                }
                else{
                    if(abbTree->father->leftSon == abbTree->cursor){
                        abbTree->father->leftSon = abbTree->cursor->leftSon;
                        free((void*)(abbTree->cursor));
                        abbTree->cant = abbTree->cant - 1;
                        return 2;
                    }
                    else{
                        abbTree->father->rightSon = abbTree->cursor->leftSon;
                        free((void*)(abbTree->cursor));
                        abbTree->cant = abbTree->cant - 1;
                        return 2;
                    }
                }
            }


            //Case 3: eliminar nodo con dos descendencias
            if(abbTree->cursor->leftSon != NULL && abbTree->cursor->rightSon != NULL){
                
                abbTree->father = abbTree->cursor;
                abbTree->cursor = abbTree->cursor->rightSon;

                while(abbTree->cursor->leftSon != NULL){
                    abbTree->cursor = abbTree->cursor->leftSon;
                }
                abbTree->father->abbDev = abbTree->cursor->abbDev;

                if(abbTree->father->rightSon != abbTree->cursor){
                    abbTree->father = abbTree->father->rightSon;
                    while(abbTree->father->leftSon != abbTree->cursor){
                        abbTree->father = abbTree->father->leftSon;
                    }
                    abbTree->father->leftSon = abbTree->cursor->rightSon;
                }
                else{
                    abbTree->father->rightSon = abbTree->cursor->rightSon;
                }
                free((void*)(abbTree->cursor));
                return 2;
            }
        }
        else{
            return 1; //Baja cancelada
        }
    }
    else{
        return 0; //No existe el elemento en el arbol
    }
}


void preordenABB(Node *nodo, int ok, int i){

    if((i%3) == 0 && (ok == 1)){
        do{
            printf("\n|------------------------------|");
            printf("\n| Ingrese 1 para seguir viendo |");
            printf("\n|     Ingrese 0 para salir     |");
            printf("\n|------------------------------|\n\n");
            scanf("%d", &ok);
        }while(ok < 1 || ok > 1);
    }
    if(ok == 1){
        if(nodo != NULL){
            printf("\n===========================================================\n");
            printf("\n| Codigo: %s", nodo->abbDev.code);
            printf("\n| Dni receptor: %ld", nodo->abbDev.doc);
            printf("\n| Dni remitente: %ld", nodo->abbDev.docSender);
            printf("\n| Nombre y apellido del receptor: %s", nodo->abbDev.name);
            printf("\n| Nombre y apellido del remitente: %s", nodo->abbDev.nameSender);
            printf("\n| Domicilio del envio: %s", nodo->abbDev.address);
            printf("\n| Fecha de envio: %s", nodo->abbDev.dateSender);
            printf("\n| Fecha de recepcion: %s", nodo->abbDev.dateReceived);
            printf("\n===========================================================\n");

            if(nodo->leftSon != NULL){
                printf("\n|------------------|");
                printf("\n|  Hijo izquierdo  |");
                printf("\n|------------------|");
                printf("\n Codigo: %s", nodo->leftSon->abbDev.code);
            }
            else{
                printf("\n|-------------------------|");
                printf("\n| No tiene hijo izquierdo |");
                printf("\n|-------------------------|");
            }

            if(nodo->rightSon != NULL){
                printf("\n|----------------|");
                printf("\n|  Hijo derecho  |");
                printf("\n|----------------|");
                printf("\n Codigo: %s", nodo->rightSon->abbDev.code);
            }
            else{
                printf("\n|-----------------------|");
                printf("\n| No tiene hijo derecho |");
                printf("\n|-----------------------|\n");
            }
        
            if(nodo->leftSon != NULL){
                preordenABB(nodo->leftSon, ok, i+1);
            }
            if(nodo->rightSon != NULL){
                preordenABB(nodo->rightSon, ok, i+1);
            }
        }
    }
}


/*
Codificacion del modificar:
return 0 - Fracaso por elemento inexistente en el arbol
return 1 - Exito en la modificacion
*/
/*
void modificarABB(abb *abbTree, Deliveries dev){

    if(localizarABB(abbTree, dev.code) == 0){

        printf("\n==================================================================");
        printf("\n               Esta por modificar datos. Estos son:         ");
        printf("\n==================================================================\n");
        printf("\n| Codigo: %s", abbTree->cursor->abbDev.code);
        printf("\n| Dni receptor: %ld", lso->deliveriesList[position].doc);
        printf("\n| Dni remitente: %ld", lso->deliveriesList[position].docSender);
        printf("\n| Nombre y apellido del receptor: %s", lso->deliveriesList[position].name);
        printf("\n| Nombre y apellido del remitente: %s", lso->deliveriesList[position].nameSender);
        printf("\n| Domicilio del envio: %s", lso->deliveriesList[position].address);
        printf("\n| Fecha de envio: %s", lso->deliveriesList[position].dateSender);
        printf("\n| Fecha de recepcion: %s", lso->deliveriesList[position].dateReceived);
        printf("\n===================================================================\n");
    }

}*/


/*
Codificacion de la Evocacion:
return 0 - Fracaso por no existir coincidencias
return 1 - Exito
*/
int evocacionABB(abb abbTree, Deliveries *dev){

    if(localizarABB(&abbTree, dev->code) == 0){
        return 0;
    }
    else{
        strcpy((*dev).code, abbTree.cursor->abbDev.code);
        (*dev).doc = abbTree.cursor->abbDev.doc;
        (*dev).docSender = abbTree.cursor->abbDev.docSender;
        strcpy((*dev).name, abbTree.cursor->abbDev.name);
        strcpy((*dev).nameSender, abbTree.cursor->abbDev.nameSender);
        strcpy((*dev).address, abbTree.cursor->abbDev.address);
        strcpy((*dev).dateSender, abbTree.cursor->abbDev.dateSender);
        strcpy((*dev).dateReceived, abbTree.cursor->abbDev.dateReceived);
        return 1;
    }
}

#endif