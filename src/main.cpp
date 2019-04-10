#include <Arduino.h>


//control motor A PB
	#define Ma1				(1<<PB5)
	#define Ma2				(1<<PB4)
	#define MaPWM			(1<<PD7)

	#define Ma1_ON		  PORTB |= Ma1
	#define Ma2_ON	 		PORTB |= Ma2
	#define Ma1_OFF		  PORTB &= ~Ma1
	#define Ma2_OFF	 		PORTB &= ~Ma2
	#define	MaPWM_ON		PORTD |= MaPWM



//control motor B
  #define Mb1				(1<<PB6)
  #define Mb2				(1<<PC6)
  #define MbPWM			(1<<PC7)

	#define Mb1_ON		  PORTB |= Mb1
	#define Mb2_ON	 		PORTC |= Mb2
	#define Mb1_OFF		  PORTB &= ~Mb1
	#define Mb2_OFF	 		PORTC &= ~Mb2
	#define	MbPWM_ON		PORTC |= MbPWM

 //control motors
	void goFoward(){
  		Ma1_OFF;
  		Ma2_ON;
  		Mb1_OFF;
  		Mb2_ON;
  	}
  	void goBackward(){
  		Ma1_ON;
  		Ma2_OFF;
  		Mb1_ON;
  		Mb2_OFF;
  	}
  	void hardStop(){
  		Ma1_ON;
  		Ma2_ON;
  		Mb1_ON;
  		Mb2_ON;
  	}
  	void slowStop(){
  		Ma1_OFF;
  		Ma2_OFF;
  		Mb1_OFF;
  		Mb2_OFF;
  	}




//Leds on board
	#define builtLed1 		(1<<PE2)
	#define builtLed2		  (1<<PE6)
	#define builtLed1_ON	PORTE |= builtLed1  	// |0000| | 0001 = |0001|
	#define builtLed2_ON	PORTE |= builtLed2
	#define builtLed1_OFF	PORTE &= ~builtLed1 	// |0001| & ~0001 = 0001 & 1110 = |0000|
	#define builtLed2_OFF	PORTE &= ~builtLed2
	#define builtLed1_TOG	PORTE ^= builtLed1 		// |0000| ^ 0001 = |0001|
	#define builtLed2_TOG	PORTE ^= builtLed2 		// |1000| ^ 1000 = |0000|

//floor sensors
  #define FaR 			  (1<<PD0)
  #define FaL				  (1<<PD1)
  #define FbR				  (1<<PD3)
  #define FbL				  (1<<PD2)

  #define edgeA   ((PIND & FaL) | (PIND & FaR))
  #define edgeB   ((PIND & FbL) | (PIND & FbR))

//buttons
  #define but1        (1<<PF0)
  #define but2        (1<<PF1)
  #define but3        (1<<PF4)
/*
  #define butConf1    ((PINF & but1) | (PINF & but2) | (PINF & but3))
  #define butConf2    (((PINF & but1) | (PINF & but2)) & (PINF & ~but3))
  #define butConf3    ((PINF & but1) & (PINF & ~but2) & (PINF & ~but3))
  #define butConf4    ((PINF & but1) & (PINF & but2) & (PINF & but3))
  #define butConf5    ((PINF & ~but1) & ((PINF & but2) | (PINF & but3)))
  #define butConf6    ((PINF & ~but1) | (PINF & ~but2) | (PINF & but3))
  #define butConf7    ((PINF & ~but1) | (PINF & but2) | (PINF & ~but3))
  #define butConf8    ((PINF & but1) | (PINF & ~but2) | (PINF & but3))
*/
void setup(){

	DDRB = 0xF0;
	DDRD |= MaPWM;
	DDRC |= MbPWM;
	DDRE |= builtLed1 | builtLed2;


	//turning on board
  builtLed2_ON;
	for (int i = 0; i < 5; ++i){
		delay(100);
		builtLed1_TOG;
    builtLed2_TOG;
	}
  builtLed1_OFF;
  builtLed2_OFF;
  //===========================

  //input ports floor sensor
  DDRD 	&= ~FaR & ~FaL & ~FbR & ~FaL;
  //disconnect inside VCC
  PORTD &= ~FaR & ~FaL & ~FbR & ~FaL;

  //input ports for buttons
  DDRF  &= ~but1 & ~but2 & ~but3;
  //disconnect insice VCC
  PORTF &= ~but1 & ~but2 & ~but3;



  	MaPWM_ON;
  	MbPWM_ON;
}
void loop(){

}





/*void two(int x){

  bool bin[8];
	for(int i = 7; i >= 0; i--){
		if(x-pow(2,i) > 0){
			bin[i] = 1;
			x -= pow(2,i);
		}
			else{
				bin[i] = 0;
			}
	}
	for(int i = 5; i >= 0; i--){
		Serial.print(bin[i]);
	}
	Serial.println();
}
*/