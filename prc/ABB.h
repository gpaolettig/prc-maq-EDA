#ifndef ABB_H_INCLUDED
#define ABB_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "articulo.h"
#define LLENA 250
#define VACIA -1

typedef struct nodo{
   articulo elem;
   struct nodo *hi;
   struct nodo *hd;
}nodo;

typedef struct {
    nodo *raiz;
    int CantNodos;
}ABB;

void init_ABB(ABB *a){
    (*a).raiz=NULL;
    (*a).CantNodos=0;
}

void borrarArbol(nodo **raiz){
    if (*raiz!=NULL){
        borrarArbol(&(*raiz)->hi);
        borrarArbol(&(*raiz)->hd);
        free(*raiz);
        *raiz=NULL;
    }
}

int LocalizarABB(ABB *a,char codigo[],nodo **p, nodo **ant,int *costo){ //acceder a nodo *p |||||| direccion p
    *p=(*a).raiz; //al cursor le doy la raiz p=a.raiz por valor???1
    *ant=*p;
    while((*p!=NULL)&&(strcmpi((**p).elem.Codigo,codigo)!=0)){ //mientras el cursor no sea nulo, y lo que apunta el cur no sea lo que busco
        *costo=*costo+1;
        *ant=*p;
        if(strcmpi((**p).elem.Codigo,codigo)<0){ //si lo que busco es mayor que lo que apunto
                *p=(**p).hd;
        }else{
                *p=(**p).hi;}
    }
    if(*p!=NULL){
    (*costo) =(*costo)+1;}
    return *p!=NULL;

}

int AltaABB(ABB *a, articulo arti,int *costo){ //caso 2 no hay memoria
    nodo *p, *ant; int b;
    if(LocalizarABB(&(*a),arti.Codigo,&p,&ant,&b))
        return 0; //LO ENCONTRO
    else{
            p=(nodo*)malloc(sizeof(nodo)); //pido memoria
            if(p==NULL){
                free((void*)p);
                return 2;}
            (*p).elem=arti;
            (*p).hd=NULL;
            (*p).hi=NULL;
            if ((*a).CantNodos==0){
                (*a).raiz=p;}
            else{
                if(strcmpi((*ant).elem.Codigo,arti.Codigo)<0)
                    (*ant).hd=p;
                else
                    (*ant).hi=p;
            }
            *costo=1;
            (*a).CantNodos++;
            return 1;}//se dio el alta
}

int evocacionABB(ABB *a,char codigo[],articulo *aux,int *costo){
    nodo *p, *ant; int punt=0;
    if(LocalizarABB((&(*a)),codigo,&p,&ant,&punt)){
        *aux=(*p).elem;
        *costo=punt;
        return 1;
    }else{
        *costo=punt;
        return 0;}
}

