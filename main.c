//Grupo 7  Sarubbi Franco - Orozco Mateo


#include "lso.h"
#include "lsobb.h"
#include "abb.h"


//Funciones menu principal
void mostrarEstructuras(abb , list , listBB , int , int );


//Funciones del menu LSO
void loadList(list *, Deliveries *, int *, StructCost *);  //Cargar elementos
void preload(list *, int *, StructCost *);    //Realizar precarga de datos por archivo
void delete(list *, int *, StructCost *);    //Eliminar elementos
void changeList(list *);    //Modificar elementos
void information(list , StructCost *);     //Mostrar informacion de un elemento


//Funciones del menu LSOBB
void loadListBB(listBB *, Deliveries *, int *, StructCost *);  //Cargar elementos
void preloadListBB(listBB *, int *, StructCost *);    //Realizar precarga de datos por archivo
void deleteListBB(listBB *, int *, StructCost *);    //Eliminar elementos
void changeListBB(listBB *);    //Modificar elementos
void informationListBB(listBB , StructCost *);     //Mostrar informacion de un elemento


//Funciones del menu ABB
void loadABB(abb *, Deliveries *, StructCost *);
void deleteABB(abb *, StructCost *);
void changeABB(abb *);
void informationABB(abb , StructCost *);
void preloadABB(abb *, StructCost *);


//Funciones internas
void loadDeliveries(Deliveries *);   //Funcion auxiliar de carga de datos
void resetAll(list *, listBB *, abb *, int *, int *);
int lecturaOperaciones(StructCost *, list *, listBB *, abb *, int *, int *);


int main(){

 abb abbTree;
 list lso;
 listBB lsobb;
 Deliveries dev;
 StructCost c;
 int opcion, cant = 0, cantBB = 0, lect;
 int menu, i = 1, ok = 1;

 init(&lso);
 initLSOBB(&lsobb);
 initABB(&abbTree);
 initStructCost(&c);


 do{
    do{
        printf("\n|===========================================|");
        printf("\n|                BIENVENIDOS!               |");
        printf("\n|              ENVIOS EL REVOLEO            |");
        printf("\n|===========================================|");
        printf("\n|              MENU DE OPCIONES             |");
        printf("\n|===========================================|");
        printf("\n|         1. Menu de opciones LSO           |");
        printf("\n|         2. Menu de opciones LSOBB         |");
        printf("\n|         3. Menu de opciones ABB           |");
        printf("\n|         4. Comparar estructuras           |");
        printf("\n|         5. Mostrar estructuras            |");
        printf("\n|         6. Mostrar costos cargados        |");
        printf("\n|         7. Salir del sistema              |");
        printf("\n|===========================================|\n\n");
        scanf("%d", &menu);
    }while(menu < 1 || menu > 7);
    
    switch(menu){
        case 1: do{ 
                    printf("\n|===========================================|");
                    printf("\n|     1.Ingresar nuevos envios              |");
                    printf("\n|     2.Eliminar envios existentes          |");
                    printf("\n|     3.Modificar datos de un envio         |");
                    printf("\n|     4.Consultar informacion de un envio   |");
                    printf("\n|     5.Memorizacion previa                 |");
                    printf("\n|     6.Volver al menu principal            |");
                    printf("\n|===========================================|\n\n");
                    scanf("%d", &opcion);

                    while(opcion < 1 || opcion > 6){

                        printf("\n|--------------------------------------|");
                        printf("\n| Por favor, ingrese un valor correcto |");
                        printf("\n|--------------------------------------|");
                        printf("\n|  1.Ingresar nuevos envios            |");
                        printf("\n|  2.Eliminar envios existentes        |");
                        printf("\n|  3.Modificar datos de un envio       |");
                        printf("\n|  4.Consultar informacion de un envio |");
                        printf("\n|  5.Memorizacion previa               |");
                        printf("\n|  6.Volver al menu principal          |");
                        printf("\n|======================================|\n\n");
                        scanf("%d", &opcion);
                    }

                    switch(opcion){
                        case 1: if(cant == SIZE){
                                    printf("\n|------------------------------------------------|");
                                    printf("\n| No se pueden cargar datos. La lista esta llena |");
                                    printf("\n|------------------------------------------------|\n");
                                }
                                else{
                                    loadList(&lso, &dev, &cant, &c);
                                }
                                break;

                        case 2: delete(&lso, &cant, &c);
                                break;

                        case 3: if(cant == 0){
                                    printf("\n|---------------------------------------------------|");
                                    printf("\n| No se pueden modificar datos. La lista esta vacia |");
                                    printf("\n|---------------------------------------------------|\n");
                                }
                                else{
                                    changeList(&lso);
                                }
                                break;

                        case 4: if(cant == 0){
                                    printf("\n|-------------------------------------------------|");
                                    printf("\n| No se pueden mostrar datos. La lista esta vacia |");
                                    printf("\n|-------------------------------------------------|\n");
                                }
                                else{
                                    information(lso, &c);
                                }
                                break;

                        case 5: preload(&lso, &cant, &c);
                                break;
                    }

                }while(opcion != 6);
                break;

        case 2: do{ 
                    printf("\n|===========================================|");
                    printf("\n|     1.Ingresar nuevos envios              |");
                    printf("\n|     2.Eliminar envios existentes          |");
                    printf("\n|     3.Modificar datos de un envio         |");
                    printf("\n|     4.Consultar informacion de un envio   |");
                    printf("\n|     5.Memorizacion previa                 |");
                    printf("\n|     6.Volver al menu principal            |");
                    printf("\n|===========================================|\n\n");
                    scanf("%d", &opcion);

                    while(opcion < 1 || opcion > 6){

                        printf("\n|--------------------------------------|");
                        printf("\n| Por favor, ingrese un valor correcto |");
                        printf("\n|--------------------------------------|");
                        printf("\n|  1.Ingresar nuevos envios            |");
                        printf("\n|  2.Eliminar envios existentes        |");
                        printf("\n|  3.Modificar datos de un envio       |");
                        printf("\n|  4.Consultar informacion de un envio |");
                        printf("\n|  5.Memorizacion previa               |");
                        printf("\n|  6.Volver al menu principal          |");
                        printf("\n|======================================|\n\n");
                        scanf("%d", &opcion);
                    }

                    switch(opcion){
                        case 1: if(cantBB == SIZE){
                                    printf("\n|------------------------------------------------|");
                                    printf("\n| No se pueden cargar datos. La lista esta llena |");
                                    printf("\n|------------------------------------------------|\n");
                                }
                                else{
                                    loadListBB(&lsobb, &dev, &cantBB, &c);
                                }
                                break;

                        case 2: deleteListBB(&lsobb, &cantBB, &c);
                                break;

                        case 3: if(cantBB == 0){
                                    printf("\n|---------------------------------------------------|");
                                    printf("\n| No se pueden modificar datos. La lista esta vacia |");
                                    printf("\n|---------------------------------------------------|\n");
                                }
                                else{
                                    changeListBB(&lsobb);
                                }
                                break;

                        case 4: if(cantBB == 0){
                                    printf("\n|-------------------------------------------------|");
                                    printf("\n| No se pueden mostrar datos. La lista esta vacia |");
                                    printf("\n|-------------------------------------------------|\n");
                                }
                                else{
                                    informationListBB(lsobb, &c);
                                }
                                break;

                        case 5: preloadListBB(&lsobb, &cantBB, &c);
                                break;
                    }

                }while(opcion != 6);
                break;

        case 3: do{
                    printf("\n|===========================================|");
                    printf("\n|     1.Ingresar nuevos envios              |");
                    printf("\n|     2.Eliminar envios existentes          |");
                    printf("\n|     3.Modificar datos de un envio         |");
                    printf("\n|     4.Consultar informacion de un envio   |");
                    printf("\n|     5.Memorizacion previa                 |");
                    printf("\n|     6.Volver al menu principal            |");
                    printf("\n|===========================================|\n\n");
                    scanf("%d", &opcion);

                    while(opcion < 1 || opcion > 6){
                        printf("\n|--------------------------------------|");
                        printf("\n| Por favor, ingrese un valor correcto |");
                        printf("\n|--------------------------------------|");
                        printf("\n|  1.Ingresar nuevos envios            |");
                        printf("\n|  2.Eliminar envios existentes        |");
                        printf("\n|  3.Modificar datos de un envio       |");
                        printf("\n|  4.Consultar informacion de un envio |");
                        printf("\n|  5.Memorizacion previa               |");
                        printf("\n|  6.Volver al menu principal          |");
                        printf("\n|======================================|\n\n");
                        scanf("%d", &opcion);
                    }

                    switch(opcion){
                        case 1: loadABB(&abbTree, &dev, &c);
                                break;

                        case 2: if(getCantABB(abbTree) == 0){
                                    printf("\n|----------------------------------------------|");
                                    printf("\n| No se pueden eliminar elementos. Arbol vacio |");
                                    printf("\n|----------------------------------------------|");
                                }
                                else{
                                    deleteABB(&abbTree, &c);
                                }
                                break;

                        case 3: if(getCantABB(abbTree) == 0){
                                    printf("\n|-----------------------------------------------|");
                                    printf("\n| No se pueden modificar elementos. Arbol vacio |");
                                    printf("\n|-----------------------------------------------|");
                                }
                                else{
                                    changeABB(&abbTree);
                                }
                                break;

                        case 4: if(getCantABB(abbTree) == 0){
                                    printf("\n|---------------------------------------------|");
                                    printf("\n| No se pueden mostrar elementos. Arbol vacio |");
                                    printf("\n|---------------------------------------------|");
                                }
                                else{
                                    informationABB(abbTree, &c);
                                }
                                break;

                        case 5: preloadABB(&abbTree, &c);
                                break;
                    }

                }while(opcion != 6);
                break;

        case 4: resetAll(&lso, &lsobb, &abbTree, &cant, &cantBB);
                initStructCost(&c);
                lect = lecturaOperaciones(&c, &lso, &lsobb, &abbTree, &cant, &cantBB);
                if(lect == 1){
                    mostrarCostos(c);
                }
                else{
                    printf("\n|-------------------------------------------------------------------|");
                    printf("\n| No hay costos cargados. No se ha realizado la lectura por archivo |");
                    printf("\n|-------------------------------------------------------------------|");
                }
                break;

        case 5: mostrarEstructuras(abbTree, lso, lsobb, cant, cantBB);
                break;

        case 6: mostrarCostos(c);
                break;
    }
 }while(menu != 7);

 
 printf("\n|===========================================|");
 printf("\n|       GRACIAS POR USAR EL SISTEMA         |");
 printf("\n|             ENVIOS EL REVOLEO             |");
 printf("\n|===========================================|");
 printf("\n|      Sarubbi Franco - Orozco Mateo        |");
 printf("\n|===========================================|\n\n");

 return 0;
}



