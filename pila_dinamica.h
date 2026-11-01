#ifndef pila_dinamicaH
#define pila_dinamicaH


/*
 
 
 especificación PILAS[ELEM]
 
 usa BOOLEANOS, NATURALES
 
 tipos pila
 
 operaciones
 
 pila-vacía     :                -->   pila     { constructora }
 apilar         : elemento pila  -->   pila     { constructora }
 desapilar      : pila           -/->  pila
 cima           : pila           -/->  elemento
 es-pila-vacía? : pila           -->   bool

 fondo          : pila           -/->  elemento
 inversa        : pila           -->   pila
 duplicar       : pila           -->   pila
 concatenar     : pila     pila  -->   pila
 entremezclar   : pila     pila  -->   pila
 
 operaciones privadas
 
 inversa_aux    : pila     pila  -->   pila
 profundidad    : pila           -->   nat
 
 variables
 
 e    : elemento
 p, q : pila
 
 ecuaciones
 
 desapilar(pila-vacía)  = error
 desapilar(apilar(e,p)) = p
 
 cima(pila-vacía)  = error
 cima(apilar(e,p)) = e
 
 es-pila-vacía?(pila-vacía)  = cierto
 es-pila-vacía?(apilar(e,p)) = falso
 
 fondo(pila-vacia)  = error
 fondo(apilar(e,p)) = e         <==   es_pila_vacía?(p)
 fondo(apilar(e,p)) = fondo(p)  <==  ¬es_pila_vacía?(p)
 
 inversa(p) = inversa_aux(p,pila-vacía)
 
 inversa_aux(pila-vacía,p)  = p
 inversa_aux(apilar(e,p),q) = inversa_aux(p,apilar(e,q))
 
 duplicar(pila-vacía)  = pila-vacía
 duplicar(apilar(e,p)) = apilar(e,apilar(e,duplicar(p)))
 
 concatenar(p,pila-vacía)  = p
 concatenar(p,apilar(e,q)) = apilar(e,concatenar(p,q))
 
 entremezclar(pila-vacía,pila-vacía) = pila-vacía
 entremezclar(apilar(e,p),q)         = apilar(e,entremezclar(p,q)) <== profundidad(p) + 1 > profundidad(q)
 entremezclar(p,apilar(e,q))         = apilar(e,entremezclar(p,q)) <== profundidad(p) <= profundidad(q) + 1
 
 profundidad(pila-vacía)  = 0
 profundidad(apilar(e,p)) = 1 + profundidad(p)
 
 
 fespecificación
 
 
*/



#include <iostream>
#include <string>


using namespace std;



// Tratamiento de excepciones


class EAccesoIndebido {
	
public:
	
    EAccesoIndebido( string mensaje = "" ) : _mensaje(mensaje) { };
	
    string mensaje ( ) {
		return _mensaje;
    };
	
private:
	
    string _mensaje;
	
};



// Clase de los nodos de la pila dinámica


template <class TElem>
class TPila;


template <class TElem>
class NodoPila {
	
public:
	
	
	NodoPila<TElem>* copiar_lista( );
	
	friend class TPila<TElem>;
	
	
private:
	
	TElem dato;
	NodoPila<TElem>* enlace;
	

};



// Clase del TAD genérico de las pilas (implementación dinámica)



template <class TElem>
class TPila {
	
public: 
		
	
 // Constructora
	
	TPila( );
	// Pre: true
	// Post: construye un valor que representa a la pila vacía
	// O(1)
	
	
 // Destructora
	
	void borrar( );
	// Pre: true
	// Post: destruye la pila hasta dejarla vacía
	// O(nª de elementos de la pila)
	
	

 // Operaciones de las pilas
	
	void apila( TElem elem );
	// Pre: true
	// Post: modifica la pila, añadiéndole "elem" en la cima
	// O(1)
	
	
	void desapila( ); //throw ( EAccesoIndebido );
	// Pre: ! esVacio()
	// Post: modifica la pila, quitando el elemento que está en la cima
	// Lanza la excepción "EAccesoIndebido" si la pila está vacía
	// O(1)
	
	
	void inversa( );
	// Pre: true
	// Post: modifica la pila, devolviendo su inversa
	// O(nº de elementos de la pila)
	
	
	void duplicar( );
	// Pre: true
	// Post: modifica la pila, duplicando sus elementos
	// O(nº de elementos de la pila)
	
	
	void concatenar( TPila<TElem> );
	// Pre: true
	// Post: coloca los elementos de la pila argumento sobre la pila
	// O(nº de elementos de la pila argumento)
	
	
	void entremezclar( TPila<TElem> );
	// Pre: true
	// Post: entremezcla los elementos de la pila con los elementos de la pila argumento
	// O(máx{nª de elementos de la pila, nº de elementos de la pila argumento})
	
	
	TElem cima( ); //throw ( EAccesoIndebido );
	// Pre: ! esVacio()
	// Post: devuelve el elemento que está en la cima
	// Lanza la excepción "EAccesoIndebido" si la pila está vacía
	// O(1)
	
	
	TElem fondo( ); //throw ( EAccesoIndebido );
	// Pre: ! esVacio()
	// Post: devuelve el elemento que está en el fondo
	// Lanza la excepción "EAccesoIndebido" si la pila está vacía
	// O(nº de elementos de la pila)
	
	
	bool esVacio( );
	// Pres: true
	// Post: determina si la pila está vacía
	// O(1)
	
	
	void escribe( );
	// Pre: true
	// Post: escribe el contenido de la pila
	
	
	TPila<TElem>* copiar_pila( );
	// Pre: true
	// Post: copia una pila
	
	
	
private:
	
	
 // Variables privadas
	