int bajaABB(ABB *a,articulo auxi,int *costo, int admcomp){
    nodo *p,*ant,*aux1,*aux2;
    int opcion,boolmenu,b;
    if(LocalizarABB(&(*a),auxi.Codigo,&p,&ant,&b)){
        if(admcomp==2){//estoy comparando
            boolmenu=((strcmpi((*p).elem.TipoDeArticulo,auxi.TipoDeArticulo)==0)&&(strcmpi((*p).elem.Marca,auxi.Marca)==0)&&(strcmpi((*p).elem.Descripcion,auxi.Descripcion)==0)&&((*p).elem.PrecioUnitario==auxi.PrecioUnitario)&&((*p).elem.CantidadExistente==auxi.CantidadExistente));
        if(boolmenu==0)
            return 3;} //aviso que no coinciden campos en comparar estructuras
        if(admcomp==1){
            printf("El elemento que quiere borrar es el siguiente:\n");
            printf("\nCodigo:%s",(*p).elem.Codigo);
            printf("\nTipo de articulo:%s",(*p).elem.TipoDeArticulo);
            printf("\nMarca:%s",(*p).elem.Marca);
            printf("\nDescripcion:%s",(*p).elem.Descripcion);
            printf("\nPrecio unitario %.2f",(*p).elem.PrecioUnitario);
            printf("\nCantidad Existente:%d",(*p).elem.CantidadExistente);
            do{
                printf("\nConfirma la baja del elemento?\n (1): Si (2) No\n");
                scanf("%d",&opcion);
            }while(opcion!=1 && opcion != 2);
                getchar();
                if(opcion==2)
                    return 2; //CANCELACION DE BAJA
            }

            //primer caso de baja: nodo a eliminar no tiene hijos.
            if((*p).hi==NULL && (*p).hd==NULL ){
                if(p==(*a).raiz){
                    (*a).raiz=NULL;
                }else{
                if((*ant).hd==p){
                    (*ant).hd = NULL;
                }else{
                   (*ant).hi = NULL;}
                }
                *costo=1;

            }else{ //2do caso eliminar el que tiene un solo hijo
                if(((*p).hi==NULL &&(*p).hd!=NULL) ||((*p).hd==NULL &&(*p).hi!=NULL)){
                    if (p==(*a).raiz){
                        if((*p).hi!=NULL){
                            (*a).raiz=(*p).hi;
                        }else{
                            (*a).raiz=(*p).hd;
                        }
                    }
                    else{
                    if((*ant).hd==p){
                        if((*p).hd!=NULL){
                            (*ant).hd=(*p).hd;
                        }else{
                            (*ant).hd=(*p).hi;}
                    }else{
                        if((*p).hi!=NULL){
                            (*ant).hi=(*p).hi;
                        }else{
                            (*ant).hi=(*p).hd;}
                        }
                    }
                *costo=1;
                }else{//3 caso TIENE DOS HIJOS no hace falta chequear que tiene dos hijos
                    aux2=(*p).hd; // Politica menor de los mayores
                    aux1=(*p).hd;
                    while ((*aux1).hi != NULL){
                        aux2=aux1;
                        aux1=(*aux1).hi;
                    }
                    if(aux1==aux2){ //caso 1 de politica
                        (*p).hd=(*aux1).hd; //vinculacion
                        (*p).elem=(*aux1).elem;//reemplazo
                        *costo=2;
                    }else{
                        (*p).elem=(*aux1).elem; //reemplazo (no hay orden entre reempl y vincu)
                        (*aux2).hi=(*aux1).hd;
                        *costo=2;}
                    p=aux1;
                    } //fin caso 3
                } // Fin casos 2 y 3
        free(p);
        (*a).CantNodos--;
        return 1;
    }else{
        return 0;}
}//fin funcion

void MostrarABB(nodo *p,int i){ //paso la raiz
    //muestro la raiz
    //if(p!=NULL)
    printf("\nCodigo:%s",(*p).elem.Codigo);
    printf("\nTipo de articulo:%s",(*p).elem.TipoDeArticulo);
    printf("\nMarca:%s",(*p).elem.Marca);
    printf("\nDescripcion:%s",(*p).elem.Descripcion);
    printf("\nPrecio unitario %.2f",(*p).elem.PrecioUnitario);
    printf("\nCantidad Existente:%d",(*p).elem.CantidadExistente);
    if ((*p).hi==NULL && (*p).hd==NULL){
    printf("\nNo tiene hijos\n");}
    if((*p).hi!=NULL){
        printf("\n------>Codigo del hijo izquierdo es %s ",(*p).hi->elem.Codigo);}
    if((*p).hd!=NULL){
        printf("\n------>Codigo del hijo derecho es %s \n",(*p).hd->elem.Codigo);}
    printf("\n************************************************************************************************\n");
    if (i%4==0 && i!=0)
        system("PAUSE");
    if((*p).hi!=NULL){
        MostrarABB((*p).hi,i+1);}
    if((*p).hd!=NULL){
        MostrarABB((*p).hd,i+1);
    }
}

int memorizacionPreviaABB(ABB *a){
    FILE *fp;
    articulo aux;
    inicializar(&aux);
    int boolalta,b;
    if((fp = fopen("Articulos.txt","r"))==NULL){
        return 0;
    }
    else{
        while(!(feof(fp)) && boolalta!=2){
                fscanf(fp,"%s\n",aux.Codigo);
                fscanf(fp,"%s\n",aux.TipoDeArticulo);
                fscanf(fp,"%s\n",aux.Marca);
                fscanf(fp,"%[^\n]s",aux.Descripcion);
                fscanf(fp,"%f\n",&aux.PrecioUnitario);
                fscanf(fp,"%d\n",&aux.CantidadExistente);
                boolalta=AltaABB(&(*a),aux,&b);
            }
                fclose(fp);
        }
            return 1;

    }



#endif // ABB_H_INCLUDED
