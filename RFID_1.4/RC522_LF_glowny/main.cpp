#include "mbed.h"
#include "MFRC522.h"
#include <stdio.h>
//KL25Z Pins for MFRC522 SPI interface
#define SPI_MOSI    p5   	//P0_9 na LPC 1769
#define SPI_MISO    p6		//P0_8
#define SPI_SCLK    p7		//P0_7
#define SPI_CS      p8		//P0_6
// KL25Z Pin for MFRC522 reset
#define MF_RESET    RESET		//P0_0
// KL25Z Pins for Debug UART port
#define RX     p10	//przypisane do pinów USB debuggera( według schematu odpowiednio USBRX => P0_1, USBTX => P0_0)
#define TX     p9

uint8_t tab[3];


PwmOut s1 (p42);
PwmOut s2 (p43);
PwmOut s3 (p44);
PwmOut s4 (p45);
PwmOut s5 (p46);
PwmOut s6 (p47);

DigitalOut fwd1	(p48);
DigitalOut fwd2	(p50);
DigitalOut fwd3	(p52);
DigitalOut fwd4	(p21);
DigitalOut fwd5 (p23);
DigitalOut fwd6	(p25);
DigitalOut rev1	(p49);
DigitalOut rev2	(p51);
DigitalOut rev3	(p53);
DigitalOut rev4	(p22);
DigitalOut rev5	(p24);
DigitalOut rev6	(p26);

DigitalIn czujnik1(A0);
DigitalIn czujnik2(A1);
DigitalIn czujnik3(A2);
DigitalIn czujnik4(A3);
DigitalIn czujnik5(A4);
DigitalIn czujnik6(A5);
DigitalIn czujnik7(p29);
DigitalIn przycisk(p30);

DigitalOut LedRed   (LED1); //LED RGB z LPC1769
DigitalOut LedGreen (LED2);
DigitalOut LedBlue  (LED3);
Serial     DebugUART(TX, RX);
MFRC522    RfChip   (SPI_MOSI, SPI_MISO, SPI_SCLK, SPI_CS, MF_RESET);