//Funciones del menu principal
void mostrarEstructuras(abb abbTree, list lso, listBB lsobb, int cant, int cantBB){
    
    int opcion, ok = 1, i = 1, enter;

    do{
        do{
            printf("\n|------------------------------------------------------------|");
            printf("\n|                    Mostrando Estructuras                   |");
            printf("\n|------------------------------------------------------------|");
            printf("\n|  0. Salir de Mostrar Estructuras                           |");
            printf("\n|  1. Mostrar Estructuras                                    |");
            printf("\n|------------------------------------------------------------|\n");
            scanf("%d", &enter);
        }while(enter < 0 || enter > 1);
        
        if(enter == 1){
            do{
                printf("\n|------------------------------------------------------------|");
                printf("\n|  1. Mostrar Lista Secuencual Ordenada                      |");
                printf("\n|  2. Mostrar Lista Secuencial Ordenada con Busqueda Binaria |");
                printf("\n|  3. Mostrar Arbol Binario de Busqueda                      |");
                printf("\n|------------------------------------------------------------|\n");
                scanf("%d", &opcion);
            }while(opcion < 1 || opcion > 3);

            switch(opcion){
                case 1: if(cant == 0){
                            printf("\n|-------------------------------------------------|");
                            printf("\n| No se pueden mostrar datos. La lista esta vacia |");
                            printf("\n|-------------------------------------------------|\n");
                        }
                        else{
                            printf("\n\n      Mostrando %d elementos\n", cant);
                            mostrarLSO(lso);
                        }
                        break;

                case 2: if(cantBB == 0){
                            printf("\n|-------------------------------------------------|");
                            printf("\n| No se pueden mostrar datos. La lista esta vacia |");
                            printf("\n|-------------------------------------------------|\n");
                        }
                        else{
                            printf("\n\n      Mostrando %d elementos\n", cantBB);
                            mostrarLSOBB(lsobb);
                        }
                        break;

                case 3: if(getCantABB(abbTree) == 0){
                            printf("\n|---------------------------------------------|");
                            printf("\n| No se pueden mostrar elementos. Arbol vacio |");
                            printf("\n|---------------------------------------------|\n");
                        }
                        else{
                            preordenABB(abbTree.root, ok, i);
                        }
                        break;
            }
        }
    }while(enter != 0);    
}


void mostrarCostos(StructCost c){

    printf("\n|------------------------------------------------------|");
    printf("\n|          Mostrando Costos de las Estructuras         |");
    printf("\n|------------------------------------------------------|\n\n");
    printf("\n|------------------------------------------------------|");
    printf("\n|              Lista Secuencial Ordenada               |");
    printf("\n|------------------------------------------------------|");
    printf("\n|    Funcion    |    Costo Max     |     Costo Medio   |");
    printf("\n|------------------------------------------------------|");
    printf("\n|      Alta     |   %.2f                %.2f           ", c.lso.maxCostInsert, c.lso.medCostInsert);
    printf("\n|------------------------------------------------------");
    printf("\n|      Baja     |   %.2f                %.2f              ", c.lso.maxCostSupress, c.lso.medCostSupress);
    printf("\n|------------------------------------------------------");
    printf("\n| Evoc. Exitosa |   %.2f                %.2f              ", c.lso.maxCostSucEvo, c.lso.medCostSucEvo);
    printf("\n|------------------------------------------------------");
    printf("\n| Evoc. Fracaso |   %.2f                %.2f              ", c.lso.maxCostFailEvo, c.lso.medCostFailEvo);
    printf("\n|------------------------------------------------------|\n");

    printf("\n|------------------------------------------------------|");
    printf("\n|      Lista Secuencial Ordenada Busqueda Binaria      |");
    printf("\n|------------------------------------------------------|");
    printf("\n|    Funcion    |    Costo Max     |     Costo Medio   |");
    printf("\n|------------------------------------------------------|");
    printf("\n|      Alta     |   %.2f                %.2f            ", c.lsobb.maxCostInsert, c.lsobb.medCostInsert);
    printf("\n|------------------------------------------------------");
    printf("\n|      Baja     |   %.2f                %.2f              ", c.lsobb.maxCostSupress, c.lsobb.medCostSupress);
    printf("\n|------------------------------------------------------");
    printf("\n| Evoc. Exitosa |   %.2f                %.2f              ", c.lsobb.maxCostSucEvo, c.lsobb.medCostSucEvo);
    printf("\n|------------------------------------------------------");
    printf("\n| Evoc. Fracaso |   %.2f                %.2f              ", c.lsobb.maxCostFailEvo, c.lsobb.medCostFailEvo);
    printf("\n|------------------------------------------------------|\n");

    printf("\n|------------------------------------------------------|");
    printf("\n|              Arbol Binario de Busqueda               |");
    printf("\n|------------------------------------------------------|");
    printf("\n|    Funcion    |    Costo Max     |     Costo Medio   |");
    printf("\n|------------------------------------------------------|");
    printf("\n|      Alta     |   %.2f                %.2f              ", c.abb.maxCostInsert, c.abb.medCostInsert);
    printf("\n|------------------------------------------------------");
    printf("\n|      Baja     |   %.2f                %.2f              ", c.abb.maxCostSupress, c.abb.medCostSupress);
    printf("\n|------------------------------------------------------");
    printf("\n| Evoc. Exitosa |   %.2f                %.2f              ", c.abb.maxCostSucEvo, c.abb.medCostSucEvo);
    printf("\n|------------------------------------------------------");
    printf("\n| Evoc. Fracaso |   %.2f                %.2f              ", c.abb.maxCostFailEvo, c.abb.medCostFailEvo);
    printf("\n|------------------------------------------------------|\n\n\n");
}



