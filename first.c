#include <avr/io.h>
#include <util/delay.h>

int main(){
	//set port B5 as output
	DDRD = DDRD | (1 << DDD3);	//use bit shift to switch the 3rd bit of the direction register for port D


	while(1){
		//turn on portB5
		PORTD = PORTD | (1 << PORTD3);	//use bitshift to turn 3rd bit of portd on
		
		//wait
		_delay_ms(1000); //1 sec wait

		//turn off portB5
		PORTD = PORTD & ~(1 << PORTD3);

		//wait
		_delay_ms(1000);
	}
}
