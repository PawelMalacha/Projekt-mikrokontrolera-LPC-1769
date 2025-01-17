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

uint8_t polki[3] = { 1, 2, 3 };

PwmOut s1(p42);
PwmOut s2(p43);
PwmOut s3(p44);
PwmOut s4(p45);
PwmOut s5(p46);
PwmOut s6(p47);

DigitalOut fwd1(p22);
DigitalOut fwd2(p24);
DigitalOut fwd3(p48);
DigitalOut fwd4(p50);
DigitalOut fwd5(p52);
DigitalOut fwd6(p25);
DigitalOut rev1(p21);
DigitalOut rev2(p23);
DigitalOut rev3(p49);
DigitalOut rev4(p51);
DigitalOut rev5(p53);
DigitalOut rev6(p26);

DigitalIn czujnik1(A0);
DigitalIn czujnik2(A1);
DigitalIn czujnik3(A2);
DigitalIn czujnik4(A3);
DigitalIn czujnik5(A4);
DigitalIn czujnik6(A5);
DigitalIn przycisk(p29);
DigitalIn kontaktron1(p28);
DigitalIn kontaktron2(p27);



//LED RGB z LPC1769
DigitalOut LedGreen(LED2);
DigitalOut LedBlue(LED3);
Serial DebugUART(TX, RX);
MFRC522 RfChip(SPI_MOSI, SPI_MISO, SPI_SCLK, SPI_CS, MF_RESET);

MFRC522::MIFARE_Key key;

void Rejestracja_mleka() {



	int rejestracja = 1;
	DebugUART.printf("\nRejestracja mleka, przylóż towar\n");
	while (rejestracja) {

		RfChip.PCD_Init();

		// RfChip.PCD_StopCrypto1();

		for (uint8_t i = 0; i < 6; i++) {
			key.keyByte[i] = 0xFF;
		}
		uint8_t Addr = 4;
		uint8_t auth = 7;      //adress for access

		uint8_t DataBlock[] = { 0x01, 0x02, 0x03, 0x04, //  1,  2,   3,  4,
				0x05, 0x06, 0x07, 0x08, //  5,  6,   7,  8,
				0x08, 0x09, 0xff, 0x0b, //  9, 10, 255, 12,
				0x0c, 0x0d, 0x0e, 0x0f }; //new information to writing

		MFRC522::StatusCode status;
		//checking for card
		if (!RfChip.PICC_IsNewCardPresent()) {
			wait_ms(300);
			continue;
		}

		if (!RfChip.PICC_ReadCardSerial()) {
			wait_ms(300);
			continue;
		}

		//getting access

		status = (MFRC522::StatusCode) RfChip.PCD_Authenticate(
				MFRC522::PICC_CMD_MF_AUTH_KEY_B, auth, &key, &(RfChip.uid));
		if (status != MFRC522::STATUS_OK) {
			DebugUART.printf("\nPCD_Authenticate() failed: ");
			DebugUART.printf("\n%s", RfChip.GetStatusCodeName(status));
			continue;
		}
		status = (MFRC522::StatusCode) RfChip.PCD_Authenticate(
				MFRC522::PICC_CMD_MF_AUTH_KEY_A, auth, &key, &(RfChip.uid));
		if (status != MFRC522::STATUS_OK) {
			DebugUART.printf("\nPCD_Authenticate() failed: ");
			DebugUART.printf("\n%s", RfChip.GetStatusCodeName(status));
			continue;
		}

		//writing
		status = (MFRC522::StatusCode) RfChip.MIFARE_Write(Addr, DataBlock, 16);
		if (status != MFRC522::STATUS_OK) {
			DebugUART.printf("\nMIFARE_Write() failed: ");
			DebugUART.printf("\n%s", RfChip.GetStatusCodeName(status));
			continue;
		}

		RfChip.PICC_HaltA();
		RfChip.PCD_StopCrypto1();

		//writing information on screen

		DebugUART.printf("Towar został zarejestrowany\n");
		rejestracja = 0;

	}
	return;

}

