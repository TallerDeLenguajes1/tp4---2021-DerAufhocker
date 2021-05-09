#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct Tarea {
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion; //
    int Duracion; // entre 10 – 100
}Tarea;

typedef struct Tnodo{
    Tarea tarea;
    struct Tnodo *siguiente;
}Tnodo;

Tnodo *crearLista();
Tnodo *CrearNodo(int id);
void CargarLista(Tnodo **cabeza, int tama);
void Mostrar(Tnodo *lista, Tnodo **realizadas, Tnodo **pendientes);
Tnodo *quitarNodo(Tnodo **cab);
void verLista(Tnodo *lista);

int main(){
    Tnodo *ListaTareas = crearLista();
    Tnodo *realizadas = crearLista();
    Tnodo *pendientes = crearLista();
    int cant_tareas;
    srand(time(NULL));

    printf("Ingrese el numero de tareas:\n");
    scanf("%d",&cant_tareas);
    CargarLista(&ListaTareas,cant_tareas);
    Mostrar(ListaTareas,&realizadas,&pendientes);
    printf("lista pendiente");
    verLista(pendientes);

    system("pause");
    return 0;
}

Tnodo *crearLista(){
    return NULL;
}

Tnodo *CrearNodo(int id){
    Tnodo *aux;
    char desc[100];

    aux = (Tnodo*)malloc(sizeof(Tnodo));
    aux->tarea.TareaID = id;
    printf("\ningrese una descripcion de la tarea numero %d\n",id);
    fflush(stdin);
    gets(desc);
    fflush(stdin);
    //necesito reservar memoria para el putnero descripcion
    aux->tarea.Descripcion=(char*)malloc(sizeof(char)* strlen(desc));
    strcpy(aux->tarea.Descripcion,desc);
    fflush(stdin);
    aux->tarea.Duracion = rand() % 90;

    aux->siguiente=NULL;

    return aux;
}

void CargarLista(Tnodo **cabeza, int tama){//inicia al comiezo de la lista
    Tnodo *nuevo;
    for (int i = 0; i < tama; i++)
    {
        //creamos un nodo que apunta a null
        nuevo = CrearNodo(i+1);
        //insertamos el nodo a la lista
        nuevo->siguiente = *cabeza;
        *cabeza = nuevo;
    }
    
}

Tnodo *quitarNodo(Tnodo **cab){
    Tnodo *anterior=crearLista();

    anterior = *cab;
    *cab = anterior->siguiente;
    anterior->siguiente = NULL;

    return anterior;
}

void verLista(Tnodo *lista){
    Tnodo *aux = lista;
    while (lista!=NULL)
    {
        /* code */
        printf("Id: %d\n",aux->tarea.TareaID);
        printf("Descripcion: %s\n",aux->tarea.Descripcion);
        printf("Duracion: %d\n",aux->tarea.Duracion);
        printf("\n\n");
    }
}

void Mostrar(Tnodo *lista, Tnodo **realizadas, Tnodo **pendientes){
    Tnodo *actual;
    Tnodo *nuevo = crearLista();
    int respuesta;
    printf("***Contenido de la lista***\n");

    for ( actual = lista; actual !=NULL; actual=actual->siguiente)
    {
        printf("Id: %d\n",actual->tarea.TareaID);
        printf("Descripcion: %s\n",actual->tarea.Descripcion);
        printf("Duracion: %d\n",actual->tarea.Duracion);
        printf("\n\n");
        printf("Se realizo esta tarea? 1.(si)  2.(no)");
        do
        {
            scanf("%d",&respuesta);
        } while (respuesta!=1 && respuesta!=2);
        if (respuesta==1)
        {
            nuevo = quitarNodo(&lista);
            nuevo = *realizadas;
            *realizadas = nuevo->siguiente;
        }else{
            nuevo = quitarNodo(&lista);
            *pendientes = (Tnodo*)malloc(sizeof(Tnodo));
            nuevo = *pendientes;
            *pendientes = nuevo->siguiente;
        }
    }    
}