//Funciones internas
void loadDeliveries(Deliveries *dev){

    int i;
    long d;
    char c[CODE], n[NAME], date[DATE];

    printf("|---------------------------------------------|\n");
    printf("| Ingrese el codigo correspondiente al envio: |\n");
    scanf("%s", c);
    for(i = 0; c[i] != '\0'; i++){
        c[i] = toupper(c[i]);
    }
    strcpy(dev->code, c);

    do{
        printf("|------------------------------------|\n");
        printf("| Ingrese el documento del receptor: |\n");
        scanf("%ld", &d);
    }while(d < 0 || d > 99999999);  //rango de documento entre 4.000.000 hasta 50.000.000
    dev->doc = d;

    do{
        printf("|----------------------------------|\n");
        printf("| Ingrese el documento del emisor: |\n");
        scanf("%ld", &d);
    }while(d < 0 || d > 99999999);  //rango de documento entre 4.000.000 hasta 50.000.000
    dev->docSender = d;

    printf("|---------------------------------|\n");
    printf("| Ingrese el nombre del receptor: |\n");
    scanf(" %[^\n]", n);
    for(i = 0; n[i] != '\0'; i++){
        n[i] = toupper(n[i]);
    }
    strcpy(dev->name, n);

    printf("|-------------------------------|\n");
    printf("| Ingrese el nombre del emisor: |\n");
    scanf(" %[^\n]", n);
    for(i = 0; n[i] != '\0'; i++){
        n[i] = toupper(n[i]);
    }
    strcpy(dev->nameSender, n);

    printf("|-----------------------------------|\n");
    printf("|  Ingrese la direccion del envio:  |\n");
    scanf(" %[^\n]", n);
    for(i = 0; n[i] != '\0'; i++){
        n[i] = toupper(n[i]);
    }
    strcpy(dev->address, n);

    printf("|------------------------------|\n");
    printf("|  Ingrese la fecha de envio:  |\n");
    scanf(" %[^\n]", date);
    for(i = 0; date[i] != '\0'; i++){
        date[i] = toupper(date[i]);
    }
    strcpy(dev->dateSender, date);

    printf("|----------------------------------|\n");
    printf("|  Ingrese la fecha de recepcion:  |\n");
    scanf(" %[^\n]", date);
    for(i = 0; date[i] != '\0'; i++){
        date[i] = toupper(date[i]);
    }
    strcpy(dev->dateReceived, date);
}


void resetAll(list *lso, listBB *lsobb, abb *abbTree, int *cant, int *cantBB){
    
    resetABB(abbTree->root);
    abbTree->root = NULL;
    abbTree->cant = 0;
    resetLSO(lso);
    resetLSOBB(lsobb);
    *cant = 0;
    *cantBB = 0;
}