void Rejestracja_kawa() {



	int rejestracja = 1;
	DebugUART.printf("\nRejestracja kawy, przyłóż towar\n");
	while (rejestracja) {

		RfChip.PCD_Init();

		// RfChip.PCD_StopCrypto1();

		for (uint8_t i = 0; i < 6; i++) {
			key.keyByte[i] = 0xFF;
		}
		uint8_t Addr = 4;
		uint8_t auth = 7;      //adress for access

		uint8_t DataBlock[] = { 0x02, 0x02, 0x03, 0x04, //  1,  2,   3,  4,
				0x05, 0x06, 0x07, 0x08, //  5,  6,   7,  8,
				0x08, 0x09, 0xff, 0x0b, //  9, 10, 255, 12,
				0x0c, 0x0d, 0x0e, 0x0f }; //new information to writing

		MFRC522::StatusCode status;
		//checking for card
		if (!RfChip.PICC_IsNewCardPresent()) {
			wait_ms(300);
			continue;
		}

		if (!RfChip.PICC_ReadCardSerial()) {
			wait_ms(300);
			continue;
		}

		//getting access

		status = (MFRC522::StatusCode) RfChip.PCD_Authenticate(
				MFRC522::PICC_CMD_MF_AUTH_KEY_B, auth, &key, &(RfChip.uid));
		if (status != MFRC522::STATUS_OK) {
			DebugUART.printf("\nPCD_Authenticate() failed: ");
			DebugUART.printf("\n%s", RfChip.GetStatusCodeName(status));
			continue;
		}
		status = (MFRC522::StatusCode) RfChip.PCD_Authenticate(
				MFRC522::PICC_CMD_MF_AUTH_KEY_A, auth, &key, &(RfChip.uid));
		if (status != MFRC522::STATUS_OK) {
			DebugUART.printf("\nPCD_Authenticate() failed: ");
			DebugUART.printf("\n%s", RfChip.GetStatusCodeName(status));
			continue;
		}

		//writing
		status = (MFRC522::StatusCode) RfChip.MIFARE_Write(Addr, DataBlock, 16);
		if (status != MFRC522::STATUS_OK) {
			DebugUART.printf("\nMIFARE_Write() failed: ");
			DebugUART.printf("\n%s", RfChip.GetStatusCodeName(status));
			continue;
		}

		RfChip.PICC_HaltA();
		RfChip.PCD_StopCrypto1();

		//writing information on screen

		DebugUART.printf("Towar został zarejestrowany\n");
		rejestracja = 0;

	}
	return;

}

void Rejestracja_cukier() {



	int rejestracja = 1;
	DebugUART.printf("\nRejestracja cukru, przyłóż towar\n");
	while (rejestracja) {

		RfChip.PCD_Init();

		// RfChip.PCD_StopCrypto1();

		for (uint8_t i = 0; i < 6; i++) {
			key.keyByte[i] = 0xFF;
		}
		uint8_t Addr = 4;
		uint8_t auth = 7;      //adress for access

		uint8_t DataBlock[] = { 0x03, 0x02, 0x03, 0x04, //  1,  2,   3,  4,
				0x05, 0x06, 0x07, 0x08, //  5,  6,   7,  8,
				0x08, 0x09, 0xff, 0x0b, //  9, 10, 255, 12,
				0x0c, 0x0d, 0x0e, 0x0f }; //new information to writing

		MFRC522::StatusCode status;
		//checking for card
		if (!RfChip.PICC_IsNewCardPresent()) {
			wait_ms(300);
			continue;
		}

		if (!RfChip.PICC_ReadCardSerial()) {
			wait_ms(300);
			continue;
		}

		//getting access

		status = (MFRC522::StatusCode) RfChip.PCD_Authenticate(
				MFRC522::PICC_CMD_MF_AUTH_KEY_B, auth, &key, &(RfChip.uid));
		if (status != MFRC522::STATUS_OK) {
			DebugUART.printf("\nPCD_Authenticate() failed: ");
			DebugUART.printf("\n%s", RfChip.GetStatusCodeName(status));
			continue;
		}
		status = (MFRC522::StatusCode) RfChip.PCD_Authenticate(
				MFRC522::PICC_CMD_MF_AUTH_KEY_A, auth, &key, &(RfChip.uid));
		if (status != MFRC522::STATUS_OK) {
			DebugUART.printf("\nPCD_Authenticate() failed: ");
			DebugUART.printf("\n%s", RfChip.GetStatusCodeName(status));
			continue;
		}

		//writing
		status = (MFRC522::StatusCode) RfChip.MIFARE_Write(Addr, DataBlock, 16);
		if (status != MFRC522::STATUS_OK) {
			DebugUART.printf("\nMIFARE_Write() failed: ");
			DebugUART.printf("\n%s", RfChip.GetStatusCodeName(status));
			continue;
		}

		RfChip.PICC_HaltA();
		RfChip.PCD_StopCrypto1();

		//writing information on screen

		DebugUART.printf("Towar został zarejestrowany\n");
		rejestracja = 0;

	}
	return;

}

