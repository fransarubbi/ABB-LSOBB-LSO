#ifndef ABB_H_INCLUDED
#define ABB_H_INCLUDED
#define SIZE 300
#include "envios.h"
#include <stdlib.h>


//Nodo del ABB
typedef struct Node{
    Deliveries abbDev;   //Datos
    struct Node *rightSon;  //Hijo derecho
    struct Node *leftSon;   //Hijo izquierdo
}Node;


//ABB
typedef struct{
    int cant;   //Cantidad de nodos internos del arbol (elementos cargados)
    Node *root;  //Raiz del arbol
    Node *father;  //Padre de un nodo
    Node *cursor;  //Cursor del arbol
}abb;


//Colocar los punteros del arbol a NULL y cant en cero
void initABB(abb *abbTree){   
    abbTree->root = NULL;
    abbTree->father = NULL;
    abbTree->cursor = NULL;
    abbTree->cant = 0;
}


//Reset arbol para comparar estructuras. Es recursivo aplicando preorden
void resetABB(Node *nodo){
    if(nodo != NULL){        
        if(nodo->leftSon != NULL){
            resetABB(nodo->leftSon);
        }
        if(nodo->rightSon != NULL){
            resetABB(nodo->rightSon);
        }
        free(nodo);
    }
}


//Obtener la cantidad de nodos internos
int getCantABB(abb abbTree){  
    return abbTree.cant;
}


/*
Codificacion de Localizacion:
return 0 - Fracaso, no existe elemento
return 1 - Exito
*/
int localizarABB(abb *abbTree, char c[], float *costo){

    float costLoc = 0.0;
    //Colocamos los cursores en la raiz
    (*abbTree).father = abbTree->root;  
    (*abbTree).cursor = abbTree->root;  

   while((abbTree->cursor != NULL) && (strcmp(abbTree->cursor->abbDev.code, c) != 0)){  //Recorrer si no se esta en nodo externo y no coincide el codigo
        if(strcmp(abbTree->cursor->abbDev.code, c) < 0){    //Codigo almacenado menor que codigo buscado
            (*abbTree).father = abbTree->cursor;            //Al padre del nodo le damos el cursor
            (*abbTree).cursor = abbTree->cursor->rightSon;  //Al cursor le damos su hijo derecho
        }
        else{                                               //Codigo almacenado mayor que codigo buscado
            (*abbTree).father = abbTree->cursor;            //Al padre del nodo le damos el cursor
            (*abbTree).cursor = abbTree->cursor->leftSon;   //Al cursor le damos su hijo izquiero
        }
        costLoc += 1;
    }

    if(abbTree->cursor != NULL){   //Cursor en nodo externo
        costLoc += 1;
        *costo = costLoc;
        return 1;                  //Exito
    }
    else{
        *costo = costLoc;
        return 0;                  //Fracaso
    }
}


/*
Codificacion del Alta:
return 0 - Fracaso por falta de memoria
return 1 - Fracaso por elemento existente
return 2 - Exito
*/
int altaABB(abb *abbTree, Deliveries dev, float *costo){

    float costLoc = 0.0;
    float cost = 0.0;

    Node *nodo = (Node*)malloc(sizeof(Node));  //Primero verifico que haya memoria disponible
    if(nodo == NULL){
        free((void*)nodo);
        return 0;  //Fracaso, no hay espacio
    }
    else{
        if(localizarABB(abbTree, dev.code, &costLoc) == 0){   //No encontro el elemento en el arbol
            nodo->abbDev = dev;     //Asignacion de datos al nodo auxiliar
            nodo->leftSon = NULL;   //Hijo izquierdo a null
            nodo->rightSon = NULL;  //Hijo derecho a null

            if(abbTree->root == NULL){  //Arbol vacio
                abbTree->root = nodo;   //Asignar el nodo auxiliar a la raiz del arbol
                abbTree->cant = abbTree->cant + 1;  //Sumar 1 a la cantidad de nodos del arbol
                cost += 0.5;
                *costo = cost;
                return 2;  //Exito
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
                cost += 0.5;
                *costo = cost;
                return 2;  //Exito
            }
        }
        else{
            free((void*)nodo);
            return 1; //Fracaso, elemento existente
        }  
    }
}


