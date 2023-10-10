//Grupo 7  Sarubbi Franco - Orozco Mateo

/*
    Conclusion:
    |-------------------------------------------|   |-------------------------------------------|   |-------------------------------------------|    
    |         Lista Secuencial Ordenada         |   |    Lista Secuencial Ordenada Biseccion    |   |         Arbol de Busqueda Binaria         |
    |-------------------------------------------|   |-------------------------------------------|   |-------------------------------------------|
    |   Funcion   |  Costo Max  |  Costo Medio  |   |   Funcion   |  Costo Max  |  Costo Medio  |   |   Funcion   |  Costo Max  |  Costo Medio  |
    |-------------------------------------------|   |-------------------------------------------|   |-------------------------------------------|
    |    Alta     |    58.00    |     15.07     |   |    Alta     |    58.00    |     15.07     |   |    Alta     |     0.50    |     0.50      |
    |-------------------------------------------|   |-------------------------------------------|   |-------------------------------------------|
    |    Baja     |    47.00    |     16.77     |   |    Baja     |    47.00    |     16.77     |   |    Baja     |     1.50    |     0.98      |
    |-------------------------------------------|   |-------------------------------------------|   |-------------------------------------------|
    |  Evoc. Exit |    60.00    |     23.97     |   |  Evoc. Exit |     6.00    |      5.57     |   |  Evoc. Exit |     12.00   |     5.71      |
    |-------------------------------------------|   |-------------------------------------------|   |-------------------------------------------|
    |  Evoc. Frac |    42.00    |     16.70     |   |  Evoc. Frac |     6.00    |      4.87     |   |  Evoc. Frac |     10.00   |     5.27      |
    |-------------------------------------------|   |-------------------------------------------|   |-------------------------------------------|
*/


#include "lso.h"
#include "lsobb.h"
#include "abb.h"


//Funciones menu principal
void mostrarEstructuras(abb , list , listBB , int , int );   //Mostrar las 3 estructuras
int lecturaOperaciones(StructCost *, list *, listBB *, abb *, int *, int *);  //Funcion para leer desde el archivo


//Funciones internas
void loadDeliveries(Deliveries *);   //Funcion auxiliar de carga de datos
void resetAll(list *, listBB *, abb *, int *, int *);   //Funcion para resetear todas las estructuras