void Rejestracja_towaru() {

	int cos = 1;
	// Init. RC522 Chip
	//	RfChip.PCD_Init();
	char ch[1];
	DebugUART.printf("\nRejestrowanie towaru, jaki towar wybrac?\n");

	DebugUART.printf("\n1-Mleko");
	DebugUART.printf("\n2-Kawa");
	DebugUART.printf("\n3-Cukier");

	while (cos) {
		if (DebugUART.readable()) {

			wait_ms(500);
			for (uint8_t i = 0; i < 2; i++) {
				ch[i] = DebugUART.getc();
			}

			switch (ch[0]) {
			case '1':

				Rejestracja_mleka();
				break;
			case '2':

				Rejestracja_kawa();
				break;
			case '3':

				Rejestracja_cukier();
				break;
			default:
				DebugUART.printf("\nBłąd \n");
				break;
			}
			cos = 0;
		}
		continue;

	}
	return;

}

void Sprawdzanie_towaru() {
	DebugUART.printf("\nSprawdzanie towaru");

	int rejestracja = 1;
	DebugUART.printf("\nPrzyłóż towar");
	while (rejestracja) {

		RfChip.PCD_Init();

		// RfChip.PCD_StopCrypto1();

		for (uint8_t i = 0; i < 6; i++) {
			key.keyByte[i] = 0xFF;
		}
		uint8_t Addr = 4;
		uint8_t auth = 7;      //adress for access
		uint8_t buff[18];       //storing readed information
		uint8_t siz = sizeof(buff);

		MFRC522::StatusCode status;
		//checking for card
		if (!RfChip.PICC_IsNewCardPresent()) {
			wait_ms(300);
			continue;
		}

		if (!RfChip.PICC_ReadCardSerial()) {
			wait_ms(300);
			continue;
		}

		//getting access

		status = (MFRC522::StatusCode) RfChip.PCD_Authenticate(
				MFRC522::PICC_CMD_MF_AUTH_KEY_B, auth, &key, &(RfChip.uid));
		if (status != MFRC522::STATUS_OK) {
			DebugUART.printf("\nPCD_Authenticate() failed: ");
			DebugUART.printf("\n%s", RfChip.GetStatusCodeName(status));
			continue;
		}
		status = (MFRC522::StatusCode) RfChip.PCD_Authenticate(
				MFRC522::PICC_CMD_MF_AUTH_KEY_A, auth, &key, &(RfChip.uid));
		if (status != MFRC522::STATUS_OK) {
			DebugUART.printf("\nPCD_Authenticate() failed: ");
			DebugUART.printf("\n%s", RfChip.GetStatusCodeName(status));
			continue;
		}

		//reading
		status = (MFRC522::StatusCode) RfChip.MIFARE_Read(Addr, buff, &siz);
		if (status != MFRC522::STATUS_OK) {
			DebugUART.printf("\nMIFARE_Read() failed: ");
			DebugUART.printf("\n%s", RfChip.GetStatusCodeName(status));

			continue;

		}

		RfChip.PICC_HaltA();
		RfChip.PCD_StopCrypto1();

		if (buff[0] == 1) {
			DebugUART.printf("\nSprawdzany towar to Mleko\n");
		} else if (buff[0] == 2) {
			DebugUART.printf("\nSprawdzany towar to Kawa\n");
		} else if (buff[0] == 3) {
			DebugUART.printf("\nSprawdzany towar to Cukier\n");
		} else
			DebugUART.printf("\nNieznany towar\n");

		//writing information on screen

		rejestracja = 0;

	}
	return;

}

