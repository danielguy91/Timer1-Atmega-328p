#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000L

//PROTOTIPOS

void  initTimers10ms ();
void ConfPort (uint8_t  RDireccion,uint8_t  RPuerto,unsigned char PDireccion, unsigned char Direccion , unsigned char PEstado, unsigned char Estado  );
void initPortimer();

//

// . Variables globales

volatile  uint16_t timeOut1ms;

//


void ConfPort (uint8_t  RDireccion,uint8_t  RPuerto,unsigned char PDireccion, unsigned char Direccion ,unsigned char PEstado, unsigned char Estado  ) {
   RDireccion |= (Direccion<< PDireccion);
   RPuerto |= (Estado << PEstado);

}
/* ConfPort() es una funcion que permite configurar cualquier puerto del microcontrolador ATMega 328P 
              RDireccion = es el registro donde se configurar
			  PDireccion = es la direccion (bit) del Puerto a configurar 
			  Direccion = Es una variable para configurar el puerto como entrada (1)  o salida (0) 
	          RPuerto = Es el registro de estado del puerto 
			  PEstado = Es bit del puerto a configurar
			  Estado =  Si esta configurado como encendido (1) o apagado (0)
*/     

void  initTimers10ms () {
	OCR1A =625 ;                            // Valor de compracion 
	TCNT1 = 0x00 ;                          // temporizador inicializo
	TIMSK1 = ( 1 << OCIE1A);                // interrupción de compracion en modo CTC OCR1A = TCNT1
	TCCR1B = ( 1 << WGM12) | ( 1 << CS12) ; // PRESCALAR EN 256 y MODO CTC
	                                        // Para poner a cero un registro lo igualo por el mismo  DDRB=DDRB 
}


ISR (TIMER1_COMPA_vect) {
	/*timeOut1ms--;
	if (! timeOut1ms) {
		timeOut1ms = 1000 ;
		// (1 << PORTB5 1) desplazado por B5 es igual a 00100000
		if (PORTB & ( 1 << PORTB5)) // desplazo al numero 1 cinco veces para que aparezca en la posicion 5
		PORTB & = ~ ( 1 << PORTB5); // ~ (1 << PORTB5) = 11011111 hago cero el bit 5 de PORTB5
		else
		PORTB | = ( 1 << PORTB5);
	}*/
	 PORTB ^= (1<<5);
	
}
	
void initPortimer(){
   DDRB |= (1<<DDB5);
   PORTB |= (1<<PORTB5);
	
}	


int main(void) {
    initPortimer();
	sei();
    initTimers10ms ();
	
    while(1) {
	
	
	}

}

