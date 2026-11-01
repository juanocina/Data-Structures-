#ifndef cola_dinamicaH
#define cola_dinamicaH


/*
 
 
 especificación COLAS[ELEM]
 
 usa BOOLEANOS
 
 tipos cola
 
 operaciones
 
	cola-vacía     :                -->   cola     { constructora }
	pedir-vez      : cola elemento  -->   cola     { constructora }
	avanzar        : cola           -/->  cola
	primero        : cola           -/->  elemento
	es-cola-vacía? : cola           -->   bool
 
 variables
 
	e : elemento
	p : cola
 
 ecuaciones
 
	avanzar(cola-vacía)     = error
	avanzar(pedir-vez(c,e)) = cola-vacía               <==   es-cola-vacía?(c)
	avanzar(pedir-vez(c,e)) = pedir-vez(avanzar(c),e)  <==  ¬es-cola-vacía?(c)
 
	primero(cola-vacía)     = error
	primero(pedir-vez(c,e)) = e           <==   es-cola-vacía?(c)
	primero(pedir-vez(c,e)) = primero(c)  <==  ¬es-cola-vacía?(c)
 
	es-cola-vacía?(cola-vacía)     = cierto
	es-cola-vacía?(pedir-vez(c,e)) = falso
 
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



template <class TElem>
class TColaDinamica;


template <class TElem>
class TNodoCola {
	
  private:
	
    TElem _elem;
    TNodoCola<TElem>* _sig;
	
    TNodoCola( TElem, TNodoCola<TElem>* = 0 );
	
  public:
	
    TElem elem( );
    TNodoCola<TElem>* sig( );
	
    friend class TColaDinamica<TElem>;
	
};



template <class TElem>
class TColaDinamica {
  public:

  // Constructora
	
     TColaDinamica( );
     // O(1)

  // Operaciones de las colas
	
     void ponDetras( TElem ); 
     // Pre: true
     // Post: Se añade 'elem' al final de la cola
     // O(1) sobre tipos predefinidos

     TElem primero( ); // throw (EAccesoIndebido);
     // Pre: ! esVacio( )
     // Post: Devuelve el primer elemento de la cola
     // Lanza la excepción "EAccesoIndebido" si la cola está vacía
     // O(1)

     void quitaPrim( ); // throw (EAccesoIndebido);
     // Pre: ! esVacio( )
     // Post: Elimina el primer elemento de la cima
     // Lanza la excepción "EAccesoIndebido" si la cola está vacía
     // O(1) sobre tipos predefinidos

     bool esVacio( );
     // Pre: true
     // Post: Devuelve true o false según si la pila está o no vacía
     // O(1)
     
     void divide(TColaDinamica<TElem>& pares, TColaDinamica<TElem>& impares);
     // Pre: true
     // Post: devuelve dos colas: una con los elementos de las posiciones pares y otra con los de las impares
     // O(n)
     
     void colapsar();
     // Pre: true
     // Post: devuelve una cola formada por la suma de los tramos separados por ceros
     // O()

  // Escritura
	
     void escribe( );
     // O(n)


  private:
	
  // Variables privadas                
	
     TNodoCola<TElem> *_prim, *_ult;             
     
};



//---------------------------------------------------------------------------
// IMPLEMENTACION
//---------------------------------------------------------------------------



  // Clase de los nodos


    template <class TElem>
    TNodoCola<TElem>::TNodoCola( TElem elem, TNodoCola<TElem>* sig ) :
      _elem(elem), _sig(sig) {
    };


    template <class TElem>
    TElem TNodoCola<TElem>::elem( ) {
		
      return _elem;
		
    }


    template <class TElem>
    TNodoCola<TElem>* TNodoCola<TElem>::sig( ) {
		
      return _sig;
		
    }





  // Constructora
  
  TColaDinamica<char> c ;
  
        									
     template <class TElem>
     TColaDinamica<TElem>::TColaDinamica( ) :
       _prim(0), _ult(0) {
     };



  // Operaciones de las colas
  
     template <class TElem>
     void TColaDinamica<TElem>::ponDetras( TElem elem ) {
		 
       TNodoCola<TElem>* p = new TNodoCola<TElem>(elem);
		 
       if( _ult != 0 )
	   
         _ult -> _sig = p;
      
       else
       
         _prim = p;
      
       _ult = p;
		 
     };


     template <class TElem>
     TElem TColaDinamica<TElem>::primero( ) // throw (EAccesoIndebido) 
	 {
		 
       if( esVacio() )
         throw EAccesoIndebido("Error: no existe el primero de la cola vacia");
       else
         return _prim -> elem();   
		 
     };

	
												                                         
     template <class TElem>
     void TColaDinamica<TElem>::quitaPrim( ) // throw (EAccesoIndebido) 
	 {
		 
       if( esVacio() )
         throw EAccesoIndebido("Error: no se puede quitar el primero de la cola vacia");
       else {
		   
         TNodoCola<TElem>* tmp = _prim;
         _prim = _prim -> sig();
		   
         if( _prim == 0 )
           _ult = 0;
		   
         delete tmp;
		   
       }
		 
     };



     template <class TElem>
     bool TColaDinamica<TElem>::esVacio( ) {
		 
       return _prim == 0;
		 
     };

  // Hoja 3 de ejercicios 
     template <class TElem>
     void TColaDinamica<TElem>::divide(TColaDinamica<TElem>& pares, TColaDinamica<TElem>& impares){
     	
     	/*
     	divide : cola -> cola cola
     	divide(cola_vacia) = <cola_vacia, cola_vacia>
     	divide(pedir-vez(c,e)) = <pedir-vez(pares(c), e), impares(c)>   <== es-impar?(longitud(c))
     	divide(pedir-vez(c,e)) = <pares(c), pedir-vez(e,impares(c))>   <== es-par?(longitud(c))
     	*/
     	
     	while (!esVacio()){
     		pares.ponDetras(primero());
     		quitaPrim();
     		if (!esVacio()){
     			impares.ponDetras(primero());
     			quitaPrim();
			 }
		 }
	 }
	 
	 template <class TElem>
	 void TColaDinamica<TElem>::colapsar(){
	 	/*
     	colapsar : cola -> cola
     	colapsar(cola-vacía) = cola-vacía
  		colapsar(pedir-vez(c,e)) = colapsa(pedir-vez(c,e), 0)
		colapsa(cola-vacía, n) = pedir-vez(cola-vacía, n)
  		colapsa(pedir-vez(c,e), n)  = colapsa(c, n + e) <==  e ≠ 0
  		colapsa(pedir-vez(c,0), n)  = pedir-vez( pedir-vez(colapsa(c, 0), 0), n )
		*/
     	
    	int restantes = 0;
    	for (TNodoCola<TElem>* tmp = _prim; tmp != 0; tmp = tmp->sig())
        	restantes++;

    	while (restantes > 0) {
        	if (primero() == 0) {
            	ponDetras(0);
            	quitaPrim();
            	restantes--;
        	 } 
			else {
            	TElem suma = 0;
            	while (restantes > 0 && primero() != 0) {
                	suma = suma + primero();
               		quitaPrim();
                	restantes--;
            	 }
            	ponDetras(suma);
        	 }
    	 }
	 }

  // Operaciones de entrada/salida
													                                           
     template <class TElem>
     void TColaDinamica<TElem>::escribe( ) {
		 
       TNodoCola<TElem>* tmp = _prim;
		 
	   cout << endl;
		 
       while ( tmp != 0 ) {
		   
         cout << tmp -> elem() << endl;
         tmp = tmp -> sig();
		   
       }
		 
	   cout << endl;
		 
     };



#endif