int main(){

    abb abbTree;
    list lso;
    listBB lsobb;
    Deliveries dev;
    StructCost c;
    int cant = 0, cantBB = 0, lect, menu;

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
            printf("\n|         1. Comparar estructuras           |");
            printf("\n|         2. Mostrar estructuras            |");
            printf("\n|         3. Mostrar costos cargados        |");
            printf("\n|         4. Salir del sistema              |");
            printf("\n|===========================================|\n\n");
            scanf("%d", &menu);
        }while(menu < 1 || menu > 4);
    
        switch(menu){
            //Comparar estructuras
            case 1: resetAll(&lso, &lsobb, &abbTree, &cant, &cantBB);
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

            //Mostrar estructuras
            case 2: mostrarEstructuras(abbTree, lso, lsobb, cant, cantBB);
                    break;

            //Mostrar los costos
            case 3: mostrarCostos(c);
                    break;
        }
        
    }while(menu != 4);

 
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
    printf("\n| Evoc. Exitosa |   %.2f                 %.2f              ", c.lsobb.maxCostSucEvo, c.lsobb.medCostSucEvo);
    printf("\n|------------------------------------------------------");
    printf("\n| Evoc. Fracaso |   %.2f                 %.2f              ", c.lsobb.maxCostFailEvo, c.lsobb.medCostFailEvo);
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
    printf("\n| Evoc. Exitosa |   %.2f               %.2f              ", c.abb.maxCostSucEvo, c.abb.medCostSucEvo);
    printf("\n|------------------------------------------------------");
    printf("\n| Evoc. Fracaso |   %.2f               %.2f              ", c.abb.maxCostFailEvo, c.abb.medCostFailEvo);
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
    init(lso);
    initLSOBB(lsobb);
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
                    case 1: if(*cant < SIZE){
                                costo = 0.0;
                                if(altaLSO(lso, dev, &costo) == 2){
                                    *cant = *cant + 1;
                                    if(c->lso.maxCostInsert < costo){
                                        c->lso.maxCostInsert = costo;
                                    }
                                    c->lso.cantInsert += 1;
                                    c->lso.costAcumInsert += costo;
                                    c->lso.medCostInsert = (c->lso.costAcumInsert)/(c->lso.cantInsert);
                                }
                            }
                            if(*cantBB < SIZE){
                                costo = 0.0;
                                if(altaLSOBB(lsobb, dev, &costo) == 2){
                                    *cantBB = *cantBB + 1;
                                    if(c->lsobb.maxCostInsert < costo){
                                        c->lsobb.maxCostInsert = costo;
                                    }
                                    c->lsobb.cantInsert += 1;
                                    c->lsobb.costAcumInsert += costo;
                                    c->lsobb.medCostInsert = (c->lsobb.costAcumInsert)/(c->lsobb.cantInsert);
                                }
                            }        
                            costo = 0.0;                    
                            if(altaABB(abbTree, dev, &costo) == 2){
                                if(c->abb.maxCostInsert < costo){
                                    c->abb.maxCostInsert = costo;
                                }
                                c->abb.cantInsert += 1;
                                c->abb.costAcumInsert += costo;
                                c->abb.medCostInsert = (c->abb.costAcumInsert)/(c->abb.cantInsert);
                            }
                            break;


                    case 2: if(*cant > 0){
                                costo = 0.0;
                                if(bajaLSO(lso, dev, &costo) == 2){
                                    *cant = *cant - 1;
                                    if(c->lso.maxCostSupress < costo){
                                        c->lso.maxCostSupress = costo;
                                    }
                                    c->lso.cantSupress += 1;
                                    c->lso.costAcumSupress += costo;
                                    c->lso.medCostSupress = (c->lso.costAcumSupress)/(c->lso.cantSupress);
                                }
                            }
                            if(*cantBB > 0){
                                costo = 0.0;
                                if(bajaLSOBB(lsobb, dev, &costo) == 2){
                                    *cantBB = *cantBB - 1;
                                    if(c->lsobb.maxCostSupress < costo){
                                        c->lsobb.maxCostSupress = costo;
                                    }
                                    c->lsobb.cantSupress += 1;
                                    c->lsobb.costAcumSupress += costo;
                                    c->lsobb.medCostSupress = (c->lsobb.costAcumSupress)/(c->lsobb.cantSupress);
                                }
                            }
                            if(abbTree->root != NULL){
                                costo = 0.0;
                                if(bajaABB(abbTree, dev, &costo) == 2){
                                    if(c->abb.maxCostSupress < costo){
                                        c->abb.maxCostSupress = costo;
                                    }
                                    c->abb.cantSupress += 1;
                                    c->abb.costAcumSupress += costo;
                                    c->abb.medCostSupress = (c->abb.costAcumSupress)/(c->abb.cantSupress);
                                }
                            }
                            break;
                }
            }
            else{
                if(codeOperator == 3){
                    costo = 0.0;
                    value = evocacionLSO(*lso, &dev, &costo);
                    switch(value){
                        case 1: if(c->lso.maxCostSucEvo < costo){
                                    c->lso.maxCostSucEvo = costo;
                                }
                                c->lso.cantSucEvo += 1;
                                c->lso.costAcumSucEvo += costo;
                                c->lso.medCostSucEvo = (c->lso.costAcumSucEvo)/(c->lso.cantSucEvo);
                                break;

                        case 0: if(c->lso.maxCostFailEvo < costo){
                                    c->lso.maxCostFailEvo = costo;
                                }
                                c->lso.cantFailEvo += 1;
                                c->lso.costAcumFailEvo += costo;
                                c->lso.medCostFailEvo = (c->lso.costAcumFailEvo)/(c->lso.cantFailEvo);
                                break;
                    }
                    costo = 0.0;
                    value = evocacionLSOBB(*lsobb, &dev, &costo);
                    switch(value){
                        case 1: if(c->lsobb.maxCostSucEvo < costo){
                                    c->lsobb.maxCostSucEvo = costo;
                                }
                                c->lsobb.cantSucEvo += 1;
                                c->lsobb.costAcumSucEvo += costo;
                                c->lsobb.medCostSucEvo = (c->lsobb.costAcumSucEvo)/(c->lsobb.cantSucEvo);
                                break;

                        case 0: if(c->lsobb.maxCostFailEvo < costo){
                                    c->lsobb.maxCostFailEvo = costo;
                                }
                                c->lsobb.cantFailEvo += 1;
                                c->lsobb.costAcumFailEvo += costo;
                                c->lsobb.medCostFailEvo = (c->lsobb.costAcumFailEvo)/(c->lsobb.cantFailEvo);
                                break;
                    }
                    costo = 0.0;
                    value = evocacionABB(*abbTree, &dev, &costo);
                    switch(value){
                        case 1: if(c->abb.maxCostSucEvo < costo){
                                    c->abb.maxCostSucEvo = costo;
                                }
                                c->abb.cantSucEvo += 1;
                                c->abb.costAcumSucEvo += costo;
                                c->abb.medCostSucEvo = (c->abb.costAcumSucEvo)/(c->abb.cantSucEvo);
                                break;

                        case 0: if(c->abb.maxCostFailEvo < costo){
                                    c->abb.maxCostFailEvo = costo;
                                }
                                c->abb.cantFailEvo += 1;
                                c->abb.costAcumFailEvo += costo;
                                c->abb.medCostFailEvo = (c->abb.costAcumFailEvo)/(c->abb.cantFailEvo);
                                break;
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