//include the keypad library
#include<Keypad.h>

//include the Wire.h library for I2C communication
#include<Wire.h>

//include the LiquidCrystal_I2C.h library
#include<LiquidCrystal_I2C.h>

//include the RFID library
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         5      //to be changed in the arduino uno to pin 9    
#define SS_PIN          53    //to be changed in the arduino uno to pin 10 

//length of password + 1 for null character
#define password_Length 8

// Create MFRC522 instance
MFRC522 mfrc522(SS_PIN, RST_PIN);  

//the two cards to use in demostrating access granted
byte accessUID_1[4]={0xCB, 0xDA, 0x63, 0x1B};
byte accessUID_2[4]={0xC7, 0x20, 0x2B, 0x3F};

//Character to hold password input
char Data[password_Length];
//Password
char Master[password_Length]="123A456";

//pin connected to door servo
int lockOutput = A1;

//counter for character entries
byte data_count=0;

//character to hold key input
char customKey;

//Constants for row and column sizes
const byte ROWS=4;
const byte COLS=4;

//Array to represent Keys on the Keypad
char hexaKeys[ROWS][COLS]={
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

//Arduino pin connections
byte rowPins[ROWS]={A0,8,7,6};
byte colPins[COLS]={9,4,3,2};

//create the keypad object
Keypad doorKeypad=Keypad(makeKeymap(hexaKeys),rowPins,colPins,ROWS,COLS);

//create an LCD 
LiquidCrystal_I2C doorLCD(0x27,16,2);

//Declaring pin for buzzer connection
const int buzzer = A3;


void setup() {
  Serial.begin(9600);		// Initialize serial communications with the PC
	while (!Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
	SPI.begin();			// Init SPI bus
	mfrc522.PCD_Init();		// Init MFRC522
	delay(4);				// Optional delay. Some board do need more time after init to be ready, see Readme
	mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
	Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));

  // Innitialize lcd and put on backlight
  doorLCD.init();
  doorLCD.backlight();

  //set lock output as an OUTPUT pin
  pinMode(lockOutput, OUTPUT);
  pinMode(buzzer, OUTPUT);
  

}

void loop() {

  //Initialize lcd display and print
  doorLCD.setCursor(0,0);
  doorLCD.print("Enter Password: ");

  rfidCard();
  passWord();

}

void passWord(){
    //look for keypad press
  customKey=doorKeypad.getKey();

  if(customKey){

    //Enter key pressed into array and increment counter
    Data[data_count]=customKey;
    doorLCD.setCursor(data_count,1);
    doorLCD.print("*");
    data_count++;
    
    };

    //See if we have reached the password length
    if (data_count==password_Length - 1){
      delay(500);
      doorLCD.clear();

      if (!strcmp(Data, Master)){
        //password is correct
        delay(500);
        doorLCD.print("Access Granted!");

        //Sound the buzzer to show success
        buzzAccept();
        doorOpen();

      }
      else{
        //password is incorrect
        buzzDeny();
        doorLCD.print("Access Denied!");
        delay(1000);
      }

      //clear data and lcd display
      doorLCD.clear();
      clearData();
    }
}

void rfidCard(){
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
    doorLCD.clear();
    delay(500);
    doorLCD.print("Access Granted!");
    buzzAccept();
    doorOpen();
  }
  else if(mfrc522.uid.uidByte[0]==accessUID_2[0] && mfrc522.uid.uidByte[1]==accessUID_2[1] && mfrc522.uid.uidByte[2]==accessUID_2[2] && mfrc522.uid.uidByte[3]==accessUID_2[3]){
    Serial.println("Access Granted!");
    doorLCD.clear();
    delay(500);
    doorLCD.print("Access Granted!");
    buzzAccept();
    doorOpen();
  }
  else{
    Serial.println("Access Denied!");
    doorLCD.clear();
    delay(500);
    doorLCD.print("Access Denied!");
    buzzDeny();
  }

  mfrc522.PICC_HaltA();
}

void clearData() {
  //go through array and clear data
  while (data_count != 0){
    Data[data_count--] = 0;
  }
  return;
}

void buzzAccept(){
  tone(buzzer, 1200); // Send 1KHz sound signal...
  delay(1000);        // ...for 1 sec
  noTone(buzzer);     // Stop sound... 

}

void buzzDeny(){
  tone(buzzer, 550); // Send 1KHz sound signal...
  delay(250);        // ...for 1 sec
  noTone(buzzer); 
  tone(buzzer, 550); // Send 1KHz sound signal...
  delay(250);        // ...for 1 sec
  noTone(buzzer);   // Stop sound... 
  delay(500); 

}

void doorOpen(){
  //turn on servo to open the door
  digitalWrite(lockOutput, HIGH);
  delay(4000);
  digitalWrite(lockOutput, LOW);
}
