#include <avr/io.h>
#include <util/delay.h>

#define FOSC 1843200
#define BAUD 9600
#define MYUBRR (F_CPU/16/BAUD)-1

static void initUART(void){	
	/*
	 * initialize usart
	 */
	//set baud rate
	UBRR0H = (unsigned char) (MYUBRR>>8);
	UBRR0L = (unsigned char) MYUBRR;

	//enable receiver and transmitter
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);

	//set frameformat (type of message)
	UCSR0C = (1 << USBS0) | (1 << UCSZ00) | (1 << UCSZ01);


	/*
	 * set port B5 as output
	 */
	DDRD |= (1 << DDD3);

}

static void printString(char* str, int size){
	for(int i=0; i<size; i++){
		//keep waiting till the UDREn bit of UCSRnA reg is on
		while(!(UCSR0A & (1 << UDRE0))); 
		
		UDR0 = str[i];
	}
}

static void printValue(int value){
	
	//keep waiting till the UDREn bit of UCSRnA reg is on
	while(!(UCSR0A & (1 << UDRE0))); 

	UDR0 = '0'+value;	//convert to ascii value
}

int main(int argc, char** argv){
	int button = 0;
	
	//initialize the usart communication
	initUART();
	
	//MAIN LOOP
	while(1){ 
		//print the value of the button input (port 0)
		printValue((~PIND&1));	

		//turn on portB5
		PORTD |= (1 << PORTD3);	//turn on 3rd bit of portd register to turn led on using or (0 or 1 = 1)

		//wait
		_delay_ms(1000); //1 sec wait

		//turn off portB5

		PORTD ^= (1 << PORTD3);	//turn off 3rd bit of portd register to turn led off (1 xor 1 = 0 turn off) 
		
		//wait
		_delay_ms(1000);
	}
}

