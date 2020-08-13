/*
 * hotCupboard.c
 *
 * Created: 04.06.2020 12:07:54
 * Author : Johann Schmid
 * Copyright: www.elektrotechniker-aufgaben.de, www.schmid-johann.de
 
 */ 
#define  F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <asf.h>

#define FREQ 2

#define LED_ON PORTB |= (1<<PORTB5)
#define LED_OFF PORTB &= ~(1<<PORTB5)

#define SWITCH_PRESSED (PINB & (1<<PINB3))
#define OPTO_PRESSED (PINB & (1<<PINB4))

volatile bool state = false;

void PWM_disable (void)
{
	TCCR0A &= ~(1<<COM0A1);
	TCCR0A &= ~(1<<COM0B1);
};

void PWM_enable (void)
{
	TCCR0A |= (1<<COM0A1);
	TCCR0A |= (1<<COM0B1);
};

/*ISR(PCINT0_vect)
{
	state = true;	
}*/

void PWM_init(void)
{
	DDRD |= (1<< DDD6);
	DDRD |= (1<< DDD5);
	OCR0A = 127;
	OCR0B = 191;
	TCCR0A |= (1<<WGM01) | (1<<WGM00);
	TCCR0B |= (1<<CS02) | (1<<CS00);
}

int main(void)
{
	bool state[21];
	bool boolOpto;
	volatile uint16_t intCount = 0;
	
	DDRB |= (1<<DDB5);
	DDRB &= ~(1<<DDB4);
	DDRB &= ~(1<<DDB3);

// *** Pull up ***
	
//	PORTB |= (1 << PORTB4);
//	PORTB |= (1 << PORTB3);
	
	PORTB &= ~(1<<PORTB4);
	PORTB &= ~(1<<PORTB3);
	
	//PCMSK0 |= (1<<PCINT4);
	//PCICR |= (1<<PCIE0);
	
	PWM_init();
	
	LED_ON;
    /* Replace with your application code */
    while (1) 
    {
		for (intCount = 0; intCount < 21; intCount++)
		{
					if(OPTO_PRESSED == 0x00)
					// *** if (OPTO_PRESSED == 0x10) ***
					{
						PWM_enable();
						LED_OFF;
						state[intCount] = true;
					}
					else
					{
						state[intCount] = false;
					}
					_delay_ms(1);	
		}
		
		if(SWITCH_PRESSED == 0x00)
		{
			for (intCount = 0; intCount < 21; intCount++)
			{
				if (state[intCount] == false)
				{
					PWM_disable();
					LED_ON;	
				}
				else
				{
					
				}
			}
			
		}
		

    }
}


