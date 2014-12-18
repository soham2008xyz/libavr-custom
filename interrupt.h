/*
 * interrupt_atmega8.h
 *
 * Created: 12/18/2014 3:17:38 AM
 *  Author: saptarshi
 
 */ 


#ifndef INTERRUPT_SETUP_H_
#define INTERRUPT_SETUP_H_
#define _INT0 PD2
#define _INT1 PD3
#define Control MCUCR
#define INTMask GICR
#endif /* INTERRUPT_SETUP_H_ */



#ifndef INTERRUPT_H_
#define INTERRUPT_H_
/* Setup interrupt to be fired whenever the PD2 pin goes low */
void _setup_INT0_low()
{
	/*interrupt fired when the PD2 pin goes low*/
	DDRD|=(0<<_INT0);
	PORTD|=(1<<_INT0);
	Control|=(0<<ISC00)|(0<<ISC01);
	INTMask|=(1<<INT0);
	
}

void _setup_INT0_logicalchange()
{
	/*interrupt fired when the PD2 pin undergoes any logical change*/
	DDRD|=(0<<_INT0);
	PORTD|=(0<<_INT0);
	Control|=(1<<ISC00)|(0<<ISC01);
	INTMask|=(1<<INT0);
	
}

void _setup_INT0_fallingedge()
{
	/*interrupt fired when the PD2 pin undergoes the falling edge*/
	DDRD|=(0<<_INT0);
	PORTD|=(1<<_INT0);
	Control|=(0<<ISC00)|(1<<ISC01);
	INTMask|=(1<<INT0);
	
}

void _setup_INT0_risingedge()
{
	/*interrupt fired when the PD2 pin undergoes the rising edge*/
	DDRD|=(0<<_INT0);
	PORTD|=(0<<_INT0);
	Control|=(1<<ISC00)|(1<<ISC01);
	INTMask|=(1<<INT0);
	
}

void _setup_INT1_risingedge()
{
	/*interrupt fired when the PD3 pin undergoes the rising edge*/
	DDRD|=(0<<_INT1);
	PORTD|=(0<<_INT1);
	Control|=(1<<ISC10)|(1<<ISC11);
	INTMask|=(1<<INT1);
	
}

void _setup_INT1_fallingedge()
{
	/*interrupt fired when the PD3 pin undergoes the falling edge*/
	DDRD|=(0<<_INT1);
	PORTD|=(1<<_INT1);
	Control|=(0<<ISC10)|(1<<ISC11);
	INTMask|=(1<<INT1);
	
}

void _setup_INT1_logicalchange()
{
	/*interrupt fired when the PD3 pin undergoes any logical change*/
	DDRD|=(0<<_INT1);
	PORTD|=(0<<_INT1);
	Control|=(1<<ISC10)|(0<<ISC11);
	INTMask|=(1<<INT1);
	
}

void _setup_INT1_lowlevel()
{
	/*interrupt fired when the PD2 pin goes low*/
	DDRD|=(0<<_INT1);
	PORTD|=(1<<_INT1);
	Control|=(0<<ISC10)|(0<<ISC11);
	INTMask|=(1<<INT1);
	
}



#endif /* INTERRUPT-ATMEGA8_H_ */