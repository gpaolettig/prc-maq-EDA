#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Articulo.h"
#include "LSO.h"
#include "LSOBT.h"
#include "RAL.h"
#include "RAC.h"
#include "ABB.h"

/* ANALIZANDO LOS COSTOS OBTENIDOS POR CADA ESTRUCTURA, LLEGAMOS A LA CONCLUSION DE QUE LA MEJOR ESTRUCTURA ES EL
 REBALSE ABIERTO CUADRATICO (RAC) YA QUE AL HACER ALTAS Y BAJAS NO NOS CUESTA NADA Y ADEMAS POSEEN EL ESFUERZO MEDIO DE
 LOCALIZACION EXITOSA Y NO EXITOSA MAS BAJO DE TODAS LAS ESTRUCTURAS  */

 /* EN EL ARBOL BINARIO DE BUSQUEDA CONSIDERAMOS COMO COSTO 1 A LA ACTUALIZACION DE PUNTEROS DEL ALTA (QUE ES LA DEL PADRE
 AL NUEVO NODO) Y QUE EL PONER LOS HI Y HD DERECHO DEL NUEVO NODO COMO NULL TIENE COSTO CERO.*/

//un vector de costo por estructura = un arreglo por estructura, la posicion 0 tendra la localizacion de exitosa, la posicion 1 para la localizacion que fracasa, la pos 2 para el alta, la 3 para la baja.
typedef struct{
    int acumulado;//me costo 3 luego me costo 5, 3+5 y asi (es la suma del vector)
    int max;
    int cant;//cantidad de elementos del vector
}componente;
void inicializarcomponente(componente c[]){
    int i;
    for(i=0;i<4;i++){
        c[i].acumulado=0;
        c[i].max=0;
        c[i].cant=0;
    }
}
void inicializarmedio(float c[]){
    int i;
    for(i=0;i<4;i++){
        c[i]=0.0;
    }
}
void mayus(char cod[]){
    int i=0;
    for (i=0;cod[i]!='\0';i++) {
      if(cod[i] >= 'a' && cod[i] <= 'z') {
         cod[i] = cod[i] -32;
      }
   }
}
void ing_datos(articulo *a){
    char icodigo[9],itipo[21],imarca[31],ides[101];
    float iprecio;
    int icantidad;
    printf("Ingrese los datos de el articulo a cargar\n");
    do{ //controlo que el el codigo tenga 8 caracteres
        printf("Ingrese el codigo: (8 caracteres) ");
        scanf("%s",&icodigo);
    }while(strlen(icodigo)!=8);
    //Pasar a mayusculas
    mayus(&icodigo);
    do{
        printf("Ingrese el tipo: ");
        fflush(stdin);
        scanf("%s",&itipo);
    }while(strlen(itipo)>20); //puede ingresar maximo 20

    do{
        printf("Ingrese la marca: ");
        fflush(stdin);
        scanf("%[^\n]",&imarca);
    }while(strlen(imarca)>30);//puede ingresar maximo 30
    do{
        printf("Ingrese la descripcion: ");
        fflush(stdin);
        scanf("%[^\n]",&ides);
    }while(strlen(ides)>100);//puede ingresar maximo 100
    do{
        printf("Ingrese el precio unitario: ");
        fflush(stdin);
        scanf("%f",&iprecio);
    }while(iprecio<=0);
    do{
    printf("Ingrese la cantidad existente: ");
    fflush(stdin);
    scanf("%d",&icantidad);
    }while(icantidad<=0);
    //agregandolo al articulo
    set_codigo(&(*a),icodigo);
    set_tipoAr(&(*a),itipo);
    set_marca(&(*a),imarca);
    set_descripcion(&(*a),ides);
    set_precio(&(*a),iprecio);
    set_CantidadExistente(&(*a),icantidad);

}