/*
Codificacion de Baja:
return 0 - Fracaso por elemento inexistente en arbol
return 1 - Fracaso por no confirmar la baja
return 2 - Exito
return 3 - Fracaso por coincidir en codigo, pero no la nupla completa
*/
int bajaABB(abb *abbTree, Deliveries dev, float *costo){
    float costLoc = 0.0;
    float cost = 0.0;
    Node *auxFather, *auxCursor;

    if(localizarABB(abbTree, dev.code, &costLoc) == 1){
        int a = strcmp((dev).code, abbTree->cursor->abbDev.code);
        int b = strcmp((dev).name, abbTree->cursor->abbDev.name);
        int c = strcmp((dev).nameSender, abbTree->cursor->abbDev.nameSender);
        int d = strcmp((dev).address, abbTree->cursor->abbDev.address);
        int e = strcmp((dev).dateSender, abbTree->cursor->abbDev.dateSender);
        int f = strcmp((dev).dateReceived, abbTree->cursor->abbDev.dateReceived);
        //Toda la nupla debe coincidir con los datos leidos del archivo
        if(a == 0 && b == 0 && c == 0 && d == 0 && e == 0 && f == 0 && (dev.doc == abbTree->cursor->abbDev.doc) && (dev.docSender == abbTree->cursor->abbDev.docSender)){
            //Case 1: eliminar nodo sin descendencia
            if((abbTree->cursor->leftSon == NULL) && (abbTree->cursor->rightSon == NULL)){
                if(abbTree->cursor == abbTree->root){  //Posible caso en que se elimina la raiz
                    free((void*)(abbTree->cursor));   //Liberar memoria
                    abbTree->root = NULL;  //Colocar raiz en NULL (arbol vacio)
                    abbTree->cant = abbTree->cant - 1;   //Decrementar cantidad
                    cost += 0.5;                        //Un solo corrimiento de punteros
                    *costo = cost;                      
                    return 2;   //Exito
                }
                else{
                    if(abbTree->father->leftSon == abbTree->cursor){  //Eliminar nodo sin descendia que es hijo izquierdo de otro nodo
                        abbTree->father->leftSon = NULL;             //El hijo izquierdo del nodo padre, a NULL (hijo eliminado)
                        free((void*)(abbTree->cursor));             //Liberar memoria
                        abbTree->cant = abbTree->cant - 1;            //Decrementar cantidad
                        cost += 0.5;                                  //Un solo corrimiento de punteros
                        *costo = cost;
                        return 2;                                     //Exito
                    }
                    else{                                             //Cursor en el hijo derecho de un nodo
                        abbTree->father->rightSon = NULL;             //Eliminar nodo sin descendia que es hijo derecho de otro nodo
                        free((void*)(abbTree->cursor));               //Liberar memoria 
                        abbTree->cant = abbTree->cant - 1;            //Decrementar cantidad
                        cost += 0.5;                                  //Un solo corrimiento de punteros
                        *costo = cost;
                        return 2;                                     //Exito
                    }
                }
            }


            //Case 2: eliminar nodo con una descendencia (hijo en nodo derecho)
            if((abbTree->cursor->leftSon == NULL) && (abbTree->cursor->rightSon != NULL)){  
                if(abbTree->cursor == abbTree->root){                //Posible caso en que se elimine la raiz
                    abbTree->root = abbTree->cursor->rightSon;       //A la raiz le damos su hijo derecho
                    free((void*)(abbTree->cursor));                  //Liberar memoria
                    abbTree->cant = abbTree->cant - 1;               //Decrementar cantidad
                    cost += 0.5;                                     //Un solo corrimiento de punteros
                    *costo = cost;
                    return 2;                                        //Exito
                }
                else{
                    if(abbTree->father->leftSon == abbTree->cursor){   //Eliminar nodo (cursor) que es hijo izquierdo de otro (padre)
                        abbTree->father->leftSon = abbTree->cursor->rightSon;  //Al padre del nodo a eliminar, le damos el hijo derecho del nodo a eliminar
                        free((void*)(abbTree->cursor));              //Liberar memoria
                        abbTree->cant = abbTree->cant - 1;          //Decrementar cantidad
                        cost += 0.5;                                //Un solo corrimiento de punteros
                        *costo = cost;
                        return 2;                                   //Exito
                    }
                    else{                                           //Eliminar nodo (cursor) que es hijo derecho de otro (padre)
                        abbTree->father->rightSon = abbTree->cursor->rightSon;  //Al padre del nodo a eliminar, le damos el hijo derecho del nodo a eliminar
                        free((void*)(abbTree->cursor));              //Liberar memoria            
                        abbTree->cant = abbTree->cant - 1;          //Decrementar cantidad
                        cost += 0.5;                                //Un solo corrimiento de punteros
                        *costo = cost;
                        return 2;                                   //Exito
                    }
                }
            }
            else{   //Case 2: eliminar nodo con una descendencia (hijo nodo izquierdo) 
                if((abbTree->cursor->leftSon != NULL) && (abbTree->cursor->rightSon == NULL)){ 
                    if(abbTree->cursor == abbTree->root){            //Posible caso en que se elimine la raiz
                        abbTree->root = abbTree->cursor->leftSon;    //A la raiz le damos su hijo izquierdo
                        free((void*)(abbTree->cursor));               //Liberar memoria
                        abbTree->cant = abbTree->cant - 1;           //Decrementar cantidad
                        cost += 0.5;  
                        *costo = cost;                               //Un solo corrimiento de punteros
                        return 2;                                    //Exito
                    }
                    else{
                        if(abbTree->father->leftSon == abbTree->cursor){          //Eliminar nodo (cursor) que es hijo izquierdo de otro (padre)
                            abbTree->father->leftSon = abbTree->cursor->leftSon;  //Al padre del nodo a eliminar, le damos el hijo izquierdo del nodo a eliminar
                            free((void*)(abbTree->cursor));                       //Liberar memoria
                            abbTree->cant = abbTree->cant - 1;                    //Decrementar cantidad
                            cost += 0.5;
                            *costo = cost;                                          //Un solo corrimiento de punteros
                            return 2;                                             //Exito
                        }
                        else{                                                     //Eliminar nodo (cursor) que es hijo derecho de otro (padre)
                            abbTree->father->rightSon = abbTree->cursor->leftSon; //Al padre del nodo a eliminar, le damos el hijo izquierdo del nodo a eliminar
                            free((void*)(abbTree->cursor));                       //Liberar memoria
                            abbTree->cant = abbTree->cant - 1;                    //Decrementar cantidad
                            cost += 0.5; 
                            *costo = cost;                                         //Un solo corrimiento de punteros
                            return 2;                                             //Exito
                        }
                    }
                }
            }


            //Case 3: eliminar nodo con dos descendencias
            if((abbTree->cursor->leftSon != NULL) && (abbTree->cursor->rightSon != NULL)){
                auxCursor = abbTree->cursor->rightSon;     //Colocar el puntero a nodo auxCursor, en el hijo derecho del nodo donde esta cursor
                auxFather = abbTree->cursor;               //Colocar el puntero a nodo auxFather, en el nodo donde esta cursor

                while(auxCursor->leftSon != NULL){         //Buscar el menor nodo de los mayores
                    auxFather = auxCursor;                 //Colocar el puntero a nodo auxFather, donde esta auxCursor
                    auxCursor = auxCursor->leftSon;        //Colocar el puntero a nodo auxCursor, en el hijo izquierdo del nodo actual
                }                                          //El auxFather esta encima (padre) del nodo donde esta cursor

                abbTree->cursor->abbDev = auxCursor->abbDev;   //El cursor esta en el nodo a eliminar. Copiamos los datos del nodo menor de los mayores, en el nodo cursor
                cost += 1;                                     //Asignacion de informacion, costo 1

                if(auxFather->leftSon == auxCursor){           //Si el hijo izquierdo del padre, es el nodo donde esta el auxCursor (caso general)
                    auxFather->leftSon = auxCursor->rightSon;  //Colocar el hijo izquierdo del padre, en el hijo izquierdo del nodo de reemplazo
                }
                else{                                       //Caso en que se elimina la raiz (el nodo de reemplazo esta a la derecha de su padre)
                    auxFather->rightSon = auxCursor->rightSon;    //Colocar el hijo derecho del padre, en el hijo derecho del nodo de reemplazo
                }
                cost += 0.5;                            //Ambos casos son de un solo corrimientos de punteros, costo 0.5
                *costo = cost;
                free((void*)auxCursor);                     //Liberar memoria
                abbTree->cant = abbTree->cant - 1;          //Decrementar cantidad
                return 2;                                   //Exito
            }
        }
        else{
            return 3;               //Fracaso por no coincidir toda la nupla
        }
    }
    else{
        return 0; //Fracaso, no existe el elemento en el arbol
    }
}