int lecturaOperaciones(StructCost *c, list *lso, listBB *lsobb, abb *abbTree, int *cant, int *cantBB){

    Deliveries dev;
    char code[CODE], name[NAME], nameSender[NAME], addres[NAME], dateS[DATE], dateR[DATE];
    long dni, dniS;
    int value, enter, i, codeOperator, baja = 1;
    float costo;

    FILE *preload;
    preload = fopen("Operaciones-Envios.txt", "r");

    if(preload == NULL){
        printf("|----------------------------------------------|\n");
        printf("|       No se pudo acceder al archivo          |\n");
        printf("|----------------------------------------------|\n\n");
        return 0;
    }
    else{
        while(!feof(preload)){
            fscanf(preload, "%d\n", &codeOperator);

            fscanf(preload, " %[^\n]\n", code);
            for(i = 0; code[i] != '\0'; i++){
                code[i] = toupper(code[i]);
            }
            strcpy(&dev.code, code);

            if(codeOperator == 1 || codeOperator == 2){
                
                fscanf(preload, "%ld\n", &dni);
                dev.doc = dni;
            
                fscanf(preload, " %[^\n]\n", nameSender);
                for(i = 0; nameSender[i] != '\0'; i++){
                    nameSender[i] = toupper(nameSender[i]);
                }
                strcpy(&dev.nameSender, nameSender);
            
                fscanf(preload, " %[^\n]\n", addres);
                for(i = 0; addres[i] != '\0'; i++){
                    addres[i] = toupper(addres[i]);
                }
                strcpy(&dev.address, addres);
            
                fscanf(preload, "%ld\n", &dniS);
                dev.docSender = dniS;

                fscanf(preload, " %[^\n]\n", name);
                for(i = 0; name[i] != '\0'; i++){
                    name[i] = toupper(name[i]);
                }
                strcpy(&dev.name, name);
            
                fscanf(preload, " %[^\n]\n", dateS);
                for(i = 0; dateS[i] != '\0'; i++){
                    dateS[i] = toupper(dateS[i]);
                }
                strcpy(&dev.dateSender, dateS);

                fscanf(preload, " %[^\n]\n", dateR);
                for(i = 0; dateR[i] != '\0'; i++){
                    dateR[i] = toupper(dateR[i]);
                }
                strcpy(&dev.dateReceived, dateR);

                switch(codeOperator){
                    case 1: if(*cant == SIZE){
                                printf("|----------------------------------------------|\n");
                                printf("| Error al cargar elemento. No hay mas espacio |\n");
                                printf("|----------------------------------------------|\n\n");
                            }
                            else{
                                costo = 0.0;
                                value = altaLSO(lso, dev, &costo);
                                switch(value){
                                    case 1: printf("|-------------------------------------------------|\n");
                                            printf("| Error al cargar elemento. El elemento ya existe |\n");
                                            printf("|-------------------------------------------------|\n\n");
                                            break;

                                    case 2: printf("|----------------------------------------------|\n");
                                            printf("|            Carga exitosa de datos            |\n");
                                            printf("|----------------------------------------------|\n\n");
                                            *cant = *cant + 1;
                                            if(c->lso.maxCostInsert < costo){
                                                c->lso.maxCostInsert = costo;
                                            }
                                            c->lso.cantInsert += 1;
                                            c->lso.costAcumInsert += costo;
                                            c->lso.medCostInsert = (c->lso.costAcumInsert)/(c->lso.cantInsert);
                                            break;
                                }
                            }
                            if(*cantBB == SIZE){
                                printf("|----------------------------------------------|\n");
                                printf("| Error al cargar elemento. No hay mas espacio |\n");
                                printf("|----------------------------------------------|\n\n");
                            }
                            else{
                                costo = 0.0;
                                value = altaLSOBB(lsobb, dev, &costo);
                                switch(value){
                                    case 1: printf("|-------------------------------------------------|\n");
                                            printf("| Error al cargar elemento. El elemento ya existe |\n");
                                            printf("|-------------------------------------------------|\n\n");
                                            break;

                                    case 2: printf("|----------------------------------------------|\n");
                                            printf("|            Carga exitosa de datos            |\n");
                                            printf("|----------------------------------------------|\n\n");
                                            *cantBB = *cantBB + 1;
                                            if(c->lsobb.maxCostInsert < costo){
                                                c->lsobb.maxCostInsert = costo;
                                            }
                                            c->lsobb.cantInsert += 1;
                                            c->lsobb.costAcumInsert += costo;
                                            c->lsobb.medCostInsert = (c->lsobb.costAcumInsert)/(c->lsobb.cantInsert);
                                            break;
                                }
                            }
                            if(getCantABB(*abbTree) == SIZE){
                                printf("|----------------------------------------------|\n");
                                printf("| Error al cargar elemento. No hay mas espacio |\n");
                                printf("|----------------------------------------------|\n\n");
                            }
                            else{
                                costo = 0.0;
                                value = altaABB(abbTree, dev, &costo);
                                switch(value){
                                    case 1: printf("|-------------------------------------------------|\n");
                                            printf("| Error al cargar elemento. El elemento ya existe |\n");
                                            printf("|-------------------------------------------------|\n\n");
                                            break;

                                    case 2: printf("|----------------------------------------------|\n");
                                            printf("|            Carga exitosa de datos            |\n");
                                            printf("|----------------------------------------------|\n\n");
                                            if(c->abb.maxCostInsert < costo){
                                                c->abb.maxCostInsert = costo;
                                            }
                                            c->abb.cantInsert += 1;
                                            c->abb.costAcumInsert += costo;
                                            c->abb.medCostInsert = (c->abb.costAcumInsert)/(c->abb.cantInsert);
                                            break;
                                }
                            }
                            break;


                    case 2: if(*cant == 0){
                                printf("|---------------------------------------|\n");
                                printf("| Error al borrar elemento. Lista vacia |\n");
                                printf("|---------------------------------------|\n\n");
                            }
                            else{
                                costo = 0.0;
                                value = bajaLSO(lso, dev, &costo, baja);
                                switch(value){
                                    case 0: printf("|-----------------------------------------------------|\n");
                                            printf("|   Error al borrar elemento. No existe en la lista   |\n");
                                            printf("|-----------------------------------------------------|\n\n");
                                            break;

                                    case 1: printf("|-----------------------------------------------------|\n");
                                            printf("|  Error al borrar elemento. Ha cancelado el proceso  |\n");
                                            printf("|-----------------------------------------------------|\n\n");
                                            break;

                                    case 2: printf("|----------------------------------------------|\n");
                                            printf("|            Baja exitosa de datos             |\n");
                                            printf("|----------------------------------------------|\n\n");
                                            *cant = *cant - 1;
                                            if(c->lso.maxCostSupress < costo){
                                                c->lso.maxCostSupress = costo;
                                            }
                                            c->lso.cantSupress += 1;
                                            c->lso.costAcumSupress += costo;
                                            c->lso.medCostSupress = (c->lso.costAcumSupress)/(c->lso.cantSupress);
                                            break; 

                                    case 3: printf("\n|------------------------------------------|");
                                            printf("\n| Error por no coincidir la nupla completa |");
                                            printf("\n|------------------------------------------|");
                                            break;
                                }
                            }
                            if(*cantBB == 0){
                                printf("|---------------------------------------|\n");
                                printf("| Error al borrar elemento. Lista vacia |\n");
                                printf("|---------------------------------------|\n\n");
                            }
                            else{
                                costo = 0.0;
                                value = bajaLSOBB(lsobb, dev, &costo, baja);
                                switch(value){
                                    case 0: printf("|-----------------------------------------------------|\n");
                                            printf("|   Error al borrar elemento. No existe en la lista   |\n");
                                            printf("|-----------------------------------------------------|\n\n");
                                            break;

                                    case 1: printf("|-----------------------------------------------------|\n");
                                            printf("|  Error al borrar elemento. Ha cancelado el proceso  |\n");
                                            printf("|-----------------------------------------------------|\n\n");
                                            break;

                                    case 2: printf("|----------------------------------------------|\n");
                                            printf("|            Baja exitosa de datos             |\n");
                                            printf("|----------------------------------------------|\n\n");
                                            *cantBB = *cantBB - 1;
                                            if(c->lsobb.maxCostSupress < costo){
                                                c->lsobb.maxCostSupress = costo;
                                            }
                                            c->lsobb.cantSupress += 1;
                                            c->lsobb.costAcumSupress += costo;
                                            c->lsobb.medCostSupress = (c->lsobb.costAcumSupress)/(c->lsobb.cantSupress);
                                            break;

                                    case 3: printf("\n|------------------------------------------|");
                                            printf("\n| Error por no coincidir la nupla completa |");
                                            printf("\n|------------------------------------------|");
                                            break; 
                                }
                            }
                            if(abbTree->root == NULL){
                                printf("|---------------------------------------|\n");
                                printf("| Error al borrar elemento. Arbol vacio |\n");
                                printf("|---------------------------------------|\n\n");
                            }
                            else{
                                costo = 0.0;
                                value = bajaABB(abbTree, dev, &costo, baja);
                                switch(value){
                                    case 0: printf("|-----------------------------------------------------|\n");
                                            printf("|   Error al borrar elemento. No existe en el arbol   |\n");
                                            printf("|-----------------------------------------------------|\n\n");
                                            break;

                                    case 1: printf("|-----------------------------------------------------|\n");
                                            printf("|  Error al borrar elemento. Ha cancelado el proceso  |\n");
                                            printf("|-----------------------------------------------------|\n\n");
                                            break;

                                    case 2: printf("|----------------------------------------------|\n");
                                            printf("|            Baja exitosa de datos             |\n");
                                            printf("|----------------------------------------------|\n\n");
                                            if(c->abb.maxCostSupress < costo){
                                                c->abb.maxCostSupress = costo;
                                            }
                                            c->abb.cantSupress += 1;
                                            c->abb.costAcumSupress += costo;
                                            c->abb.medCostSupress = (c->abb.costAcumSupress)/(c->abb.cantSupress);
                                            break; 
                                    
                                    case 3: printf("\n|------------------------------------------|");
                                            printf("\n| Error por no coincidir la nupla completa |");
                                            printf("\n|------------------------------------------|");
                                            break;
                                }
                            }
                            break;
                }
            }
            else{
                if(codeOperator == 3){
                    if(*cant == 0){
                        printf("|---------------------------------------|\n");
                        printf("| Error al evocar elemento. Lista vacia |\n");
                        printf("|---------------------------------------|\n\n");
                    }
                    else{
                        costo = 0.0;
                        value = evocacionLSO(*lso, &dev, &costo);
                        switch(value){
                            case 1: printf("\n|---------------------------------|");
                                    printf("\n    INFORMACION DEL ENVIO %s", code);
                                    printf("\n|---------------------------------|\n\n");
                                    printf("\n| Codigo: %s", dev.code);
                                    printf("\n| Dni receptor: %ld", dev.doc);
                                    printf("\n| Dni remitente: %ld", dev.docSender);
                                    printf("\n| Nombre y apellido del receptor: %s", dev.name);
                                    printf("\n| Nombre y apellido del remitente: %s", dev.nameSender);
                                    printf("\n| Domicilio del envio: %s", dev.address);
                                    printf("\n| Fecha de envio: %s", dev.dateSender);
                                    printf("\n| Fecha de recepcion: %s", dev.dateReceived);
                                    if(c->lso.maxCostSucEvo < costo){
                                        c->lso.maxCostSucEvo = costo;
                                    }
                                    c->lso.cantSucEvo += 1;
                                    c->lso.costAcumSucEvo += costo;
                                    c->lso.medCostSucEvo = (c->lso.costAcumSucEvo)/(c->lso.cantSucEvo);
                                    break;

                            case 0: printf("|--------------------------------------------------------------|\n");
                                    printf("    No se han encontrado coincidencias para el codigo %s\n", code);
                                    printf("|--------------------------------------------------------------|\n\n");
                                    if(c->lso.maxCostFailEvo < costo){
                                        c->lso.maxCostFailEvo = costo;
                                    }
                                    c->lso.cantFailEvo += 1;
                                    c->lso.costAcumFailEvo += costo;
                                    c->lso.medCostFailEvo = (c->lso.costAcumFailEvo)/(c->lso.cantFailEvo);
                                    break;
                        }
                    }

                    if(*cantBB == 0){
                        printf("|---------------------------------------|\n");
                        printf("| Error al evocar elemento. Lista vacia |\n");
                        printf("|---------------------------------------|\n\n");
                    }
                    else{
                        costo = 0.0;
                        value = evocacionLSOBB(*lsobb, &dev, &costo);
                        switch(value){
                            case 1: printf("\n|---------------------------------|");
                                    printf("\n    INFORMACION DEL ENVIO %s", code);
                                    printf("\n|---------------------------------|\n\n");
                                    printf("\n| Codigo: %s", dev.code);
                                    printf("\n| Dni receptor: %ld", dev.doc);
                                    printf("\n| Dni remitente: %ld", dev.docSender);
                                    printf("\n| Nombre y apellido del receptor: %s", dev.name);
                                    printf("\n| Nombre y apellido del remitente: %s", dev.nameSender);
                                    printf("\n| Domicilio del envio: %s", dev.address);
                                    printf("\n| Fecha de envio: %s", dev.dateSender);
                                    printf("\n| Fecha de recepcion: %s", dev.dateReceived);
                                    if(c->lsobb.maxCostSucEvo < costo){
                                        c->lsobb.maxCostSucEvo = costo;
                                    }
                                    c->lsobb.cantSucEvo += 1;
                                    c->lsobb.costAcumSucEvo += costo;
                                    c->lsobb.medCostSucEvo = (c->lsobb.costAcumSucEvo)/(c->lsobb.cantSucEvo);
                                    break;

                            case 0: printf("|--------------------------------------------------------------|\n");
                                    printf("    No se han encontrado coincidencias para el codigo %s\n", code);
                                    printf("|--------------------------------------------------------------|\n\n");
                                    if(c->lsobb.maxCostFailEvo < costo){
                                        c->lsobb.maxCostFailEvo = costo;
                                    }
                                    c->lsobb.cantFailEvo += 1;
                                    c->lsobb.costAcumFailEvo += costo;
                                    c->lsobb.medCostFailEvo = (c->lsobb.costAcumFailEvo)/(c->lsobb.cantFailEvo);
                                    break;
                        }
                    }
                    
                    if(getCantABB(*abbTree) == 0){
                        printf("|---------------------------------------|\n");
                        printf("| Error al evocar elemento. Arbol vacio |\n");
                        printf("|---------------------------------------|\n\n");
                    }
                    else{
                        costo = 0.0;
                        value = evocacionABB(*abbTree, &dev, &costo);
                        switch(value){
                            case 1: printf("\n|---------------------------------|");
                                    printf("\n    INFORMACION DEL ENVIO %s", code);
                                    printf("\n|---------------------------------|\n\n");
                                    printf("\n| Codigo: %s", dev.code);
                                    printf("\n| Dni receptor: %ld", dev.doc);
                                    printf("\n| Dni remitente: %ld", dev.docSender);
                                    printf("\n| Nombre y apellido del receptor: %s", dev.name);
                                    printf("\n| Nombre y apellido del remitente: %s", dev.nameSender);
                                    printf("\n| Domicilio del envio: %s", dev.address);
                                    printf("\n| Fecha de envio: %s", dev.dateSender);
                                    printf("\n| Fecha de recepcion: %s", dev.dateReceived);
                                    if(c->abb.maxCostSucEvo < costo){
                                        c->abb.maxCostSucEvo = costo;
                                    }
                                    c->abb.cantSucEvo += 1;
                                    c->abb.costAcumSucEvo += costo;
                                    c->abb.medCostSucEvo = (c->abb.costAcumSucEvo)/(c->abb.cantSucEvo);
                                    break;

                            case 0: printf("|--------------------------------------------------------------|\n");
                                    printf("    No se han encontrado coincidencias para el codigo %s\n", code);
                                    printf("|--------------------------------------------------------------|\n\n");
                                    if(c->abb.maxCostFailEvo < costo){
                                        c->abb.maxCostFailEvo = costo;
                                    }
                                    c->abb.cantFailEvo += 1;
                                    c->abb.costAcumFailEvo += costo;
                                    c->abb.medCostFailEvo = (c->abb.costAcumFailEvo)/(c->abb.cantFailEvo);
                                    break;
                        }
                    }
                }
                else{
                    printf("\n|----------------------------------------|");
                    printf("\n| Error. Codigo de operacion no conocido |");
                    printf("\n|----------------------------------------|");
                }
            }
            codeOperator = 0;
        }
        fclose(preload);
        return 1;
    }
}



