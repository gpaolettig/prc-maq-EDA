#ifndef ARTICULO_H_INCLUDED
#define ARTICULO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 250
#define COD 9
#define TIPO 21
#define MARC 31
#define DESC 101

typedef struct{
    char Codigo[COD];
    char TipoDeArticulo[TIPO];
    char Marca[MARC];
    char Descripcion[DESC];
    float PrecioUnitario; /* En dolares */
    int CantidadExistente;
}articulo;

void inicializar(articulo *a){
    strcpy((*a).Codigo,"XXXXXXXX");
    strcpy((*a).TipoDeArticulo,"Desconocido");
    strcpy((*a).Marca,"Desconocido");
    strcpy((*a).Descripcion,"Desconocido");
    (*a).PrecioUnitario=0.0;
    (*a).CantidadExistente=0;
}
                /*SETTERS*/

void set_codigo(articulo *a,char cod[]){
    strcpy((*a).Codigo,cod);
}
void set_tipoAr(articulo *a,char tipoar[]){
    strcpy((*a).TipoDeArticulo,tipoar);
}
void set_marca(articulo *a,char mar[]){
    strcpy((*a).Marca,mar);
}
void set_descripcion(articulo *a,char des[]){
    strcpy((*a).Descripcion,des);
}
void set_precio(articulo *a,float precio){
    (*a).PrecioUnitario=precio;
}
void set_CantidadExistente(articulo *a,int cant){
    (*a).CantidadExistente=cant;
}


#endif // ARTICULO_H_INCLUDED