void Przyjecie_polka_1() {

	while (przycisk == true) {

		fwd2 = 0;
		rev2 = 1;
		DebugUART.printf("\nWinda nie jest na dole, resetuje");

		if (przycisk == false) {
			fwd2 = 0;
			rev2 = 0;
			return;
		}

	}

	while (czujnik4 == true) {

		while (czujnik1 == false) {

			while (czujnik3 == true) {
				fwd1 = 1;
				rev1 = 0;
				fwd3 = 1;
				rev3 = 0;
			}
			fwd1 = 0;
			fwd4 = 1;
			rev4 = 0;
		}

	}
	fwd3 = 0;
	fwd4 = 0;
	if (czujnik4 == false) {
		DebugUART.printf("Towar na polce 1\n");
	}
	return;
}

void Przyjecie_polka_2() {

	while (przycisk == true) {

		fwd2 = 0;
		rev2 = 1;
		DebugUART.printf("\nWinda nie jest na dole, resetuje");

		if (przycisk == false) {
			fwd2 = 0;
			rev2 = 0;
		}

	}

	while (czujnik5 == true) {

		wait_ms(2000);

		while (czujnik1 == false) {

			while (czujnik3 == true) {

				fwd1 = 1;
				rev1 = 0;
				fwd3 = 1;
				rev3 = 0;
			}
			fwd1 = 0;
			fwd3 = 0;
			while (kontaktron1 == true) {
				fwd2 = 1;
				rev2 = 0;
			}
		}

		fwd2 = 0;
		fwd3 = 1;
		fwd5 = 1;
		rev5 = 0;

	}
	fwd3 = 0;
	fwd5 = 0;

	if (czujnik5 == false) {
		DebugUART.printf("Towar na polce 2\n");

	}
	while (przycisk == true) {

		fwd2 = 0;
		rev2 = 1;

	}
	rev2 = 0;
	fwd2 = 0;

	return;
}

void Przyjecie_polka_3() {

	while (przycisk == true) {

		fwd2 = 0;
		rev2 = 1;
		DebugUART.printf("\nWinda nie jest na dole, resetuje");

		if (przycisk == false) {
			fwd2 = 0;
			rev2 = 0;
		}

	}

	while (czujnik6 == true) {

		wait_ms(2000);

		while (czujnik1 == false) {

			while (czujnik3 == true) {

				fwd1 = 1;
				rev1 = 0;
				fwd3 = 1;
				rev3 = 0;
			}
			fwd1 = 0;
			fwd3 = 0;
			while (kontaktron2 == true) {
				fwd2 = 1;
				rev2 = 0;
			}
		}

		fwd2 = 0;
		fwd3 = 1;
		fwd6 = 1;
		rev6 = 0;

	}
	fwd3 = 0;
	fwd6 = 0;

	if (czujnik6 == false) {
		DebugUART.printf("Towar na polce 2\n");

	}
	while (przycisk == true) {

		fwd2 = 0;
		rev2 = 1;

	}
	rev2 = 0;
	fwd2 = 0;

	return;
}

void Przyjecie_towaru() {

	DebugUART.printf("\nPrzyjecie towaru\n");

	int rejestracja = 1;
	DebugUART.printf("\nPrzyloz towar\n");
	while (rejestracja) {

		RfChip.PCD_Init();

		// RfChip.PCD_StopCrypto1();

		for (uint8_t i = 0; i < 6; i++) {
			key.keyByte[i] = 0xFF;
		}
		uint8_t Addr = 4;
		uint8_t auth = 7;      //adress for access
		uint8_t buff[18];       //storing readed information
		uint8_t siz = sizeof(buff);

		MFRC522::StatusCode status;
		//checking for card
		if (!RfChip.PICC_IsNewCardPresent()) {
			wait_ms(300);
			continue;
		}

		if (!RfChip.PICC_ReadCardSerial()) {
			wait_ms(300);
			continue;
		}

		//getting access

		status = (MFRC522::StatusCode) RfChip.PCD_Authenticate(
				MFRC522::PICC_CMD_MF_AUTH_KEY_B, auth, &key, &(RfChip.uid));
		if (status != MFRC522::STATUS_OK) {
			DebugUART.printf("\nPCD_Authenticate() failed: ");
			DebugUART.printf("\n%s", RfChip.GetStatusCodeName(status));
			continue;
		}
		status = (MFRC522::StatusCode) RfChip.PCD_Authenticate(
				MFRC522::PICC_CMD_MF_AUTH_KEY_A, auth, &key, &(RfChip.uid));
		if (status != MFRC522::STATUS_OK) {
			DebugUART.printf("\nPCD_Authenticate() failed: ");
			DebugUART.printf("\n%s", RfChip.GetStatusCodeName(status));
			continue;
		}

		//reading
		status = (MFRC522::StatusCode) RfChip.MIFARE_Read(Addr, buff, &siz);
		if (status != MFRC522::STATUS_OK) {
			DebugUART.printf("\nMIFARE_Read() failed: ");
			DebugUART.printf("\n%s", RfChip.GetStatusCodeName(status));

			continue;

		}

		RfChip.PICC_HaltA();
		RfChip.PCD_StopCrypto1();

		wait_ms(500);

		switch (buff[0]) {
		case 1:
			DebugUART.printf("\nTowar z mlekiem, polka 1\n");
			Przyjecie_polka_1();
			break;
		case 2:
			DebugUART.printf("\nTowar z kawa, polka 2\n");
			Przyjecie_polka_2();
			break;
		case 3:
			DebugUART.printf("\nTowar z cukrem, polka 3\n");
			Przyjecie_polka_3();
		default:
			DebugUART.printf("\nNiezarejestrowany towar\n");
			break;
		}
		rejestracja = 0;

	}
	return;

}