//Funciones del menu LSO
void loadList(list *lso, Deliveries *dev, int *cant, StructCost *c){

    int value, enter;
    float costo = 0.0;

    printf("\n|--------------------------------|");
    printf("\n|-------- Cargando Datos --------|");
    printf("\n|--------------------------------|\n\n");
    loadDeliveries(dev);
    value = altaLSO(lso, *dev, &costo);
    switch(value){
        case 0: printf("|----------------------------------------------|\n");
                printf("| Error al cargar elemento. No hay mas espacio |\n");
                printf("|----------------------------------------------|\n\n");
                break;
            
        case 1: printf("|-------------------------------------------------|\n");
                printf("| Error al cargar elemento. El elemento ya existe |\n");
                printf("|-------------------------------------------------|\n\n");
                break;

        case 2: printf("|----------------------------------------------|\n");
                printf("|           Carga exitosa de datos             |\n");
                printf("|----------------------------------------------|\n\n");
                *cant = *cant + 1;
                if(c->lso.maxCostInsert < costo){
                    c->lso.maxCostInsert = costo;
                }
                c->lso.cantInsert += 1;
                c->lso.costAcumInsert += costo;
                c->lso.medCostInsert = (c->lso.costAcumInsert)/(c->lso.cantInsert);
                break;
    }

    do{
        printf("\n|---------------------------------|");
        printf("\n|  Ingrese 1 para volver al menu  |");
        printf("\n|---------------------------------|\n");
        scanf("%d", &enter);
    }while(enter != 1);
}


void preload(list *lso, int *cant, StructCost *c){
    
    Deliveries dev;
    char code[CODE], name[NAME], nameSender[NAME], addres[NAME], dateS[DATE], dateR[DATE];
    long dni, dniS;
    int value, enter, i;
    float costo = 0.0;

    FILE *preload;
    preload = fopen("Envios.txt", "r");

    if(preload == NULL){
        printf("|----------------------------------------------|\n");
        printf("|       No se pudo acceder al archivo          |\n");
        printf("|----------------------------------------------|\n\n");
        exit(1);
    }
    else{
        while(!feof(preload)){
            fscanf(preload, " %[^\n]\n", code);
            for(i = 0; code[i] != '\0'; i++){
                code[i] = toupper(code[i]);
            }
            strcpy(&dev.code, code);
            
            fscanf(preload, "%ld\n", &dni);
            dev.doc = dni;
            
            fscanf(preload, " %[^\n]\n", nameSender);
            for(i = 0; nameSender[i] != '\0'; i++){
                nameSender[i] = toupper(nameSender[i]);
            }
            strcpy(&dev.nameSender, nameSender);
            
            fscanf(preload, " %[^\n]\n", addres);
            for(i = 0; addres[i] != '\0'; i++){
                addres[i] = toupper(addres[i]);
            }
            strcpy(&dev.address, addres);
            
            fscanf(preload, "%ld\n", &dniS);
            dev.docSender = dniS;

            fscanf(preload, " %[^\n]\n", name);
            for(i = 0; name[i] != '\0'; i++){
                name[i] = toupper(name[i]);
            }
            strcpy(&dev.name, name);
            
            fscanf(preload, " %[^\n]\n", dateS);
            for(i = 0; dateS[i] != '\0'; i++){
                dateS[i] = toupper(dateS[i]);
            }
            strcpy(&dev.dateSender, dateS);

            fscanf(preload, " %[^\n]\n", dateR);
            for(i = 0; dateR[i] != '\0'; i++){
                dateR[i] = toupper(dateR[i]);
            }
            strcpy(&dev.dateReceived, dateR);

            value = altaLSO(lso, dev, &costo);
            switch(value){
                case 0: printf("|----------------------------------------------|\n");
                        printf("| Error al cargar elemento. No hay mas espacio |\n");
                        printf("|----------------------------------------------|\n\n");
                        exit(1);
                        break;
            
                case 1: printf("|-------------------------------------------------|\n");
                        printf("| Error al cargar elemento. El elemento ya existe |\n");
                        printf("|-------------------------------------------------|\n\n");
                        break;

                case 2: printf("|----------------------------------------------|\n");
                        printf("|            Carga exitosa de datos            |\n");
                        printf("|----------------------------------------------|\n\n");
                        *cant = *cant + 1;
                        if(c->lso.maxCostInsert < costo){
                            c->lso.maxCostInsert = costo;
                        }
                        c->lso.cantInsert += 1;
                        c->lso.costAcumInsert += costo;
                        c->lso.medCostInsert = (c->lso.costAcumInsert)/(c->lso.cantInsert);
                        break;
            }
        }
        printf("           Elementos cargados: %d\n", *cant);
        fclose(preload);
    }
    
    do{
        printf("\n|---------------------------------|");
        printf("\n|  Ingrese 1 para volver al menu  |");
        printf("\n|---------------------------------|\n");
        scanf("%d", &enter);
    }while(enter != 1);
}


void delete(list *lso, int *cant, StructCost *c){

    Deliveries dev;
    char code[CODE];
    int n, i = 0, j = 0, lowValue, evocationValue, enter, baja = 0;
    float costo = 0.0;

    if(*cant < 1){
        printf("\n|------------------------------------------|");
        printf("\n| No se pueden eliminar datos. Lista vacia |");
        printf("\n|------------------------------------------|\n");
    }
    else{
        do{
            printf("|---------------------------------------------------|\n");
            printf("    ¿Cuantos envios quiere eliminar? Maximo %d\n", *cant);
            printf("|---------------------------------------------------|\n");
            scanf("%d", &n);
        }while(n < 1 || n > *cant);

        do{
            printf("\n|----------------------------------------------|");
            printf("\n|-------------- Eliminando Datos --------------|");
            printf("\n|----------------------------------------------|");
            printf("\n|   Ingrese el codigo del envio a eliminar:    |\n");
            scanf("%s", code);
            for(i = 0; code[i] != '\0'; i++){
                code[i] = toupper(code[i]);
            }
            strcpy(&dev.code, code);

            lowValue = bajaLSO(lso, dev, &costo, baja);
            switch(lowValue){
                case 0: printf("|-----------------------------------------------------|\n");
                        printf("|   Error al borrar elemento. No existe en la lista   |\n");
                        printf("|-----------------------------------------------------|\n\n");
                        j++;
                        break;

                case 1: printf("|-----------------------------------------------------|\n");
                        printf("|  Error al borrar elemento. Ha cancelado el proceso  |\n");
                        printf("|-----------------------------------------------------|\n\n");
                        j++;
                        break;

                case 2: printf("|----------------------------------------------|\n");
                        printf("|            Baja exitosa de datos             |\n");
                        printf("|----------------------------------------------|\n\n");
                        j++;
                        *cant = *cant - 1;
                        if(c->lso.maxCostSupress < costo){
                            c->lso.maxCostSupress = costo;
                        }
                        c->lso.cantSupress += 1;
                        c->lso.costAcumSupress += costo;
                        c->lso.medCostSupress = (c->lso.costAcumSupress)/(c->lso.cantSupress);
                        break;
            }
        }while(j < n);
    }

    do{
        printf("\n|---------------------------------|");
        printf("\n|  Ingrese 1 para volver al menu  |");
        printf("\n|---------------------------------|\n");
        scanf("%d", &enter);
    }while(enter != 1);
}


