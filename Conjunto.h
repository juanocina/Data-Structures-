/*

    PRACTICA 1: IMPLEMENTACION EN C++ DEL TAD GENERICO DE LOS CONJUNTOS FINITOS 
	            USANDO ARRAYS ORDENADOS SIN REPETICIONES

    ASIGNATURA: ESTRUCTURAS DE DATOS
    CURSO:      2026-2027
    SUBGRUPO:    

    APELLIDOS:	OCINA ALVAREZ
    NOMBRE:	    JUAN	

*/


#include <iostream>
#include <string>


using namespace std;


template<class TElem>
class TCjto {
	
  public:

  // Tamano maximo (como maximo se pueden almacenar 'longMax' elementos)
     static const int longMax = 100;
     
  // Constructora
     TCjto();
     // Pre:  true
     // Post: construye un valor que representa al conjunto vacio
     // O(1)

  // Operaciones de los conjuntos
     bool esVacio();
     // Pre:  true
     // Post: determina si el conjunto esta vacio
     // O(1)

     void pon(TElem x);
     // Pre:  ! esLleno( ) || pertenece(x)
     // Post: modifica el conjunto, anadiendole x
     // O(n)

     void quita(TElem x);
     // Pre:  true
     // Post: modifica el conjunto, quitando x
     // O(n)

     bool pertenece(TElem x);
     // Pre:  true
     // Post: determina si x esta en el conjunto
     // O(log n)

     bool esLleno();
     // Pre:  true
     // Post: determina si el conjunto tiene 'longMax' elementos
     // O(1)

  // Escritura
     void escribe(std::ostream &salida);
     // Pre:  true
     // Post: escribe en 'salida' el contenido del conjunto
     TCjto<TElem> diferencia(TCjto<TElem> &c); 
     // Pre: true
	 // Post: devuelve la diferencia entre dos conjuntos.
	 // O(n^2) para n la longitud.

  private:
  	
  // Variables privadas
     TElem espacio[longMax];  // Tipo representante del TAD: array ordenado sin repeticiones.
     int   longitud;          // Tamano de los datos: n = numero de elementos almacenados en el conjunto.
     
};



//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//                  OPERACIONES AUXILIARES PRIVADAS                         //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


// Busqueda binaria en el array

template<class TElem>
int buscaBin(TElem v[], TElem x, int a, int b) {
	
  // Pre: v esta ordenado entre 0 .. num-1
  //      ( 0 <= a <= num ) && ( -1 <= b <= num ) && ( a <= b+1 )
  //      todos los elementos a la izquierda de 'a' son <= x
  //      todos los elementos a la derecha de 'b' son > x

  	 int p, m;

  	 if (a == b + 1)
    	 p = a - 1;
    
  	 else if (a <= b) {
  	
    	 m = (a + b) / 2;
    
    	 if (v[m] <= x)
      	 	p = buscaBin(v, x, m + 1, b);
    	 else
      	 	p = buscaBin(v, x, a, m - 1);
      
  	 }
  
  	 return p;
  
  // Post: devuelve el mayor indice i (0 <= i <= num-1) que cumple
  //       v[i] <= x
  //       si x es menor que todos los elementos de v, devuelve -1

}


template<class TElem>
void buscaBin(TElem x, TElem v[], int num, bool &encontrado, int &pos) {
	
  // Pre: los num primeros elementos de v estan ordenados
  //      num >= 0

  	 pos        = buscaBin(v, x, 0, num-1);
  	 encontrado = (pos >= 0) && (pos < num) && (v[pos] == x);

  // Post : devuelve el mayor Ìndice i (0 <= i <= num-1) que cumple
  //        v[i] <= x
  //        si x es menor que todos los elementos de v, devuelve -1
  //        encontrado es true si x esta en v[0..num-1]
  
}



// funcion auxiliar privada para mostrar un mensaje de error

void error( string mensaje ) {
	
  cout << "Error: " + mensaje;
  
}



//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//                       OPERACIONES PUBLICAS                               //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


template<class TElem>
TCjto<TElem>::TCjto() {
	
	// Pre: true
	
   	   longitud = 0;
   	   
	// Post: construye un valor que representa al conjunto vacio

}


template<class TElem>
bool TCjto<TElem>::esVacio() {
	
	// P: true
	
       return longitud == 0;
       
	// Q: determina si el conjunto esta vacio

}


template<class TElem>
void TCjto<TElem>::pon(TElem x) {
	
	// Pre: ! esLleno( ) || pertenece(x)
	
  	   bool encontrado;
       int pos;

  	   buscaBin(x, espacio, longitud, encontrado, pos);
  	   
  	   if (! encontrado) {
  	   	
    		if (esLleno())
    		
      			error("No se puede insertar el elemento");
      			
    		else {
    			
      			for (int k = longitud ; k > pos + 1; k--)
        			espacio[k] = espacio[k - 1];
        			
      			espacio[pos + 1] = x;
      			longitud++;
      
    	}
    
  	}
  
	// Post: modifica el conjunto, anadiendole x
	
}


template<class TElem>
void TCjto<TElem>::quita(TElem x) {
	
	// Pre: true
	
  	   bool encontrado;
       int  pos;

  	   buscaBin(x, espacio, longitud, encontrado, pos);
  	   
  	   if (encontrado) {
  	   	
    		for (int k = pos ; k < longitud - 1 ; k++)
      			espacio[k] = espacio[k + 1];
      			
    		longitud--;
    		
  	}
  	
	// Post: modifica el conjunto, quitando x
	
}


template<class TElem>
bool TCjto<TElem>::pertenece(TElem x) {
	
	// Pre: true
	
  	   bool encontrado;
  	   int  pos;

  	   buscaBin(x, espacio, longitud, encontrado, pos);
  	   
  	   return encontrado;
  	   
	// Post: determina si x esta en el conjunto
	
}


template<class TElem>
bool TCjto<TElem>::esLleno() {
	
	// Pre: true
	
  	   return longitud == longMax;
  	   
	// Post: determina si el conjunto tiene 'longMax' elementos
	
}


template<class TElem>
TCjto<TElem> TCjto<TElem>::diferencia(TCjto<TElem> &c){ //O(n^2) donde n es la longitud 
	
	TCjto<TElem> result;
	for (int i=0; i<longitud;i++){
		if (!c.pertenece(espacio[i])) result.pon(espacio[i]);
	}
	return result;
}



//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//                       OPERACIONES DE ESCRITURA                           //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


template<class TElem>
void TCjto<TElem>::escribe(ostream &salida ) {
	
	// Pre: true
	
  	   salida << "{";
  	   
  	   for (int i = 0 ; i < longitud ; i++) {
  	   	
    		salida << espacio[i];
    		
    		if (i < longitud - 1)
      				salida << ", ";
      				
 		}
 		
  		cout << "}" << endl;
  		
	// Post: muestra por pantalla el contenido del conjunto

}


template <class TElem>
ostream& operator<< (ostream& salida, TCjto<TElem> cjto) {
	
  cjto.escribe(salida);
  
  return salida;
  
}