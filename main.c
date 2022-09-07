/*
 * introFadeProj.c
 *
 * Created: 9/4/2022 3:14:43 PM
 * Author : Joseph D
 * MIT License
 * Intended to have sleep modes enabled to save power but who has time for that
 */ 


// Compile
//	avr-gcc -O2 -mmcu=atmega328p ./main.c -o ./out.out

// Link
//	avr-objcopy -0 ihex out.out	.out.hex

// Upload (Arduino NANO Clone, CH430G or whatever (old bootloader)), pathing and port need changes if on w*ndows
//	avrdude -C/etc/avrdude.conf -v -patmega328p -carduino -P/dev/ttyUSB0 -b57600 -D -Uflash:w:./.out.hex:i

#define F_CPU 16000000UL
#define BAUD 9600
#define USARTARG F_CPU/16/BAUD-1	// 9600 BAUD

#define BUTTON_PIN	2				// Must be in PORTD or you have to change the PCINT setup
#define LED_PIN		3				// Must be in Timer2 compare match pin

// Delay calculation kinda wack, just choose a number that works well
#define OVF_DELAY	14				// Calculate with ms delay = DELAY * ((16000000 / 1024) / 2 ^ 16)
#define FADE_DELAY	1

#include <avr/io.h>
#include <avr/interrupt.h>

#define NEWLINE		10
#define FADE_LOOPS	127

//#define SERIAL_OUT_EN				// UNCOMMENT ONLY WITH SERIAL ENABLED DEV BOARDS (UNO, NANO)
//#define BLINK_MODE				// Uncomment if blinking operation is desired, else LED will fade

volatile uint8_t state_change = 0;	//	Flag to indicate valid button press
volatile uint8_t globee = 0;		//	Global TIMER_0 overflow counter
volatile uint8_t bottle = 0;		//	Global TIMER_0 overflow accumulator (counter of counter)

#ifdef SERIAL_OUT_EN

void init_serial(unsigned int someVal);
void serialWrite(unsigned char data);
void serialWriteNl(unsigned char data);
void printStr(uint8_t data);
void printBin8(uint8_t data);

#endif



ISR(PCINT2_vect){
	if(bottle && !(PIND & (1 << BUTTON_PIN))){	// debounce flag + sbic(PIND, 2)
		state_change = 1;						// Indicate state change
		bottle = 0;								// Reset debounce counter
	}
}

// Button pulls low on PD2

ISR(TIMER0_OVF_vect){
	if(globee >= OVF_DELAY){				// TIMER0 overflow counter
		bottle = 1;
		globee = 0;							// proper delay reached
	} else {
		globee += 1;	
	}
}

#ifndef BLINK_MODE
	void fadeLed(volatile uint8_t *currMode);
	void fade_loops(uint8_t to_pt_);
	void fade_delay(uint8_t __ms__);
#endif



int main(void){
	cli();
#ifdef SERIAL_OUT_EN
	init_serial(USARTARG);
#endif

#ifndef BLINK_MODE
	volatile uint8_t LIGHTSTATE = 0;	//	Light state for LED in fade mode, 2 == full, 1 == dimmed, 0 == off
#endif

	DDRD |= (1 << LED_PIN);				// PD3 = led
	DDRD |= (1 << BUTTON_PIN);			// PD2 = button
	PORTD |= (1 << BUTTON_PIN);			// Pullup enabled
	
	PCICR |= (1 << 2);					// Enable PCINT2 (PORT D)
	PCMSK2 |= (1 << 2);					// Enable interrupt on PD2

#ifdef SERIAL_OUT_EN
	printBin8(PCICR);
	serialWrite(NEWLINE);

	printBin8(PCMSK2);
	serialWrite(NEWLINE);
#endif


	TCCR0A = 0x00;							// Normal Operation
	TCCR0B |= (1 << 2) | (1);				// clk/1024 prescale CTR0

	TIMSK0 |= (1);							// Overflow interrupt enabled

	TCNT0 = 0x00;							// Set timer 0 init value
	
	TCCR2A |= (1 << COM2B1);				// Phase Correct PWM Mode on PD3, Timer 2
	TCCR2A |= (1 << WGM20);					// Enable Phase Correct PWM in WGM (fast works fine too)
											// For fast push another bit to WGM21
											
	TCCR2B |= (1 << CS20);					// Set Timer 2 Prescalar (curr 1x)
	
	
	
	sei();								// Enable global interrupts

#ifdef SERIAL_OUT_EN
	uint8_t ctr = 0;					// General Purpose Output Counter
#endif

    while (1){		
		if(state_change){
			// Button pin pulled low
#ifdef SERIAL_OUT_EN
			printStr(ctr);
			serialWrite(NEWLINE);
			ctr += 1;
#endif
			
#ifdef BLINK_MODE
			PORTD ^= (1 << LED_PIN);
#else
			fadeLed(&LIGHTSTATE);
#endif
			state_change = 0;
		}
		
    }
}						// End main