void changeList(list *lso){
    
    Deliveries d;
    char code[CODE];
    int i, changeValue, enter;

    printf("|----------------------------------------------------|\n");
    printf("|  Ingrese el codigo del envio que desea modificar:  |\n");
    scanf("%s", code);
    for(i = 0; code[i] != '\0'; i++){
        code[i] = toupper(code[i]);
    }
    strcpy(&d.code, code);

    changeValue = modificarLSO(lso, &d);
    if(changeValue == 1){
        printf("|-------------------------------------------------------|\n");
        printf("|   Se han realizado las modificaciones correctamente   |\n");
        printf("|-------------------------------------------------------|\n");
    }
    else{
        printf("|----------------------------------------------|\n");
        printf("|         Error al modificar los datos         |\n");
        printf("|----------------------------------------------|\n");
    }

    do{
        printf("\n|---------------------------------|");
        printf("\n|  Ingrese 1 para volver al menu  |");
        printf("\n|---------------------------------|\n");
        scanf("%d", &enter);
    }while(enter != 1);
}


void information(list lso, StructCost *c){

    Deliveries d;
    int i, evocationValue, enter;
    char code[CODE];
    float costo = 0.0;

    printf("\n|----------------------------------------------------------------|");
    printf("\n|   Ingrese el codigo del envio que desea obtener informacion:   |");
    printf("\n|----------------------------------------------------------------|\n");
    scanf("%s", code);
    for(i = 0; code[i] != '\0'; i++){
        code[i] = toupper(code[i]);
    }
    strcpy(&d.code, code);

    evocationValue = evocacionLSO(lso, &d, &costo);
    if(evocationValue == 1){
        printf("\n|---------------------------------|");
        printf("\n    INFORMACION DEL ENVIO %s", code);
        printf("\n|---------------------------------|\n\n");
        printf("\n| Codigo: %s", d.code);
        printf("\n| Dni receptor: %ld", d.doc);
        printf("\n| Dni remitente: %ld", d.docSender);
        printf("\n| Nombre y apellido del receptor: %s", d.name);
        printf("\n| Nombre y apellido del remitente: %s", d.nameSender);
        printf("\n| Domicilio del envio: %s", d.address);
        printf("\n| Fecha de envio: %s", d.dateSender);
        printf("\n| Fecha de recepcion: %s", d.dateReceived);
        if(c->lso.maxCostSucEvo < costo){
            c->lso.maxCostSucEvo = costo;
        }
        c->lso.cantSucEvo += 1;
        c->lso.costAcumSucEvo += costo;
        c->lso.medCostSucEvo = (c->lso.costAcumSucEvo)/(c->lso.cantSucEvo);
    }
    else{
        printf("|--------------------------------------------------------------|\n");
        printf("    No se han encontrado coincidencias para el codigo %s\n", code);
        printf("|--------------------------------------------------------------|\n\n");
        if(c->lso.maxCostFailEvo < costo){
            c->lso.maxCostFailEvo = costo;
        }
        c->lso.cantFailEvo += 1;
        c->lso.costAcumFailEvo += costo;
        c->lso.medCostFailEvo = (c->lso.costAcumFailEvo)/(c->lso.cantFailEvo);
    }

    do{
        printf("\n|---------------------------------|");
        printf("\n|  Ingrese 1 para volver al menu  |");
        printf("\n|---------------------------------|\n");
        scanf("%d", &enter);
    }while(enter != 1);
}



//Funciones del menu LSOBB
void loadListBB(listBB *lsobb, Deliveries *dev, int *cantBB, StructCost *c){

    int value, enter;
    float costo = 0.0;

    printf("\n|--------------------------------|");
    printf("\n|-------- Cargando Datos --------|");
    printf("\n|--------------------------------|\n\n");
    loadDeliveries(dev);
    value = altaLSOBB(lsobb, *dev, &costo);
    switch(value){
        case 0: printf("|----------------------------------------------|\n");
                printf("| Error al cargar elemento. No hay mas espacio |\n");
                printf("|----------------------------------------------|\n\n");
                break;
            
        case 1: printf("|-------------------------------------------------|\n");
                printf("| Error al cargar elemento. El elemento ya existe |\n");
                printf("|-------------------------------------------------|\n\n");
                break;

        case 2: printf("|----------------------------------------------|\n");
                printf("|           Carga exitosa de datos             |\n");
                printf("|----------------------------------------------|\n\n");
                *cantBB = *cantBB + 1;
                if(c->lsobb.maxCostInsert < costo){
                    c->lsobb.maxCostInsert = costo;
                }
                c->lsobb.cantInsert += 1;
                c->lsobb.costAcumInsert += costo;
                c->lsobb.medCostInsert = (c->lsobb.costAcumInsert)/(c->lsobb.cantInsert);
                break;
    }

    do{
        printf("\n|---------------------------------|");
        printf("\n|  Ingrese 1 para volver al menu  |");
        printf("\n|---------------------------------|\n");
        scanf("%d", &enter);
    }while(enter != 1);
}


void preloadListBB(listBB *lsobb, int *cantBB, StructCost *c){
    
    Deliveries dev;
    char code[CODE], name[NAME], nameSender[NAME], addres[NAME], dateS[DATE], dateR[DATE];
    long dni, dniS;
    int value, enter, i;
    float costo = 0.0;

    FILE *preload;
    preload = fopen("Envios.txt", "r");

    if(preload == NULL){
        printf("|----------------------------------------------|\n");
        printf("|       No se pudo acceder al archivo          |\n");
        printf("|----------------------------------------------|\n\n");
        exit(1);
    }
    else{
        while(!feof(preload)){
            fscanf(preload, " %[^\n]\n", code);
            for(i = 0; code[i] != '\0'; i++){
                code[i] = toupper(code[i]);
            }
            strcpy(&dev.code, code);
            
            fscanf(preload, "%ld\n", &dni);
            dev.doc = dni;
            
            fscanf(preload, " %[^\n]\n", nameSender);
            for(i = 0; nameSender[i] != '\0'; i++){
                nameSender[i] = toupper(nameSender[i]);
            }
            strcpy(&dev.nameSender, nameSender);
            
            fscanf(preload, " %[^\n]\n", addres);
            for(i = 0; addres[i] != '\0'; i++){
                addres[i] = toupper(addres[i]);
            }
            strcpy(&dev.address, addres);
            
            fscanf(preload, "%ld\n", &dniS);
            dev.docSender = dniS;

            fscanf(preload, " %[^\n]\n", name);
            for(i = 0; name[i] != '\0'; i++){
                name[i] = toupper(name[i]);
            }
            strcpy(&dev.name, name);
            
            fscanf(preload, " %[^\n]\n", dateS);
            for(i = 0; dateS[i] != '\0'; i++){
                dateS[i] = toupper(dateS[i]);
            }
            strcpy(&dev.dateSender, dateS);

            fscanf(preload, " %[^\n]\n", dateR);
            for(i = 0; dateR[i] != '\0'; i++){
                dateR[i] = toupper(dateR[i]);
            }
            strcpy(&dev.dateReceived, dateR);

            value = altaLSOBB(lsobb, dev, &costo);

            switch(value){
                case 0: printf("|----------------------------------------------|\n");
                        printf("| Error al cargar elemento. No hay mas espacio |\n");
                        printf("|----------------------------------------------|\n\n");
                        exit(1);
                        break;
            
                case 1: printf("|-------------------------------------------------|\n");
                        printf("| Error al cargar elemento. El elemento ya existe |\n");
                        printf("|-------------------------------------------------|\n\n");
                        break;

                case 2: printf("|----------------------------------------------|\n");
                        printf("|            Carga exitosa de datos            |\n");
                        printf("|----------------------------------------------|\n\n");
                        *cantBB = *cantBB + 1;
                        if(c->lsobb.maxCostInsert < costo){
                            c->lsobb.maxCostInsert = costo;
                        }
                        c->lsobb.cantInsert += 1;
                        c->lsobb.costAcumInsert += costo;
                        c->lsobb.medCostInsert = (c->lsobb.costAcumInsert)/(c->lsobb.cantInsert);
                        break;
            }
        }
        printf("           Elementos cargados: %d\n", *cantBB);
        fclose(preload);
    }
    
    do{
        printf("\n|---------------------------------|");
        printf("\n|  Ingrese 1 para volver al menu  |");
        printf("\n|---------------------------------|\n");
        scanf("%d", &enter);
    }while(enter != 1);
}


