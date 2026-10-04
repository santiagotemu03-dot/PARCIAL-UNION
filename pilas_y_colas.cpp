#include <iostream>
#include <cstdlib>
using namespace std;

// Capacidad maxima (igual para pila y cola, cambiala si quieres otro limite)
const int MAX_ELEM = 5;


/* ========================================================================
                               PILAS
  */

struct nodoPila
{
    int d;
    nodoPila *a;
};

nodoPila *cima = NULL;   // tope de la pila


int contarPila()
{
    int n = 0;
    nodoPila *t = cima;
    while( t )
    {
        n++;
        t = t->a;
    }
    return n;
}

void ingresarPila()
{
    if( contarPila() >= MAX_ELEM )
    {
        cout<<"\n\nLa pila esta LLENA, no se pueden ingresar mas elementos!!";
        return;
    }

    nodoPila *nuevo = new nodoPila;
    cout<<"\nIngrese elemento: ";
    cin>>nuevo->d;
    nuevo->a = cima;
    cima = nuevo;
}

void ultimoPila()   // muestra el primer dato que se ingreso (el del fondo)
{
    if( !cima )
    {
        cout<<"\n\nPila vacia! No hay elementos.";
        return;
    }
    nodoPila *t = cima;
    while( t->a != NULL )
        t = t->a;
    cout<<"\n\nEl primer dato ingresado (ultimo en salir) fue: "<< t->d;
}

void sacarPila()
{
    if( !cima )
    {
        cout<<"\n\nNo hay elementos!!";
        return;
    }
    nodoPila *t = cima;
    cout<<"\n\nElemento eliminado: "<< t->d;
    cima = t->a;
    delete t;
}

void mostrarPila()
{
    cout<<"\n--- PILA (tope arriba) ---";
    if( !cima )
    {
        cout<<"\n   (vacia)";
        return;
    }
    int i = 0;
    nodoPila *t = cima;
    while( t )
    {
        cout<<"\n   "<< ++i <<" - "<< t->d;
        t = t->a;
    }
}

void primeroPila()
{
    if( !cima )
    {
        cout<<"\n\nPila vacia! No hay elemento para salir.";
        return;
    }
    cout<<"\n\nEl primero en salir es: "<< cima->d;
}

void estadoPila()
{
    if( !cima )
        cout<<"\n\nLa pila esta VACIA (0/"<<MAX_ELEM<<")";
    else if( contarPila() >= MAX_ELEM )
        cout<<"\n\nLa pila esta LLENA ("<<contarPila()<<"/"<<MAX_ELEM<<")";
    else
        cout<<"\n\nLa pila NO esta llena ("<<contarPila()<<"/"<<MAX_ELEM<<")";
}

void vaciarPila()
{
    while( cima )
    {
        nodoPila *t = cima;
        cima = cima->a;
        delete t;
    }
    cout<<"\n\nPila vaciada!!";
}


/* ========================================================================
                               COLAS
   ======================================================================== */

struct nodoCola
{
    int nro;
    nodoCola *sgte;
};

struct cola
{
    nodoCola *delante;
    nodoCola *atras;
};

cola q = { NULL, NULL };   // la cola del programa


void encolar( cola &c, int valor )
{
    nodoCola *aux = new nodoCola;

    aux->nro  = valor;
    aux->sgte = NULL;

    if( c.delante == NULL )
        c.delante = aux;          // primer elemento
    else
        (c.atras)->sgte = aux;

    c.atras = aux;                // siempre apunta al ultimo
}

int desencolar( cola &c )
{
    nodoCola *aux = c.delante;
    int num = aux->nro;

    c.delante = (c.delante)->sgte;
    if( c.delante == NULL )       // si quedo vacia, atras tambien
        c.atras = NULL;
    delete aux;

    return num;
}

void muestraCola( cola c )
{
    nodoCola *aux = c.delante;

    while( aux != NULL )
    {
        cout<<"   "<< aux->nro;
        aux = aux->sgte;
    }
}

