#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         5          
#define SS_PIN          53         

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

byte accessUID_1[4]={0xCB, 0xDA, 0x63, 0x1B};
byte accessUID_2[4]={0xC7, 0x20, 0x2B, 0x3F};

void setup() {
	Serial.begin(9600);		// Initialize serial communications with the PC
	while (!Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
	SPI.begin();			// Init SPI bus
	mfrc522.PCD_Init();		// Init MFRC522
	delay(4);				// Optional delay. Some board do need more time after init to be ready, see Readme
	mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
	Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

void loop() {
	// Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
	if ( ! mfrc522.PICC_IsNewCardPresent()) {
		return;
	}

	// Select one of the cards
	if ( ! mfrc522.PICC_ReadCardSerial()) {
		return;
	}

	// Dump debug info about the card; PICC_HaltA() is automatically called
	if(mfrc522.uid.uidByte[0]==accessUID_1[0] && mfrc522.uid.uidByte[1]==accessUID_1[1] && mfrc522.uid.uidByte[2]==accessUID_1[2] && mfrc522.uid.uidByte[3]==accessUID_1[3]){
    Serial.println("Access Granted!");
  }
  else if(mfrc522.uid.uidByte[0]==accessUID_2[0] && mfrc522.uid.uidByte[1]==accessUID_2[1] && mfrc522.uid.uidByte[2]==accessUID_2[2] && mfrc522.uid.uidByte[3]==accessUID_2[3]){
    Serial.println("Access Granted!");
  }
  else{
    Serial.println("Access Denied!");
  }

  mfrc522.PICC_HaltA();
}