//=============================================== FUNctions ==============================================//
#ifndef BLINK_MODE

void fadeLed(volatile uint8_t *currMode){
	PCMSK2 &= ~(1 << 2);				// Disable button PCINT
	
	// Set OCR2B compare register for timing
	
	if(*currMode == 2){
		// If light is full brightness, go to 50%
		fade_loops(127);
		*currMode = 1;
	} else
	if(*currMode == 1){
		// If light is dimmed, turn off
		fade_loops(0);
		*currMode = 0;
		} else {
		// Light is off, turn light to full brightness
		fade_loops(127);
		fade_loops(254);
		*currMode = 2;
	}
	
	PCMSK2 |= (1 << 2);					// Re enable button PCINT
}

void fade_loops(uint8_t to_pt_){
	uint8_t mode_ = 0;
	
	if(to_pt_ > OCR2B){
		mode_ = 1;
	}
	
	for(uint8_t n = 0; n < FADE_LOOPS; n++){
		if(mode_){
			OCR2B += 1;
		} else {
			OCR2B -= 1;
		}
		fade_delay(FADE_DELAY);
	}
	
	OCR2B = to_pt_;
}

void fade_delay(uint8_t __ms__){
	globee = 0;
	
	for(uint8_t n = 0; n < __ms__; n++){
		while(globee < FADE_DELAY);	
	}
}

#endif


#ifdef SERIAL_OUT_EN

void init_serial(unsigned int someVal){         // Debug for use with development boards

	// Set Baud rate
	UBRR0H = (unsigned char)(someVal >> 8);
	UBRR0L = (unsigned char)(someVal);

	// Enable Tx and Rx
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);

	// Setup 8N2 format // Change to 8N1 later
	UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

void serialWrite(unsigned char data){
	while(!(UCSR0A & (1 << UDRE0)));			// Wait for empty transmit buffer
	UDR0 = data;
}

void serialWriteNl(unsigned char data){
	serialWrite(data);
	serialWrite(NEWLINE);
}

void printStr(uint8_t data){
	if(!data){
		serialWrite('0');
		return;
	}
	uint8_t zero_rejection = 0, tctr__ = 0;

	for(uint16_t n = 1000; n > 0; n/= 10){
		switch(data / n){
			case 0:
			if(zero_rejection){
				serialWrite('0');
			}
				break;
			case 1:
				serialWrite('1');
				zero_rejection = 0x01;
				break;
			case 2:
				serialWrite('2');
				zero_rejection = 0x01;
				break;
			case 3:
				serialWrite('3');
				zero_rejection = 0x01;
				break;
			case 4:
				serialWrite('4');
				zero_rejection = 0x01;
				break;
			case 5:
				serialWrite('5');
				zero_rejection = 0x01;
				break;
			case 6:
				serialWrite('6');
				zero_rejection = 0x01;
				break;
			case 7:
				serialWrite('7');
				zero_rejection = 0x01;
				break;
			case 8:
				serialWrite('8');
				zero_rejection = 0x01;
				break;
			case 9:
				serialWrite('9');
				zero_rejection = 0x01;
				break;
			default:
				break;
		}
		tctr__ += 1;
		
		data = data % n;
	}
}

void printBin8(uint8_t data){
	for(uint8_t n = 0; n < 8; n++){
		uint8_t tm_ = (data >> (7 - n)) & (0x01);
		if(tm_){
			serialWrite('1');
		} else {
			serialWrite('0');
		}
	}
}

#endif