int main()
{
    //Variables, declaraciones, etc, para EL FUNCIONAMIENTO DE ADM ESTRUCTURAS CASE 1
    int opMenu,opLSOBS,opLSOBB,opRAL,opRAC,opABB,boolAlta,boolevo,boolbaja,boolmemo,boolperte,admcomp,opc;
    char codaux[9];
    float mRAL[4],mRAC[4],mABB[4],mLSOBS[4],mLSOBB[4];
    inicializarmedio(mRAL);inicializarmedio(mRAC);inicializarmedio(mABB);inicializarmedio(mLSOBB);inicializarmedio(mLSOBS);
    articulo aux,aux1;
    inicializar(&aux);
    //ABB
    ABB arbol;
    init_ABB(&arbol);
    //RAL
    RAL rebalse;
    init_RAL(&rebalse);
    //RAC
    RAC rac;
    init_RAC(&rac);
    //LSO BS
    ListaArticulos LSO;
    inicializar_lista(&LSO);
    //LSO BB
    ListaArticulosB LSOB;
    inicializar_listaB(&LSOB);
    //COSTOS
    int costo=0;
    componente c_RAL[4];
    componente c_RAC[4];
    componente c_ABB[4];
    componente c_LSOBS[4];
    componente c_LSOBB[4];




//****************************MENU PRINCIPAL***************************************
 int opcMP;
 do{
 printf("Bienvenido\n[1]ADMINISTRAR ESTRUCTURAS\n[2]COMPARAR ESTRUCTURAS\n[3]SALIR\nSeleccione una opcion...");
 scanf("%d",&opcMP);
 switch(opcMP){
     case 1:{
         system("CLS");
         system("color 06");
         do{
    printf("ADMINISTRACION DE ESTRUCUTRAS\nSeleccione la estructura con la que desea trabajar:\n[1] Rebalse Abierto Lineal (RAL)\n[2] Rebalse Abierto Cuadratico (RAC)\n[3] Arbol Binario de Busqueda (ABB)\n[4] LSO Busqueda Secuencial\n[5] LSO Busqueda Binaria\n[6]VOLVER AL MENU PRINCIPAL\n");
    scanf("%d",&opMenu);
    switch(opMenu){
        case 1:{
            system("CLS");
            system("color 0B"); //0c RAC
            printf("******************************\nUsted esta trabajando con RAL\n******************************\n");
            do{
                printf("Seleccione una opcion:\n[1]Ingresar nuevo articulo(Alta)\n[2]Eliminar articulo existente(Baja)\n[3]Consultar articulo\n[4]Mostrar articulos\n[5]Cargar articulos desde el archivo(Mem.previa)\n[6]Volver al menu de ADMINISTRACION\n[7]Limpiar pantalla\nOpcion: ");
                scanf("%d",&opRAL);
                switch(opRAL){
                case 1:{
                    //if (RAL.cantidad==MAX) {printf("Rebalse lleno");}
                        ing_datos(&aux);
                        boolAlta=AltaRAL(&rebalse,aux,&costo);
                        if(boolAlta==0){
                            printf("*******************\nEl articulo ya se encuentra en la estructura\n*******************\n");}
                        if(boolAlta==2){
                            printf("**************************************\nEl articulo no pudo darse de alta por falta de espacio\n**************************************\n");}
                        if(boolAlta==1){
                            printf("*******************\nAlta exitosa\n*******************\n");}break;}

                case 2:
                {
                    if(rebalse.cantidad==0)
                        printf("***************************************************************\nLa estructura esta vacia, no se puede dar de baja un articulo\n***************************************************************\n");
                    else{
                        do{//controlo que el el codigo tenga 8 caracteres
                            printf("Ingrese el codigo del articulo a dar de baja:\n");
                            scanf("%s",&codaux);
                        }while(strlen(codaux)!=8);
                        mayus(&codaux);
                        set_codigo(&aux,codaux);
                        boolbaja=BajaRAL(&rebalse,aux,1,&costo);
                        if(boolbaja==2)
                            printf("*******************\nLa baja ha sido cancelada\n*******************\n");
                        if(boolbaja==0)
                            printf("***************************************************************\nEl articulo a dar de baja no se encuentra en la estructura\n***************************************************************\n");
                        if(boolbaja==1)
                            printf("*******************\nBaja exitosa\n*******************\n");

                    }//fin else

                  }break;


                case 3: {
                    if(rebalse.cantidad==0)
                        printf("***************************************************************\nLa estructura esta vacia, no se puede consultar\n***************************************************************\n");
                    else
                    {
                    do{//controlo que el el codigo tenga 8 caracteres
                            printf("Ingrese el codigo del articulo a consultar:\n");
                            scanf("%s",&codaux);
                        }while(strlen(codaux)!=8);
                    mayus(&codaux);
                    boolevo=evocacionRAL(rebalse,codaux,&aux,&costo);
                    if(boolevo==1){
                        printf("\n*************************************\nLos datos del articulo consultado son:\n");
                        printf("Codigo:%s\n",aux.Codigo);
                        printf("Tipo:%s\n",aux.TipoDeArticulo);
                        printf("Marca:%s\n",aux.Marca);
                        printf("Descripcion:%s\n",aux.Descripcion);
                        printf("Precio unitario:%.2f\n",aux.PrecioUnitario);
                        printf("Cantidad existente:%d\n*************************************\n",aux.CantidadExistente);
                        }else
                            printf("******************************\nEl articulo no fue encontrado\n******************************\n");}}break;

                case 4: {
                        MostrarRAL(rebalse);}break;
                case 5:{
                    boolmemo=memorizacionPreviaRAL(&rebalse);
                    if(boolmemo==0){
                        printf("******************************\nEl archivo no se pudo abrir\n******************************\n");}
                    if(boolmemo==1){
                        printf("******************************\nMemorizacion previa exitosa\n******************************\n");}}break;

                case 7: system("CLS");break;
                }//fin switch RAL

            }while(opRAL!=6);
            system("CLS"); //vuelta a menu de administracion
            system("color 06");


        }break;//fin case 1 MENU administracion

        case 2:{
            system("CLS");
            system("color 0C");
            printf("******************************\nUsted esta trabajando con RAC\n******************************\n");
            do{
                printf("Seleccione una opcion:\n[1]Ingresar nuevo articulo(Alta)\n[2]Eliminar articulo existente(Baja)\n[3]Consultar articulo\n[4]Mostrar articulos\n[5]Cargar articulos desde el archivo(Mem.previa)\n[6]Volver al menu de ADMINISTRACION\n[7]Limpiar pantalla\nOpcion: ");
                scanf("%d",&opRAC);
                switch(opRAC){
                case 1: {
                    //if (RAC.cantidad==MAX) {printf("Rebalse lleno");}
                        ing_datos(&aux);
                        boolAlta=AltaRAC(&rac,aux,&costo);
                        if(boolAlta==0){
                            printf("***************************************************************\nEl articulo ya se encuentra en la estructura\n***************************************************************\n");}
                        if(boolAlta==2){
                            printf("***************************************************************\nEl articulo no pudo darse de alta por falta de espacio\n***************************************************************\n");}
                        if(boolAlta==1){
                            printf("*******************\nAlta exitosa\n*******************\n");}break;}
                case 2: {
                    if(rac.cantidad==0)
                        printf("***************************************************************\nLa estructura esta vacia, no se puede dar de baja un articulo\n***************************************************************\n");
                    else{
                        do{//controlo que el el codigo tenga 8 caracteres
                            printf("Ingrese el codigo del articulo a dar de baja:\n");
                            scanf("%s",&codaux);
                        }while(strlen(codaux)!=8);
                        mayus(&codaux);
                        set_codigo(&aux,codaux);
                        boolbaja=BajaRAC(&rac,aux,1,&costo);
                        if(boolbaja==2)
                            printf("*******************\nLa baja ha sido cancelada\n*******************\n");
                        if(boolbaja==0)
                            printf("***************************************************************\nEl articulo a dar de baja no se encuentra en la estructura\n***************************************************************\n");
                        if(boolbaja==1)
                            printf("*******************\nBaja exitosa\n*******************\n");

                    }//fin else

                  }break;
                case 3: {
                    if(rac.cantidad==0)
                        printf("***************************************************************\nLa estructura esta vacia, no se puede consultar\n***************************************************************\n");
                    else
                    {
                    do{//controlo que el el codigo tenga 8 caracteres
                            printf("Ingrese el codigo del articulo a consultar:\n");
                            scanf("%s",&codaux);
                        }while(strlen(codaux)!=8);
                    mayus(&codaux);
                    boolevo=evocacionRAC(rac,codaux,&aux,&costo);
                    if(boolevo==1){
                        printf("\n*************************************\nLos datos del articulo consultado son:\n");
                        printf("Codigo:%s\n",aux.Codigo);
                        printf("Tipo:%s\n",aux.TipoDeArticulo);
                        printf("Marca:%s\n",aux.Marca);
                        printf("Descripcion:%s\n",aux.Descripcion);
                        printf("Precio unitario:%.2f\n",aux.PrecioUnitario);
                        printf("Cantidad existente:%d\n*************************************\n",aux.CantidadExistente);
                        }else
                            printf("******************************\nEl articulo no fue encontrado\n******************************\n");}}break;
                case 4: {
                        MostrarRAC(rac);}break;
                case 5:{
                    boolmemo=memorizacionPreviaRAC(&rac);
                    if(boolmemo==0){
                        printf("******************************\nEl archivo no se pudo abrir\n******************************\n");}
                    if(boolmemo==1){
                        printf("******************************\nMemorizacion previa exitosa\n******************************\n");}}break;
                case 7: system("CLS");break;
                }//fin switch RAL

            }while(opRAC!=6);
            system("CLS"); //vuelta a menu principal
            system("color 06");


        }break;//fin case 2 MENU PRINCIPAL

        case 3: {
            system("CLS");
            system("color 0A");
            printf("******************************\nUsted esta trabajando con ABB\n******************************\n");
            do{
                printf("Seleccione una opcion:\n[1]Ingresar nuevo articulo(Alta)\n[2]Eliminar articulo existente(Baja)\n[3]Consultar articulo\n[4]Mostrar articulos\n[5]Cargar articulos desde el archivo(Mem.previa)\n[6]Volver al menu de ADMINISTRACION\n[7]Limpiar pantalla\nOpcion: ");
                scanf("%d",&opABB);
                switch(opABB){
                case 1:{
                    ing_datos(&aux);
                    boolAlta=AltaABB(&arbol,aux,&costo);
                    if(boolAlta == 0)
                        printf("***************************************************************\nEl articulo a  dar de alta ya se encuentra\n***************************************************************\n");
                    if(boolAlta == 2)
                        printf("*******************\nNo hay memoria\n*******************\n");
                    if(boolAlta == 1)
                        printf("*******************\nAlta exitosa\n*******************\n");break;}

                case 2:{
                    if(arbol.CantNodos==0)
                        printf("***************************************************************\nLa estructura esta vacia, no se puede dar de baja un articulo\n***************************************************************\n");
                    else{
                        do{//controlo que el el codigo tenga 8 caracteres
                            printf("Ingrese el codigo del articulo a dar de baja:\n");
                            scanf("%s",&codaux);
                        }while(strlen(codaux)!=8);
                        set_codigo(&aux,codaux);
                        boolbaja=bajaABB(&arbol,aux,&costo,1);
                        if(boolbaja==2)
                            printf("*******************\nLa baja ha sido cancelada\n*******************\n");
                        if(boolbaja==0)
                            printf("***************************************************************\nEl articulo a dar de baja no se encuentra en la estructura\n***************************************************************\n");
                        if(boolbaja==1)
                            printf("*******************\nBaja exitosa\n*******************\n");



                    }//fin else

                  }break;
                case 3:{
                    if(arbol.CantNodos==0)
                        printf("***************************************************************\nLa estructura esta vacia, no se puede consultar\n***************************************************************\n");
                    else
                    {
                    do{//controlo que el el codigo tenga 8 caracteres
                            printf("Ingrese el codigo del articulo a consultar:\n");
                            scanf("%s",&codaux);
                        }while(strlen(codaux)!=8);
                    boolevo=evocacionABB(&arbol,codaux,&aux,&costo);
                    if(boolevo==1){
                        printf("\n*************************************\nLos datos del articulo consultado son:\n");
                        printf("Codigo:%s\n",aux.Codigo);
                        printf("Tipo:%s\n",aux.TipoDeArticulo);
                        printf("Marca:%s\n",aux.Marca);
                        printf("Descripcion:%s\n",aux.Descripcion);
                        printf("Precio unitario:%.2f\n",aux.PrecioUnitario);
                        printf("Cantidad existente:%d\n*************************************\n",aux.CantidadExistente);
                        }else
                            printf("******************************\nEl articulo no fue encontrado\n******************************\n");}}break;
                case 4:if(arbol.CantNodos==0)
                           printf("******************************\nNo hay articulos para mostrar\n******************************\n");
                        else
                            MostrarABB(arbol.raiz,0);
                        break;
                case 5:{
                    boolmemo=memorizacionPreviaABB(&arbol);
                    if(boolmemo==0){
                        printf("******************************\nEl archivo no se pudo abrir\n******************************\n");}
                    if(boolmemo==1){
                        printf("******************************\nMemorizacion previa exitosa\n******************************\n");}}break;

                case 7: system("CLS");break;
                case 8: borrarArbol(&arbol.raiz);
                }//fin switch ABB

            }while(opABB!=6);
            system("CLS"); //vuelta a menu administracion
            system("color 06");


        }break;//fin case 3 MENU administracion


        case 4:{

        system("CLS");
        system("color 0B"); //color para la LSOBS
        printf("Usted esta trabajando con LSO-busqueda secuencial\n");
        //menu para LSO-BS
        do{
            printf("Seleccione una opcion:\n[1]Ingresar nuevo articulo(Alta)\n[2]Eliminar articulo existente(Baja)\n[3]Consultar articulo\n[4]Mostrar articulos\n[5]Cargar articulos desde el archivo(Mem.previa)\n[6]Volver al menu de Administracion\n[7]Limpiar pantalla\nOpcion: ");
            scanf("%d",&opLSOBS);
                switch(opLSOBS){
                case 1:
                    {
                    if(LSO.ult==LLENA-1) //si la estructura esta llena no puedo ingresar mas articulos
                        printf("------>No es posible cargar mas articulos, la estructura se encuentra llena\n");
                    else {//si no esta llena
                        ing_datos(&aux);
                        boolAlta=alta(&LSO,aux,&costo);
                        if(boolAlta==0) //aunque este en un if, lo carga, en si es una invocación
                            printf("\n------>El articulo con el codigo %s ya ha sido ingresado a la estructura \n",aux.Codigo);
                        if(boolAlta==2) //aunque este en un if, lo carga, en si es una invocación
                            printf("\n------>El articulo se cargo con exito(alta exitosa) \n");
                            }
                            }break;
                case 2:
                    {
                    if(LSO.ult==VACIA) //si la estructura esta vacia no hay nada que eliminar
                        printf("------>No es posible eliminar articulos, la estructura esta vacia\n");
                    else{
                        do{//controlo que el el codigo tenga 8 caracteres
                            printf("Por favor ingrese el codigo del articulo a dar de baja\n");
                            scanf("%s",&codaux);
                        }while(strlen(codaux)!=8);
                        set_codigo(&aux,codaux);
                        boolbaja=baja(&LSO,aux,&costo,1);
                        if(boolbaja==1)
                            printf("\n------>El articulo se elimino con exito(baja exitosa)\n");
                        if(boolbaja==2)
                            printf("\nUsted decidio no dar de baja el articulo\n");
                        if(boolbaja==0)
                            printf("\nEl articulo no existe en el deposito\n");
                        }
                        }break;
                case 3:{
                    if(LSO.ult==VACIA)
                        printf("La estructura esta vacia, no se puede consultar\n");
                    else
                    {


                    do{//controlo que el el codigo tenga 8 caracteres
                            printf("Ingrese el codigo del articulo a consultar:\n");
                            scanf("%s",&codaux);
                        }while(strlen(codaux)!=8);
                    boolevo=evocacionAsociativa(LSO,codaux,&aux,&costo);
                    if(boolevo==1){
                        printf("\n*************************************\nLos datos del articulo consultado son:\n");
                        printf("Codigo:%s\n",aux.Codigo);
                        printf("Tipo:%s\n",aux.TipoDeArticulo);
                        printf("Marca:%s\n",aux.Marca);
                        printf("Descripcion:%s\n",aux.Descripcion);
                        printf("Precio unitario:%.2f\n",aux.PrecioUnitario);
                        printf("Cantidad existente:%d\n*************************************\n",aux.CantidadExistente);
                        }else
                            printf("------>El articulo no fue encontrado\n");}}break;
                case 4:{
                    if(LSO.ult==VACIA)
                        printf("\n------>La estructura esta vacia\n");
                    else
                        mostrar(LSO);}break;
                case 5:{
                        if(LSO.ult==LLENA-1){
                            printf("Lista llena no podemos cargar desde el archivo\n");}
                        else{
                            if (memorizacionPreviaLSO(&LSO)==0){
                                printf("\nArchivo no encontrado\n");
                            } else{
                                printf("\n------>Memorizacion Previa Realizada correctamente\n"); system("PAUSE");}
                            }

                    }break;
                case 7: system("CLS");break;
            }//fin switch LSO-BS
         }while(opLSOBS!=6);
         system("CLS");
         system("color 06");

        }break;//fin case 4 del menu admin

        case 5:{

        system("CLS");
        system("color 0E"); //color para la LSOBS
        printf("Usted esta trabajando con LSO-busqueda binaria\n");
        do{
            printf("Seleccione una opcion:\n[1]Ingresar nuevo articulo(Alta)\n[2]Eliminar articulo existente(Baja)\n[3]Consultar articulo\n[4]Mostrar articulos\n[5]Cargar articulos desde el archivo(Mem.previa)\n[6]Volver al menu principal\n[7]Limpiar Pantalla\nOpcion: ");
            scanf("%d",&opLSOBB);
            switch(opLSOBB){
                case 1: {
                    if(LSOB.ult==LLENA-1) //si la estructura esta llena no puedo ingresar mas articulos
                        printf("------>No es posible cargar mas articulos, la estructura se encuentra llena\n");
                    else {//si no esta llena
                        ing_datos(&aux);
                        boolAlta=altaB(&LSOB,aux,&costo);
                        if(boolAlta==0) //aunque este en un if, lo carga, en si es una invocación
                            printf("\n------>El articulo con el codigo %s ya ha sido ingresado a la estructura \n",aux.Codigo);
                        if(boolAlta==2) //aunque este en un if, lo carga, en si es una invocación
                            printf("\n------>El articulo se cargo con exito(alta exitosa) \n");
                            }
                            }break;

                case 2:
                   {
                    if(LSOB.ult==VACIA) //si la estructura esta vacia no hay nada que eliminar
                        printf("------>No es posible eliminar articulos, la estructura esta vacia\n");
                    else{
                        do{//controlo que el el codigo tenga 8 caracteres
                            printf("Por favor ingrese el codigo del articulo a dar de baja\n");
                            scanf("%s",&codaux);
                        }while(strlen(codaux)!=8);
                        set_codigo(&aux,codaux);
                        boolbaja=bajaB(&LSOB,aux,&costo,1);
                        if(boolbaja==1)
                            printf("\n------>El articulo se elimino con exito(baja exitosa)\n");
                        if(boolbaja==2)
                            printf("\nUsted decidio no dar de baja el articulo\n");
                        if(boolbaja==0)
                            printf("\nEl articulo no existe en el deposito\n");
                        }
                        }break;

                case 3: {
                    if(LSOB.ult==VACIA)
                        printf("La estructura esta vacia, no se puede consultar\n");
                    else
                    {


                    do{//controlo que el el codigo tenga 8 caracteres
                            printf("Ingrese el codigo del articulo a consultar:\n");
                            scanf("%s",&codaux);
                        }while(strlen(codaux)!=8);
                    boolevo=evocacionAsociativaB(LSOB,codaux,&aux,&costo);
                    if(boolevo==1){
                        printf("\n*************************************\nLos datos del articulo consultado son:\n");
                        printf("Codigo:%s\n",aux.Codigo);
                        printf("Tipo:%s\n",aux.TipoDeArticulo);
                        printf("Marca:%s\n",aux.Marca);
                        printf("Descripcion:%s\n",aux.Descripcion);
                        printf("Precio unitario:%.2f\n",aux.PrecioUnitario);
                        printf("Cantidad existente:%d\n*************************************\n",aux.CantidadExistente);
                        }else
                            printf("------>El articulo no fue encontrado\n");}}break;
                case 4:{
                    if(LSOB.ult==VACIA)
                        printf("\n------>La estructura esta vacia\n");
                    else
                        mostrarB(LSOB);}break;

                case 5:{
                        if(LSOB.ult==LLENA-1){
                            printf("Lista llena no podemos cargar desde el archivo\n");}
                        else{
                            if (memorizacionPreviaLSOB(&LSOB)==0){
                                printf("\nArchivo no encontrado\n");
                            } else{
                                printf("\n------>Memorizacion Previa Realizada correctamente\n"); system("PAUSE");}
                            }

                    }break;
                case 7: system("CLS");break;
            }//fin switch LSO-BB



        }while(opLSOBB!=6);//fin do while
         system("CLS"); //vuelta a menu principal
         system("color 06");






        }//fin case 5 lso bb

    }//finswitch de admin de estrucutras
    }while(opMenu!=6);
    system("CLS");
    system("color 07");
     }break;//fin case 1 del menu principal


     case 2: {
        system("CLS");
        inicializar_lista(&LSO);
        inicializar_listaB(&LSOB);
        borrarArbol(&arbol);
        init_ABB(&arbol);
        init_RAL(&rebalse);
        init_RAC(&rac);
        inicializar(&aux1);
        inicializarcomponente(c_RAL);
        inicializarcomponente(c_RAC);
        inicializarcomponente(c_ABB);
        inicializarcomponente(c_LSOBS);
        inicializarcomponente(c_LSOBB);
        inicializarmedio(mRAL);
        inicializarmedio(mRAC);
        inicializarmedio(mABB);
        inicializarmedio(mLSOBB);
        inicializarmedio(mLSOBS);
        costo=0;
        FILE *fp;
        inicializar(&aux);
        if((fp = fopen("Operaciones.txt","r"))==NULL){
            printf("No se pudo abrir el archivo\n");
        }
        else{
            while(!(feof(fp))){
                fscanf(fp,"%d\n",&opc);
                fscanf(fp,"%s\n",aux.Codigo);
                switch(opc){
                    case 1:{
                        fscanf(fp,"%s\n",aux.TipoDeArticulo);
                        fscanf(fp,"%s\n",aux.Marca);
                        fscanf(fp,"%[^\n]s",aux.Descripcion);
                        fscanf(fp,"%f\n",&aux.PrecioUnitario);
                        fscanf(fp,"%d\n",&aux.CantidadExistente);
                        //COSTOS RAL
                        costo=0;
                        boolAlta=AltaRAL(&rebalse,aux,&costo);
                        if(boolAlta==1){
                            c_RAL[2].acumulado= c_RAL[2].acumulado + costo;
                            c_RAL[2].cant++;
                            if(costo > c_RAL[2].max)
                                c_RAL[2].max=costo;}
                        //COSTOS RAC
                       costo=0;
                       boolAlta=AltaRAC(&rac,aux,&costo);
                       if(boolAlta==1){
                            c_RAC[2].acumulado= c_RAC[2].acumulado + costo;
                            c_RAC[2].cant++;
                            if(costo > c_RAC[2].max)
                                c_RAC[2].max=costo;}
                        //COSTOS ABB
                        costo=0;
                        boolAlta=AltaABB(&arbol,aux,&costo);
                        if(boolAlta==1){
                            c_ABB[2].acumulado=c_ABB[2].acumulado + costo;
                            c_ABB[2].cant++;
                            if(costo > c_ABB[2].max)
                                c_ABB[2].max=costo;}
                        //COSTOS LSO BS
                        costo=0;
                        boolAlta=alta(&LSO,aux,&costo);
                        if(boolAlta==2){
                            c_LSOBS[2].acumulado=c_LSOBS[2].acumulado + costo;
                            c_LSOBS[2].cant++;
                            if(costo > c_LSOBS[2].max)
                                c_LSOBS[2].max=costo;}
                        //COSTOS LSO BB
                        costo=0;
                        boolAlta=altaB(&LSOB,aux,&costo);
                        if(boolAlta==2){
                            c_LSOBB[2].acumulado=c_LSOBB[2].acumulado + costo;
                            c_LSOBB[2].cant++;
                            if(costo > c_LSOBB[2].max)
                                c_LSOBB[2].max=costo;}
                    }break;
                    case 2:{
                        fscanf(fp,"%s\n",aux.TipoDeArticulo);
                        fscanf(fp,"%s\n",aux.Marca);
                        fscanf(fp,"%[^\n]s",aux.Descripcion);
                        fscanf(fp,"%f\n",&aux.PrecioUnitario);
                        fscanf(fp,"%d\n",&aux.CantidadExistente);
                        //COSTOS RAL
                        costo=0;
                        boolbaja=BajaRAL(&rebalse,aux,2,&costo);
                        if(boolbaja==1){
                            c_RAL[3].acumulado= c_RAL[3].acumulado + costo;
                            c_RAL[3].cant++;
                            if(costo > c_RAL[3].max)
                                c_RAL[3].max=costo;}
                        //COSTOS RAC
                        costo=0;
                        boolbaja=BajaRAC(&rac,aux,2,&costo);
                        if(boolbaja==1){
                            c_RAC[3].acumulado= c_RAC[3].acumulado + costo;
                            c_RAC[3].cant++;
                            if(costo > c_RAC[3].max)
                                c_RAC[3].max=costo;}
                        //COSTOS ABB
                        costo=0;
                        boolbaja=bajaABB(&arbol,aux,&costo,2);
                        if(boolbaja==1){
                            c_ABB[3].acumulado=c_ABB[3].acumulado + costo;
                            c_ABB[3].cant++;
                            if(costo > c_ABB[3].max)
                                c_ABB[3].max=costo;}
                        //COSTOS LSO BS
                        costo=0;
                        boolbaja=baja(&LSO,aux,&costo,2);
                        if(boolbaja==1){
                            c_LSOBS[3].acumulado=c_LSOBS[3].acumulado + costo;
                            c_LSOBS[3].cant++;
                            if(costo > c_LSOBS[3].max)
                                c_LSOBS[3].max=costo;}
                        //COSTOS LSO BT
                        costo=0;
                        boolbaja=bajaB(&LSOB,aux,&costo,2);
                        if(boolbaja==1){
                            c_LSOBB[3].acumulado=c_LSOBB[3].acumulado + costo;
                            c_LSOBB[3].cant++;
                            if(costo > c_LSOBB[3].max)
                                c_LSOBB[3].max=costo;}
                    }break;
                    case 3:{
                        //costos evocacion RAL
                        costo=0;
                        boolevo=evocacionRAL(rebalse,aux.Codigo,&aux1,&costo);
                        if(boolevo==1){//LOCALIZACION EXITOSA
                            c_RAL[0].acumulado=c_RAL[0].acumulado+costo;
                            c_RAL[0].cant++;
                            if(costo>c_RAL[0].max)
                                c_RAL[0].max=costo;}
                        if(boolevo==0){ //localizacion que fracasa!
                            c_RAL[1].acumulado=c_RAL[1].acumulado+costo;
                            c_RAL[1].cant++;
                            if(costo>c_RAL[1].max)
                                c_RAL[1].max=costo;}
                        costo=0;
                        boolevo=evocacionRAC(rac,aux.Codigo,&aux1,&costo);
                        if(boolevo==1){//LOCALIZACION EXITOSA
                            c_RAC[0].acumulado=c_RAC[0].acumulado+costo;
                            c_RAC[0].cant++;
                            if(costo>c_RAC[0].max)
                                c_RAC[0].max=costo;}
                        if(boolevo==0){ //localizacion que fracasa!
                            c_RAC[1].acumulado=c_RAC[1].acumulado+costo;
                            c_RAC[1].cant++;
                            if(costo>c_RAC[1].max)
                                c_RAC[1].max=costo;}
                        costo=0;
                        boolevo=evocacionABB(&arbol,aux.Codigo,&aux1,&costo);
                        if(boolevo==1){//LOCALIZACION EXITOSA
                            c_ABB[0].acumulado=c_ABB[0].acumulado+costo;
                            c_ABB[0].cant++;
                            if(costo>c_ABB[0].max)
                                c_ABB[0].max=costo;}
                        if(boolevo==0){ //localizacion que fracasa!
                                c_ABB[1].acumulado=c_ABB[1].acumulado+costo;
                            c_ABB[1].cant++;
                            if(costo>c_ABB[1].max)
                                c_ABB[1].max=costo;}
                        costo=0;
                        boolevo=evocacionAsociativa(LSO,aux.Codigo,&aux1,&costo);
                        if(boolevo==1){//LOCALIZACION EXITOSA
                            c_LSOBS[0].acumulado=c_LSOBS[0].acumulado+costo;
                            c_LSOBS[0].cant++;
                            if(costo>c_LSOBS[0].max)
                                c_LSOBS[0].max=costo;}
                        if(boolevo==0){ //localizacion que fracasa!
                            c_LSOBS[1].acumulado=c_LSOBS[1].acumulado+costo;
                            c_LSOBS[1].cant++;
                            if(costo>c_LSOBS[1].max)
                                c_LSOBS[1].max=costo;}
                        costo=0;
                        boolevo=evocacionAsociativaB(LSOB,aux.Codigo,&aux1,&costo);
                        if(boolevo==1){//LOCALIZACION EXITOSA
                            c_LSOBB[0].acumulado=c_LSOBB[0].acumulado+costo;
                            c_LSOBB[0].cant++;
                            if(costo>c_LSOBB[0].max)
                                c_LSOBB[0].max=costo;}
                        if(boolevo==0){ //localizacion que fracasa!
                            c_LSOBB[1].acumulado=c_LSOBB[1].acumulado+costo;
                            c_LSOBB[1].cant++;
                            if(costo>c_LSOBB[1].max)
                                c_LSOBB[1].max=costo;}
                    }break;
                }
            }
            fclose(fp);
            if (c_LSOBS[0].cant!=0){mLSOBS[0]=c_LSOBS[0].acumulado*(1.0/c_LSOBS[0].cant);}
            if (c_LSOBS[1].cant!=0){mLSOBS[1]=c_LSOBS[1].acumulado*(1.0/c_LSOBS[1].cant);}
            if (c_LSOBS[2].cant!=0){mLSOBS[2]=c_LSOBS[2].acumulado*(1.0/c_LSOBS[2].cant);}
            if (c_LSOBS[3].cant!=0){mLSOBS[3]=c_LSOBS[3].acumulado*(1.0/c_LSOBS[3].cant);}
            if (c_LSOBB[0].cant!=0){mLSOBB[0]=c_LSOBB[0].acumulado*(1.0/c_LSOBB[0].cant);}
            if (c_LSOBB[1].cant!=0){mLSOBB[1]=c_LSOBB[1].acumulado*(1.0/c_LSOBB[1].cant);}
            if (c_LSOBB[2].cant!=0){mLSOBB[2]=c_LSOBB[2].acumulado*(1.0/c_LSOBB[2].cant);}
            if (c_LSOBB[3].cant!=0){mLSOBB[3]=c_LSOBB[3].acumulado*(1.0/c_LSOBB[3].cant);}
            if (c_RAL[0].cant!=0){mRAL[0]=c_RAL[0].acumulado*(1.0/c_RAL[0].cant);}
            if (c_RAL[1].cant!=0){mRAL[1]=c_RAL[1].acumulado*(1.0/c_RAL[1].cant);}
            if (c_RAL[2].cant!=0){mRAL[2]=c_RAL[2].acumulado*(1.0/c_RAL[2].cant);}
            if (c_RAL[3].cant!=0){mRAL[3]=c_RAL[3].acumulado*(1.0/c_RAL[3].cant);}
            if (c_RAC[0].cant!=0){mRAC[0]=c_RAC[0].acumulado*(1.0/c_RAC[0].cant);}
            if (c_RAC[1].cant!=0){mRAC[1]=c_RAC[1].acumulado*(1.0/c_RAC[1].cant);}
            if (c_RAC[2].cant!=0){mRAC[2]=c_RAC[2].acumulado*(1.0/c_RAC[2].cant);}
            if (c_RAC[3].cant!=0){mRAC[3]=c_RAC[3].acumulado*(1.0/c_RAC[3].cant);}
            if (c_ABB[0].cant!=0){mABB[0]=c_ABB[0].acumulado*(1.0/c_ABB[0].cant);}
            if (c_ABB[1].cant!=0){mABB[1]=c_ABB[1].acumulado*(1.0/c_ABB[1].cant);}
            if (c_ABB[2].cant!=0){mABB[2]=c_ABB[2].acumulado*(1.0/c_ABB[2].cant);}
            if (c_ABB[3].cant!=0){mABB[3]=c_ABB[3].acumulado*(1.0/c_ABB[3].cant);}
            printf("\t COMPARACION DE ESTRUCTURAS\n\n"
                   "COSTOS\t\tLSO\tLSOBT\tRAL\tRAC\tABB\n"
                   "_____________________________________________________\n");
            printf("MAX.ALTA\t%d\t%d\t%d\t%d\t%d\n",c_LSOBS[2].max,c_LSOBB[2].max,c_RAL[2].max,c_RAC[2].max,c_ABB[2].max);
            printf("MED.ALTA\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n",mLSOBS[2],mLSOBB[2],mRAL[2],mRAC[2],mABB[2]);
            printf("MAX.BAJA\t%d\t%d\t%d\t%d\t%d\n",c_LSOBS[3].max,c_LSOBB[3].max,c_RAL[3].max,c_RAC[3].max,c_ABB[3].max);
            printf("MED.BAJA\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n",mLSOBS[3],mLSOBB[3],mRAL[3],mRAC[3],mABB[3]);
            printf("MAX.EVOEX\t%d\t%d\t%d\t%d\t%d\n",c_LSOBS[0].max,c_LSOBB[0].max,c_RAL[0].max,c_RAC[0].max,c_ABB[0].max);
            printf("MED.EVOEX\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n",mLSOBS[0],mLSOBB[0],mRAL[0],mRAC[0],mABB[0]);
            printf("MAX.EVONOEX\t%d\t%d\t%d\t%d\t%d\n",c_LSOBS[1].max,c_LSOBB[1].max,c_RAL[1].max,c_RAC[1].max,c_ABB[1].max);
            printf("MED.EVONOEX\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n\n",mLSOBS[1],mLSOBB[1],mRAL[1],mRAC[1],mABB[1]);
            system("PAUSE");
            system("cls");
        }
    }break;

 }//fin switch del menu principal
 }while(opcMP!=3);
 printf("Practico maquina nro3 - Software brothers\n");
return 0;
}
