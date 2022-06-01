#ifndef RAC_H_INCLUDED
#define RAC_H_INCLUDED
#define MAX 307 // MAX ES M QUE ES IGUAL A TECHO DE (250/0.83)=301,2 y NOS VAMOS AL PRIMO MAS CERCANO (MAYOR) QUE ES 307
#include <stdlib.h>
#include <string.h>
#include "articulo.h"

typedef struct{
    char estado; //*(virgen) +(libre) -(ocupada)
    articulo arti;
}celdaRAC;

typedef struct{
    celdaRAC arr[MAX];
    int cantidad;
}RAC;

int hashing1(char *x , int M){
    int longitud, i;
    int contador=0;
    longitud=strlen(x);
    for( i=0;i<longitud;i++)
        contador+=((int)x[i])*(i+1);
    return (contador%M);
}

void init_RAC(RAC *rebalse){
    int i;
    for(i=0;i<MAX;i++){
        (*rebalse).arr[i].estado='*';
    }
    (*rebalse).cantidad=0;
}

int LocalizarRAC(RAC rebalse,char codigo[],int *pos,int *costo){
    int i=hashing1(codigo,MAX);
    int j=0;
    int k=0;
    int libre=0;
    while(j!=MAX && (rebalse.arr[i].estado!='*')){
        *costo=*costo+1;
        if((strcmpi(codigo,rebalse.arr[i].arti.Codigo)==0) && (rebalse.arr[i].estado=='-')){
                *pos=i;
                return 1; //Localizacion exitosa (1)
        }else{
            if((rebalse.arr[i].estado=='+')&& (libre==0)){
                libre++;
                *pos=i;
            }
            j++;
            k++;
            i=(i+k)%MAX;
        }//fin else
    }//fin while
    if(rebalse.arr[i].estado=='*'){
        (*costo) =(*costo)+1;}
    if(libre==1){
        return 0;} // Encontre una libre y retorno 0, pos esta en el i de la libre (porque lo asigno el if (1)
    if(j==MAX){
        return 3;} // No hay espacio, estan todas las celdas llenas
    if(libre==0){
        *pos=i;
        return 0;} // No encontre libre y sali del while porque llegue a un *
}//fin funcion

int AltaRAC(RAC *rebalse, articulo ar,int *costo){
    int pos,exitoloc,b;
    if ((*rebalse).cantidad==MAX){
        return 2;}
    exitoloc=LocalizarRAC(*rebalse,ar.Codigo,&pos,&b);
    if(exitoloc==1)
        return 0; //fracaso el alta ya que la localiz es exitosa
    if(exitoloc==3)
        return 2; //fracaso el alta por falta de espacio
    if(exitoloc==0){
        (*rebalse).arr[pos].arti=ar;
        (*rebalse).arr[pos].estado='-';
        (*rebalse).cantidad++;
        *costo=0;
        return 1; //alta exitosa
    }

}
void MostrarRAC(RAC rebalse){
int i;
for(i=0;i<MAX;i++){
    if (i%20==0 && i!=0)
        system("PAUSE");
    if(rebalse.arr[i].estado=='-'){
        //muestro los datos
        printf("\n************Articulo con clave****************** %d\n",i);
        printf("\nCodigo:%s",rebalse.arr[i].arti.Codigo);
        printf("\nTipo de articulo:%s",rebalse.arr[i].arti.TipoDeArticulo);
        printf("\nMarca:%s",rebalse.arr[i].arti.Marca);
        printf("\nDescripcion:%s",rebalse.arr[i].arti.Descripcion);
        printf("\nPrecio unitario %.2f",rebalse.arr[i].arti.PrecioUnitario);
        printf("\nCantidad Existente:%d",rebalse.arr[i].arti.CantidadExistente);
        printf("\n********************************\n");
        }
    if(rebalse.arr[i].estado=='*'){
        printf("\n---------------------------------\nLa celda con clave %d es virgen(*)\n---------------------------------\n",i);}

    if(rebalse.arr[i].estado=='+'){
        printf("\n---------------------------------\nLa celda con clave %d es libre(+)\n---------------------------------\n",i);}
    }//fin for
}//fin funcion

int BajaRAC(RAC *rebalse,articulo auxi,int admcomp,int *costo){
    int pos, opc,exito,boolmenu,b;
    exito=LocalizarRAC(*rebalse,auxi.Codigo,&pos,&b);
    if(exito==0){
        return 0;
    }else{//si la localizacion tiene exito
        if(exito==3){
            return 0; // Aclaramos que sale porque la lista esta llena y tampoco lo encontro??
        }
        else{
            if(admcomp==2){
                boolmenu=((strcmpi((*rebalse).arr[pos].arti.TipoDeArticulo,auxi.TipoDeArticulo)==0)&&(strcmpi((*rebalse).arr[pos].arti.Marca,auxi.Marca)==0)&&(strcmpi((*rebalse).arr[pos].arti.Descripcion,auxi.Descripcion)==0)&&((*rebalse).arr[pos].arti.PrecioUnitario==auxi.PrecioUnitario)&&((*rebalse).arr[pos].arti.CantidadExistente==auxi.CantidadExistente));
            if(boolmenu==0)
                return 3;} //aviso que no coinciden campos en comparar estructuras
            if(admcomp==1){
            //muestro datos
            printf("\nCodigo:%s",(*rebalse).arr[pos].arti.Codigo);
            printf("\nTipo de articulo:%s",(*rebalse).arr[pos].arti.TipoDeArticulo);
            printf("\nMarca:%s",(*rebalse).arr[pos].arti.Marca);
            printf("\nDescripcion:%s",(*rebalse).arr[pos].arti.Descripcion);
            printf("\nPrecio unitario %.2f",(*rebalse).arr[pos].arti.PrecioUnitario);
            printf("\nCantidad Existente:%d",(*rebalse).arr[pos].arti.CantidadExistente);
            printf("\n********************************\n");
            do{
                printf("\nConfirma la baja del elemento?\n (1): Si (2) No\n");
                scanf("%d",&opc);
            }while(opc!=1 && opc != 2);
            getchar();
            if(opc==2)
                return 2; //la baja ha sido cancelada
            }//fin if admcomp==1

            (*rebalse).arr[pos].estado='+'; //celda libre
            (*rebalse).cantidad--;
            *costo=0;
            return 1; //baja exitosa

        }
    }

}
int evocacionRAC(RAC rebalse,char codigo[],articulo *aux,int *costo){
    int pos,punt=0;
    if((LocalizarRAC(rebalse,codigo,&pos,&punt))==1){
        *aux=rebalse.arr[pos].arti;
        *costo=punt;
        return 1;
    }else{
        *costo=punt;
        return 0;}
}

int memorizacionPreviaRAC(RAC *rebalse){
    FILE *fp; int b;
    articulo aux;
    inicializar(&aux);
    if((fp = fopen("Articulos.txt","r"))==NULL){
        return 0;
    }
    else{
        while(!(feof(fp)) && !((*rebalse).cantidad==MAX)){
                fscanf(fp,"%s\n",aux.Codigo);
                fscanf(fp,"%s\n",aux.TipoDeArticulo);
                fscanf(fp,"%s\n",aux.Marca);
                fscanf(fp,"%[^\n]s",aux.Descripcion);
                fscanf(fp,"%f\n",&aux.PrecioUnitario);
                fscanf(fp,"%d\n",&aux.CantidadExistente);
                AltaRAC(&(*rebalse),aux,&b);
                }//fin while
                fclose(fp);
                return 1;
    }
}



#endif // RAC_H_INCLUDED
