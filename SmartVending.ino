#include <Servo.h>
#include <Keypad.h>
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>

// LCD pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Servo motors
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

// RFID pins
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

// Keypad setup
const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {A0, A1, A2, A3};
byte colPins[COLS] = {A4, A5, 6};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Function to move servo
void dispense(Servo s){
  s.write(90);
  delay(1000);
  s.write(0);
  delay(500);
}

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  lcd.begin(16,2);
  
  servo1.attach(7);
  servo2.attach(8);
  servo3.attach(9);
  servo4.attach(10);

  lcd.print("Smart Vending");
  lcd.setCursor(0,1);
  lcd.print("Machine Ready");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Check RFID
  if ( mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    lcd.print("Card Accepted");
    delay(1000);
    lcd.clear();
    
    lcd.print("Enter Product #: ");
    char key = keypad.waitForKey();
    lcd.setCursor(0,1);
    lcd.print(key);
    
    switch(key){
      case '1': dispense(servo1); break;
      case '2': dispense(servo2); break;
      case '3': dispense(servo3); break;
      case '4': dispense(servo4); break;
      default: lcd.print("Invalid"); break;
    }
    delay(2000);
    lcd.clear();
  }
}