void Odbior_polka1() {

	while (przycisk == true) {

		fwd2 = 0;
		rev2 = 1;
		DebugUART.printf("\nWinda nie jest na dole, resetuje");

		if (przycisk == false) {
			fwd2 = 0;
			rev2 = 0;

		}

	}

	if (czujnik4 == false) {

		while (czujnik1 == true) {

			fwd4 = 0;
			rev4 = 1;
			fwd3 = 0;
			rev3 = 1;
			fwd1 = 0;
			rev1 = 1;

		}

		DebugUART.printf("\nTowar do odebrania");
		rev4 = 0;
		rev3 = 0;
		rev1 = 0;

	} else
		DebugUART.printf("\nBrak towaru na polce");

	return;

}

void Odbior_polka2() {

	while (przycisk == true) {

		fwd2 = 0;
		rev2 = 1;
		DebugUART.printf("\nWinda nie jest na dole, resetuje");

		if (przycisk == false) {
			fwd2 = 0;
			rev2 = 0;

		}

	}

	if (czujnik5 == false) {
		while (kontaktron1 == true) {
			fwd2 = 1;
			rev2 = 0;
		}
		fwd2 = 0;

		while (czujnik2 == true) {

			fwd5 = 0;
			rev5 = 1;
			fwd3 = 0;
			rev3 = 1;
		}

		rev5 = 0;
		rev3 = 0;

		while (przycisk == true) {

			fwd2 = 0;
			rev2 = 1;

		}

		rev2 = 0;
		fwd2 = 0;

		while (czujnik1 == true) {

			rev3 = 1;
			fwd3 = 0;
			rev1 = 1;
			fwd1 = 0;
		}

		rev3 = 0;
		rev1 = 0;

		DebugUART.printf("\nTowar do odebrania");

	} else
		DebugUART.printf("\nBrak towaru\n");
	return;

}

void Odbior_polka3() {

	while (przycisk == true) {

		fwd2 = 0;
		rev2 = 1;
		DebugUART.printf("\nWinda nie jest na dole, resetuje");

		if (przycisk == false) {
			fwd2 = 0;
			rev2 = 0;

		}

	}

	if (czujnik6 == false) {

		while (kontaktron2 == true) {
			fwd2 = 1;
			rev2 = 0;
		}
		fwd2 = 0;
		while (czujnik2 == true) {

			fwd6 = 0;
			rev6 = 1;
			fwd3 = 0;
			rev3 = 1;
		}

		rev6 = 0;
		rev3 = 0;

		while (przycisk == true) {

			fwd2 = 0;
			rev2 = 1;

		}

		rev2 = 0;
		fwd2 = 0;

		while (czujnik1 == true) {

			rev3 = 1;
			fwd3 = 0;
			rev1 = 1;
			fwd1 = 0;
		}

		rev3 = 0;
		rev1 = 0;

		DebugUART.printf("\nTowar do odebrania");

	} else
		DebugUART.printf("Brak towaru\n");
	return;

}