/*void przyjecie_towaru(){
	int przyjecie=1;
	while (przyjecie) {
		LedRed   = 0;
		LedGreen = 1;
		LedBlue  =	1;
     // Look for new cards
		if ( ! RfChip.PICC_IsNewCardPresent()){
			wait_ms(500);
			continue;
		}
		LedRed   = 0;

     // Select one of the cards
		if ( ! RfChip.PICC_ReadCardSerial()){
			wait_ms(500);
			continue;
		}
		LedRed   = 1;
		LedGreen = 0;
     // Print Card UID
		DebugUART.printf("Card UID: ");
		for (uint8_t i = 0; i < RfChip.uid.size; i++){
			DebugUART.printf(" %X", RfChip.uid.uidByte[i]);
			tab[i] = RfChip.uid.uidByte[i];
		}
		DebugUART.printf("\n\r");
		wait_ms (1000);
		LedBlue=0;
     // Print Card type
		uint8_t piccType = RfChip.PICC_GetType(RfChip.uid.sak);
		DebugUART.printf("PICC Type: %s \n\r", RfChip.PICC_GetTypeName(piccType));
		wait_ms(1000);
		przyjecie = 0;
	}

//		if(przycisk == true){
			switch(tab[0]){
//półka I
			case 0x25:
				DebugUART.printf("polka 1");
				while (czujnik4 == true){
					if (czujnik1 == false){
						while (czujnik3 == true){
							fwd1 = 1;
							rev1 = 0;
							fwd3 = 1;
							rev3 = 0;
						}
						fwd1 = 0;
						fwd4 = 1;
						rev4 = 0;
						wait_ms(2000);
						break;
					}
					else DebugUART.printf("Brak towaru!!!\n");
				}
				fwd3 = 0;
				fwd4 = 0;
				if (czujnik4 == false){
					DebugUART.printf("Towar na polce\n");
				}
				break;
//półka II
			case 0x32:
				DebugUART.printf("polka 2");
				while (czujnik5 == true){//zmienić na czujnik5
					if (czujnik1 == false){
						while (czujnik3 == true){
							fwd1 = 1;
							rev1 = 0;
							fwd3 = 1;
							rev3 = 0;
						}
						fwd1 = 0;
						fwd3 = 0;
						fwd2 = 1;
						rev2 = 0;
						wait_ms(3000);
						fwd2 = 0;
						fwd3 = 1;
						fwd5 = 1;//zmienić na silnik5
						rev5 = 0;
						wait_ms(2000);
						break;
					}
					else DebugUART.printf("Brak towaru!!!\n");
				}
				fwd3 = 0;
				fwd5 = 0;//zmienić na silnik5
				if (czujnik5 == false){//zmienić na czujnik5
					DebugUART.printf("Towar na polce\n");
				}
				rev2 = 1;
				wait_ms (3000);
				rev2 = 0;
	 	 	 	break;
	 // półka III
			case 0x53:
				DebugUART.printf("polka 3");
				while (czujnik6 == true){
					if (czujnik1 == false){
						while (czujnik3 == true){
							fwd1 = 1;
							rev1 = 0;
							fwd3 = 1;
							rev3 = 0;
						}
						fwd1 = 0;
						fwd3 = 0;
						fwd2 = 1;
						rev2 = 0;
						wait_ms(6000);
						fwd2 = 0;
						fwd3 = 1;
						fwd6 = 1;
						rev6 = 0;
						wait_ms(2000);
						break;
					}
					else DebugUART.printf("Brak towaru!!!\n");
				}
				fwd3 = 0;
				fwd6 = 0;
				if (czujnik6 == false){
					DebugUART.printf("Towar na polce\n");
				}
				rev2 = 1;
				wait_ms (6000);
				rev2 = 0;
				break;
// Obce ID
			default:
				DebugUART.printf("Obce ID!!!!!!!");
				break;
			}
		}//
	else{
			while (przycisk == true){
				fwd2 = 0;
				rev2 = 1;
			}
		}
	}
void odbior_towaru(){
	int odbior = 1;
	while (odbior) {
		LedRed   = 0;
		LedGreen = 1;
		LedBlue  =	1;
		// Look for new cards
		if ( ! RfChip.PICC_IsNewCardPresent()){
			wait_ms(500);
			continue;
		}
		LedRed   = 0;
		// Select one of the cards
		if ( ! RfChip.PICC_ReadCardSerial()){
			wait_ms(500);
			continue;
		}
		LedRed   = 1;
		LedGreen = 0;
		// Print Card UID
		DebugUART.printf("Card UID: ");
		for (uint8_t i = 0; i < RfChip.uid.size; i++){
			DebugUART.printf(" %X", RfChip.uid.uidByte[i]);
			tab[i] = RfChip.uid.uidByte[i];
		}
		DebugUART.printf("\n\r");
		wait_ms (1000);
		LedBlue=0;
		// Print Card type
		uint8_t piccType = RfChip.PICC_GetType(RfChip.uid.sak);
		DebugUART.printf("PICC Type: %s \n\r", RfChip.PICC_GetTypeName(piccType));
		wait_ms(1000);
		odbior = 0;
	}

		if(przycisk == false){
			switch(tab[0]){
			//półka I
			case 0x25:
				DebugUART.printf("polka1");
				if (czujnik4 == false){
					while(czujnik1 == true){
						fwd4 = 0;
						rev4 = 1;
						fwd3 = 0;
						rev3 = 1;
						fwd1 = 0;
						rev1 = 1;
					}
					DebugUART.printf("Towar do odebrania \n");
					rev4 = 0;
					rev3 = 0;
					rev1 = 0;
				}
				else DebugUART.printf("Brak towaru!!!\n");
				break;
				//półka II
			case 0x32:
				DebugUART.printf("polka2");
				if (czujnik4 == false){//zmienić na czujnik5
					fwd2 = 1;
					rev2 = 0;
					wait_ms (3000);
					fwd2 = 0;
					while (czujnik3 == true){//zmienić na czujnik2
						fwd4 = 0;//zmienić na silnik5
						rev4 = 1;
						fwd3 = 0;
						rev3 = 1;
					}
					if (czujnik3 == false){
						rev4 = 0;//zmienić na silnik5
						rev3 = 0;
						rev2 = 1;
						wait_ms (3000);
						while (czujnik1 == true){
							rev2 = 0;
							rev3 = 1;
							rev1 = 1;
						}
					}
					DebugUART.printf("Towar do odebrania \n");
					rev3 = 0;
					rev1 = 0;
				}
				else DebugUART.printf("Brak towaru!!!\n");
				break;
				//półka III
			case 0x53:
				DebugUART.printf("polka3");
				if (czujnik6 == false){
					fwd2 = 1;
					rev2 = 0;
					wait_ms (6000);
					fwd2 = 0;
					while (czujnik2 == true){
						fwd6 = 0;
						rev6 = 1;
						fwd3 = 0;
						rev3 = 1;
					}
	 			 		if (czujnik2 == false){
	 			 			rev6 = 0;
	 			 			rev3 = 0;
	 			 			rev2 = 1;
	 			 			wait_ms (6);
	 			 			while (czujnik1 == true){
	 			 				rev2 = 0;
	 			 				rev3 = 1;
	 			 				rev1 = 1;
	 			 			}
	 			 		}
	 			 		DebugUART.printf("Towar do odebrania \n");
	 			 		rev3 = 0;
	 			 		rev1 = 0;
				}
				else DebugUART.printf("Brak towaru!!!\n");
				break;
			default:
				DebugUART.printf("Obce ID!!!!!!!");
				break;
			}
		}
		{
			while (przycisk == true){
				fwd2 = 0;
				rev2 = 1;
			}
		}
	}
void stan_magazynu(){
		if (czujnik6 == true){
			if (czujnik5 == true){
				if (czujnik4 == true){
					DebugUART.printf("Magazyn jest pusty. \n");
				}
				else DebugUART.printf("Wolne są półki 3 i 2. \n");
			}
			else if(czujnik4 == true){
					DebugUART.printf("Wolne są półki 3 i 1. \n");
				}
				else DebugUART.printf("Wolna jest półka 3. \n");
			}
		else{
			if (czujnik5 == true){
				if (czujnik4 == true){
					DebugUART.printf("Wolne są półki 2 i 1. \n");
				}
				else DebugUART.printf("Wolna jest półka 2. \n");
			}
			else if(czujnik4 == true){
				DebugUART.printf("Wolna jest póółka 1. \n");
			}
			else DebugUART.printf("Magazyn pełny.\n");
		}
	}
*/
void PWM_init(){
	// PWM
	s1.period(0.10f);      // 4 second period
	s1.write(0.50f);      // 50% duty cycle, relative to period
	s2.period(0.10f);      // 4 second period
	s2.write(0.90f);      // 50% duty cycle, relative to period
	s3.period(0.10f);      // 4 second period
	s3.write(0.50f);      // 50% duty cycle, relative to period
	s4.period(0.10f);      // 4 second period
	s4.write(0.50f);      // 50% duty cycle, relative to period
	s5.period(0.10f);      // 4 second period
	s5.write(0.50f);      // 50% duty cycle, relative to period
	s6.period(0.10f);      // 4 second period
	s6.write(0.50f);
}
int main() {
	//PWM
	RfChip.PCD_Init();
	PWM_init();
	while(true){
if(czujnik1 == true ){
	DebugUART.printf("Dziala");
	fwd2=1;
	rev2=0;
	fwd3=1;
	rev3=0;
}
else {
	DebugUART.printf("Nie dziala");
}
	}


	// Set debug UART speed
/*	DebugUART.baud(9600);
	// Init. RC522 Chip
	RfChip.PCD_Init();
	char ch[1];
//	char jedynka[2]={1,0};
	while(true){
		if ( DebugUART.readable()){

			wait_ms(500);
			for(uint8_t i = 0; i < 2; i++){
						ch[i] = DebugUART.getc();
					}
			DebugUART.printf("%c",ch[0]);
			switch( ch[0] ){
				case '2':
					DebugUART.printf("Stan magazynu \n");
					stan_magazynu();
					break;
				case '1':
					DebugUART.printf("Przyjecie towaru \n");
					przyjecie_towaru();
					break;
				case '0':
					DebugUART.printf("Odbior towaru \n");
					odbior_towaru();
					break;
				default:
					DebugUART.printf("Co ty mi tu wysylasz ??? \n");
					break;
			}
			DebugUART.printf("Oczekuje na zadanie. \n");
		}
		continue;
	}
	return 0;
*/}