/*
Codificacion de la Evocacion:
return 0 - Fracaso por no existir coincidencias
return 1 - Exito
*/
int evocacionABB(abb abbTree, Deliveries *dev, float *costo){
    float costLoc = 0.0;

    if(localizarABB(&abbTree, dev->code, &costLoc) == 0){
        *costo = costLoc;
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
        *costo = costLoc;
        return 1;
    }
}


/*
Codificacion del modificar:
return 0 - Fracaso por elemento inexistente en el arbol
return 1 - Exito en la modificacion
*/
int modificarABB(abb *abbTree, Deliveries *dev){

    int option, j = 0, i;
    char n[NAME], date[DATE];
    float costLoc = 0.0;

    if(localizarABB(abbTree, (*dev).code, &costLoc) == 1){

        (*dev) = abbTree->cursor->abbDev;
        printf("\n==================================================================");
        printf("\n               Esta por modificar datos. Estos son:         ");
        printf("\n==================================================================\n");
        printf("\n| Codigo: %s", abbTree->cursor->abbDev.code);
        printf("\n| Dni receptor: %ld", abbTree->cursor->abbDev.doc);
        printf("\n| Dni remitente: %ld", abbTree->cursor->abbDev.docSender);
        printf("\n| Nombre y apellido del receptor: %s", abbTree->cursor->abbDev.name);
        printf("\n| Nombre y apellido del remitente: %s", abbTree->cursor->abbDev.nameSender);
        printf("\n| Domicilio del envio: %s", abbTree->cursor->abbDev.address);
        printf("\n| Fecha de envio: %s", abbTree->cursor->abbDev.dateSender);
        printf("\n| Fecha de recepcion: %s", abbTree->cursor->abbDev.dateReceived);
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

        abbTree->cursor->abbDev = (*dev);
        return 1;
    }
    else{
        return 0;
    }
}


//Preorden recursivo
void preordenABB(Node *nodo, int ok, int i){

    if((i%3) == 0 && (ok == 1)){  
        do{
            printf("\n|--------------------------|");
            printf("\n| Ingrese 1 para continuar |");
            printf("\n|--------------------------|\n\n");
            scanf("%d", &ok);
        }while(ok < 0 || ok > 1);
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




#endif