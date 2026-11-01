/*

    PRACTICA 1: IMPLEMENTACION EN C++ DEL TAD DE LOS NUMEROS COMPLEJOS SOBRE LOS ENTEROS

    ASIGNATURA: ESTRUCTURAS DE DATOS
    CURSO:      2026-2027
    SUBGRUPO:    

    APELLIDOS: OCINA ALVAREZ	
    NOMBRE:	   JUAN 	

*/


#include <iostream>
#include <string>
#include <cmath>


using namespace std;


class MiComplejo {
	
	public:
		
		MiComplejo();
		MiComplejo(float, float);
		int re();
		int im();
		void suma(MiComplejo &c);
		void resta(MiComplejo &c);
		void producto(MiComplejo c); //Defino la función producto de números complejos.
		float modulo(); //Defino la función módulo de un número complejo.
		void conjugado();
		bool iguales(MiComplejo &c);
    	MiComplejo& operator=(MiComplejo &p);
		bool operator==(MiComplejo &c);
		void mostrar();
		
	private:
		
		float p_re;
		float p_im;
	
};


MiComplejo::MiComplejo() {
	
   p_re = 0;
   p_im = 0;
   
}


MiComplejo::MiComplejo(float x, float y) {
	
   p_re = x;
   p_im = y;
   
}


int MiComplejo::re() {

	return p_re;
	
}


int MiComplejo::im() {

	return p_im;
	
}


void MiComplejo::suma(MiComplejo &c) {
	
	p_re += c.p_re;
	p_im += c.p_im;
	
}


void MiComplejo::resta(MiComplejo &c) {
	
	p_re -= c.p_re;
	p_im -= c.p_im;
	
}


void MiComplejo::producto(MiComplejo c){
	
	/*
	op _*_ : Complejo Complejo -> Complejo .
	eq < A ; B > * < C ; D >  = < A * C - B * D ; A * D + C * B > .

	*/
	float aux_re = p_re;
	
	p_re = aux_re * c.p_re - p_im * c.p_im;
	p_im = aux_re * c.p_im + p_im * c.p_re;
	
}


float MiComplejo::modulo(){
	
	/*
	modulo = sqrt(a^2 + b^2)
	
	*/

	return sqrt(p_re * p_re + p_im * p_im);	
	
}



void MiComplejo::conjugado() {
	
	p_im = -p_im;
	
}


bool MiComplejo::iguales(MiComplejo &c) {
	
	if (this == &c) return true;
	
	if ((p_re == c.p_re) && (p_im == c.p_im)) return true;
	else return false;
	
}


bool MiComplejo::operator==(MiComplejo &c) {  

	if (this == &c) return true;

   	if ((p_re == c.p_re) && (p_im == c.p_im)) return true;
   	
   	else return false;
}


MiComplejo& MiComplejo::operator=(MiComplejo &c){  	

	if (this != &c) {
		
		this->p_re = c.p_re;
		this->p_re = c.p_re;
		
	}
	
	return *this;
	
}


void MiComplejo::mostrar() {
	
	cout << "Parte real: " << p_re << endl << "Parte imaginaria: " << p_im << endl;
	
}