	NodoPila<TElem>* _cima;
	
	
};



/*
 
 Implementación dinámica de las pilas como listas enlazadas mediante punteros
 
*/



//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//                       OPERACIONES PUBLICAS                               //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////



template <class TElem>
TPila<TElem>::TPila( ) {
	
	_cima = 0;
	
}



template <class TElem>
void TPila<TElem>::borrar( ) {
	
	while (! esVacio() ) {
		
		desapila();
		
	}
	
}



template <class TElem>
void TPila<TElem>::apila( TElem x ) {
	
	NodoPila<TElem>* nuevo_nodo = new NodoPila<TElem>;
	
	nuevo_nodo -> dato = x;
	nuevo_nodo -> enlace = _cima;
	
	_cima = nuevo_nodo;
	
}



template <class TElem>
void TPila<TElem>::desapila( ) //throw ( EAccesoIndebido ) 
{
	
	if ( esVacio( ) ) EAccesoIndebido( "No se puede desapilar de la pila vacía" );
	else {
		
		NodoPila<TElem>* aux = _cima;
		
		_cima = _cima -> enlace;
		
		delete aux;
		
	}
	
}



template <class TElem>
void TPila<TElem>::inversa( ) { // O(nº de elementos de la pila)
	
	TPila<TElem> aux;
	
	while ( !esVacio() ){
		
		aux.apila(cima());
		desapila();
		
	}
	_cima = aux._cima;

}



template <class TElem>
void TPila<TElem>::duplicar( ) { // O(nº de elementos de la pila)
	
	NodoPila<TElem>* aux;
	aux = _cima;
	
	while ( aux != 0 ){ // para cuando aux sea nullptr
		
		NodoPila<TElem>* p = new NodoPila<TElem>;
		
		p -> dato = aux -> dato;
		p -> enlace = aux -> enlace;
		aux -> enlace = p;
		aux = p -> enlace;
	}
	
	
}



template <class TElem>
void TPila<TElem>::concatenar( TPila<TElem> pila ) { // O(nº de elementos de la pila)
	
	pila.inversa();
	while ( !pila.esVacio() ){
		apila(pila.cima());
		pila.desapila();
	}
	
}



template <class TElem>
void TPila<TElem>::entremezclar( TPila<TElem> pila ) { // O(máx{nª de elementos de la pila, nº de elementos de la pila argumento})
	
	TPila<TElem> aux;
	inversa();
	pila.inversa();
	
	while ( !esVacio() && !pila.esVacio() ){
		aux.apila(_cima -> dato);
		desapila();
		aux.apila(pila._cima -> dato);
		pila.desapila();
	}
	
	if ( !esVacio() ) aux.concatenar(*this);
	if ( !pila.esVacio() ) aux.concatenar(pila);
	
	*this = aux;
	
}


	
template <class TElem>
TElem TPila<TElem>::cima( ) //throw ( EAccesoIndebido ) 
{
	
	if ( esVacio() ) 
		
		throw EAccesoIndebido( "No existe la cima de la pila vacía" );
	
	else 
		
		return _cima -> dato;
	
}



template <class TElem>
TElem TPila<TElem>::fondo( ) //throw ( EAccesoIndebido ) O(nº de elementos de la pila)
{
	
	inversa();
	return _cima -> dato;
	
}



template <class TElem>
bool TPila<TElem>::esVacio( ) {
	
	if ( _cima == 0 ) 
		
		return true;
	
	else 
		
		return false;
	
}



//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//                       OPERACION DE ESCRITURA                             //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////



template <class TElem>
void TPila<TElem>::escribe( ) {
	
	NodoPila<TElem>* aux = _cima;
	
	cout << endl;
	
	while ( aux != 0 ){
		
		cout << aux -> dato << " ";
		aux = aux -> enlace;
		
	}
	
	cout << endl;
	
}



//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//                       OPERACIONES AUXILIARES                             //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////



template <class TElem>
NodoPila<TElem>* NodoPila<TElem>::copiar_lista( ) {
	
	if ( this == 0 ) return 0;
	else {
		
		NodoPila<TElem>* r = enlace -> copiar_lista( );
		NodoPila<TElem>* nuevo_nodo = new NodoPila<TElem>;
		nuevo_nodo -> dato = dato;
		nuevo_nodo -> enlace = r;
		
		return nuevo_nodo;
		
	}
	
}



template <class TElem>
TPila<TElem>* TPila<TElem>::copiar_pila( ) {
	
	TPila<TElem>* p = new TPila<TElem>;
	
	if ( _cima == 0 ) return 0;
	else {
		
		p -> _cima = _cima -> copiar_lista( );
		
		return p;
	}
	
}


#endif