void vaciaCola( cola &c )
{
    while( c.delante != NULL )
    {
        nodoCola *aux = c.delante;
        c.delante = aux->sgte;
        delete aux;
    }
    c.delante = NULL;
    c.atras   = NULL;
}

int contarElementos( cola c )
{
    int cont = 0;
    nodoCola *aux = c.delante;

    while( aux != NULL )
    {
        cont++;
        aux = aux->sgte;
    }
    return cont;
}

bool colaLlena( cola c )
{
    return contarElementos( c ) >= MAX_ELEM;
}

void mostrarEstadoLlena( cola c )
{
    if( colaLlena( c ) )
        cout<<"\n\n\tLa cola esta LLENA ("<< contarElementos( c ) <<"/"<< MAX_ELEM <<")"<<endl;
    else
        cout<<"\n\n\tLa cola NO esta llena ("<< contarElementos( c ) <<"/"<< MAX_ELEM <<")"<<endl;
}

void mostrarPrimero( cola c )
{
    if( c.delante != NULL )
        cout<<"\n\n\tEl primer elemento en salir es: "<< (c.delante)->nro <<endl;
    else
        cout<<"\n\n\tCola vacia...! No hay elemento para salir."<<endl;
}

// Extrae un elemento de cualquier posicion (la primera vez que aparece)
bool extraerElemento( cola &c, int valor )
{
    nodoCola *actual   = c.delante;
    nodoCola *anterior = NULL;

    while( actual != NULL && actual->nro != valor )
    {
        anterior = actual;
        actual   = actual->sgte;
    }

    if( actual == NULL )
        return false;

    if( anterior == NULL )
        c.delante = actual->sgte;
    else
        anterior->sgte = actual->sgte;

    if( actual == c.atras )
        c.atras = anterior;

    delete actual;
    return true;
}


/* ========================================================================
                          UTILIDADES Y VISTA UNIDA
   ======================================================================== */

void pausa()
{
    cout<<"\n\nOprima ENTER para continuar";
    cin.ignore( 10000, '\n' );
    cin.get();
}

int leerOpcion()
{
    int op;
    if( !(cin>>op) )
        exit(0);
    return op;
}

void mostrarTodo()
{
    cout<<"\n\n========== ESTRUCTURAS UNIDAS ==========";
    mostrarPila();
    cout<<"\n\n--- COLA (frente -> final) ---\n   ";
    if( q.delante != NULL )
        muestraCola( q );
    else
        cout<<"(vacia)";
    cout<<"\n\n  Pila: "<< contarPila() <<"/"<< MAX_ELEM
        <<"     Cola: "<< contarElementos( q ) <<"/"<< MAX_ELEM;
    cout<<"\n========================================";
}


/* ========================================================================
                               SUBMENUS
   ======================================================================== */

void menuPilas()
{
    int op;
    do
    {
        cout<<"\n\n===== MENU DE PILAS =====";
        cout<<"\n1. Ingresar dato";
        cout<<"\n2. Extraer dato";
        cout<<"\n3. Ultimo en salir (primer dato ingresado)";
        cout<<"\n4. Primero en salir";
        cout<<"\n5. Pila llena o vacia?";
        cout<<"\n6. Vaciar pila";
        cout<<"\n7. Mostrar pila";
        cout<<"\n0. VOLVER al menu principal";
        cout<<"\nIngrese opcion: ";
        op = leerOpcion();

        switch( op )
        {
            case 1: ingresarPila();  break;
            case 2: sacarPila();     break;
            case 3: ultimoPila();    break;
            case 4: primeroPila();   break;
            case 5: estadoPila();    break;
            case 6: vaciarPila();    break;
            case 7: break;           // se muestra abajo
            case 0: return;
            default: cout<<"\n Opcion no valida!!"; break;
        }

        mostrarPila();
        pausa();
    } while( op != 0 );
}

