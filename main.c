#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000L
#define timeEjecucion 25 
//-----------------PROTOTIPOS--------------------------

void  initTimers10ms ();
void initPortimer();

//------------------------------------------------------

//------------VARIABLES GLOBALES------------------------

volatile  uint16_t timeOut1ms;

//------------------------------------------------------

void  initTimers10ms () {
	OCR1A =625 ;                            // Valor de compracion para 10 ms
	TCNT1 = 0x00 ;                          // temporizador inicializo
	TIMSK1 = ( 1 << OCIE1A);                // interrupción de compracion en modo CTC OCR1A = TCNT1
	TCCR1B = ( 1 << WGM12) | ( 1 << CS12) ; // PRESCALAR EN 256 y MODO CTC
	                                        // Para poner a cero un registro lo igualo por el mismo  DDRB=DDRB 
}



void initPortimer(){
   DDRB |= (1<<DDB5);
   PORTB |= (1<<PORTB5);
	
}	


int main(void) {
    initPortimer();
	sei();                     //Activa interrupciones en el micro
    initTimers10ms ();
	timeOut1ms=timeEjecucion ;            // configuro en 250 ms
    while(1) {
	
	
	}

}

ISR (TIMER1_COMPA_vect) {                           // Interrupcion del timer1
	timeOut1ms--;
	if (! timeOut1ms) {
		timeOut1ms = timeEjecucion ;
		// (1 << PORTB5 1) desplazado por B5 es igual a 00100000
		if (PORTB & ( 1 << PORTB5)){ // desplazo al numero 1 cinco veces para que aparezca en la posicion 5
		PORTB &= ~( 1 << PORTB5);} // ~ (1 << PORTB5) = 11011111 hago cero el bit 5 de PORTB5
		else{
		PORTB |= ( 1 << PORTB5);}
	}
	 //PORTB ^= (1<<5);
	
}
	