void Odbior_towaru() {

	DebugUART.printf("\nOdbior towaru");

	int rejestracja = 1;

	DebugUART.printf("\nJaki towar chcesz wybrac?");

	DebugUART.printf("\nPolka-1 Mleko");
	DebugUART.printf("\nPolka-2 Kawa");
	DebugUART.printf("\nPolka-3 Cukier");

	char ch[1];
	while (rejestracja) {

		if (DebugUART.readable()) {

			wait_ms(500);
			for (uint8_t i = 0; i < 2; i++) {
				ch[i] = DebugUART.getc();
			}

			switch (ch[0]) {
			case '1':
				DebugUART.printf("\nTowar z mlekiem, polka 1 ");
				Odbior_polka1();
				break;
			case '2':
				DebugUART.printf("\nTowar z kawa, polka 2 ");
				Odbior_polka2();
				break;
			case '3':
				DebugUART.printf("\nTowar z cukrem, polka 3 ");
				Odbior_polka3();
				break;
			default:
				DebugUART.printf("\nPodano zla wartosc ");
				break;
			}
			rejestracja = 0;
		}
	}
	return;
}

void Stan_magazynu() {
	DebugUART.printf("\nStan magazynu \n");
	if (czujnik6 == true) {
		if (czujnik5 == true) {
			if (czujnik4 == true) {
				DebugUART.printf("Magazyn jest pusty. \n");
			} else
				DebugUART.printf("Wolne są półki 3 i 2. \n");
		} else if (czujnik4 == true) {
			DebugUART.printf("Wolne są półki 3 i 1. \n");
		} else
			DebugUART.printf("Wolna jest półka 3. \n");
	} else {
		if (czujnik5 == true) {
			if (czujnik4 == true) {
				DebugUART.printf("Wolne są półki 2 i 1. \n");
			} else
				DebugUART.printf("Wolna jest półka 2. \n");
		} else if (czujnik4 == true) {
			DebugUART.printf("Wolna jest póółka 1. \n");
		} else
			DebugUART.printf("Magazyn pełny.\n");
	}
}

void PWM_init() {
	// PWM
	s1.period(0.10f);      // 4 second period
	s1.write(0.90f);      // 50% duty cycle, relative to period
	s2.period(0.10f);      // 4 second period
	s2.write(0.90f);      // 50% duty cycle, relative to period
	s3.period(0.10f);      // 4 second period
	s3.write(0.90f);      // 50% duty cycle, relative to period
	s4.period(0.10f);      // 4 second period
	s4.write(0.90f);      // 50% duty cycle, relative to period
	s5.period(0.10f);      // 4 second period
	s5.write(0.90f);      // 50% duty cycle, relative to period
	s6.period(0.10f);      // 4 second period
	s6.write(0.90f);
}

void Menu() {


	char ch[1];

	    DebugUART.printf("\nCo robimy?");
		DebugUART.printf("\n1-Rejestracja towaru");
		DebugUART.printf("\n2-Stan magazynu");
		DebugUART.printf("\n3-Pzyjęcie towaru");
		DebugUART.printf("\n4-Odbiór towaru");
		DebugUART.printf("\n5-Sprawdzanie towaru\n");

	while (true) {
			if (DebugUART.readable()) {

				wait_ms(500);
				for (uint8_t i = 0; i < 2; i++) {
					ch[i] = DebugUART.getc();
				}

				switch (ch[0]) {
				case '1':

					Rejestracja_towaru();
					break;
				case '2':

					Stan_magazynu();
					break;
				case '3':

					Przyjecie_towaru();
					break;
				case '4':

					Odbior_towaru();
					break;
				case '5':

					Sprawdzanie_towaru();
					break;
				case '9':

								Menu();
								break;
				default:
					DebugUART.printf("\nZla dana \n");
					break;
				}

			}
			continue;
		}
		return;
}

int main(void) {
	PWM_init();
	DebugUART.baud(9600);
	char ch[1];
	LedGreen = 1;
	LedBlue = 1;

	kontaktron1.mode(PullUp);
	kontaktron2.mode(PullUp);
	przycisk.mode(PullDown);


	while (true) {
		if (DebugUART.readable()) {

			wait_ms(500);
			for (uint8_t i = 0; i < 2; i++) {
				ch[i] = DebugUART.getc();
			}

			switch (ch[0]) {
			case '9':
				Menu();
				break;
			default:
				DebugUART.printf("\nZla dana \n");
				break;
			}

		}

	}
	return 0;
}