void deleteListBB(listBB *lsobb, int *cantBB, StructCost *c){

    Deliveries dev;
    char code[CODE];
    int n, i = 0, j = 0, lowValue, enter, baja = 0;
    float costo = 0.0;

    if(*cantBB < 1){
        printf("\n|------------------------------------------|");
        printf("\n| No se pueden eliminar datos. Lista vacia |");
        printf("\n|------------------------------------------|\n");
    }
    else{
        do{
            printf("|---------------------------------------------------|\n");
            printf("    ¿Cuantos envios quiere eliminar? Maximo %d\n", *cantBB);
            printf("|---------------------------------------------------|\n");
            scanf("%d", &n);
        }while(n < 1 || n > *cantBB);

        do{
            printf("\n|----------------------------------------------|");
            printf("\n|-------------- Eliminando Datos --------------|");
            printf("\n|----------------------------------------------|");
            printf("\n|   Ingrese el codigo del envio a eliminar:    |\n");
            scanf("%s", code);
            for(i = 0; code[i] != '\0'; i++){
                code[i] = toupper(code[i]);
            }
            strcpy(&dev.code, code);

            lowValue = bajaLSOBB(lsobb, dev, &costo, baja);
            switch(lowValue){
                case 0: printf("|-----------------------------------------------------|\n");
                        printf("|   Error al borrar elemento. No existe en la lista   |\n");
                        printf("|-----------------------------------------------------|\n\n");
                        j++;
                        break;

                case 1: printf("|-----------------------------------------------------|\n");
                        printf("|  Error al borrar elemento. Ha cancelado el proceso  |\n");
                        printf("|-----------------------------------------------------|\n\n");
                        j++;
                        break;

                case 2: printf("|----------------------------------------------|\n");
                        printf("|            Baja exitosa de datos             |\n");
                        printf("|----------------------------------------------|\n\n");
                        j++;
                        *cantBB = *cantBB - 1;
                        if(c->lsobb.maxCostSupress < costo){
                            c->lsobb.maxCostSupress = costo;
                        }
                        c->lsobb.cantSupress += 1;
                        c->lsobb.costAcumSupress += costo;
                        c->lsobb.medCostSupress = (c->lsobb.costAcumSupress)/(c->lsobb.cantSupress);
                        break;
            }
        }while(j < n);
    }

    do{
        printf("\n|---------------------------------|");
        printf("\n|  Ingrese 1 para volver al menu  |");
        printf("\n|---------------------------------|\n");
        scanf("%d", &enter);
    }while(enter != 1);
}


void changeListBB(listBB *lsobb){
    
    Deliveries d;
    char code[CODE];
    int i, changeValue, enter;

    printf("|----------------------------------------------------|\n");
    printf("|  Ingrese el codigo del envio que desea modificar:  |\n");
    scanf("%s", code);
    for(i = 0; code[i] != '\0'; i++){
        code[i] = toupper(code[i]);
    }
    strcpy(&d.code, code);

    changeValue = modificarLSOBB(lsobb, &d);
    if(changeValue == 1){
        printf("|-------------------------------------------------------|\n");
        printf("|   Se han realizado las modificaciones correctamente   |\n");
        printf("|-------------------------------------------------------|\n");
    }
    else{
        printf("|----------------------------------------------|\n");
        printf("|         Error al modificar los datos         |\n");
        printf("|----------------------------------------------|\n");
    }

    do{
        printf("\n|---------------------------------|");
        printf("\n|  Ingrese 1 para volver al menu  |");
        printf("\n|---------------------------------|\n");
        scanf("%d", &enter);
    }while(enter != 1);
}


void informationListBB(listBB lsobb, StructCost *c){

    Deliveries d;
    int i, evocationValue, enter;
    char code[CODE];
    float costo = 0.0;

    printf("\n|----------------------------------------------------------------|");
    printf("\n|   Ingrese el codigo del envio que desea obtener informacion:   |");
    printf("\n|----------------------------------------------------------------|\n");
    scanf("%s", code);
    for(i = 0; code[i] != '\0'; i++){
        code[i] = toupper(code[i]);
    }
    strcpy(&d.code, code);

    evocationValue = evocacionLSOBB(lsobb, &d, &costo);
    if(evocationValue == 1){
        printf("\n|---------------------------------|");
        printf("\n    INFORMACION DEL ENVIO %s", code);
        printf("\n|---------------------------------|\n\n");
        printf("\n| Codigo: %s", d.code);
        printf("\n| Dni receptor: %ld", d.doc);
        printf("\n| Dni remitente: %ld", d.docSender);
        printf("\n| Nombre y apellido del receptor: %s", d.name);
        printf("\n| Nombre y apellido del remitente: %s", d.nameSender);
        printf("\n| Domicilio del envio: %s", d.address);
        printf("\n| Fecha de envio: %s", d.dateSender);
        printf("\n| Fecha de recepcion: %s", d.dateReceived);
        if(c->lsobb.maxCostSucEvo < costo){
            c->lso.maxCostSucEvo = costo;
        }
        c->lsobb.cantSucEvo += 1;
        c->lsobb.costAcumSucEvo += costo;
        c->lsobb.medCostSucEvo = (c->lsobb.costAcumSucEvo)/(c->lsobb.cantSucEvo);
    }
    else{
        printf("|--------------------------------------------------------------|\n");
        printf("    No se han encontrado coincidencias para el codigo %s\n", code);
        printf("|--------------------------------------------------------------|\n\n");
        if(c->lsobb.maxCostFailEvo < costo){
            c->lsobb.maxCostFailEvo = costo;
        }
        c->lsobb.cantFailEvo += 1;
        c->lsobb.costAcumFailEvo += costo;
        c->lsobb.medCostFailEvo = (c->lsobb.costAcumFailEvo)/(c->lsobb.cantFailEvo);    
    }

    do{
        printf("\n|---------------------------------|");
        printf("\n|  Ingrese 1 para volver al menu  |");
        printf("\n|---------------------------------|\n");
        scanf("%d", &enter);
    }while(enter != 1);
}




//Funciones del menu ABB
void loadABB(abb *abbTree, Deliveries *dev, StructCost *c){

    int value, enter;
    float costo = 0.0;
    printf("\n|--------------------------------|");
    printf("\n|-------- Cargando Datos --------|");
    printf("\n|--------------------------------|\n\n");
    loadDeliveries(dev);
    value = altaABB(abbTree, *dev, &costo);
    switch(value){
        case 0: printf("|----------------------------------------------|\n");
                printf("| Error al cargar elemento. No hay mas espacio |\n");
                printf("|----------------------------------------------|\n\n");
                break;
            
        case 1: printf("|-------------------------------------------------|\n");
                printf("| Error al cargar elemento. El elemento ya existe |\n");
                printf("|-------------------------------------------------|\n\n");
                break;

        case 2: printf("|----------------------------------------------|\n");
                printf("|           Carga exitosa de datos             |\n");
                printf("|----------------------------------------------|\n\n");
                if(c->abb.maxCostInsert < costo){
                    c->abb.maxCostInsert = costo;
                }
                c->abb.cantInsert += 1;
                c->abb.costAcumInsert += costo;
                c->abb.medCostInsert = (c->abb.costAcumInsert)/(c->abb.cantInsert);
                break;
    }

    do{
        printf("\n|---------------------------------|");
        printf("\n|  Ingrese 1 para volver al menu  |");
        printf("\n|---------------------------------|\n");
        scanf("%d", &enter);
   }while(enter != 1);
}