void menuColas()
{
    int op, dato, x;
    do
    {
        cout<<"\n\n===== MENU DE COLAS =====";
        cout<<"\n 1. ENCOLAR";
        cout<<"\n 2. DESENCOLAR";
        cout<<"\n 3. MOSTRAR COLA";
        cout<<"\n 4. VACIAR COLA";
        cout<<"\n 5. ESTA LLENA LA COLA?";
        cout<<"\n 6. MOSTRAR PRIMER ELEMENTO EN SALIR";
        cout<<"\n 7. ESCOGER UN ELEMENTO Y EXTRAERLO";
        cout<<"\n 0. VOLVER al menu principal";
        cout<<"\n\n INGRESE OPCION: ";
        op = leerOpcion();

        switch( op )
        {
            case 1:
                cout<<"\n NUMERO A ENCOLAR: ";
                cin>>dato;
                if( colaLlena( q ) )
                    cout<<"\n\n\t\tLa cola esta LLENA, no se puede encolar el "<< dato <<"...\n";
                else
                {
                    encolar( q, dato );
                    cout<<"\n\n\t\tNumero "<< dato <<" encolado...\n";
                }
                break;

            case 2:
                if( q.delante == NULL )
                    cout<<"\n\n\t\tCola vacia...! No hay nada que desencolar.\n";
                else
                {
                    x = desencolar( q );
                    cout<<"\n\n\t\tNumero "<< x <<" desencolado...\n";
                }
                break;

            case 3:
                cout<<"\n\n MOSTRANDO COLA\n\n";
                if( q.delante != NULL ) muestraCola( q );
                else cout<<"\n\n\tCola vacia...!"<<endl;
                break;

            case 4:
                vaciaCola( q );
                cout<<"\n\n\t\tHecho...\n";
                break;

            case 5:
                mostrarEstadoLlena( q );
                break;

            case 6:
                mostrarPrimero( q );
                break;

            case 7:
                if( q.delante == NULL )
                    cout<<"\n\n\tCola vacia...! No hay elementos para extraer."<<endl;
                else
                {
                    cout<<"\n COLA ACTUAL: ";
                    muestraCola( q );
                    cout<<"\n\n NUMERO A EXTRAER: ";
                    cin>>dato;
                    if( extraerElemento( q, dato ) )
                        cout<<"\n\n\t\tNumero "<< dato <<" extraido de la cola...\n";
                    else
                        cout<<"\n\n\t\tEl numero "<< dato <<" no esta en la cola...\n";
                }
                break;

            case 0:
                return;

            default:
                cout<<"\n Opcion no valida!!";
                break;
        }

        cout<<"\n\n--- COLA (frente -> final) ---\n   ";
        if( q.delante != NULL ) muestraCola( q );
        else cout<<"(vacia)";
        pausa();
    } while( op != 0 );
}


/* ========================================================================
                           MENU PRINCIPAL
   ======================================================================== */

int main()
{
    int op;
    do
    {
        cout<<"\n\n#######################################";
        cout<<"\n#        PILAS Y COLAS EN C++         #";
        cout<<"\n#######################################";
        cout<<"\n 1. Trabajar con PILAS";
        cout<<"\n 2. Trabajar con COLAS";
        cout<<"\n 3. VER TODO (pila y cola juntas)";
        cout<<"\n 0. Salir";
        cout<<"\n\n Ingrese opcion: ";
        op = leerOpcion();

        switch( op )
        {
            case 1: menuPilas(); break;
            case 2: menuColas(); break;
            case 3:
                mostrarTodo();
                pausa();
                break;
            case 0: break;
            default: cout<<"\n Opcion no valida!!"; break;
        }
    } while( op != 0 );

    vaciarPila();
    vaciaCola( q );
    cout<<"\n\nPrograma terminado.\n";
    return 0;
}