void preloadABB(abb *abbTree, StructCost *c){

    Deliveries dev;
    char code[CODE], name[NAME], nameSender[NAME], addres[NAME], dateS[DATE], dateR[DATE];
    long dni, dniS;
    int value, enter, i;
    float costo = 0.0;

    FILE *preload;
    preload = fopen("Envios.txt", "r");

    if(preload == NULL){
        printf("|----------------------------------------------|\n");
        printf("|       No se pudo acceder al archivo          |\n");
        printf("|----------------------------------------------|\n\n");
        exit(1);
    }
    else{
        while(!feof(preload)){
            fscanf(preload, " %[^\n]\n", code);
            for(i = 0; code[i] != '\0'; i++){
                code[i] = toupper(code[i]);
            }
            strcpy(&dev.code, code);
            
            fscanf(preload, "%ld\n", &dni);
            dev.doc = dni;
            
            fscanf(preload, " %[^\n]\n", nameSender);
            for(i = 0; nameSender[i] != '\0'; i++){
                nameSender[i] = toupper(nameSender[i]);
            }
            strcpy(&dev.nameSender, nameSender);
            
            fscanf(preload, " %[^\n]\n", addres);
            for(i = 0; addres[i] != '\0'; i++){
                addres[i] = toupper(addres[i]);
            }
            strcpy(&dev.address, addres);
            
            fscanf(preload, "%ld\n", &dniS);
            dev.docSender = dniS;

            fscanf(preload, " %[^\n]\n", name);
            for(i = 0; name[i] != '\0'; i++){
                name[i] = toupper(name[i]);
            }
            strcpy(&dev.name, name);
            
            fscanf(preload, " %[^\n]\n", dateS);
            for(i = 0; dateS[i] != '\0'; i++){
                dateS[i] = toupper(dateS[i]);
            }
            strcpy(&dev.dateSender, dateS);

            fscanf(preload, " %[^\n]\n", dateR);
            for(i = 0; dateR[i] != '\0'; i++){
                dateR[i] = toupper(dateR[i]);
            }
            strcpy(&dev.dateReceived, dateR);

            value = altaABB(abbTree, dev, &costo);

            switch(value){
                case 0: printf("|----------------------------------------------|\n");
                        printf("| Error al cargar elemento. No hay mas espacio |\n");
                        printf("|----------------------------------------------|\n\n");
                        exit(1);
                        break;
            
                case 1: printf("|-------------------------------------------------|\n");
                        printf("| Error al cargar elemento. El elemento ya existe |\n");
                        printf("|-------------------------------------------------|\n\n");
                        break;

                case 2: printf("|----------------------------------------------|\n");
                        printf("|            Carga exitosa de datos            |\n");
                        printf("|----------------------------------------------|\n\n");
                        if(c->abb.maxCostInsert < costo){
                            c->abb.maxCostInsert = costo;
                        }
                        c->abb.cantInsert += 1;
                        c->abb.costAcumInsert += costo;
                        c->abb.medCostInsert = (c->abb.costAcumInsert)/(c->abb.cantInsert);
                        break;
            }
        }
        printf("           Elementos cargados: %d\n", getCantABB(*abbTree));
        fclose(preload);
    }
    
    do{
        printf("\n|---------------------------------|");
        printf("\n|  Ingrese 1 para volver al menu  |");
        printf("\n|---------------------------------|\n");
        scanf("%d", &enter);
    }while(enter != 1);
}


void deleteABB(abb *abbTree, StructCost *c){

    Deliveries dev;
    char code[CODE];
    int lowValue, n, i, j = 0, enter;
    float costo = 0.0;
    int baja = 0;

    do{
        printf("|---------------------------------------------------|\n");
        printf("    ¿Cuantos envios quiere eliminar? Maximo %d\n", getCantABB(*abbTree));
        printf("|---------------------------------------------------|\n");
        scanf("%d", &n);
    }while(n < 1 || n > getCantABB(*abbTree));

    do{
        printf("\n|----------------------------------------------|");
        printf("\n|-------------- Eliminando Datos --------------|");
        printf("\n|----------------------------------------------|");
        printf("\n|   Ingrese el codigo del envio a eliminar:    |\n");
        scanf("%s", code);
        for(i = 0; code[i] != '\0'; i++){
            code[i] = toupper(code[i]);
        }
        strcpy(&dev.code, code);

        lowValue = bajaABB(abbTree, dev, &costo, baja);
        switch(lowValue){
            case 0: printf("|-----------------------------------------------------|\n");
                    printf("|   Error al borrar elemento. No existe en el arbol   |\n");
                    printf("|-----------------------------------------------------|\n\n");
                    j++;
                    break;

            case 1: printf("|-----------------------------------------------------|\n");
                    printf("|  Error al borrar elemento. Ha cancelado el proceso  |\n");
                    printf("|-----------------------------------------------------|\n\n");
                    j++;
                    break;

            case 2: printf("|----------------------------------------------|\n");
                    printf("|            Baja exitosa de datos             |\n");
                    printf("|----------------------------------------------|\n\n");
                    j++;
                    if(c->abb.maxCostSupress < costo){
                        c->abb.maxCostSupress = costo;
                    }
                    c->abb.cantSupress += 1;
                    c->abb.costAcumSupress += costo;
                    c->abb.medCostSupress = (c->abb.costAcumSupress)/(c->abb.cantSupress);
                    break;
            }
    }while(j < n);

    do{
        printf("\n|---------------------------------|");
        printf("\n|  Ingrese 1 para volver al menu  |");
        printf("\n|---------------------------------|\n");
        scanf("%d", &enter);
    }while(enter != 1);
}


void changeABB(abb *abbTree){

    Deliveries d;
    char code[CODE];
    int i, changeValue, enter;

    printf("|----------------------------------------------------|\n");
    printf("|  Ingrese el codigo del envio que desea modificar:  |\n");
    scanf("%s", code);
    for(i = 0; code[i] != '\0'; i++){
        code[i] = toupper(code[i]);
    }
    strcpy(&d.code, code);

    changeValue = modificarABB(abbTree, &d);
    if(changeValue == 1){
        printf("|-------------------------------------------------------|\n");
        printf("|   Se han realizado las modificaciones correctamente   |\n");
        printf("|-------------------------------------------------------|\n");
    }
    else{
        printf("|----------------------------------------------|\n");
        printf("|         Error al modificar los datos         |\n");
        printf("|----------------------------------------------|\n");
    }

    do{
        printf("\n|---------------------------------|");
        printf("\n|  Ingrese 1 para volver al menu  |");
        printf("\n|---------------------------------|\n");
        scanf("%d", &enter);
    }while(enter != 1);
}


void informationABB(abb abbTree, StructCost *c){
    Deliveries d;
    int i, evocationValue, enter;
    char code[CODE];
    float costo = 0.0;

    printf("\n|----------------------------------------------------------------|");
    printf("\n|   Ingrese el codigo del envio que desea obtener informacion:   |");
    printf("\n|----------------------------------------------------------------|\n");
    scanf("%s", code);
    for(i = 0; code[i] != '\0'; i++){
        code[i] = toupper(code[i]);
    }
    strcpy(&d.code, code);

    evocationValue = evocacionABB(abbTree, &d, &costo);
    if(evocationValue == 1){
        printf("\n|---------------------------------|");
        printf("\n    INFORMACION DEL ENVIO %s", code);
        printf("\n|---------------------------------|\n\n");
        printf("\n| Codigo: %s", d.code);
        printf("\n| Dni receptor: %ld", d.doc);
        printf("\n| Dni remitente: %ld", d.docSender);
        printf("\n| Nombre y apellido del receptor: %s", d.name);
        printf("\n| Nombre y apellido del remitente: %s", d.nameSender);
        printf("\n| Domicilio del envio: %s", d.address);
        printf("\n| Fecha de envio: %s", d.dateSender);
        printf("\n| Fecha de recepcion: %s", d.dateReceived);
        if(c->abb.maxCostSucEvo < costo){
            c->abb.maxCostSucEvo = costo;
        }
        c->abb.cantSucEvo += 1;
        c->abb.costAcumSucEvo += costo;
        c->abb.medCostSucEvo = (c->abb.costAcumSucEvo)/(c->abb.cantSucEvo);
    }
    else{
        printf("|--------------------------------------------------------------|\n");
        printf("    No se han encontrado coincidencias para el codigo %s\n", code);
        printf("|--------------------------------------------------------------|\n\n");
        if(c->abb.maxCostFailEvo < costo){
            c->abb.maxCostFailEvo = costo;
        }
        c->abb.cantFailEvo += 1;
        c->abb.costAcumFailEvo += costo;
        c->abb.medCostFailEvo = (c->abb.costAcumFailEvo)/(c->abb.cantFailEvo);
    }

    do{
        printf("\n|---------------------------------|");
        printf("\n|  Ingrese 1 para volver al menu  |");
        printf("\n|---------------------------------|\n");
        scanf("%d", &enter);
    }while(enter != 1);
}
